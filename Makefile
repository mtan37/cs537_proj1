#make file for assignment1 @CS537
537ps: 537ps.o processArgs.o
	gcc -Wall 537ps.o processArgs.o -o 537ps
537ps.o: 537ps.c
	gcc -c -Wall -pedantic 537ps.c
processArgs.o: processArgs.c
	gcc -c -Wall -pedantic processArgs.c
clean:
	rm *.o
	rm run
