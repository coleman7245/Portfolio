/* Author: coleman7245
 * File: C++ Ray header file for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Ray class.
 */

//If the Ray header hasn't been included, then...
#ifndef RAY_H
//Define the Ray header.
#define RAY_H

//Include the Vector header for the point and direction class attributes.
#include "vector.h"

/* Class declaration */
class Ray
{
	public:
		/* Constructor methods */
		Ray();
		Ray(const Vector<double> &p, const Vector<double> &v);
		~Ray();
		/* Get methods */
		inline const Vector<double> & getDirection() const {return direction;}
		inline const Vector<double> & getPoint() const {return point;}
		/* Set methods */
		inline void setDirection(const Vector<double> &d) {direction = d;}
		inline void setPoint(const Vector<double> &p) {point = p;}
		/* Operator overload methods */
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Ray object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Ray &ray)
		{
			//Load the class attribute information to the ostream object reference.
			out << ray.getPoint() << " " << ray.getDirection();
			
			//Return the ostream object reference.
			return out;
		}
		
	private:
		/* Class attributes
		 *  point: The point of origin of the ray.
		 *  direction: The direction of the ray.
		 */
		Vector<double> point;
		Vector<double> direction;
};

#endif
