#make file for assignment1 @CS537
CC = gcc
CFLAGS = -c -Wall -pedantic -g
ODIR = ./obj
SDIR = ./src
OBJECTS = $(ODIR)/537ps.o $(ODIR)/processArgs.o $(ODIR)/fileParser.o $(ODIR)/userProcUtil.o $(ODIR)/memReader.o $(ODIR)/outputGenerator.o $(ODIR)/tests.o
537ps:$(OBJECTS)
	$(CC) -Wall $(OBJECTS) -o 537ps
$(ODIR)/537ps.o: $(SDIR)/537ps.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/tests.o: $(SDIR)/tests.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/outputGenerator.o: $(SDIR)/outputGenerator.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/memReader.o: $(SDIR)/memReader.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/userProcUtil.o: $(SDIR)/userProcUtil.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/fileParser.o: $(SDIR)/fileParser.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/processArgs.o: $(SDIR)/processArgs.c | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR):
	mkdir -p $(ODIR)
clean:
	rm $(ODIR)/*.o
	rm 537ps
