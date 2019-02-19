/* Author: coleman7245
 * File: C++ Sphere Class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The Sphere class stores information on the sphere rendered in the scene. Contains an intersect method to determine if a 
 * ray intersected with it and an obsolete coloring method used in previous assignments, but not with the current implementation.
 */

#include "sphere.h"

//Method Summary: Default constructor
Sphere::Sphere() : center(Vector()), radius(0.0), material(Material()) {}

//Method Summary: Constructor using input from the provided parameters.
Sphere::Sphere(const Vector &c, const double r, const Material &m) : center(c), radius(r), material(m) {}

//Method Summary: Deconstructor
Sphere::~Sphere() {}

//Method Summary: An obsolete method from previous assignments used for coloring a sphere in a scene. Some of the code carried over to the 
//recursive raytracer method in the Camera class.
//Precondtions: A ray that intersected with the sphere, the intersection value, the lights in the scene, and the ambient lighting.
//Postconditions: The color of the sphere is returned.
Vector Sphere::colorSphere(Ray &ray, double &t, vector<Light> &lights, const Vector &ambientLight)
{
	//D: The directional vector of the ray.
	//P: The origin vector of the ray.
	//pointOfIntersection: The point of intersection between the ray and the sphere.
	//surfaceNormal: The vector perpindicular to the sphere's surface at the point of intersection.
	//color: The color of the sphere.
	Vector D = ray.getVector();
	Vector P = ray.getPoint();
	//pointOfIntersection equation: point of ray's origin + (intersection value * directional vector of ray).
	Vector pointOfIntersection = t * D;
	pointOfIntersection = P + pointOfIntersection;
	//surfaceNormal equation: point of intersection - center of sphere.
	Vector surfaceNormal = pointOfIntersection;
	surfaceNormal = surfaceNormal - center;
	//Normalize the surface normal.
	surfaceNormal = surfaceNormal.normalize();
	//Mix the material's ambient value with the ambient lighting.
	Vector color = Vector::pairwiseProduct(material.getKA(), ambientLight);
	
	//For every light in the scene...				
	for (unsigned int l = 0; l < lights.size(); l++)
	{
		//toLight: Vector that points at the light.
		//toCamera: Vector that points at the camera.
		Vector toLight = lights[l].getPoint();
		toLight = toLight - pointOfIntersection;
		//Normalize the vector pointing at the light.
		toLight = toLight.normalize();
		Vector toCamera = ray.getPoint();
		toCamera =  toCamera - pointOfIntersection;
		//Normalize the vector pointing at the camera.
		toCamera = toCamera.normalize();
		
		//If the surface normal is pointing in the wrong direction...				
		if (Vector::dotProduct(toCamera, surfaceNormal) < 0.0)
		{
			//Reserve the direction of the surface normal.
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
	
	//Return the color of the sphere.
	return color;
}

//Method Summary: Get methods for class variables that simply return their value.
const Vector & Sphere::getCenter() const {return center;}

const Material & Sphere::getMaterial() const {return material;}

double Sphere::getRadius() const {return radius;}

//Method Summary: Detects if a ray has intersected with the sphere. 
//Precondtions: A ray and the intersection value.
//Postconditions: Returns true if the intersect happened, false otherwise.
bool Sphere::intersect(const Ray &ray, double &t)
{
	//L: The origin point of the ray.
	//U: The ray's directional vector.
	//T: Vector pointing toward the center of the sphere from the ray's origin point.
	//v: Cosine of the angle between U and T.
	//Tsq: Cosine of the angle between T and itself.
	//disc: The discriminant of the formula.
	//t0: The initial intersection value.
	Vector L = ray.getPoint();
	Vector U = ray.getVector();
	Vector T = center - L;
	double v = Vector::dotProduct(U, T);
	double Tsq = Vector::dotProduct(T, T);
	double disc = (radius * radius) - Tsq + (v * v);
	double t0 = v - sqrt(disc);
	
	//If either the discriminant or the t value is negative, then...
	if (disc < 0 || t0 < 0.0)
	{
		//Set the intersection value to 0.
		t = 0.0;
		//Return false, indicating no intersection took place.
		return false;
	}
	else
	{
		//Set the intersection value to the initial intersection value.
		t = t0;
		//Return true, indicating success.
		return true;
	}
}

//Method Summary: Set methods that simply set the values for class variables.
void Sphere::setCenter(const Vector &c) {center = c;}

void Sphere::setRadius(const double r) {radius = r;}
