/* Author: coleman7245
 * File: C++ Triangle class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The Triangle class stores all information about the triangles present within the scene, which is almost always represents the faces 
 * of the model. Additional methods are provided to calculate the surface normal of a triangle, color a triangle depending on the 
 * intersection, and detecting an intersection between a ray and a triangle, 
 */

#include "triangle.h"

unsigned int count = 0;

//Method Summary: Default constructor
Triangle::Triangle() : A(Vector()), B(Vector()), C(Vector()) {}

//Method Summary: Constructor using input from the provided parameters.
Triangle::Triangle(const Vector &a, const Vector &b, const Vector &c) : A(a), B(b), C(c) {calculateSurfaceNormal();}

//Method Summary: Deconstructor
Triangle::~Triangle() {}

//Method Summary: Calculates the surface normal of the triangle.
//Precondtions: None.
//Postconditions: None.
void Triangle::calculateSurfaceNormal()
{
	//U: Vector representing one side of the triangle.
	//V: Vector representing another side of the triangle.
	Vector U = B - A;
	Vector V = C - A;
	
	//The surface normal is the cross product of U and V.
	surfaceNormal = Vector::crossProduct(U, V);
	//Normalize the surface normal.
	surfaceNormal = surfaceNormal.normalize();
}

//Method Summary: An obsolete method from previous assignments used for coloring a triangle in a scene. Some of the code carried over to the 
//recursive raytracer method in the Camera class.
//Precondtions: The material of the model that contains the face, a ray that intersected with the triangle, the intersection value, 
//the lights in the scene, and the ambient lighting.
//Postconditions: The color of the triangle is returned.
Vector Triangle::colorTriangle(const Material &material, const Ray &ray, double &t, const vector<Light> &lights, 
							   const Vector &ambientLight)
{
	//D: The directional vector of the triangle.
	//P: The origin point of the ray.
	Vector D = ray.getVector();
	Vector P = ray.getPoint();
	//pointOfIntersection: The point of intersection between the ray and triangle that is formed by this formula: t * D + P.
	Vector pointOfIntersection = t * D;
	pointOfIntersection = P + pointOfIntersection;
	//color: Vector representing the color of the triangle. It begins by mixing the ambient light with the ambient properties of the 
	//material.
	Vector color = Vector::pairwiseProduct(material.getKA(), ambientLight);
	
	//For every light in the scene...
	for (unsigned int l = 0; l < lights.size(); l++)
	{
		//toLight: Vector pointing toward the current light.
		Vector toLight = lights[l].getPoint();
		toLight = toLight - pointOfIntersection;
		//Normalize the vector.
		toLight = toLight.normalize();
		//toCamera: Vector pointing toward the camera.
		Vector toCamera = ray.getPoint();
		toCamera =  toCamera - pointOfIntersection;
		//Normalize the vector.
		toCamera = toCamera.normalize();
		
		//If the surface normal is pointing in the opposite direction...				
		if (Vector::dotProduct(toCamera, surfaceNormal) < 0.0)
		{
			//Reverse its direction.
			surfaceNormal = -1.0 * surfaceNormal;
		}
		
		//If the angle of between the vector pointing toward the light and the surface normal is less than 90 degrees, then...
		if (Vector::dotProduct(toLight, surfaceNormal) > 0.0)
		{
			//Mix the light emission with the material's diffuse property.
			Vector diffuseEmission = Vector::pairwiseProduct(material.getKD(), lights[l].getEmission());
			//Scale the diffuse emission by the cosine of the angle between the vector pointing toward the light and the surface normal.
			diffuseEmission = Vector::dotProduct(toLight, surfaceNormal) * diffuseEmission;
			//Add the diffuse emission.
			color = color + diffuseEmission;
			//Start the specular reflection by scaling the surface normal by the cosine of the angle between the vector pointing toward 
			//the light and the surface normal and 2.
			Vector specularReflection = ((2 * Vector::dotProduct(toLight, surfaceNormal)) * surfaceNormal);
			//Combine the reversed toLight vector to the specular reflection.
			specularReflection = specularReflection - toLight;
			//Mix the light emission with the material's surface property.
			Vector surfaceEmission = Vector::pairwiseProduct(material.getKS(), lights[l].getEmission());
			//Scale the surface emission by the cosine of the angle between the vector pointing toward the light and the surface normal. 
			//The scaling needs to occur 16 times.
			surfaceEmission = pow(Vector::dotProduct(toCamera, specularReflection), 16.0) * surfaceEmission;
			//Add the surface emission to the color.
			color = color + surfaceEmission;
		}
	}
	
	//Return the color of the triangle.
	return color;
}

