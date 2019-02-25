/* Author: coleman7245
 * File: C++ Sphere header file for the Raytracer program.
 * Last Update: 2/24/2019
 * File Summary: Provides the function and class declarations for the Sphere class.
 */

//If the header file is not included, then...
#ifndef SPHERE_H
//Define the header file.
#define SPHERE_H

//Include the Ray header for intersection calculations.
#include "ray.h"
//Include the material header for color calculations.
#include "material.h"

/* Class declaration */
class Sphere
{
	public:
		/* Constructor methods */
		Sphere();
		Sphere(const Vector<double> &c, const double r, const Material &m);
		~Sphere();
		/* Get methods */
		inline const Vector<double> & getCenter() const {return center;}
		inline const Material & getMaterial() const {return material;}
		inline double getRadius() const {return radius;}
		/* Set methods */
		inline void setCenter(const Vector<double> &c) {center = c;}
		inline void setRadius(const double r) {radius = r;}
		/* Operator overload methods */
		Sphere & operator=(const Sphere &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Sphere object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Sphere &sphere)
		{
			//Load the class attribute information to the ostream object reference.
			out << sphere.getCenter() << " " << sphere.getRadius() << " " << sphere.getMaterial();
			
			//Return the ostream object reference.
			return out;
		}
		/* Other methods */
		double intersect(const Ray &ray) const;
		
	private:
		/* Class Attributes
		 *  center: The position of the sphere's center.
		 *  radius: The distance between the sphere's center and it's outermost point.
		 *  material: The rendering properties of the sphere. 
		 */
		Vector<double> center;
		double radius;
		Material material;
};

#endif
