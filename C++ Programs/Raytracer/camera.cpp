/* Author: coleman7245
 * File: C++ Camera Class for Raytracer
 * Last Update: 2/18/2019
 * File Summary: The Camera class is the primary means of how a scene is rendered. Using the information provided by the driver file, it 
 * creates a coordinate system that orients the camera's position, rotation, and projection to the scene. Afterward, it constructs a ray, 
 * based on the coordinate system, for every pixel in the driver-specified resolution. Every pixel ray is cycled through to see if they 
 * intersect with any models or spheres within the scene. 
 */

//Include header file.
#include "camera.h"

//Method Summary: Default constructor
Camera::Camera() : lookAtPoint(Vector()), eyePoint(Vector()), distance(0.0), near(0.0), far(0.0), top(0.0), bottom(0.0), left(0.0), right(0.0), width(0.0),
	height(0.0), up(Vector()), ambientLight(Vector())
{
	//Construct the camera coordinate system.
	constructCameraCoordinates();
	//Create the pixel arrays.
	createPixelRays();
}

//Method Summary: Constructor using input from the provided driver.
Camera::Camera(const Vector &look, const Vector &eye, double d, double nr, double fr, double tp, double bm, double lt, double rt, double wh, double ht, 
			const Vector &_up, const Vector &al) : lookAtPoint(look), eyePoint(eye), distance(d), near(nr), 
			far(fr), top(tp), bottom(bm), left(lt), right(rt), width(wh), height(ht), up(_up), ambientLight(al)
{
	//Construct the camera coordinate system.
	constructCameraCoordinates();
	//Create the pixel rays.
	createPixelRays();
}

//Method Summary: Deconstructor
Camera::~Camera() {}

//Method Summary: Adds a valid light object from the input to the vector of lights.
//Precondtions: A constant reference to a valid Light object.
//Postconditions: The valid Light object is added to the vector.
void Camera::addLight(const Light &light)
{
	lights.push_back(light);
}

//Method Summary: Constructs the coordinate system for the camera.
//Preconditions: None.
//Postconditions: The camera's coordinate system is constructed.
void Camera::constructCameraCoordinates()
{
	//The w vector is the eyepoint vector summed with the inverse vector of the focal point vector.
	w = eyePoint - lookAtPoint;
	//Give the w vector a length of 1.
	w = w.normalize();
	//The u vector is the cross product of the UP vector and the normalized w vector.
	u = Vector::crossProduct(up, w);
	//Give the u vector a length of 1.
	u = u.normalize();
	//The v vector is the cross product of the u and w vectors. Normalization is not required, since u and w are already normalized.
	v = Vector::crossProduct(u, w);
}

//Method Summary: Creates a pixel ray using the camera's coordinate system.
//Preconditions: Two double numbers: one for the x-axis (i), the other for the y-axis (j).
//Postconditions: Returns a pixel ray with a direction and origin point. 
Ray Camera::pixelRay(double i, double j)
{	
	//The pixel coordinate on the x-axis.
	double px = i / (width - 1) * (right - left) + left;
	//The pixel coordinate on the y-axis.
	double py = j / (height - 1) * (top - bottom) + bottom;
	//Scale the u vector by px.
	Vector Upx = px * u;
	//Scale the v vector by py.
	Vector Vpy = py * v;
	//Scale the w vector by the camera's near projection value.
	Vector Wnr = near * w;
	//The origin point of the pixel ray is the sum of the three previous vectors and the eye point of the camera. 
	Vector L = eyePoint + Upx;
	L = L + Vpy;
	L = L + Wnr;
	//The direction of the pixel ray is the sum of the direction of the pixel ray and the inverse vector of the camera's eyepoint.
	Vector U = L - eyePoint;
	//Give the pixel ray's direction vector a length of 1.
	U = U.normalize();
	
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
	pixelRays = vector< vector<Ray> >(height);
	
	//For every column of the resolution...
	for (unsigned int i = 0; i < pixelRays.size(); i++)
	{
		//Initialize each vector entry with a vector of rays.
		pixelRays[i] = vector<Ray>(width);
	}
	
	//For each pixel coordinate...
	for (unsigned int i = 0; i < pixelRays.size(); i++)
	{
		for (unsigned int j = 0; j < pixelRays[i].size(); j++)
		{
			//Create a pixel ray. Note that j cooresponds with the x-axis and i with the y-axis.
			pixelRays[i][j] = pixelRay(j, i);
		}
	}
}

