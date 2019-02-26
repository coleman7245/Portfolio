CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = LAB9.o
EXE = lab9

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
LAB9.o: LAB9.cpp
	$(CPP) $(CPPFLAGS) LAB9.cpp
	
clean:
	rm -f *.o *~ $(EXE)
