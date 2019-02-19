/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

class Light
{
	public:
		Light();
		Light(const Vector &p, const Vector &e, const double &_w);
		~Light();
		const Vector & getEmission() const;
		const Vector & getPoint() const;
		const double & getW() const;
		friend ostream & operator <<(ostream &out, const Light &light)
		{
			out << light.getPoint() << " " << light.getEmission() << " " << light.getW();
			
			return out;
		}
		
	private:
		Vector point;
		Vector emission;
		double w;
};

#endif
