/* Author: coleman7245
 * File: C++ Vector class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The Vector class stores information regarding the vectors for various mathmatical calculations. Additional methods are 
 * provided that normalize the vector, calculate pairwise products, calculate cross products, calculate dot products, and overload 
 * operators.
 */

#include "vector.h"

//Method Summary: Default constructor
Vector::Vector() : x(0.0), y(0.0), z(0.0) {}

//Method Summary: Constructor using input from the provided parameters.
Vector::Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

//Method Summary: An overloaded assignment operator that copies values from one vector to another.
//Precondtions: The vector to be copied from.
//Postconditions: Returns this vector with values copied from the parameter vector.
const Vector & Vector::operator=(const Vector &B)
{
	//If the reference of this vector is NOT the same as that of the parameter vector, then...
	if (this != &B)
	{
		//Copy the x, y, and z values of the parameter vector.
		x = B.getX();
		y = B.getY();
		z = B.getZ();
	}
	
	//Return this vector.
	return *this;
}

//Method Summary: Deconstructor
Vector::~Vector() {}

//Method Summary: Creates a new vector that is perpindiclular to the given vectors.
//Precondtions: 2 vectors.
//Postconditions: Returns the cross product of the 2 vectors.
Vector Vector::crossProduct(Vector &A, Vector &B)
{
	//crossX: The cross product's x calculations.
	//crossY: The cross product's y calculations.
	//crossZ: The cross product's z calculations 
	double crossX = (A.getY() * B.getZ()) - (A.getZ() * B.getY());
	double crossY = (A.getZ() * B.getX()) - (A.getX() * B.getZ());
	double crossZ = (A.getX() * B.getY()) - (A.getY() * B.getX());
	
	//Create and return a vector with the calculate values.
	return Vector(crossX, crossY, crossZ);
}

//Method Summary: Performs the multiplication and sum of the values of 2 vectors.
//Precondtions: 2 vectors.
//Postconditions: Returns the dot product of the 2 vectors.
double Vector::dotProduct(Vector &A, Vector &B) {return (A.getX() * B.getX()) + (A.getY() * B.getY()) + (A.getZ() * B.getZ());}

//Method Summary: Get methods for class variables that simply return their value.
double Vector::getMagnitude() {return sqrt((x * x) + (y * y) + (z * z));}

double Vector::getX() const {return x;}

double Vector::getY() const {return y;}

double Vector::getZ() const {return z;}

//Method Summary: Normalizes the vector by adjusting its values so that the vector's magnitude is 1.
//Precondtions: The vector to be normalized.
//Postconditions: Returns the normalized vector.
Vector Vector::normalize()
{	
	//If the magnitude of the pre-normalized vector is greater than 1, then...
	if (getMagnitude() > 0)
	{
		//Normalize the vector's values by dividing them by the vector's magnitude.
		double normalizedX = getX() / getMagnitude();
		double normalizedY = getY() / getMagnitude();
		double normalizedZ = getZ() / getMagnitude();
		
		//Return a vector with the normalized values.
		return Vector(normalizedX, normalizedY, normalizedZ);
	}
	else
	{
		//Return a zero vector.
		return Vector();
	}
}

//Method Summary: Multiplies the values of 2 vectors in pairs.
//Precondtions: 2 vectors.
//Postconditions: Returns a vector with the pairwise product.
Vector Vector::pairwiseProduct(const Vector &A, const Vector &B) {return Vector((A.getX() * B.getX()), (A.getY() * B.getY()), (A.getZ() * B.getZ()));}

//Method Summary: Set methods that simply set the values for class variables.
void Vector::setX(double _x) {x = _x;}

void Vector::setY(double _y) {y = _y;}

void Vector::setZ(double _z) {z = _z;}

//Method Summary: An overloaded operator that creates the sum of 2 vectors.
//Precondtions: 2 vectors.
//Postconditions: Returns a new vector formed from the sums of the 2 vectors' values.
Vector operator+(Vector &A, Vector &B)
{
	//Add the x, y, and z values of vectors A and B.
	double aPlusbx = A.getX() + B.getX();
	double aPlusby = A.getY() + B.getY();
	double aPlusbz = A.getZ() + B.getZ();
	
	//Return the sum of the 2 vectors.
	return Vector(aPlusbx, aPlusby, aPlusbz);
}

//Method Summary: An overloaded operator that creates the sum of 2 vectors, one of which is inverted.
//Precondtions: 2 vectors.
//Postconditions: Returns the sum 2 vectors, one of which is inverted.
Vector operator-(Vector &A, Vector &B)
{
	//Subtract the x, y, and z values of vector B from vector A.
	double aMinusbx = A.getX() - B.getX();
	double aMinusby = A.getY() - B.getY();
	double aMinusbz = A.getZ() - B.getZ();
	
	//Return the sum of vector A and the inverted vector B.
	return Vector(aMinusbx, aMinusby, aMinusbz);
}

//Method Summary: An overloaded operator that scales vector A by scalar s. 
//Precondtions: A scalar and a vector.
//Postconditions: Returns a vector that is vector A scaled by s.
Vector operator*(double s, Vector&A)
{
	//Scale the x, y, and z values of vector A by s.
	double sx = s * A.getX();
	double sy = s * A.getY();
	double sz = s * A.getZ();
	
	//Return a vector with the scaled values.
	return Vector(sx, sy, sz);
}

//Method Summary: Overloaded ostream operator for debugging purposes.
//Precondtions: An ostream object and a vector.
//Postconditions: Every attribute of the vector is displayed.
ostream & operator<<(ostream &out, const Vector &A)
{
	out << A.getX() << " " << A.getY() << " " << A.getZ();
	
	return out;
}

//Method Summary: An overloaded boolean operator that checks if two vectors are equal.
//Precondtions: A right vector and a left vector.
//Postconditions: Returns a true or false value depending on if the every element in the right vector matches every element in the left 
//vector.
bool operator==(const Vector &A, const Vector&B)
{
	//If the x values are NOT the same, then...
	if (A.getX() != B.getX())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the y values are NOT the same, then...
	if (A.getY() != B.getY())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the z values are NOT the same, then...
	if (A.getZ() != B.getZ())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//Return true, indicating the 2 vectors are the same.
	return true;
}

bool operator!=(const Vector &A, const Vector&B)
{
	//If the x values are NOT the same, then...
	if (A.getX() == B.getX())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the y values are NOT the same, then...
	if (A.getY() == B.getY())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the z values are NOT the same, then...
	if (A.getZ() == B.getZ())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//Return true, indicating the 2 vectors are the same.
	return true;
}
