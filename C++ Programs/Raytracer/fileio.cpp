/* Author: coleman7245
 * File: C++ file for FileIO.
 * Last Update: 2/18/2019
 * File Summary: A collection methods for both obtaining graphics data from a driver file and writing PPM files. 
 */

#include "fileio.h"

//Method Summary: Determines the number of models in the driver file.
//Precondtions: A reference to an open ifstream object.
//Postconditions: Returns an unsigned integer representing the number of models. 
unsigned int numOfModels(ifstream &fileReader)
{
	//numOfModels: Number of models in the driver file.
	//s: The string variable that captures the next input. Afterward, the string is checked to see if the input is for a model or 
	//otherwise.
	unsigned int numOfModels = 0;
	string s = "";
	
	//While the file reader hasn't reached the end of the file...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> s;
		
		//If the string reads as "model,", then...
		if (s.compare("model") == 0)
		{
			//Increment the model count.
			numOfModels++;
			//Replace the string input with an empty string.
			s = "";
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

//Method Summary: Determines the number of spheres in the driver file.
//Precondtions: A reference to an open ifstream object.
//Postconditions: Returns an unsigned integer representing the number of spheres.
unsigned int numOfSpheres(ifstream &fileReader)
{
	//numOfSpheres: The count of spheres in the driver file.
	//s: The string variable that captures the next input. Afterward, the string is checked to see if the input is for a sphere or 
	//otherwise.
	unsigned int numOfSpheres = 0;
	string s = "";
	
	//While the file reader is not at the end of the file...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> s;
		
		//If the string represents a sphere, then...
		if (s.compare("sphere") == 0)
		{
			//Increment the sphere count.
			numOfSpheres++;
			//Replace the current string input with an empty string.
			s = "";
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
bool readDriverData(const char *driverFilename, vector< vector<double> > &axis, vector<double> &degrees, vector<double> &scales, 
	vector< vector<double> > &translations, vector<string> &modelFilenames, vector<Sphere> &spheres, Camera &camera, unsigned int &recursionLevel)
{
	//Open the driver file with the filename.
	ifstream fileReader = ifstream(driverFilename, ifstream::in);
	
	//If the driver file failed to open, then...
	if (!fileReader.good())
	{
		//Display an error message.
		cerr << "Failed to open file with given name." << endl;
		//Close the file.
		fileReader.close();
		//Return false, indicating failure.
		return false;
	}
	
	//numOfM: The number of models within the scene.
	//linePos: Position of the file line.
	//numOfS: The number of spheres within the scene.
	//sPos: Position in the list of spheres.
	//distance: The viewing distance of the camera.
	//
	unsigned int numOfM = numOfModels(fileReader), linePos = 0, numOfS = numOfSpheres(fileReader), sPos = 0;
	double distance = 0.0, far = 0.0, top = 0.0, bottom = 0.0, left = 0.0, right = 0.0, width = 0.0, height = 0.0,
	tempX = 0.0, tempY = 0.0, tempZ = 0.0, tempW = 0.0, radius = 0.0, eta = 0.0, phongConstant = 0.0;
	Vector lookAtPoint, eyePoint, up, center, ka, kd, kr, ks, ko = Vector(0.5, 0.5, 0.5), ambientLight, pointL, emissionL;
	axis = vector< vector<double> >(numOfM);
	degrees = vector<double>(numOfM);
	scales = vector<double>(numOfM);
	translations = vector< vector<double> >(numOfM);
	modelFilenames = vector<string>(numOfM);
	spheres = vector<Sphere>(numOfS);
	vector<Light> lights = vector<Light>();
	string filename = "", s = "";
	
	for (unsigned int i = 0; i < numOfM; i++)
	{
		axis[i] = vector<double>(3);
		translations[i] = vector<double>(3);
	}
	
	while (!fileReader.eof())
	{
		fileReader >> s;
		
		//cout << s << endl;
		
		if (s.compare("recursionLevel") == 0)
		{
			fileReader >> recursionLevel;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
		}
		else if (s.compare("ambient") == 0)
		{
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			ambientLight = Vector(tempX, tempY, tempZ);
		}
		else if (s.compare("light") == 0)
		{
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			pointL = Vector(tempX, tempY, tempZ);
			
			fileReader >> tempW;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			emissionL = Vector(tempX, tempY, tempZ);
			
			lights.push_back(Light(pointL, emissionL, tempW));
		}
		else if (s.compare("model") == 0)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				fileReader >> axis[linePos][i];
				
				if (fileReader.fail() || fileReader.bad())
				{
					if (fileReader.eof())
					{
						break;
					}
					
					cerr << "Error encounter while parsing file.\n";
					cerr << "Failed to read axis double!" << endl;
					fileReader.close();
					return false;
				}
			}
			
			fileReader >> degrees[linePos];
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				cerr << "Failed to read degree double!" << endl;
				fileReader.close();
				return false;
			}
			
			fileReader >> scales[linePos];
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			for (unsigned int i = 0; i < 3; i++)
			{
				fileReader >> translations[linePos][i];
				
				if (fileReader.fail() || fileReader.bad())
				{
					if (fileReader.eof())
					{
						break;
					}
					
					cerr << "Error encounter while parsing file.\n";
					fileReader.close();
					return false;
				}
			}
			
			fileReader >> filename;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			modelFilenames[linePos] = filename;
			linePos++;
		}
		else if (s.compare("eye") == 0)
		{
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			eyePoint = Vector(tempX, tempY, tempZ);
		}
		else if (s.compare("look") == 0)
		{
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			lookAtPoint = Vector(tempX, tempY, tempZ);
		}
		else if (s.compare("up") == 0)
		{
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			up = Vector(tempX, tempY, tempZ);
		}
		else if (s.compare("d") == 0)
		{
			fileReader >> distance;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
		}
		else if (s.compare("bounds") == 0)
		{
			fileReader >> left;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> bottom;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> right;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> top;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
		}
		else if (s.compare("res") == 0)
		{
			fileReader >> width;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> height;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
		}
		else if (s.compare("sphere") == 0)
		{
			fileReader >> tempX;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempY;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> tempZ;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			center = Vector(tempX, tempY, tempZ);
			
			fileReader >> radius;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
				
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			unsigned int i = 0;
			
			while (i < 5)
			{
				fileReader >> tempX;
				
				if (fileReader.fail() || fileReader.bad())
				{
					if (fileReader.eof())
					{
						break;
					}
					
					cerr << "Error encounter while parsing file.\n";
					fileReader.close();
					return false;
				}
				
				fileReader >> tempY;
				
				if (fileReader.fail() || fileReader.bad())
				{
					if (fileReader.eof())
					{
						break;
					}
					
					cerr << "Error encounter while parsing file.\n";
					fileReader.close();
					return false;
				}
				
				fileReader >> tempZ;
				
				switch (i)
				{
					case 0: 
						ka = Vector(tempX, tempY, tempZ);
						break;
					case 1:
						kd = Vector(tempX, tempY, tempZ);
						break;
					case 2:
						ks = Vector(tempX, tempY, tempZ);
						break;
					case 3:
						kr = Vector(tempX, tempY, tempZ);
						break;
					default:
						ko = Vector(tempX, tempY, tempZ);
						break;
				}
				
				i++;
			}
			
			fileReader >> phongConstant;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
					
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			fileReader >> eta;
			
			if (fileReader.fail() || fileReader.bad())
			{
				if (fileReader.eof())
				{
					break;
				}
					
				cerr << "Error encounter while parsing file.\n";
				fileReader.close();
				return false;
			}
			
			spheres[sPos] = Sphere(center, radius, Material(ka, kd, ko, kr, ks, 0, 0, phongConstant, eta));
			sPos++;
		}
		
		fileReader.ignore(256, '\n');
		s = "";
	}
	
	camera = Camera(lookAtPoint, eyePoint, distance, -distance, far, top, bottom, left, right, width, height, up, ambientLight);
	
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		camera.addLight(lights[i]);
	}
	
	fileReader.close();
	
	return true;
}

