CPP = g++
CPPFLAGS = -c -g -Wall -std=c++11
LFLAGS = -g -Wall -std=c++11
OBJECTFILES = HelloJupiter.o
EXE = exercise1

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
HelloJupiter.o: HelloJupiter.cpp
	$(CPP) $(CPPFLAGS) HelloJupiter.cpp
	
clean:
	rm -f *.o *~ $(EXE)
