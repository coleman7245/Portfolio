/* Author: coleman7245
 * File: C++ Triangle class header file for the raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Triangle class. 
 */

//If the Triangle header is already included, then...
#ifndef TRIANGLE_H
//Define the Triangle header.
#define TRIANGLE_H

//Include the Matrix header for intersection calculations.
#include "matrix.h"
//Include the Ray header for intersection calculations.
#include "ray.h"

/* Class declaration */ 
class Triangle
{
	public:
		/* Constructor methods */
		Triangle();
		Triangle(const Vector<double> &a, const Vector<double> &b, const Vector<double> &c);
		~Triangle();
		/* Get methods */
		inline const Vector<double> & getA() const {return A;}
		inline const Vector<double> & getB() const {return B;}
		inline const Vector<double> & getC() const {return C;}
		inline const Vector<double> & getSurfaceNormal() const {return surfaceNormal;}
		/* Set methods */
		inline void setA(const Vector<double> &a) {A = a;}
		inline void setB(const Vector<double> &b) {B = b;}
		inline void setC(const Vector<double> &c) {C = c;}
		/* Operator overload methods */
		Triangle & operator=(const Triangle &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Triangle object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Triangle &triangle)
		{
			//Load the class attribute information to the ostream object reference.
			out << triangle.getA() << " " << triangle.getB() << " " << triangle.getC() << " " << triangle.getSurfaceNormal();
			
			//Return the ostream object reference.
			return out;
		}
		/* Other methods */
		double intersect(const Ray &ray) const;
		
	private:
		/* Class Attributes
		 *  A: First vertex of the triangle.
		 *  B: Second vertex of the triangle.
		 *  C: Third vertex of the triangle.
		 *  surfaceNormal: Normal vector to the triangle.
		 */
		Vector<double> A;
		Vector<double> B;
		Vector<double> C;
		Vector<double> surfaceNormal;
		/* Other methods */
		void calculateSurfaceNormal();
};

#endif
