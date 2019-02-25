/* Author: coleman7245
 * File: C++ Camera Class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The Camera class is the primary means of how a scene is rendered. Using the information provided by the driver file, it 
 * creates a coordinate system that orients the camera's position, rotation, and projection to the scene. Afterward, it constructs a ray, 
 * based on the coordinate system, for every pixel in the driver-specified resolution. Every pixel ray is cycled through to see if they 
 * intersect with any models or spheres within the scene. 
 */

//Include header file.
#include "camera.h"

//Method Summary: Default constructor
Camera::Camera() : lookAtPoint(Vector<double>()), eyePoint(Vector<double>()), viewPlane(ViewPlane()), width(0.0), height(0.0), 
	recursionLevel(0), up(Vector<double>()), heightInt(0), widthInt(0)
{
	//Construct the camera coordinate system.
	constructCameraCoordinates();
	//Create the pixel arrays.
	createPixelRays();
}

//Method Summary: Constructor using input from the provided driver.
Camera::Camera(const Vector<double> &lookAtPointP, const Vector<double> &eyePointP, const ViewPlane &viewPlaneP, const double widthP, 
	const double heightP, const int recursionLevelP, const Vector<double> &upP) : lookAtPoint(lookAtPointP), eyePoint(eyePointP), 
	viewPlane(viewPlaneP), width(widthP), height(heightP), recursionLevel(recursionLevelP), up(upP), 
	heightInt(static_cast<unsigned int>(heightP)), widthInt(static_cast<unsigned int>(widthP))
{
	//Construct the camera coordinate system.
	constructCameraCoordinates();
	//Create the pixel rays.
	createPixelRays();
}

//Method Summary: Deconstructor
Camera::~Camera() {}

//Method Summary: Constructs the coordinate system for the camera.
//Preconditions: None.
//Postconditions: The camera's coordinate system is constructed.
void Camera::constructCameraCoordinates()
{
	//The w vector is the eyepoint vector summed with the inverse vector of the focal point vector.
	w = (eyePoint - lookAtPoint).normalize();
	//The u vector is the cross product of the UP vector and the normalized w vector.
	u = up.crossProduct(w).normalize();
	//The v vector is the cross product of the u and w vectors. Normalization is not required, since u and w are already normalized.
	v = u.crossProduct(w);
}

//Method Summary: Creates a pixel ray using the camera's coordinate system.
//Preconditions: Two double numbers: one for the x-axis (i), the other for the y-axis (j).
//Postconditions: Returns a pixel ray with a direction and origin point. 
Ray Camera::pixelRay(const double x, const double y) const
{	
	//The pixel coordinate on the x-axis.
	double px = x / (width - 1) * (viewPlane.getRight() - viewPlane.getLeft()) + viewPlane.getLeft();
	//The pixel coordinate on the y-axis.
	double py = y / (height - 1) * (viewPlane.getTop() - viewPlane.getBottom()) + viewPlane.getBottom();
	
	//The origin point of the pixel ray is the sum of the three previous vectors and the eye point of the camera. 
	Vector<double> L = eyePoint + (px * u) + (py * v) + (viewPlane.getNear() * w);
	
	//The direction of the pixel ray is the sum of the direction of the pixel ray and the inverse vector of the camera's eyepoint.
	Vector<double> U = (L - eyePoint).normalize();
	
	//Return a new Ray object with the calculated direction and point vectors.
	return Ray(L, U);
}

//Method Summary: Creates a pixel ray for each pixel in the specified resolution. Not that the order of method calls goes by the resolution 
//from top-left to bottom-right.
//Preconditions: None.
//Postconditions: Every pixel coordinate has a valid pixel ray object. 
void Camera::createPixelRays()
{
	//Initialize the pixel ray class variable with a vector of vectors of rays according to the height of the resolution.
	pixelRays = std::vector<Ray>(widthInt * heightInt);
	
	//For each pixel coordinate...
	for (unsigned int px = 0; px < heightInt; px++)
	{
		for (unsigned int py = 0; py < widthInt; py++)
		{
			//Create a pixel ray. Note that j cooresponds with the x-axis and i with the y-axis.
			pixelRays[px * widthInt + py] = pixelRay(py, px);
		}
	}
}