//Method Summary: Sets the colors of each pixel to a value bound between 0 and 255. The value of the color is determined by the recursive 
//call.
//Preconditions: A vector of sphere objects, a vector of model objects, an attenuation vector, and a recursion level. 
//Postconditions: A color vector is set for every pixel in the resolution. 
void Camera::setColors(vector<Sphere> &spheres, vector<Model> &models, Vector &attenuation, unsigned int recursionLevel)
{
	//Initialize the colors vector according to the resolution's height.
	colors = vector< vector<Vector> >(pixelRays.size());
	//Initialize the vector to the default values i.e. (0, 0, 0).
	Vector color = Vector();
	
	//For every pixel along the height of the resolution.
	for (unsigned int i = 0; i < pixelRays.size(); i++)
	{
		//Create a vector of color vectors for every pixel along the resolution's width.
		colors[i] = vector<Vector>(pixelRays[i].size());
	}
	
	//For every pixel value...
	for (unsigned int i = 0; i < colors.size(); i++)
	{
		for (unsigned int j = 0; j < colors[i].size(); j++)
		{
			//Call the recursive method for ray intersection and color accumulation.
			recursiveTrace(pixelRays[i][j], spheres, models, color, attenuation, recursionLevel, numeric_limits<unsigned int>::max(), 
						   numeric_limits<unsigned int>::max());
			//Set the color of the given pixel to a value clamped between 0 and 255.
			colors[i][j] = Vector(fmax(0.0, fmin(255.0, 255.0 * color.getX())), fmax(0.0, fmin(255.0, 255.0 * color.getY())), 
								  fmax(0.0, fmin(255.0, 255.0 * color.getZ())));
			//Reset the accumulated color vector to (0, 0, 0) in preparation for the next pixel.
			color = Vector();
		}
	}
}

//Method Summary: Get methods for class variables that simply return their value.
const Vector & Camera::getAmbientLight() const {return ambientLight;}

double Camera::getBottom() const {return bottom;}

const vector< vector<Vector> > & Camera::getColors() const {return colors;}

double  Camera::getDistance() const {return distance;}

const Vector &  Camera::getEyePoint() const {return eyePoint;}

double  Camera::getFar() const {return far;}

double  Camera::getHeight() const {return height;}

double  Camera::getLeft() const {return left;}

const vector<Light> & Camera::getLights() const {return lights;}

const Vector &  Camera::getLookAtPoint() const {return lookAtPoint;}

double  Camera::getNear() const {return near;}

double  Camera::getRight() const {return right;}

double  Camera::getTop() const {return top;}

double  Camera::getWidth() const {return width;}

const Vector &  Camera::getU() const {return u;}

const Vector &  Camera::getUp() const {return up;}

const Vector &  Camera::getV() const {return v;}

const Vector &  Camera::getW() const {return w;}

