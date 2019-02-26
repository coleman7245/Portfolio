CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = Lab4.o
EXE = lab4

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
Lab4.o: Lab4.cpp
	$(CPP) $(CPPFLAGS) Lab4.cpp
	
clean:
	rm -f *.o *~ $(EXE)