//Method Summary: Sets the colors of each pixel to a value bound between 0 and 255. The value of the color is determined by the recursive 
//call.
//Preconditions: A vector of sphere objects, a vector of model objects, an attenuation vector, and a recursion level. 
//Postconditions: A color vector is set for every pixel in the resolution. 
void Camera::setColors(const std::vector<Sphere> &spheres, const std::vector<Model> &models, const Vector<double> &attenuation, 
	const std::vector<Light> &lights, const Vector<double> &ambientLight)
{
	//Initialize the colors vector according to the resolution's height.
	colors = std::vector< Vector<double> >(widthInt * heightInt);
	//Initialize the vector to the default values i.e. (0, 0, 0).
	Vector<double> color = Vector<double>();
	
	//For every pixel value...
	for (unsigned int px = 0; px < heightInt; px++)
	{
		for (unsigned int py = 0; py < widthInt; py++)
		{
			//Call the recursive method for ray intersection and color accumulation.
			recursiveTrace(pixelRays[px * widthInt + py], spheres, models, lights, ambientLight, color, attenuation, recursionLevel, 
				std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max());
			//Set the color of the given pixel to a value clamped between 0 and 255.
			colors[px * widthInt + py] = Vector<double>(fmax(0.0, fmin(255.0, 255.0 * color.getX())), 
				fmax(0.0, fmin(255.0, 255.0 * color.getY())), 
				fmax(0.0, fmin(255.0, 255.0 * color.getZ())));
			//Reset the accumulated color vector to (0, 0, 0) in preparation for the next pixel.
			color = Vector<double>();
		}
	}
}