//Method Summary: Where the magic happens: A pixel ray is shot into the scene, and if it intersects with an object, that pixel is then 
//colored according to a number of constraints like reflection, refraction, and lighting.
//Preconditions: A ray, a vector of spheres, a vector of models, an accumulated color vector, an color attenuation vector, a recursion 
//level, the index of the last intersected model face, and the index of the last intersected sphere.
//Postconditions: The accumlated color vector is set with the proper values.
void Camera::recursiveTrace(Ray &pRay, vector<Sphere> &spheres, vector<Model> &models, Vector &accumulation, const Vector &attenuation, 
							int level, unsigned int lastFaceIndex, unsigned int lastSphereIndex)
{
	//The intersection value. The smaller the value, the closer the object is to the camera. 
	double t = 0.0;
	//A struct that contains the best t and what object that t cooresponds to. 
	bestPick best = bestPick();
	
	//If the ray intersects with either a sphere or an object within the scene, then...
	if (inScene(pRay, spheres, models, best, lastFaceIndex, lastSphereIndex))
	{
		//Set the t value to t value found in the best pick struct.
		t = best.t;
	}
	
	//If the t value is greater than zero, and therefore, intersects with an object, then...
	if (t > 0.0)
	{
		//Create a material variable for the potential model material relative to the intersected face.
		Material material;
		//The surface normal vector that is perpindicular to the surface intersected by the ray, the direction and point vectors of the 
		//pixel ray, the material attenuation vector, the point of intersection vector, and the inverted direction vector of the pixel ray.
		Vector surfaceNormal, D = pRay.getVector(), P = pRay.getPoint(), materialAttenuation, pointOfIntersection = t * D, 
		invertedD = -1.0 * D;
		pointOfIntersection = P + pointOfIntersection;
		
		//If the best sphere index is valid, then...
		if (best.sphereIndex != numeric_limits<unsigned int>::max())
		{
			//Retrieve the best sphere's center coordinates.
			Vector center = spheres[best.sphereIndex].getCenter();
			//Calculate the surface normal.
			surfaceNormal = pointOfIntersection;
			surfaceNormal = surfaceNormal - center;
			//Normalize the surface normal.
			surfaceNormal = surfaceNormal.normalize();
			//Retrieve the material for the sphere.
			material = spheres[best.sphereIndex].getMaterial();
			//Apply the material's attenuation value to the overall attenuation.
			materialAttenuation = Vector::pairwiseProduct(material.getKR(), attenuation);
		}
		else //If the sphere index is not valid, then the t value must belong to a model face.
		{
			//Retrieve the model face's surface normal.
			surfaceNormal = models[best.modelIndex].getFaceVertices()[best.faceIndex].getSurfaceNormal();
			
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
			materialAttenuation = Vector::pairwiseProduct(Vector(1.0, 1.0, 1.0), attenuation);
		}
		
		//Apply ambient lighting to the overall color of the pixel.
		Vector color = Vector::pairwiseProduct(material.getKA(), ambientLight);
		
		//For every point light in the scene...
		for (unsigned int l = 0; l < lights.size(); l++)
		{
			//Retrieve the point light's position.
			Vector toLight = lights[l].getPoint();
			//Calculate and normalize the vector pointing to the light.
			toLight = toLight - pointOfIntersection;
			toLight = toLight.normalize();
			//Create a ray meant for determining shadows.
			Ray shadowRay = Ray(pointOfIntersection, toLight);
			//Calculate and normalize a vector pointing to the camera.
			Vector toCamera = pRay.getPoint();
			toCamera =  toCamera - pointOfIntersection;
			toCamera = toCamera.normalize();
			
			//If the surface normal is pointing in the opposite direction, then...
			if (Vector::dotProduct(toCamera, surfaceNormal) < 0.0)
			{
				//Reverse its direction.
				surfaceNormal = -1.0 * surfaceNormal;
			}
			
			//Initialize the best shadow objects.
			bestPick shadowBest = bestPick();
			//Vectors for diffuse and surface color.
			Vector diffuseEmission, surfaceEmission;
			
			//If the shadow ray intersects with an object, then...
			if (inScene(shadowRay, spheres, models, shadowBest, best.faceIndex, best.sphereIndex))
			{
				Vector h = toLight - D;
				h = h.normalize();
				
				double nDotl = fmax(0.0, Vector::dotProduct(surfaceNormal, toLight));
				double nDoth = Vector::dotProduct(surfaceNormal, h);
				
				diffuseEmission = Vector::pairwiseProduct(material.getKD(), lights[l].getEmission());
				diffuseEmission = nDotl * diffuseEmission;
				color = color - diffuseEmission;
				
				surfaceEmission = Vector::pairwiseProduct(material.getKS(), lights[l].getEmission());
				surfaceEmission = pow(nDoth, material.getNS()) * surfaceEmission;
				color = color - surfaceEmission;
			}
			
			//If the light is pointing in the correct general area, then...
			if (Vector::dotProduct(toLight, surfaceNormal) > 0.0)
			{
				//Apply diffuse lighting.
				diffuseEmission = Vector::pairwiseProduct(material.getKD(), lights[l].getEmission());
				diffuseEmission = Vector::dotProduct(toLight, surfaceNormal) * diffuseEmission;
				//Apply the diffuse lighting to the accumulated color.
				color = color + diffuseEmission;
				
				//Apply specular lighting.
				Vector specularReflection = ((2 * Vector::dotProduct(toLight, surfaceNormal)) * surfaceNormal);
				specularReflection = specularReflection - toLight;
				surfaceEmission = Vector::pairwiseProduct(material.getKS(), lights[l].getEmission());
				surfaceEmission = pow(Vector::dotProduct(toCamera, specularReflection), material.getNS()) * surfaceEmission;
				//Apply the specular lighting to the accumulated color.
				color = color + surfaceEmission;
			}
		}
		
		//Apply light degeneration.
		Vector degeneration = Vector::pairwiseProduct(color, attenuation);
		degeneration = Vector::pairwiseProduct(degeneration, material.getKO());
		accumulation = accumulation + degeneration;
		
		//If the recursion level is greater than 0, then...
		if (level > 0)
		{
			//A separate vector for color accumulation.
			Vector flec = Vector();
			//Create a ray for reflecting light.
			Vector reflectionU = 2.0 * Vector::dotProduct(surfaceNormal, invertedD) * surfaceNormal;
			reflectionU = reflectionU - invertedD;
			Ray pRayReflection = Ray(pointOfIntersection, reflectionU);
			//Recursive call using the new color accumulation vector and the reflecting ray.
			recursiveTrace(pRayReflection, spheres, models, flec, materialAttenuation, level - 1, best.faceIndex, best.sphereIndex);
			//Apply attenuation.
			degeneration = Vector::pairwiseProduct(flec, attenuation);
			degeneration = Vector::pairwiseProduct(degeneration, material.getKO());
			//Add this round of color accumulation to the overall total.
			accumulation = accumulation + degeneration;
		}
		
		//If the recursion level is greater than 0, the material properties allow refraction, and a sphere is the intersected object, 
		//then...
		if (level > 0 && (material.getKO().getX() + material.getKO().getY() + material.getKO().getZ()) < 3.0 && best.sphereIndex != numeric_limits<unsigned int>::max())
		{
			//Create an exit ray for refraction.
			Ray exitRay = createRefractionExitRay(spheres[best.sphereIndex].getCenter(), invertedD, pointOfIntersection, 
												  material.getETA());
			
			//If the direction vector of  the exit ray is valid, then...
			if (exitRay.getVector().getX() != 0.0 || exitRay.getVector().getY() != 0.0 || exitRay.getVector().getZ() != 0.0)
			{
				//Another new vector for color accumulation.
				Vector through = Vector();
				//Inverse vector for the material's refraction properties.
				Vector oneVector = Vector(1.0, 1.0, 1.0);
				Vector Ko = material.getKO();
				Vector inverseKO = oneVector - Ko;
				//Recursive call using the exit ray and the new color accumulation vector.
				recursiveTrace(exitRay, spheres, models, through, materialAttenuation, level - 1, best.faceIndex, best.sphereIndex);
				//Apply attenuation to the color accumulation.
				degeneration = Vector::pairwiseProduct(through, attenuation);
				degeneration = Vector::pairwiseProduct(degeneration, inverseKO);
				//Add this round of color accumulation to the overall total.
				accumulation = accumulation + degeneration;
			}
		}
	}
}

