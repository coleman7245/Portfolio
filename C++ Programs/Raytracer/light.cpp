/* Author: coleman7245
 * File: C++ Light class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The class designed for storing information on point lights in a scene. It has no complex operations, just rudimentory get 
 * methods.
 */

#include "light.h"

//Method Summary: Default constructor
Light::Light() : point(Vector()), emission(Vector()), w(0.0) {}

//Method Summary: Constructor using input from the provided parameters.
Light::Light(const Vector &p, const Vector &e, const double &_w): point(p), emission(e), w(_w) {}

//Method Summary: Deconstructor
Light::~Light() {}

//Method Summary: Get methods for class variables that simply return their value.
const Vector & Light::getEmission() const {return emission;}

const Vector & Light::getPoint() const {return point;}

const double & Light::getW() const {return w;}
