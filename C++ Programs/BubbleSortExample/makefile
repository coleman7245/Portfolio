CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = LAB7.o
EXE = lab7

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
LAB7.o: LAB7.cpp
	$(CPP) $(CPPFLAGS) LAB7.cpp
	
clean:
	rm -f *.o *~ $(EXE)