//Method Summary: A method that determines if a list of models and spheres intersect with the provided ray.
//Preconditions: A ray to be shot into the scene, a list of spheres, a list of models, a best pick structure for the closest intersection,
//and indecies for the last intersected sphere and model.
//Postconditions: Returns a true or false value indicating an intersect, and modifies the best pick structure with the closest 
//intersection.
bool Camera::inScene(Ray &pRay, vector<Sphere> &spheres, vector<Model> &models, bestPick &best, unsigned int lastFaceIndex, unsigned int lastSphereIndex)
{
	//Note: The smaller the t value, the closer the intersection. A 0 t value indicates no intersection.
	//tS: Closest sphere intersection value.
	//tT: Closest model face intersection. 
	//tSmallestS: Smallest of the sphere t values.
	//tSmallestT: Smallest of the model face t values.
	double tS = 0.0, tT = 0.0, tSmallestS = numeric_limits<double>::max(), tSmallestT = numeric_limits<double>::max();
	
	//For every sphere in the list...
	for (unsigned int i = 0; i < spheres.size(); i++)
	{
		//Is this sphere the same as the last intersection?
		if (i != lastSphereIndex)
		{
			//Does this sphere intersect with the provided ray?
			if (spheres[i].intersect(pRay, tS))
			{	
				//Is the newly attained sphere t value smaller than the currently smallest sphere t value?
				if (tS < tSmallestS)
				{
					//Set the smallest sphere t value to the newly attained sphere t value.
					tSmallestS = tS;
					//Set the current closest sphere intersection index to this one.
					best.sphereIndex = i;
				}
			}
		}
	}
	
	//For every model in the list...
	for (unsigned int i = 0; i < models.size(); i++)
	{
		//For every face vertex in the current model...
		for (unsigned int j = 0; j < models[i].getFaceVertices().size(); j++)
		{
			//Is this face vertex index the same as the last intersected face vertex index?
			if (j != lastFaceIndex)
			{
				//Does this face vertext intersect with the provided ray?
				if (models[i].getFaceVertices()[j].intersect(pRay, tT))
				{	
					//Is the newly attained face vertex t value smaller than the currently smallest face vertex t value?
					if (tT < tSmallestT)
					{
						//Set the smallest face vertex t value to the newly attained one.
						tSmallestT = tT;
						//Set the closest intersected model to the current one.
						best.modelIndex = i;
						//Set the closest intersected face vertex to the current one.
						best.faceIndex = j;
					}			
				}
			}
		}
	}
	
	//Is the closest intersection value from a model face vertex or a sphere?
	if (tSmallestS < tSmallestT && tSmallestS != numeric_limits<double>::max())
	{
		//If it's from a sphere...
		//Set the closest intersection value to that of the closest sphere.
		best.t = tSmallestS;
		//Set the closest face vertex index to a non-valid value.
		best.faceIndex = numeric_limits<unsigned int>::max();
		//Return true, indicating an intersection.
		return true;
	}
	else if (tSmallestT != numeric_limits<double>::max())
	{
		//If it's from a model face vertex...
		//Set the closest intersection value to that of the closest model face vertex.
		best.t = tSmallestT;
		//Set the closest sphere index to a non-valid value.
		best.sphereIndex = numeric_limits<unsigned int>::max();
		//Return true, indicating an intersection.
		return true;
	}
	else //Otherwise...
	{
		//Set all best pick values to non-valid values.
		best.t = 0.0;
		best.faceIndex = numeric_limits<unsigned int>::max();
		best.sphereIndex = numeric_limits<unsigned int>::max();
		//Return false, indicating no intersection took place.
		return false;
	}
}

