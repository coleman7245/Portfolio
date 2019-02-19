/* Author: coleman7245
 * File: C++ FileIO Header for Raytracer
 * Last Update: 2/18/2019
 * File Summary: Method prototypes for the FileIO.
 */

#ifndef FILEIO_H
#define FILEIO_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include "camera.h"
#include "sphere.h"
#include "vector.h"
#include "light.h"

using namespace std;

unsigned int numOfModels(ifstream &fileReader);
unsigned int numOfSpheres(ifstream &fileReader);
bool readDriverData(const char *driverFilename, vector< vector<double> > &axis, vector<double> &degrees, vector<double> &scales, 
	vector< vector<double> > &translations, vector<string> &modelFilenames, vector<Sphere> &spheres, Camera &camera, unsigned int &recursionLevel);
bool writePPMFile(const char *filename, const vector<vector <Vector> > &colors);

#endif
