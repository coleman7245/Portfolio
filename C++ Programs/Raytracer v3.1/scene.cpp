/* Author: coleman7245
 * File: C++ file for Scene.
 * Last Update: 2/25/2019
 * File Summary: The Scene class contains the main means of creating and rendering a scene. It contains all the objects necessary: Models, 
 * a Camera, Spheres, Lights, and the ambient light Vector. It also contains methods to retrieve the scene data from a driver, and write them as a PPM file.
 */

//Include the header file.
#include "scene.h"

//Method Summary: Default constructor
Scene::Scene() : models(std::vector<Model>()), spheres(std::vector<Sphere>()), lights(std::vector<Light>()), ambientLight(Vector<double>()), 
	camera(Camera()), initialized(false) {}

//Method Summary: Constructor using input from the provided parameters.
Scene::Scene(const char *driverFilename) 
{
	//Try to retrieve the scene data. 
	initialized = readDriverData(driverFilename);
	
	//If successful in retrieving the scene data, then...
	if (initialized)
	{	
		//Create the scene.
		constructScene();
	}
	else //Otherwise...
	{
		//Set this to the default constructor.
		*this = Scene();
	}
}

//Method Summary: Deconstructor
Scene::~Scene() {}

//Method Summary: Copy contructor
Scene & Scene::operator=(const Scene &rhs)
{
	//If the reference of this and the parameter are NOT one in the same, then...
	if (this != &rhs)
	{
		//Copy all class attribultes to this object.
		models = rhs.getModels();
		spheres = rhs.getSpheres();
		lights = rhs.getLights();
		ambientLight = rhs.getAmbientLight();
		camera = rhs.getCamera();
		initialized = rhs.isInitialized();
		constructScene();
	}
	
	//Return this object.
	return *this;
}

//Method Summary: Constructs the scene primarily through the camera attribute.
void Scene::constructScene()
{
	//attenuation: Color degradation of a single pixel. Not used for this implementation and set to the default of 1.0.
	Vector<double> attenuation = Vector<double>(1.0, 1.0, 1.0);
	//Sets the color of all pixels in the scene using a recursive raytracer.
	camera.setColors(spheres, models, attenuation, lights, ambientLight);
}

//Method Summary: Determines the number of models in the driver file.
//Precondtions: A reference to an open ifstream object.
//Postconditions: Returns an unsigned integer representing the number of models. 
unsigned int Scene::numberOfModels(std::ifstream &fileReader)
{
	//numOfModels: Number of models in the driver file.
	//next: The string variable that captures the next input. Afterward, the string is checked to see if the input is for a model or 
	//otherwise.
	unsigned int numOfModels = 0;
	std::string next = "";
	
	//While the file reader hasn't reached the end of the file...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> next;
		
		//If the file input failed, then...
		if (!fileReader.good())
		{
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Display an error message specifying the failure.
			std::cerr << "Error encounter while parsing file.\n";
			//Close the file.
			fileReader.close();
			
			//Return false, indicating failure.
			return false;
		}
		
		//If the string reads as "model,", then...
		if (next.compare("model") == 0)
		{
			//Increment the model count.
			numOfModels++;
			//Replace the string input with an empty string.
			next = "";
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
	}
	
	//Clear the current state of the file reader.
	fileReader.clear();
	//Return the file reader to the beginning of the file.
	fileReader.seekg(0, fileReader.beg);
	
	//Return the model count.
	return numOfModels;
}

//Method Summary: Counts the number of lights in a driver.
//Preconditions: A reference to an open ifstream object.
//Postconditions: Returns an unsigned integer representing the number of lights.
unsigned int Scene::numberOfLights(std::ifstream &fileReader)
{
	//numOfModels: Number of lights in the driver file.
	//next: The string variable that captures the next input. Afterward, the string is checked to see if the input is for a model or 
	//otherwise.
	unsigned int numOfLights = 0;
	std::string next = "";
	
	//While the file reader hasn't reached the end of the file...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> next;
		
		//If the file input read failed, then...
		if (!fileReader.good())
		{
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Displays the errors message specifying the type of failure.
			std::cerr << "Error encounter while parsing file.\n";
			//Close the file.
			fileReader.close();
			
			//Return false, indicating failure.
			return false;
		}
		
		//If the string reads as "light,", then...
		if (next.compare("light") == 0)
		{
			//Increment the light count.
			numOfLights++;
			//Replace the string input with an empty string.
			next = "";
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
	}
	
	//Clear the current state of the file reader.
	fileReader.clear();
	//Return the file reader to the beginning of the file.
	fileReader.seekg(0, fileReader.beg);
	
	//Return the light count.
	return numOfLights;
}

