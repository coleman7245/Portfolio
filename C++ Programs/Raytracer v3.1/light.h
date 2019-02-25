/* Author: coleman7245
 * File: C++ Light header file for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Light class.
 */

//If the Light header file hasn't been included, then...
#ifndef LIGHT_H
//Define the header file.
#define LIGHT_H

//Include the Vector header for point and emission vectors.
#include "vector.h"

/* Class declaration */
class Light
{
	public:
		/* Constructor methods */
		Light();
		Light(const Vector<double> &p, const Vector<double> &e, const double _w);
		~Light();
		/* Get methods */
		inline const Vector<double> & getEmission() const {return emission;}
		inline const Vector<double> & getPoint() const {return point;}
		inline double getW() const {return w;}
		/* Operator overload methods */
		Light & operator=(const Light &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Light object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator <<(std::ostream &out, const Light &light)
		{
			//Load the class attribute information to the ostream object reference.
			out << light.getPoint() << " " << light.getEmission() << " " << light.getW();
			
			//Return the ostream object reference.
			return out;
		}
		
	private:
		/* Class attributes
		 *  point: The origin point of the light.
		 *  emission: Emission of the light for color calculation.
		 *  w: Value for a later update.
		 */
		Vector<double> point;
		Vector<double> emission;
		double w;
};

#endif
