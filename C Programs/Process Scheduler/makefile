C = gcc
CFLAGS = -c -std=gnu99 -cpp -Wall
OBJECTFILES1 = scheduler.o process.o scheduleroverhead.o
EXE = processscheduler

all: $(EXE)

processscheduler: $(OBJECTFILES1)
	$(C) $(OBJECTFILES1) -o $(EXE)
	
process.o: process.c process.h
	$(C) $(CFLAGS) process.c
	
scheduleroverhead.o: scheduleroverhead.c scheduleroverhead.h
	$(C) $(CFLAGS) scheduleroverhead.c
  
process.o: process.c process.h
	$(C) $(CFLAGS) process.c

scheduleroverhead.o: scheduleroverhead.c scheduleroverhead.h
	$(C) $(CFLAGS) scheduleroverhead.c

scheduler.o: scheduler.c scheduler.h
	$(C) $(CFLAGS) scheduler.c

clean:
	rm -f *.o *~ processscheduler
