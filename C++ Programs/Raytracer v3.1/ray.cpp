/* Author: coleman7245
 * File: C++ Ray class for the Raytracer program. 
 * Last Update: 2/25/19
 * File Summary: The Ray class stores information on the ray shot into a scene to intersect with objects, be it spheres or models.
 */

#include "ray.h"

//Method Summary: Default constructor
Ray::Ray() : point(Vector<double>()), direction(Vector<double>()) {}

//Method Summary: Constructor using input from the provided parameters.
Ray::Ray(const Vector<double> &p, const Vector<double> &d) : point(p), direction(d) 
{
	//If the magnitude of the directional vector is greater than 1, then...
	if (direction.getMagnitude() > 1.0)
	{
		//Normalize the directional vector.
		direction.normalize();
	}
}

//Method Summary: Deconstructor
Ray::~Ray() {}
