objects = dirsync.o

dirsync : $(objects)
	cc -o dirsync $(objects)

.PHONY : clean
clean : 
	rm dirsync $(objects)
