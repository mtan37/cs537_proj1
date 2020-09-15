#make file for assignment1 @CS537
CC = gcc
CFLAGS = -c -Wall -pedantic
ODIR = ./obj
SDIR = ./src
OBJECTS = $(ODIR)/537ps.o $(ODIR)/processArgs.o
537ps:$(OBJECTS)
	$(CC) -Wall $(OBJECTS) -o 537ps
$(ODIR)/537ps.o: $(SDIR)/537ps.c
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/processArgs.o: $(SDIR)/processArgs.c
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm $(ODIR)/*.o
	rm 537ps
