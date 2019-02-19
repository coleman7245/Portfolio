/* Author: coleman7245
 * File: C++ Ray class for the Raytracer program. 
 * Last Update: 2/18/2019
 * File Summary: The Ray class stores information on the ray shot into a scene to intersect with objects, be it spheres or models.
 */

#include "ray.h"

//Method Summary: Default constructor
Ray::Ray() : point(Vector()), vector(Vector()) {}

//Method Summary: Constructor using input from the provided parameters.
Ray::Ray(const Vector &p, const Vector &v) : point(p), vector(v) 
{
	//If the magnitude of the directional vector is greater than 1, then...
	if (vector.getMagnitude() > 1.0)
	{
		//Normalize the directional vector.
		vector = vector.normalize();
	}
}

//Method Summary: Deconstructor
Ray::~Ray() {}

//Method Summary: Get methods for class variables that simply return their value.
const Vector & Ray::getPoint() const {return point;}

const Vector & Ray::getVector() const {return vector;}

//Method Summary: Set methods that simply set the values for class variables.
void Ray::setPoint(const Vector &p) {point = p;}

void Ray::setVector(const Vector &v) {vector = v;}