//Method Summary: Where the magic happens: A pixel ray is shot into the scene, and if it intersects with an object, that pixel is then 
//colored according to a number of constraints like reflection, refraction, and lighting.
//Preconditions: A ray, a vector of spheres, a vector of models, an accumulated color vector, an color attenuation vector, a recursion 
//level, the index of the last intersected model face, and the index of the last intersected sphere.
//Postconditions: The accumlated color vector is set with the proper values.
void Camera::recursiveTrace(const Ray &pRay, const std::vector<Sphere> &spheres, const std::vector<Model> &models, 
	const std::vector<Light> &lights, const Vector<double> &ambientLight, Vector<double> &accumulation, const Vector<double> &attenuation, 
	int level, const unsigned int lastFaceIndex, const unsigned int lastSphereIndex)
{
	//A struct that contains the best t and what object that t cooresponds to. 
	bestPick best = inScene(pRay, spheres, models, lastFaceIndex, lastSphereIndex);
	
	//If the t value is greater than zero, and therefore, intersects with an object, then...
	if (best.t > 0.0)
	{
		//The surface normal vector that is perpindicular to the surface intersected by the ray, 
		//The material attenuation vector for color deteriation.
		//The inverted direction vector of the pixel ray.
		//The point of intersection between the pixel ray and the shape.
		Vector<double> surfaceNormal;
		Vector<double> materialAttenuation;
		Vector<double> invertedDirection = -1.0 * pRay.getDirection();
		Vector<double> pointOfIntersection = pRay.getPoint() + (best.t * pRay.getDirection());
		Material material;
		
		//If the best sphere index is valid, then...
		if (best.sphereIndex != std::numeric_limits<unsigned int>::max())
		{
			//Calculate the surface normal.
			surfaceNormal = (pointOfIntersection - spheres[best.sphereIndex].getCenter()).normalize();
			material = spheres[best.sphereIndex].getMaterial();
			//Apply the material's attenuation value to the overall attenuation.
			materialAttenuation = (material.getKR() * attenuation);
		}
		else //If the sphere index is not valid, then the t value must belong to a model face.
		{	
			//Retrieve the surface normal from the given face on the favored model.
			surfaceNormal = models[best.modelIndex].getFaces()[best.faceIndex].getSurfaceNormal();
			
			//For every material of the model...
			for (unsigned int i = 0; i < models[best.modelIndex].getMaterials().size(); i++)
			{	
				//If the model's face index is aligned with the correct material index, then...
				if (best.faceIndex >= models[best.modelIndex].getMaterials()[i].getBeginningIndex() && 
					best.faceIndex <= models[best.modelIndex].getMaterials()[i].getEndingIndex())
				{
					//Set the material of that model face.
					material = models[best.modelIndex].getMaterials()[i];
				}
			}
			
			//Apply a constant to the overall material attenuation.
			materialAttenuation = Vector<double>(1.0, 1.0, 1.0) * attenuation;
		}
		
		//Apply ambient lighting to the overall color of the pixel.
		Vector<double> color = (material.getKA() * ambientLight);
		
		//For every point light in the scene...
		for (unsigned int l = 0; l < lights.size(); l++)
		{
			//Retrieve the point light's position and normalize it.
			Vector<double> toLight = (lights[l].getPoint() - pointOfIntersection).normalize();
			//Create a ray meant for determining shadows.
			Ray shadowRay = Ray(pointOfIntersection, toLight);
			//Calculate and normalize a vector pointing to the camera.
			Vector<double> toCamera = (pRay.getPoint() - pointOfIntersection).normalize();
			
			//If the surface normal is pointing in the opposite direction, then...
			if (toCamera.dotProduct(surfaceNormal) < 0.0)
			{
				//Reverse its direction.
				surfaceNormal = -1.0 * surfaceNormal;
			}
			
			//Initialize the best shadow objects.
			bestPick shadowBest = inScene(shadowRay, spheres, models, best.faceIndex, best.sphereIndex);
			//Vectors for diffuse and surface color.
			Vector<double> diffuseEmission;
			Vector<double> surfaceEmission;
			
			//If the light is pointing in the correct general area, then...
			if (toLight.dotProduct(surfaceNormal) > 0.0 && shadowBest.t == 0.0)
			{
				//Apply diffuse lighting.
				diffuseEmission = toLight.dotProduct(surfaceNormal) * (material.getKD() * lights[l].getEmission());
				//Apply the diffuse lighting to the accumulated color.
				color += diffuseEmission;
				
				//Apply specular lighting.
				Vector<double> specularReflection = ((2.0 * toLight.dotProduct(surfaceNormal)) * surfaceNormal) - toLight;

				surfaceEmission = pow(toCamera.dotProduct(specularReflection), material.getNS()) * (material.getKS() * 
					lights[l].getEmission());
				//Apply the specular lighting to the accumulated color.
				color += surfaceEmission;
			}
		}
		
		//Apply light degeneration.
		Vector<double> degeneration = color * attenuation * material.getKO();
		accumulation += degeneration;
		
		//If the recursion level is greater than 0, then...
		if (level > 0)
		{
			//A separate vector for color accumulation.
			Vector<double> flec = Vector<double>();
			//Create a ray for reflecting light.
			Vector<double> reflectionDirection = ((2.0 * surfaceNormal.dotProduct(invertedDirection)) * surfaceNormal) - invertedDirection;
			Ray pRayReflection = Ray(pointOfIntersection, reflectionDirection);
			//Recursive call using the new color accumulation vector and the reflecting ray.
			recursiveTrace(pRayReflection, spheres, models, lights, ambientLight, flec, materialAttenuation, level - 1, best.faceIndex, 
				best.sphereIndex);
			//Apply attenuation.
			degeneration = flec * attenuation * material.getKO();
			//Add this round of color accumulation to the overall total.
			accumulation += degeneration;
		}
		
		//If the recursion level is greater than 0, the material properties allow refraction, and a sphere is the intersected object, 
		//then...
		if (level > 0 && (material.getKO().getX() + material.getKO().getY() + material.getKO().getZ()) < 3.0 && 
			best.sphereIndex != std::numeric_limits<unsigned int>::max())
		{
			//Create an exit ray for refraction.
			Ray exitRay = createRefractionExitRay(spheres[best.sphereIndex].getCenter(), invertedDirection, pointOfIntersection, 
												  material.getETA());
			
			//If the direction vector of  the exit ray is valid, then...
			if (exitRay.getDirection().getX() != 0.0 || exitRay.getDirection().getY() != 0.0 || exitRay.getDirection().getZ() != 0.0)
			{
				//Another new vector for color accumulation.
				Vector<double> through = Vector<double>();
				//Inverse vector for the material's refraction properties.
				Vector<double> oneVector = Vector<double>(1.0, 1.0, 1.0);
				Vector<double> inverseKO = oneVector - material.getKO();
				//Recursive call using the exit ray and the new color accumulation vector.
				recursiveTrace(exitRay, spheres, models, lights, ambientLight, through, materialAttenuation, level - 1, best.faceIndex, 
					best.sphereIndex);
				//Apply attenuation to the color accumulation.
				degeneration = through * attenuation * inverseKO;
				//Add this round of color accumulation to the overall total.
				accumulation += degeneration;
			}
		}
	}
}

