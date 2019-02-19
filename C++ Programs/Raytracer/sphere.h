/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "ray.h"
#include "light.h"
#include "material.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

class Sphere
{
	public:
		Sphere();
		Sphere(const Vector &c, const double r, const Material &m);
		~Sphere();
		Vector colorSphere(Ray &ray, double &t, vector<Light> &lights, const Vector &ambientLight);
		const Vector & getCenter() const;
		const Material & getMaterial() const;
		double getRadius() const;
		bool intersect(const Ray &ray, double &t);
		void setCenter(const Vector &c);
		void setRadius(const double r);
		friend ostream & operator<<(ostream &out, const Sphere &sphere)
		{
			out << sphere.getCenter() << " " << sphere.getRadius() << " " << sphere.getMaterial();
			
			return out;
		}
		
	private:
		Vector center;
		double radius;
		Material material;
};

ostream & operator<<(ostream &out, const Sphere &sphere);

#endif
