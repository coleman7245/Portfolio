/* Author: coleman7245
 * File: C++ Light class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The class designed for storing information on point lights in a scene. It has no complex operations, just rudimentory get 
 * methods.
 */

#include "light.h"

//Method Summary: Default constructor
Light::Light() : point(Vector<double>()), emission(Vector<double>()), w(0.0) {}

//Method Summary: Constructor using input from the provided parameters.
Light::Light(const Vector<double> &p, const Vector<double> &e, const double _w): point(p), emission(e), w(_w) {}

//Method Summary: Copy constructor
Light & Light::operator=(const Light &rhs)
{
	//if the two references are not one in the same, then...
	if (this != &rhs)
	{
		//Copy all attributes into the attributes of this Light instance.
		point = rhs.getPoint();
		emission = rhs.getEmission();
		w = rhs.getW();
	}
	
	//Return this Light object.
	return *this;
}

//Method Summary: Deconstructor
Light::~Light() {}