//Method Summary: A method that determines if a list of models and spheres intersect with the provided ray.
//Preconditions: A ray to be shot into the scene, a list of spheres, a list of models, a best pick structure for the closest intersection,
//and indecies for the last intersected sphere and model.
//Postconditions: Returns a true or false value indicating an intersect, and modifies the best pick structure with the closest 
//intersection.
bestPick Camera::inScene(const Ray &pRay, const std::vector<Sphere> &spheres, const std::vector<Model> &models, 
	const unsigned int lastFaceIndex, const unsigned int lastSphereIndex)
{
	//Note: The smaller the t value, the closer the intersection. A zero t value indicates no intersection.
	//tS: Closest sphere intersection value.
	//tT: Closest model face intersection. 
	//tSmallestS: Smallest of the sphere t values.
	//tSmallestT: Smallest of the model face t values.
	double tS = 0.0;
	double tT = 0.0;
	double tSmallestS = std::numeric_limits<double>::max();
	double tSmallestT = std::numeric_limits<double>::max();
	unsigned int modelIndex = std::numeric_limits<unsigned int>::max();
	unsigned int faceIndex = std::numeric_limits<unsigned int>::max();
	unsigned int sphereIndex = std::numeric_limits<unsigned int>::max();
	bestPick best;
	best.t = 0.0;
	best.faceIndex = std::numeric_limits<unsigned int>::max();
	best.sphereIndex = std::numeric_limits<unsigned int>::max();
	
	//For every sphere in the list...
	for (unsigned int i = 0; i < spheres.size(); i++)
	{
		//Is this sphere the same as the last intersection?
		if (i != lastSphereIndex)
		{	
			//Calculate the intersection between the sphere and the ray.
			tS = spheres[i].intersect(pRay);
			
			//Is the newly attained sphere t value smaller than the currently smallest sphere t value?
			if (tS > 0 && tS < tSmallestS)
			{
				//Set the smallest sphere t value to the newly attained sphere t value.
				tSmallestS = tS;
				//Set the current closest sphere intersection index to this one.
				sphereIndex = i;
			}
		}
	}
	
	//For every model in the list...
	for (unsigned int i = 0; i < models.size(); i++)
	{
		//For every face vertex in the current model...
		for (unsigned int j = 0; j < models[i].getFaces().size(); j++)
		{
			//Is this face index the same as the last intersected face index?
			if (j != lastFaceIndex)
			{
				//Calculate the intersection value between the model face and the ray.
				tT = models[i].getFaces()[j].intersect(pRay);
				
				//Is the newly attained face vertex t value smaller than the currently smallest face vertex t value?
				if (tT > 0 && tT < tSmallestT)
				{
					//Set the smallest face vertex t value to the newly attained one.
					tSmallestT = tT;
					//Set the closest intersected model to the current one.
					modelIndex = i;
					//Set the closest intersected face vertex to the current one.
					faceIndex = j;
				}			
			}
		}
	}
	
	//Is the closest intersection value from a model face vertex or a sphere?
	if (tSmallestS < tSmallestT && tSmallestS != std::numeric_limits<double>::max())
	{
		//If it's from a sphere...
		//Set the closest intersection value to that of the closest sphere.
		best.t = tSmallestS;
		//Set the closest face vertex index to a non-valid value.
		best.sphereIndex = sphereIndex;
	}
	else if (tSmallestT != std::numeric_limits<double>::max())
	{
		//If it's from a model face vertex...
		//Set the closest intersection value to that of the closest model face vertex.
		best.t = tSmallestT;
		//Set the closest sphere index to a non-valid value.
		best.modelIndex = modelIndex;
		best.faceIndex = faceIndex;
	}
	
	return best;
}

