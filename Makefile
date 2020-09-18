#make file for assignment1 @CS537
CC = gcc
CFLAGS = -c -Wall -pedantic
ODIR = ./obj
SDIR = ./src
OBJECTS = $(ODIR)/537ps.o $(ODIR)/processArgs.o $(ODIR)/tests.o
537ps:$(OBJECTS)
	$(CC) -Wall $(OBJECTS) -o 537ps
$(ODIR)/537ps.o: $(SDIR)/537ps.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/tests.o: $(SDIR)/tests.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/processArgs.o: $(SDIR)/processArgs.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR):
	mkdir -p $(ODIR)
clean:
	rm $(ODIR)/*.o
	rm 537ps