//Method Summary:
//Precondtions:
//Postconditions:
bool writePPMFile(const char *filename, const vector<vector <Vector> > &colors)
{
	ofstream fileWriter = ofstream(filename, ofstream::out);
	
	if (!fileWriter.good())
	{
		cerr << "Failed to open file with the given name." << endl;
		fileWriter.close();
		return false;
	}
	
	fileWriter << "P3\n" <<colors[0].size() << " " << colors.size() << " " << 255 << endl;
	
	for (unsigned int i = 0; i < colors.size(); i++)
	{
		for (unsigned int j = 0; j < colors[i].size(); j++)
		{
			if (j != 0 && (unsigned int)round(colors[i][j].getX()) >= 100)
			{
				fileWriter << " ";
			}
			else if (j != 0 && (unsigned int)round(colors[i][j].getX()) >= 10)
			{
				fileWriter << "  ";
			}
			else if (j != 0)
			{
				fileWriter << "   ";
			}
			
			fileWriter << (unsigned int)round(colors[i][j].getX());
			
			if ((unsigned int)round(colors[i][j].getY()) >= 100)
			{
				fileWriter << " ";
			}
			else if ((unsigned int)round(colors[i][j].getY()) >= 10)
			{
				fileWriter << "  ";
			}
			else
			{
				fileWriter << "   ";
			}
			
			fileWriter << (unsigned int)round(colors[i][j].getY());
			
			if ((unsigned int)round(colors[i][j].getZ()) >= 100)
			{
				fileWriter << " ";
			}
			else if ((unsigned int)round(colors[i][j].getZ()) >= 10)
			{
				fileWriter << "  ";
			}
			else
			{
				fileWriter << "   ";
			}
			
			fileWriter << (unsigned int)round(colors[i][j].getZ());
		}
		
		fileWriter << endl;
	}
	
	fileWriter.close();
	
	return true;
}
