/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class Vector
{
	public:
		Vector();
		Vector(double _x, double _y, double _z);
		const Vector & operator=(const Vector &B);
		~Vector();
		static Vector crossProduct(Vector &A, Vector &B);
		static double dotProduct(Vector &A, Vector &B);
		double getMagnitude();
		double getX() const;
		double getY() const;
		double getZ() const;
		Vector normalize();
		static Vector pairwiseProduct(const Vector &A, const Vector &B);
		void setX(double _x);
		void setY(double _y);
		void setZ(double _z);
		friend ofstream & operator<<(ofstream &out, const Vector &A)
		{
			out << A.getX() << " " << A.getY() << " " << A.getZ();
	
			return out;
		}
		
	private:
		double x;
		double y;
		double z;
};

Vector operator+(Vector &A, Vector &B);
Vector operator-(Vector &A, Vector &B);
Vector operator*(double s, Vector&A);
ostream & operator<<(ostream &out, const Vector &A);
bool operator==(const Vector &A, const Vector &B);
bool operator!=(const Vector &A, const Vector &B);

#endif
