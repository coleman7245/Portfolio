/* Author: coleman7245
 * File: C++ ViewPlane class header for the raytracer.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the ViewPlane class. 
 */

//If the viewplane header is not defined yet, then...
#ifndef VIEWPLANE_H
//Define the viewplane header.
#define VIEWPLANE_H

//Include ostream for displaying class attributes on the command console.
#include <ostream>

/* Class declaration */
class ViewPlane
{
	public:
		/* Constructor methods */
		ViewPlane();
		ViewPlane(const double distanceP, const double nearP, const double farP, const double topP, const double bottomP, 
			const double leftP, const double rightP);
		~ViewPlane();
		/* Get methods */
		inline double getDistance() const {return distance;}
		inline double getNear() const {return near;}
		inline double getFar() const {return far;}
		inline double getTop() const {return top;}
		inline double getBottom() const {return bottom;}
		inline double getLeft() const {return left;}
		inline double getRight() const {return right;}
		/* Operator overload methods */
		ViewPlane & operator=(const ViewPlane &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant ViewPlane object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const ViewPlane &viewPlane)
		{
			//Load the class attribute information to the ostream object reference.
			out << viewPlane.getDistance() << " " << viewPlane.getNear() << " " << viewPlane.getFar() << " " << viewPlane.getTop() << " " 
				<< viewPlane.getBottom() << " " << viewPlane.getLeft() << " " << viewPlane.getRight();
			
			//Return the ostream object reference.
			return out;
		}
		
	private:
		/* Class Attributes
		 *  distance: The maximum distance of the view plane.
		 *  near: The closest forward bounds of the view plane.
		 *  far: The farthest forward bounds of the view plane.
		 *  top: The vertical upper bounds of the view plane.
		 *  bottom: The vertical lower bounds of the view plane.
		 *  left: The horizontal upper bounds of the view plane.
		 *  right: The horizontal lower bounds of the view plane.
		 */
		double distance;
		double near;
		double far;
		double top;
		double bottom;
		double left;
		double right;
};

#endif
