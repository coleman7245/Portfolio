C = gcc
CFLAGS = -c -std=gnu99 -cpp -Wall
OBJECTFILES1 = scheduler.o
EXE = processscheduler

all: $(EXE)

processscheduler: $(OBJECTFILES1)
	$(C) $(OBJECTFILES1) -o $(EXE)

scheduler.o: scheduler.c
	$(C) $(CFLAGS) scheduler.c

clean: 
	rm -f *.o *~ processscheduler