//Method Summary: Creates a refraction ray for proper refraction computation.
//Preconditions: The center of the sphere, the vector to the camera, the point of intersection, and the refraction index of the material.
//Postconditions: Returns a complete refraction ray.
Ray Camera::createRefractionExitRay(const Vector &center, const Vector &W, const Vector &pointOfIntersection, const double &etai)
{
	//w: Vector pointing toward the camera.
	//c: The center of the sphere.
	//point: Point of intersection.
	//surfaceNormal: Vector perpindicular to the surface plane.
	Vector w = W, c = center, point = pointOfIntersection, surfaceNormal = point - c;
	//Normalize the surface normal.
	surfaceNormal = surfaceNormal.normalize();
	//Displaced directional vector after passing through the object at the entrance point.
	Vector T1 = createRefractionTVector(w, surfaceNormal, 1.0, etai);
	
	//If the T1 vector is not valid, then...
	if (T1.getX() == 0.0 && T1.getY() == 0.0 && T1.getZ() == 0.0)
	{
		//Return a default ray object.
		return Ray();
	}
	
	//Surface normal with an inverted direction.
	Vector invertedNormal = c - point;
	//Exit point of the refraction ray.
	Vector exitPointPart1 = 2.0 * Vector::dotProduct(invertedNormal, T1) * T1; 
	Vector exitPoint = exitPointPart1 + point;
	
	//Surface normal with the exit point as its base.
	Vector exitSurfaceNormal = c - exitPoint;
	//Normalize the exit surface normal.
	exitSurfaceNormal = exitSurfaceNormal.normalize();
	
	//Invert the direction of the T1 vector.
	Vector invertedT1 = -1.0 * T1;
	//T2: Displaced directional vector after the exiting the object through the exit point.
	Vector T2 = createRefractionTVector(invertedT1, exitSurfaceNormal, etai, 1.0);
	
	//Return the refraction ray with the exit point as the point and the T2 vector as the directional vector.
	return Ray(exitPoint, T2);
}

