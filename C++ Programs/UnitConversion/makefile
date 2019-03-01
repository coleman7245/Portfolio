CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = staticcast.o
EXE = staticcast

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
staticcast.o: staticcast.cpp
	$(CPP) $(CPPFLAGS) staticcast.cpp
	
clean:
	rm -f *.o *~ $(EXE)
