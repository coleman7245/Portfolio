/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef RAY_H
#define RAY_H

#include "vector.h"

using namespace std;

class Ray
{
	public:
		Ray();
		Ray(const Vector &p, const Vector &v);
		~Ray();
		const Vector & getPoint() const;
		const Vector & getVector() const;
		void setPoint(const Vector &p);
		void setVector(const Vector &v);
		friend ostream & operator<<(ostream &out, const Ray &ray)
		{
			out << ray.getPoint() << " " << ray.getVector();
			
			return out;
		}
		
	private:
		Vector point;
		Vector vector;
};

ostream & operator<<(ostream &out, const Ray &ray);

#endif
