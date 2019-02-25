/* Author: coleman7245
 * File: C++ Triangle class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The Triangle class stores all information about the triangles present within the scene, which is almost always represents the faces 
 * of the model. Additional methods are provided to calculate the surface normal of a triangle, color a triangle depending on the 
 * intersection, and detecting an intersection between a ray and a triangle, 
 */

//Include the header file.
#include "triangle.h"

//Method Summary: Default constructor
Triangle::Triangle() : A(Vector<double>()), B(Vector<double>()), C(Vector<double>()), surfaceNormal(Vector<double>()) {}

//Method Summary: Constructor initialized with the provided parameters.
Triangle::Triangle(const Vector<double> &a, const Vector<double> &b, const Vector<double> &c) : A(a), B(b), C(c) {calculateSurfaceNormal();}

//Method Summary: Deconstructor
Triangle::~Triangle() {}

//Method Summary: Copy Constructor
Triangle & Triangle::operator=(const Triangle &rhs)
{
	//If both pointers do NOT reference the same object, then...
	if (this != &rhs)
	{
		//Replace the Vector objects in this object with those of the parameter Triangle.
		(*this).A = rhs.getA();
		(*this).B = rhs.getB();
		(*this).C = rhs.getC();
	}
	
	//Calculate the surface normal.
	calculateSurfaceNormal();
	
	//Return this Triangle.
	return *this;
}

//Method Summary: Calculates the surface normal of the triangle.
//Precondtions: The vertices of the Triangle must have been previously initialized.
//Postconditions: The surface normal is calulated and stored in the appropriate class attribute.
void Triangle::calculateSurfaceNormal()
{
	//U: Vector representing one side of the triangle.
	//V: Vector representing another side of the triangle.
	Vector<double> U = B - A;
	Vector<double> V = C - A;
	
	//The surface normal is the cross product of U and V.
	surfaceNormal = U.crossProduct(V).normalize();
}

//Method Summary: Detects if a ray intersected with the triangle.
//Precondtions: A constant Ray object reference.
//Postconditions: Returns the intersection value as a double.
double Triangle::intersect(const Ray &ray) const
{
	//Create a 3 x 3 matrix for intersection values.
	Matrix M = Matrix(3, 3);
	
	//For every element in the matrix...
	for (unsigned int i = 0; i < M.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < M.getColumnSize(); j++)
		{
			//In the beginning column...
			if (i == 0)
			{
				//In the first row...
				if (j == 0)
				{
					//Place the difference of the x values between vectors A and B.
					M.at(i, j) = getA().getX() - getB().getX();
				}
				else if (j == 1) //In the second row...
				{
					//Place the difference of the x values between vectors A and C.
					M.at(i, j) = getA().getX() - getC().getX();
				}
				else if (j == 2) //In the third row...
				{
					//Place the x value of the ray's directional vector.
					M.at(i, j) = ray.getDirection().getX();
				}
			}
			else if (i == 1) //In the second column...
			{
				//In the first row...
				if (j == 0)
				{
					//Place the difference of the y values between vectors A and B.
					M.at(i, j) = getA().getY() - getB().getY();
				}
				else if (j == 1) //In the second row...
				{
					//Place the difference of the y values between vectors A and C.
					M.at(i, j) = getA().getY() - getC().getY();
				}
				else if (j == 2) //In the third row...
				{
					//Place the y value of the ray's directional vector.
					M.at(i, j) = ray.getDirection().getY();
				}
			}
			else if (i == 2) //In the third column...
			{
				//In the first row...
				if (j == 0) 
				{
					//Place the difference of the z values between vectors A and B.
					M.at(i, j) = getA().getZ() - getB().getZ();
				}
				else if (j == 1) //In the second row...
				{
					//Place the difference of the z values between vectors A and C.
					M.at(i, j) = getA().getZ() - getC().getZ();
				}
				else if (j == 2) //In the third row...
				{
					//Place the z value of the ray's directional vector.
					M.at(i, j) = ray.getDirection().getZ();
				}
			}
		}
	}
	
	//Create a 3 x 1 matrix for the vector formed from the triangle's A side and the ray's inverted origin point.
	Matrix Y = Matrix(3, 1);
	
	//For every element in the matrix...
	for (unsigned int i = 0; i < Y.getRowSize(); i++)
	{
		//In the first column...
		if (i == 0)
		{
			//Place the difference between the x values of the triangle's A side and the ray's origin point. 
			Y.at(i, 0) = getA().getX() - ray.getPoint().getX();
		}
		else if (i == 1) //In the second column...
		{
			//Place the difference between the y values of the triangle's A side and the ray's origin point. 
			Y.at(i, 0) = getA().getY() - ray.getPoint().getY();
		}
		else //In the (presumably) third column...
		{
			//Place the difference between the z values of the triangle's A side and the ray's origin point. 
			Y.at(i, 0) = getA().getZ() - ray.getPoint().getZ();
		}
	}
	
	//Minverse: Create an inverse of matrix M.
	Matrix Minverse = M.inverse();
	//X: Multiply the inverse of M by Y.
	Matrix X = Minverse * Y;
	
	//If the first element is less than 0 OR
	//the second element is less than 0 OR
	//the sum of the first and second elements is greater than 1 OR
	//The third element is less than or equal to 0, then...
	if (X.at(0, 0) < 0 || X.at(1, 0) < 0 || X.at(0, 0) + X.at(1, 0) > 1 || X.at(2, 0) <= 0.0)
	{
		//Return false, indicating no intersection was found.
		return 0.0;
	}
	
	//The third element in X is the intersection value. If all checks are cleared, store the intersection value.
	double t = X.at(2, 0);
	
	//Return true, indicating an intersection took place.
	return t;
}
