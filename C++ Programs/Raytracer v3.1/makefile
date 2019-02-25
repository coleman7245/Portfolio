CPP = g++
CPPFLAGS = -c -g -std=c++11 -Wall
LFLAGS = -g -std=c++11 -Wall
OBJECTFILES = matrix.o main.o camera.o sphere.o triangle.o model.o vector.o light.o ray.o material.o scene.o viewplane.o
EXE = raytracernew

default: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $(EXE)
	
matrix.o: matrix.h matrix.cpp
	$(CPP) $(CPPFLAGS) matrix.cpp

main.o: main.cpp 
	$(CPP) $(CPPFLAGS) main.cpp
	
camera.o: camera.h camera.cpp
	$(CPP) $(CPPFLAGS) camera.cpp
	
sphere.o: sphere.h sphere.cpp
	$(CPP) $(CPPFLAGS) sphere.cpp
	
triangle.o: triangle.h triangle.cpp
	$(CPP) $(CPPFLAGS) triangle.cpp
	
model.o: model.h model.cpp
	$(CPP) $(CPPFLAGS) model.cpp
	
vector.o: vector.h vector.cpp
	$(CPP) $(CPPFLAGS) vector.cpp
	
light.o: light.h light.cpp
	$(CPP) $(CPPFLAGS) light.cpp
	
ray.o: ray.h ray.cpp
	$(CPP) $(CPPFLAGS) ray.cpp
	
material.o: material.h material.cpp
	$(CPP) $(CPPFLAGS) material.cpp
	
scene.o: scene.h scene.cpp
	$(CPP) $(CPPFLAGS) scene.cpp
	
viewplane.o: viewplane.h viewplane.cpp
	$(CPP) $(CPPFLAGS) viewplane.cpp

clean: 
	rm -f *.o *~ $(EXE)