//Method Summary: Helper function to the createRefractionExitRay method that creates the displaced directional vector.
//Preconditions: The vector pointing toward the camera, the surface normal vector, the refraction index of the entrance point material, and the
//refraction index of the exit point material.
//Postconditions: The displaced directional vector is returned.
Vector Camera::createRefractionTVector(const Vector &W, const Vector &N, const double &eta1, const double &eta2)
{
	//w: Vector pointing toward the camera.
	//n: Surface normal vector.
	//eta1copy: Refraction index of the entrance point's material.
	//eta2copy: Refraction index of the exit point's material.
	//etar: Ratio of the entrance and exit refraction material.
	//alpha: Inverse of the refraction index ratio.
	//wDotN: Dot product of the w and n vectors.
	//disc: Discriminant required to form the beta variable.
	Vector w = W, n = N;
	double eta1copy = eta1, eta2copy = eta2;
	double etar = eta1copy / eta2copy;
	double alpha = -1.0 * etar;
	double wDotN = Vector::dotProduct(w, n);
	double disc = (etar * etar) * ((wDotN * wDotN) - 1) + 1;
	
	//If the discriminant is less than 0, then...
	if (disc < 0.0)
	{
		//Return a default vector.
		return Vector();
	}
	
	//beta: Scalar of the surface normal.
	//Tpart1: w scaled by alpha that forms the first part of the T vector.
	//Tpart2: n scaled by beta that forms the second part of the T vector.
	//T: The displaced directional vector that is the sum of the scaled w and n vectors.
	double beta = (etar * wDotN) - sqrt(disc);
	Vector Tpart1 = alpha * w;
	Vector Tpart2 = beta * n;
	Vector T = Tpart1 + Tpart2;
	//Normalize the T vector.
	T = T.normalize();
	
	//Return the displaced directional vector.
	return T;
}
