CPP = g++
CPPFLAGS = -c -g -std=c++11 -Wall
LFLAGS = -g -std=c++11 -Wall
OBJECTFILES = matrix.o model.o fileio.o ray.o vector.o sphere.o camera.o triangle.o main.o light.o material.o
EXE = raytracer

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)

material.o: material.h material.cpp
	$(CPP) $(CPPFLAGS) material.cpp

triangle.o: triangle.h triangle.cpp
	$(CPP) $(CPPFLAGS) triangle.cpp
	
light.o: light.h light.cpp
	$(CPP) $(CPPFLAGS) light.cpp

camera.o: camera.h camera.cpp
	$(CPP) $(CPPFLAGS) camera.cpp

ray.o: ray.h ray.cpp
	$(CPP) $(CPPFLAGS) ray.cpp
	
sphere.o: sphere.h sphere.cpp
	$(CPP) $(CPPFLAGS) sphere.cpp
	
vector.o: vector.h vector.cpp
	$(CPP) $(CPPFLAGS) vector.cpp
	
fileio.o: fileio.h fileio.cpp
	$(CPP) $(CPPFLAGS) fileio.cpp

matrix.o: matrix.h matrix.cpp
	$(CPP) $(CPPFLAGS) matrix.cpp
	
model.o: model.h model.cpp
	$(CPP) $(CPPFLAGS) model.cpp

main.o: main.cpp 
	$(CPP) $(CPPFLAGS) main.cpp

clean: 
	rm -f *.o *~ raytracer

