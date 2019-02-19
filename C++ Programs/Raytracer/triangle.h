/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "light.h"
#include "material.h"
#include <cmath>

using namespace std;

class Triangle
{
	public: 
		Triangle();
		Triangle(const Vector &a, const Vector &b, const Vector &c);
		~Triangle();
		void calculateSurfaceNormal();
		Vector colorTriangle(const Material &material, const Ray &ray, double &t, 
							 const vector<Light> &lights, const Vector &ambientLight);
		const Vector & getA() const;
		const Vector & getB() const;
		const Vector & getC() const;
		const Vector & getSurfaceNormal() const;
		bool intersect(const Ray &ray, double &t);
		void setA(const Vector &a);
		void setB(const Vector &b);
		void setC(const Vector &c);
		friend ostream & operator<<(ostream &out, const Triangle &triangle)
		{
			out << triangle.getA() << " " << triangle.getB() << " " << triangle.getC() << " " << triangle.getSurfaceNormal();
			
			return out;
		}
		
	private:
		Vector A;
		Vector B;
		Vector C;
		Vector surfaceNormal;
};

#endif
