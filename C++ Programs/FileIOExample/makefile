CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = Lab3.o
EXE = lab3

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
Lab3.o: Lab3.cpp
	$(CPP) $(CPPFLAGS) Lab3.cpp
	
clean:
	rm -f *.o *~ $(EXE)