//Method Summary: Creates a refraction ray for proper refraction computation.
//Preconditions: The center of the sphere, the vector to the camera, the point of intersection, and the refraction index of the material.
//Postconditions: Returns a complete refraction ray.
Ray Camera::createRefractionExitRay(const Vector<double> &center, const Vector<double> &W, const Vector<double> &pointOfIntersection, 
	const double etai) const
{
	//w: Vector pointing toward the camera.
	//c: The center of the sphere.
	//point: Point of intersection.
	//surfaceNormal: Vector perpindicular to the surface plane.
	Vector<double> surfaceNormal = (pointOfIntersection - center).normalize();
	//Displaced directional vector after passing through the object at the entrance point.
	Vector<double> T1 = createRefractionTVector(W, surfaceNormal, 1.0, etai);
	
	//If the T1 vector is not valid, then...
	if (T1.getX() == 0.0 && T1.getY() == 0.0 && T1.getZ() == 0.0)
	{
		//Return a default ray object.
		return Ray();
	}
	
	//Surface normal with an inverted direction.
	Vector<double> invertedNormal = center - pointOfIntersection;
	//Exit point of the refraction ray.
	Vector<double> exitPoint = ((2.0 * invertedNormal.dotProduct(T1)) * T1) + pointOfIntersection; 
	
	//Surface normal with the exit point as its base.
	Vector<double> exitSurfaceNormal = (center - exitPoint).normalize();
	
	//Invert the direction of the T1 vector.
	Vector<double> invertedT1 = -1.0 * T1;
	//T2: Displaced directional vector after the exiting the object through the exit point.
	Vector<double> T2 = createRefractionTVector(invertedT1, exitSurfaceNormal, etai, 1.0);
	
	//Return the refraction ray with the exit point as the point and the T2 vector as the directional vector.
	return Ray(exitPoint, T2);
}

//Method Summary: Helper function to the createRefractionExitRay method that creates the displaced directional vector.
//Preconditions: The vector pointing toward the camera, the surface normal vector, the refraction index of the entrance point material, and the
//refraction index of the exit point material.
//Postconditions: The displaced directional vector is returned.
Vector<double> Camera::createRefractionTVector(const Vector<double> &W, const Vector<double> &N, const double eta1, const double eta2) const
{
	//w: Vector pointing toward the camera.
	//n: Surface normal vector.
	//eta1copy: Refraction index of the entrance point's material.
	//eta2copy: Refraction index of the exit point's material.
	//etar: Ratio of the entrance and exit refraction material.
	//alpha: Inverse of the refraction index ratio.
	//wDotN: Dot product of the w and n vectors.
	//disc: Discriminant required to form the beta variable.
	double etaRatio = eta1 / eta2;
	double alpha = -1.0 * etaRatio;
	double wDotN = W.dotProduct(N);
	double disc = (etaRatio * etaRatio) * ((wDotN * wDotN) - 1) + 1;
	
	//If the discriminant is less than 0, then...
	if (disc < 0.0)
	{
		//Return a default vector.
		return Vector<double>();
	}
	
	//beta: Scalar of the surface normal.
	//Tpart1: w scaled by alpha that forms the first part of the T vector.
	//Tpart2: n scaled by beta that forms the second part of the T vector.
	//T: The displaced directional vector that is the sum of the scaled w and n vectors.
	double beta = (etaRatio * wDotN) - sqrt(disc);
	Vector<double> T = ((alpha * W) + (beta * N)).normalize();
	
	//Return the displaced directional vector.
	return T;
}
