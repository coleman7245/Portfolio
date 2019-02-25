/* Author: coleman7245
 * File: C++ Vector class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The Vector class stores information regarding the vectors for various mathmatical calculations. Additional methods are 
 * provided that normalize the vector, calculate pairwise products, calculate cross products, calculate dot products, and overload 
 * operators.
 */

//Include the header file.
#include "vector.h"

//Method Summary: Default constructor
template<typename T>
Vector<T>::Vector() : x(0), y(0), z(0) {}

//Method Summary: Constructor initialized with the provided parameters.
template<typename T>
Vector<T>::Vector(const T _x, const T _y, const T _z) : x(_x), y(_y), z(_z) {}

//Method Summary: An overloaded assignment operator that copies values from one vector to another.
//Precondtions: The vector to be copied from.
//Postconditions: Returns this vector with values copied from the parameter vector.
template<typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> &B)
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
template<typename T>
Vector<T>::~Vector() {}

//Method Summary: Normalizes the vector by adjusting its values so that the vector's magnitude is 1.
//Precondtions: The vector to be normalized.
//Postconditions: Returns the normalized vector.
template<typename T>
Vector<T> & Vector<T>::normalize()
{
	T magnitude = getMagnitude();
	//If the magnitude of the pre-normalized vector is greater than 1, then...
	if (magnitude > 0)
	{
		//Normalize the vector's values by dividing them by the vector's magnitude.
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
	
	//Return this vector after normalization.
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator+=(const Vector<T> &A)
{
	x += A.getX();
	y += A.getY();
	z += A.getZ();
	
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator-=(const Vector<T> &A)
{
	x -= A.getX();
	y -= A.getY();
	z -= A.getZ();
	
	return *this;
}

//Method Summary: An overloaded boolean operator that checks if two vectors are equal.
//Precondtions: A right vector and a left vector.
//Postconditions: Returns a true or false value depending on if the every element in the right vector matches every element in the left 
//vector.
template<typename T>
bool Vector<T>::operator==(const Vector<T> &A)
{
	//If the x values are NOT the same, then...
	if (x != A.getX())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the y values are NOT the same, then...
	if (y != A.getY())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the z values are NOT the same, then...
	if (z != A.getZ())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//Return true, indicating the 2 vectors are the same.
	return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> &A)
{
	//If the x values are NOT the same, then...
	if (x == A.getX())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the y values are NOT the same, then...
	if (y == A.getY())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//If the z values are NOT the same, then...
	if (z == A.getZ())
	{
		//Return false, indicating the 2 vectors are NOT the same.
		return false;
	}
	
	//Return true, indicating the 2 vectors are the same.
	return true;
}

//Explicit template definition.
template class Vector<double>;
