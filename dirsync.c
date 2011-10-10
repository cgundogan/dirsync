#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE	1024

char copy_buffer[BUFSIZE];

int copy(char *source, char *target)
{
    int fhs,fht,count;

    if((fhs = open(source, O_RDONLY)) == -1) {
	printf("could not open source file %s : %s\n", source, strerror(errno));
	return EXIT_FAILURE;
    }

/*    if((fht = open(target, O_WRONLY)) != -1) {
	close(fhs);
	return -2;
    }

    close(fht);
*/
    if((fht = open(target, O_WRONLY | O_TRUNC | O_CREAT)) == -1) {
	printf("could not open target file %s : %s\n", target, strerror(errno));
	close(fhs);
	return EXIT_FAILURE;
    } else {
	while(count = read(fhs,copy_buffer, BUFSIZE))
	    write(fht,copy_buffer,count);
	close(fhs);
	close(fht);
	return EXIT_SUCCESS;
    }
}

int main(int argc, char **argv)
{
    DIR *source_dir = NULL;
    struct dirent *ent = NULL;

    if(argc != 3) {
	printf("Usage: dirsync <source> <destination>\n");
	    exit(EXIT_FAILURE);
    }
/* use lstat instead of stat because of symbolic links */
/*    while(argc--)
	printf("%s\n", *argv++);
    exit(EXIT_SUCCESS);
*/
    struct stat f_stat;
    if(stat(argv[2], &f_stat) < 0) {
	if(mkdir(argv[2], 0777) != 0) {
	    perror("could not create directory");
	    exit(EXIT_FAILURE);
	}
    }

    source_dir = opendir(argv[1]);
    if (source_dir) {
	while((ent = readdir(source_dir)) != NULL) {
	    printf("%s\n", ent->d_name);
	}
	closedir(source_dir);
    } else {
	printf("could not open source dir %s : %s\n", argv[1], strerror(errno));
	exit(EXIT_FAILURE);
    }
/*    printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t%lu bytes\n",fileStat.st_size);
    printf("Number of Links: \t%lu\n",fileStat.st_nlink);
    printf("File inode: \t\t%lu\n",fileStat.st_ino);
//TODO: case over st_mode, recursive copying, after that, introduce heuristic to do hard links instead of copying
    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
*/
    exit(EXIT_SUCCESS);
}