//Method Summary: Get methods for class variables that simply return their value.
const Vector & Triangle::getA() const {return A;}

const Vector & Triangle::getB() const {return B;}

const Vector & Triangle::getC() const {return C;}

const Vector & Triangle::getSurfaceNormal() const {return surfaceNormal;}

//Method Summary: Detects if a ray intersected with the triangle.
//Precondtions: The ray and the intersection value.
//Postconditions: Returns true if the intersection happened, false otherwise.
bool Triangle::intersect(const Ray &ray, double &t)
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
					M[i][j] = getA().getX() - getB().getX();
				}
				else if (j == 1) //In the second row...
				{
					//Place the difference of the x values between vectors A and C.
					M[i][j] = getA().getX() - getC().getX();
				}
				else if (j == 2) //In the third row...
				{
					//Place the x value of the ray's directional vector.
					M[i][j] = ray.getVector().getX();
				}
			}
			else if (i == 1) //In the second column...
			{
				//In the first row...
				if (j == 0)
				{
					//Place the difference of the y values between vectors A and B.
					M[i][j] = getA().getY() - getB().getY();
				}
				else if (j == 1) //In the second row...
				{
					//Place the difference of the y values between vectors A and C.
					M[i][j] = getA().getY() - getC().getY();
				}
				else if (j == 2) //In the third row...
				{
					//Place the y value of the ray's directional vector.
					M[i][j] = ray.getVector().getY();
				}
			}
			else if (i == 2) //In the third column...
			{
				//In the first row...
				if (j == 0) 
				{
					//Place the difference of the z values between vectors A and B.
					M[i][j] = getA().getZ() - getB().getZ();
				}
				else if (j == 1) //In the second row...
				{
					//Place the difference of the z values between vectors A and C.
					M[i][j] = getA().getZ() - getC().getZ();
				}
				else if (j == 2) //In the third row...
				{
					//Place the z value of the ray's directional vector.
					M[i][j] = ray.getVector().getZ();
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
			Y[i][0] = getA().getX() - ray.getPoint().getX();
		}
		else if (i == 1) //In the second column...
		{
			//Place the difference between the y values of the triangle's A side and the ray's origin point. 
			Y[i][0] = getA().getY() - ray.getPoint().getY();
		}
		else //In the (presumably) third column...
		{
			//Place the difference between the z values of the triangle's A side and the ray's origin point. 
			Y[i][0] = getA().getZ() - ray.getPoint().getZ();
		}
	}
	
	//Minverse: Create an inverse of matrix M.
	Matrix Minverse = M.inverse();
	//X: Multiply the inverse of M by Y.
	Matrix X = Matrix::multiplyMatrices(Minverse, Y);
	
	if (count < 1)
	{
		cout << X << endl;
		count++;
	}
	
	//If the first element is less than 0 OR
	//the second element is less than 0 OR
	//the sum of the first and second elements is greater than 1 OR
	//The third element is less than or equal to 0, then...
	if (X[0][0] < 0 || X[1][0] < 0 || X[0][0] + X[1][0] > 1 || X[2][0] <= 0.0)
	{
		//Return false, indicating no intersection took place.
		return false;
	}
	
	//The third element in X is the intersection value. If all checks are cleared, store the intersection value.
	t = X[2][0];
	
	//Return true, indicating an intersection took place.
	return true;
}

//Method Summary: Set methods that simply set the values for class variables.
void Triangle::setA(const Vector &a) {A = a;}

void Triangle::setB(const Vector &b) {B = b;}

void Triangle::setC(const Vector &c) {C = c;}
