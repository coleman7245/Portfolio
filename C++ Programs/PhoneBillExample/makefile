CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = Exercise15.o
EXE = exercise15

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
Exercise15.o: Exercise15.cpp
	$(CPP) $(CPPFLAGS) Exercise15.cpp
	
clean:
	rm -f *.o *~ $(EXE)