//Method Summary: Determines the number of spheres in the driver file.
//Precondtions: A reference to an open ifstream object.
//Postconditions: Returns an unsigned integer representing the number of spheres.
unsigned int Scene::numberOfSpheres(std::ifstream &fileReader)
{
	//numOfSpheres: The count of spheres in the driver file.
	//next: The string variable that captures the next input. Afterward, the string is checked to see if the input is for a sphere.
	unsigned int numOfSpheres = 0;
	std::string next = "";
	
	//While the file reader is not at the end of the file...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> next;
		
		//If the file read failed, then...
		if (!fileReader.good())
		{
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Display an error message specifying the type of failure.	
			std::cerr << "Error encounter while parsing file.\n";
			//Close the file.
			fileReader.close();
			
			//Return false, indicating failure.
			return false;
		}
		
		//If the string represents a "sphere", then...
		if (next.compare("sphere") == 0)
		{
			//Increment the sphere count.
			numOfSpheres++;
			//Replace the current string input with an empty string.
			next = "";
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
	}
	
	//Clear the end of file status for the file reader.
	fileReader.clear();
	//Return the input pointer to the beginning of the file.
	fileReader.seekg(0, fileReader.beg);
	
	//Return the sphere count.
	return numOfSpheres;
}

//Method Summary: Reads information from the driver file and feeds it to the appropriate objects.
//Precondtions: The driver filename, the axis of the rotation, the degree of the rotation, the scale axis, the translation axis, the list 
//of model filenames, the list of spheres, the camera, and the recursion level.
//Postconditions: Returns true if all file reads were successful, false otherwise.
bool Scene::readDriverData(const char *driverFilename)
{
	//Open the driver file with the filename parameter.
	std::ifstream fileReader = std::ifstream(driverFilename, std::ifstream::in);
	
	//If the driver file failed to open, then...
	if (!fileReader.good())
	{
		//Display an error message specifying the type of failure.
		std::cerr << "Failed to open file with given name." << std::endl;
		//Close the file.
		fileReader.close();
		//Return false, indicating failure.
		return false;
	}
	
	//numOfM: The number of models within the scene.
	//modelPos: The current position within the vector of Models.
	//linePos: The current position of the file line.
	//numOfS: The number of spheres within the scene.
	//sPos: The current position within the vector of spheres.
	//numOfL: The number of lights within a scene.
	//recursionLevel: The recursion level of the scene.
	//distance: The viewing distance of the camera.
	//far: The maximum viewing length of the camera.
	//top: The vertical upper bounds of the viewing plane.
	//bottom: The vertical lower bounds of the viewing plane.
	//left: The horizontal upper bounds of the viewing plane.
	//right: The horizontal lower bounds of the viewing plane.
	//width: The maximum horizontal resolution.
	//height: The maximum vertical resolution.
	//degree: The degree needed to rotate the model's vertices.
	//scale: The value needed to scale the model's vertices.
	//tempX, tempY, tempZ: Temporary variables to hold Vector values.
	//tempW: The light value.
	//radius: The distance between the center of a sphere and its outermost point.
	//eta: The refraction index.
	//phongConstant: The reflection index.
	//lookAtPoint: The focus point of the camera.
	//eyePoint: The eye of the camera.
	//up: The driver-defined positive vertical vector in the scene.
	//center: The center poiint of the sphere.
	//ka: The ambient lighting vector.
	//kd: The diffuse lighting vector.
	//kr: Attenuation vector.
	//ks: The surface lighting vector.
	//ko: The refraction lighting vector.
	//pointL: A light's point of origin.
	//emissionL: A light's emission vector.
	//translation: The translation of a model's vertices.
	//rotation: The rotation of a model's vertices.
	//filename: The filename of a model.
	//next: The next read input.
	unsigned int numOfM = numberOfModels(fileReader);
	unsigned int modelPos = 0;
	unsigned int lightPos = 0;
	unsigned int numOfS = numberOfSpheres(fileReader);
	unsigned int sPos = 0;
	unsigned int numOfL = numberOfLights(fileReader);
	int recursionLevel = 0;
	double distance = 0.0;
	double far = 0.0;
	double top = 0.0;
	double bottom = 0.0;
	double left = 0.0;
	double right = 0.0;
	double width = 0.0;
	double height = 0.0;
	double degree = 0.0;
	double scale = 0.0;
	double tempX = 0.0;
	double tempY = 0.0; 
	double tempZ = 0.0;
	double tempW = 0.0;
	double radius = 0.0;
	double eta = 0.0;
	double phongConstant = 0.0;
	Vector<double> lookAtPoint;
	Vector<double> eyePoint;
	Vector<double> up;
	Vector<double> center;
	Vector<double> ka;
	Vector<double> kd;
	Vector<double> kr;
	Vector<double> ks;
	Vector<double> ko = Vector<double>(0.5, 0.5, 0.5);
	Vector<double> pointL;
	Vector<double> emissionL;
	Vector<double> translation;
	Vector<double> rotation;
	std::string filename = "";
	std::string next = "";
	
	//Resize the vectors of the models, spheres, and light.
	spheres.resize(numOfS);
	models.resize(numOfM);
	lights.resize(numOfL);
	
	//While the driver file is not at the end...
	while (!fileReader.eof())
	{
		//Read the next driver file input
		fileReader >> next;
		
		//If the file read failed, then...
		if (!fileReader.good())
		{
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
				
			//Display an error message specifying the failure.	
			std::cerr << "Error encounter while parsing file.\n";
			//Close the file.
			fileReader.close();
			
			//Return false, indicating failure.
			return false;
		}
		
		if (next.compare("recursionLevel") == 0) //If the next input is for the recursion level, then...
		{
			//Read the recursion level.
			fileReader >> recursionLevel;
			
			//If the file read failed, then...
			if (!fileReader.good())
			{
				//If the end of the file has been reached, then...
				if (fileReader.eof())
				{
					//Break out of the loop.
					break;
				}
				
				//Display an error message specifying the failure.
				std::cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				
				//Return false, indicating failure.
				return false;
			}
		}
		else if (next.compare("ambient") == 0) //If the next input read is for the ambient light vector, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Initializde the ambient light vector with the collected values.
			ambientLight = Vector<double>(tempX, tempY, tempZ);
		}
		else if (next.compare("light") == 0) //If the next input read is for lights, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 7; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else if (i == 2) //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
				else if (i == 3) //Fourth read:
				{
					//Set the point vector after the third read.
					pointL = Vector<double>(tempX, tempY, tempZ);
					//Read the light's W value.
					fileReader >> tempW;
				}
				else if (i == 4) //Fifth read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 5) //Sixth read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else //Seventh read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Set the emission vector with the collected values.
			emissionL = Vector<double>(tempX, tempY, tempZ);
			//Set the a light in the vector with the collected vectors and values.
			lights[lightPos] = Light(pointL, emissionL, tempW);
			//Increment the light position.
			lightPos++;
		}
		else if (next.compare("model") == 0) //If next input read is for a model, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 9; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					 //Read the second vector value.
					fileReader >> tempY;
				}
				else if (i == 2) //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
				else if (i == 3) //Fourth value:
				{
					//Set the rotation vector with the values collected after the third input read.
					rotation = Vector<double>(tempX, tempY, tempZ);
					//Read the degree value.
					fileReader >> degree;
				}
				else if (i == 4) //Fifth read:
				{
					//Read the scale value.
					fileReader >> scale;
				}
				else if (i == 5) //Sixth read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 6) //Seventh read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else if (i == 7) //Eighth read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
				else //Ninth read:
				{
					//Set the translation vector with the collected values after the eighth input read.
					translation = Vector<double>(tempX, tempY, tempZ);
					//Read the model filename.
					fileReader >> filename;
				}
				
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			models[modelPos] = Model(filename.c_str(), translation, rotation, scale, degree);
			modelPos++;
		}
		else if (next.compare("eye") == 0) //If the next input read is for the eye of the camera, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Set the eye point of the camera with the collected values.
			eyePoint = Vector<double>(tempX, tempY, tempZ);
		}
		else if (next.compare("look") == 0) //If the next input read is for the focal point of the camera, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Set the focal point vector with the collected values.
			lookAtPoint = Vector<double>(tempX, tempY, tempZ);
		}
		else if (next.compare("up") == 0) //If the next input read is for the camera's up value, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Set the camera's up vector with the collected values.
			up = Vector<double>(tempX, tempY, tempZ);
		}
		else if (next.compare("d") == 0) //If the next input read is for the view plane's distance value, then...
		{
			//Read the view plane's distance value.
			fileReader >> distance;
			
			//If the file read failed, then...
			if (!fileReader.good())
			{
				//If the end of the file has been reached, then...
				if (fileReader.eof())
				{
					//Break out of the loop.
					break;
				}
				
				//Display an error message specifying the failure.
				std::cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				
				//Return false, indicating failure.
				return false;
			}
		}
		else if (next.compare("bounds") == 0) //If the next input read is for the view plane's bounds, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 4; i++)
			{
				if (i == 0) //First read:
				{
					//Read the view plane's left value.
					fileReader >> left;
				}
				else if (i == 1) //Second read:
				{
					//Read the view plane's bottom value.
					fileReader >> bottom;
				}
				else if (i == 2) //Third read:
				{
					//Read the view plane's right value.
					fileReader >> right;
				}
				else //Fourth read:
				{
					//Read the view plane's top value.
					fileReader >> top;
				}
				
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
		}
		else if (next.compare("res") == 0) //If the next input read is for the camera's resolution, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 2; i++)
			{
				if (i == 0) //First read:
				{
					//Read the camera's width value.
					fileReader >> width;
				}
				else //Second read:
				{
					//Read the camera's height value.
					fileReader >> height;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
		}
		else if (next.compare("sphere") == 0) //If the next input read is for a sphere, then...
		{
			//For every value in the line...
			for (unsigned int i = 0; i < 4; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vector value.
					fileReader >> tempY;
				}
				else if (i == 2) //Third read:
				{
					//Read the third vector value.
					fileReader >> tempZ;
				}
				else //Fourth read:
				{
					//Set the center vector with the values collected after the third input read.
					center = Vector<double>(tempX, tempY, tempZ);
					//Read the sphere's radius value.
					fileReader >> radius;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Represents which vector is currently being set.
			unsigned int vec = 0;
			
			//While the vector count is less than five...
			while (vec < 5)
			{
				//For every value in the line...
				for (unsigned int i = 0; i < 3; i++)
				{
					if (i == 0) //First read:
					{
						//Read the first vector value.
						fileReader >> tempX;
					}
					else if (i == 1) //Second read:
					{
						//Read the second vector value.
						fileReader >> tempY;
					}
					else //Third read:
					{
						//Read the third vector value.
						fileReader >> tempZ;
					}
				
					//If the file read failed, then...
					if (!fileReader.good())
					{
						//If the end of the file has been reached, then...
						if (fileReader.eof())
						{
							//Break out of the loop.
							break;
						}
						
						//Display an error message specifying the failure.
						std::cerr << "Error encounter while parsing file.\n";
						//Close the file.
						fileReader.close();
						
						//Return false, indicating failure.
						return false;
					}
				}
				
				//If the end of the file has been reached, then...
				if (fileReader.eof())
				{
					//Break out of the loop.
					break;
				}
				
				switch (vec) //Check the value of the vector count.
				{
					//If zero, then...
					case 0:
						//Set the ambient light material vector.
						ka = Vector<double>(tempX, tempY, tempZ);
						//Break out of the loop.
						break;
					case 1:
						//Set the diffuse material vector.
						kd = Vector<double>(tempX, tempY, tempZ);
						//Break out of the loop.
						break;
					case 2:
						//Set the specular material vector.
						ks = Vector<double>(tempX, tempY, tempZ);
						//Break out of the loop.
						break;
					case 3:
						//Set the attenuation material vector.
						kr = Vector<double>(tempX, tempY, tempZ);
						//Break out of the loop.
						break;
					default:
						//Set the refraction material vector.
						ko = Vector<double>(tempX, tempY, tempZ);
						//Break out of the loop.
						break;
				}
				
				//Increment the vector count.
				vec++;
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//For every value in the line...
			for (unsigned int i = 0; i < 2; i++)
			{
				if (i == 0) //First read:
				{
					//Read the material's phong constant.
					fileReader >> phongConstant;
				}
				else //Second read:
				{
					//Read the material's refraction index.
					fileReader >> eta;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the end of the file has been reached, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message specifying the failure.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the end of the file has been reached, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Set the sphere within the vector to the sphere initialized with the collected values.
			spheres[sPos] = Sphere(center, radius, Material(ka, kd, ko, kr, ks, 0, 0, phongConstant, eta));
			//Increment the sphere count.
			sPos++;
		}
		
		//Move onto the next line.
		fileReader.ignore(256, '\n');
		//Reset the next input value to an empty string.
		next = "";
	}
	
	//Set the camera with the collected values.
	camera = Camera(lookAtPoint, eyePoint, ViewPlane(distance, -distance, far, top, bottom, left, right), width, height, recursionLevel, 
		up);
	
	//Close the file.
	fileReader.close();
	
	//Return true, indicating success.
	return true;
}

//Method Summary: Writes out the rendered scene as a PPM file.
//Precondtions: The filename of PPM file as a const char pointer.
//Postconditions: Returns true if the file write was successful, false otherwise.
bool Scene::writePPMFile(const char *ppmFilename)
{
	//Open the PPM file with the given filename.
	std::ofstream fileWriter = std::ofstream(ppmFilename, std::ofstream::out);
	
	//If the file failed to open, then...
	if (!fileWriter.good())
	{
		//Display an error message specifying the failure.
		std::cerr << "Failed to open file with the given name." << std::endl;
		//Close the file.
		fileWriter.close();
		
		//Return false, indicating failure.
		return false;
	}
	
	//Write the standard PPM file header.
	fileWriter << "P3\n" << camera.getWidthInt() << " " << camera.getHeightInt() << " " << 255 << std::endl;
	
	//For every color cooresponding to a pixel ray...
	//Note: The amount of spaces between values increase depending on the size of the value. This is implemented for better formatting.
	for (unsigned int px = 0; px < camera.getHeightInt(); px++)
	{
		for (unsigned int py = 0; py < camera.getWidthInt(); py++)
		{
			if (py != 0 && (unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getX()) >= 100)
			{
				//Write a space if the color is not at the beginning AND if the color value greater than or equal to 100.
				fileWriter << " ";
			}
			else if (py != 0 && (unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getX()) >= 10)
			{
				//Write two spaces if the color is not at the beginning AND if the color value greater than or equal to 10.
				fileWriter << "  ";
			}
			else if (py != 0)
			{
				//Write three spaces if the color is not at the beginning.
				fileWriter << "   ";
			}
			
			//Write the color value's red value.
			fileWriter << (unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getX());
			
			if ((unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getY()) >= 100)
			{
				//Write a space if the color is not at the beginning AND if the color value greater than or equal to 100.
				fileWriter << " ";
			}
			else if ((unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getY()) >= 10)
			{
				//Write two spaces if the color is not at the beginning AND if the color value greater than or equal to 10.
				fileWriter << "  ";
			}
			else
			{
				//Write three spaces if the color is not at the beginning.
				fileWriter << "   ";
			}
			
			//Write the color value's green value.
			fileWriter << (unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getY());
			
			if ((unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getZ()) >= 100)
			{
				//Write a space if the color is not at the beginning AND if the color value greater than or equal to 100.
				fileWriter << " ";
			}
			else if ((unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getZ()) >= 10)
			{
				//Write two spaces if the color is not at the beginning AND if the color value greater than or equal to 10.
				fileWriter << "  ";
			}
			else
			{
				//Write three spaces if the color is not at the beginning.
				fileWriter << "   ";
			}
			
			//Write the color value's blue value.
			fileWriter << (unsigned int)round(camera.getColors()[px * camera.getWidthInt() + py].getZ());
		}
		
		//Write the end of line value.
		fileWriter << std::endl;
	}
	
	//Close the file.
	fileWriter.close();
	
	//Return true, indicating success.
	return true;
}
