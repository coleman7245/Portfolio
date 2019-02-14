C = gcc
CFLAGS = -c -std=c99 -g -Wall
OBJECTFILES = encryption.o main.o fileio.o
EXE = encrypt

all: $(EXE)

encrypt: $(OBJECTFILES)
	$(C) $(OBJECTFILES) -o $(EXE)

main.o: main.c
	$(C) $(CFLAGS) main.c

encryption.o: encryption.c encryption.h
	$(C) $(CFLAGS) encryption.c
	
fileio.o: fileio.c fileio.h
	$(C) $(CFLAGS) fileio.c

clean: 
	rm -f *.o *~ $(EXE)
