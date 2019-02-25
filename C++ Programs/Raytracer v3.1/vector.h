/* Author: coleman7245
 * File: C++ Vector class header for the raytracer.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Vector class. 
 */

//If the Vector header is already included, then...
#ifndef VECTOR_H
//Defire the Vector header.
#define VECTOR_H

//Include iostream for displaying class attributes on the command console.
#include <iostream>
//Include fstream for displaying class attributes in a file.
#include <fstream>
//Include cmath for the square root function.
#include <cmath>

/* Template declaration */
template<typename T>
/* Class declaration */
class Vector
{
	public:
		/* Constructor methods */
		Vector();
		Vector(const T _x, const T _y, const T _z);
		~Vector();
		/* Get methods */
		inline T getMagnitude() const {return sqrt((x * x) + (y * y) + (z * z));}
		inline T getX() const {return x;}
		inline T getY() const {return y;}
		inline T getZ() const {return z;}
		/* Set methods */
		inline void setX(const T &_x) {x = _x;}
		inline void setY(const T &_y) {y = _y;}
		inline void setZ(const T &_z) {z = _z;}
		/* Operator overload methods */
		Vector<T> & operator=(const Vector<T> &B);
		inline Vector<T> operator+(const Vector<T> &A) const {return Vector<T>(x + A.getX(), y + A.getY(), z + A.getZ());}
		Vector<T> & operator+=(const Vector<T> &A);
		inline Vector<T> operator-(const Vector<T> &A) const {return Vector<T>(x - A.getX(), y - A.getY(), z - A.getZ());}
		Vector<T> & operator-=(const Vector<T> &A);
		inline Vector<T> operator*(const T &scalar) const {return Vector<T>(scalar * x, scalar * y, scalar * z);}
		friend inline Vector<T> operator*(const T &scalar, const Vector<T> A)
			{return Vector<T>(scalar * A.getX(), scalar * A.getY(), scalar * A.getZ());}
		inline Vector<T> operator*(const Vector<T> &A) const {return Vector<T>(x * A.getX(), y * A.getY(), z * A.getZ());}
		bool operator==(const Vector<T> &A);
		bool operator!=(const Vector<T> &A);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Vector object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Vector<T> &A)
		{
			//Load the class attribute information to the ostream object reference.
			out << A.getX() << " " << A.getY() << " " << A.getZ();
			
			//Return the ostream object reference.
			return out;
		}
		/* Other methods */
		inline Vector<T> crossProduct(const Vector<T> &A) const
			{return Vector<T>((y * A.getZ()) - (z * A.getY()), (z * A.getX()) - (x * A.getZ()), (x * A.getY()) - (y * A.getX()));}
		inline T dotProduct(const Vector<T> &A) const {return (x * A.getX()) + (y * A.getY()) + (z * A.getZ());}
		Vector<T> & normalize();
		
	private:
		/*
		 * Class Attributes
		 *  x: First vector value.
		 *  y: Second vecto value.
		 *  z: Third vector value.
		 */
		T x;
		T y;
		T z;
};

#endif
