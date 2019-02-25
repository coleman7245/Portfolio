/* Author: Derek Coleman
 * File: C++ Sphere Class for the Raytracer program.
 * Last Update: 2/23/2019
 * File Summary: The Sphere class stores information on the sphere rendered in the scene. Contains an intersect method to determine if a 
 * ray intersected with it and an obsolete coloring method used in previous assignments, but not with the current implementation.
 */

//Include the header file.
#include "sphere.h"

//Method Summary: Default constructor
Sphere::Sphere() : center(Vector<double>()), radius(0.0), material(Material()) {}

//Method Summary: Constructor using input from the provided parameters.
Sphere::Sphere(const Vector<double> &c, const double r, const Material &m) : center(c), radius(r), material(m) {}

//Method Summary: Deconstructor
Sphere::~Sphere() {}

Sphere & Sphere::operator=(const Sphere &rhs)
{
	if (this != &rhs)
	{
		center = rhs.getCenter();
		radius = rhs.getRadius();
		material = rhs.getMaterial();
	}
	
	return *this;
}

//Method Summary: Detects if a ray has intersected with the sphere. 
//Precondtions: A constant Ray object reference.
//Postconditions: Returns the intersection value as a double.
double Sphere::intersect(const Ray &ray) const
{
	//T: Vector pointing toward the center of the sphere from the ray's origin point.
	//v: Cosine of the angle between U and T.
	//Tsq: Cosine of the angle between T and itself.
	//disc: The discriminant of the formula.
	//t: The intersection value.
	Vector<double> T = center - ray.getPoint();
	double v = ray.getDirection().dotProduct(T);
	double Tsq = T.dotProduct(T);
	double disc = (radius * radius) - Tsq + (v * v);
	
	//If either the discriminant or the t value is negative, then...
	if (disc < 0)
	{
		//Return zero as the intersection value.
		return 0.0;
	}
	else //Otherwise...
	{
		//Calculate the intersection value.
		double t = v - sqrt(disc);
		
		//If the intersection value is less than zero, then...
		if (t < 0.0)
		{
			//Set the intersection value to 0.
			t = 0.0;
		}
		
		//Return the intersection value.
		return t;
	}
}
