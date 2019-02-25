/* Author: coleman7245
 * File: C++ ViewPlane class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The ViewPlane class stores information regarding the view plane of the camera for rendering a scene. It primarly acts as a 
 * convenient wat to store information without overwhelming the Camera class.
 */

//Include the header file.
#include "viewplane.h"

//Method Summary: Default constructor
ViewPlane::ViewPlane() : distance(0.0), near(0.0), far(0.0), top(0.0), bottom(0.0), left(0.0), right(0.0) {}

//Method Summary: Constructor initialized with the provided parameters.
ViewPlane::ViewPlane(const double distanceP, const double nearP, const double farP, const double topP, const double bottomP, 
	const double leftP, const double rightP) : distance(distanceP), near(nearP), far(farP), top(topP), bottom(bottomP), left(leftP), 
	right(rightP) {}

//Method Summary: Deconstructor
ViewPlane::~ViewPlane() {}

//Method Summary: Copy constructor
ViewPlane & ViewPlane::operator=(const ViewPlane &rhs)
{
	//If the object references are not one in the same, then...
	if (this != &rhs)
	{
		//Copy the parameter object's class attributes to this object.
		distance = rhs.getDistance();
		near = rhs.getNear();
		far = rhs.getFar();
		top = rhs.getTop();
		bottom = rhs.getBottom();
		left = rhs.getLeft();
		right = rhs.getRight();
	}
	
	//Return this object.
	return *this;
}
