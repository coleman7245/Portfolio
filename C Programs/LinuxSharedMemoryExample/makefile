C = gcc
CFLAGS = -c -Wall -g -std=c99
OBJECTFILES1 = Initiator.o
OBJECTFILES2 = Mean.o FileReader.o
OBJECTFILES3 = Median.o FileReader.o
OBJECTFILES4 = Mode.o FileReader.o
EXE1 = Initiator
EXE2 = Mean
EXE3 = Median
EXE4 = Mode

all: $(EXE1) $(EXE2) $(EXE3) $(EXE4)

Initiator: $(OBJECTFILES1)
	$(C) $(OBJECTFILES1) -o $(EXE1)
	
Mean: $(OBJECTFILES2)
	$(C) $(OBJECTFILES2) -o $(EXE2)
	
Median: $(OBJECTFILES3)
	$(C) $(OBJECTFILES3) -o $(EXE3)
	
Mode: $(OBJECTFILES4)
	$(C) $(OBJECTFILES4) -o $(EXE4)
	
Initiator.o: Initiator.c
	$(C) $(CFLAGS) Initiator.c

FileReader.o: FileReader.c FileReader.h
	$(C) $(CFLAGS) FileReader.c

Mean.o: Mean.c
	$(C) $(CFLAGS) Mean.c
	
Median.o: Median.c
	$(C) $(CFLAGS) Median.c
	
Mode.o: Mode.c
	$(C) $(CFLAGS) Mode.c

clean:
	rm -f *.o *~ Mean Mode Median Initiator
