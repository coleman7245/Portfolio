/* Author: coleman7245
 * File: C++ Model class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The Model class stores information regarding the model rendered in the scene. Also contains methods for model 
 * transformations, reading wavefront .obj file information, and writing back that very information.
 */

#include "model.h"

//Method Summary: Default constructor
Model::Model() : vertices(std::vector< Vector<double> >()), faceIndices(std::vector<unsigned int>()), faces(std::vector<Triangle>()), 
	materials(std::vector<Material>()) {}

//Method Summary: Constructor using input from the provided parameters.
Model::Model(const char *filename, const Vector<double> &translationP, const Vector<double> &rotationP, 
	const double scaleP, const double degreesP)
{
	//If the model file read was successful, then...
	if (readModelData(filename))
	{
		//Transform the vertices.
		transformVertices(createTranslationMatrix(translationP), createRotationMatrix(rotationP, degreesP), createScaleMatrix(scaleP));
		//Create the faces.
		createFaces();
	}
	else //Otherwise...
	{
		//Set this object with the default Model constructor.
		*this = Model();
	}
}

//Method Summary: Deconstructor
Model::~Model() {}

//Method Summary: Copy constructor
//Preconditions: A const Model object reference.
//Postcondiitons: This Model object with is attributes copied from the parameter Model object.
Model & Model::operator=(const Model &rhs)
{
	//If the two references are NOT one in the same, then...
	if (this != &rhs)
	{
		//Copy the attributes of the parameter object.
		vertices = rhs.getVertices();
		faceIndices = rhs.getFaceIndices();
		faces = rhs.getFaces();
		materials = rhs.getMaterials();
	}
	
	//Return this Model object.
	return *this;
}

//Method Summary: Creates a rotation matrix to transformed a model's rotation.
//Precondtions: The axis of rotation and the number of degrees to rotate.
//Postconditions: Returns a rotation matrix.
Matrix Model::createRotationMatrix(const Vector<double> &rotation, const double degrees) const
{
	//RMz: Rotation around the z-axis.
	//RWw: General axes of rotation.
	//W: Axis of rotation.
	//U: Heuristic pick for an axis perdindicular to W.
	//V: Axis perpindicular to W and U.
	Matrix RMz = Matrix::identity(4);
	Matrix RMw = Matrix::identity(4);
	Vector<double> W = Vector<double>(rotation.getX(), rotation.getY(), rotation.getZ()).normalize();
	//W.normalize();
	Vector<double> U = Vector<double>(rotation.getX(), rotation.getY(), rotation.getZ()).normalize();
	//U.normalize();
	
	//Change the minimum value of U to 1.
	if (U.getX() < U.getY() && U.getX() < U.getZ())
	{
		U.setX(1.0);
	}
	else if (U.getY() < U.getX() && U.getY() < U.getZ())
	{
		U.setY(1.0);
	}
	else
	{
		U.setZ(1.0);
	}
	
	//Create U using the cross product of W and modified U.
	U = W.crossProduct(U);
	//Normalize U.
	U.normalize();
	//Create V using the cross product of W and the normalized U.
	Vector<double> V = W.crossProduct(U);
	
	//Create the rotation matrix for the z-axis.
	for (unsigned int i = 0; i < RMz.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < RMz.getColumnSize(); j++)
		{
			if (i == j && (i == 0 || i == 1))
			{
				RMz.at(i, j) = cos(degrees * PI / 180.0);
			}
			else if (i == 0 && j == 1)
			{
				RMz.at(i, j) = sin(degrees * PI / 180.0) * -1.0;
			}
			else if (i == 1 && j == 0)
			{
				RMz.at(i, j) = sin(degrees * PI / 180.0);
			}
		}
	}
	
	//Create the general rotation matrix with W, U, and V.
	for (unsigned int i = 0; i < RMw.getRowSize(); i++)
	{
		if (i == 0)
		{
			RMw.at(i, 0) = U.getX();
			RMw.at(i, 1) = U.getY();
			RMw.at(i, 2) = U.getZ();
		}
		else if (i == 1)
		{
			RMw.at(i, 0) = V.getX();
			RMw.at(i, 1) = V.getY();
			RMw.at(i, 2) = V.getZ();
		}
		else if (i == 2)
		{
			RMw.at(i, 0) = W.getX();
			RMw.at(i, 1) = W.getY();
			RMw.at(i, 2) = W.getZ();
		}
	}
	
	//Multipy all three matricies in this order: RMwT * RMz * RMw
	Matrix RM = RMw.transpose() * RMz * RMw;
	
	//Return the rotation matrix.
	return RM;
}

//Method Summary: Creates the matrix to scale the model's size.
//Precondtions: The amount of scaling.
//Postconditions: Returns a scaling matrix.
Matrix Model::createScaleMatrix(const double scale) const
{
	//SM: The scale matrix.
	Matrix SM = Matrix(4, 4);
	
	//Create the scale matrix.
	for (unsigned int i = 0; i < SM.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < SM.getColumnSize(); j++)
		{
			if (i == j && i != 3)
			{
				SM.at(i, j) = scale;
			}
			else if (i == j && i == 3)
			{
				SM.at(i, j) = 1.0;
			}
			else
			{
				SM.at(i, j) = 0.0;
			}
		}
	}
	
	//Return the scale matrix.
	return SM;
}

//Method Summary: Creates a translation matrix to reposition the model in the scene.
//Precondtions: The axis of translation.
//Postconditions: Returns a translation matrix.
Matrix Model::createTranslationMatrix(const Vector<double> &translation) const
{
	//TM: The translation matrix.
	Matrix TM = Matrix(4, 4);
	
	TM.at(0, 3) = translation.getX();
	TM.at(1, 3) = translation.getY();
	TM.at(2, 3) = translation.getZ();
	
	//Create the translation matrix.
	for (unsigned int i = 0; i < TM.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < TM.getColumnSize(); j++)
		{
			if (i == j)
			{
				TM.at(i, j) = 1.0;
			}
			else if (j != 3)
			{
				TM.at(i, j) = 0.0;
			}
		}
	}
	
	//Return the translation matrix.
	return TM;
}

//Method Summary: Reads the material attached to a specific model. The model could have 1 or more materials attached, which is considered 
//by the algorithm.
//Precondtions: The filename of the model.
//Postconditions: Returns true if the execution was successful, false otherwise. 
bool Model::readMaterialData(const char *filename)
{
	//Create an ifstream file object for reading the material file.
	std::ifstream fileReader = std::ifstream(filename, std::ifstream::in);
	//Find the number of materials in the file.
	unsigned int numOfMaterials = numberOfMaterials(fileReader);
	//Create a vector to store the materials.
	materials.resize(numOfMaterials);
	//ka: Ambient shading.
	//kd: Diffuse shading.
	//kr: To be used for a later date.
	//ks: Specular shading.
	//ko: Refraction shading. Not used for models and set to a default vector of (1, 1, 1).
	Vector<double> ka;
	Vector<double> kd;
	Vector<double> kr;
	Vector<double> ks;
	Vector<double> ko = Vector<double>(1.0, 1.0, 1.0);
	//count: The count of data incorporated into the material.
	unsigned int count = 0;
	//materialCount: The count of materials for this Model instance.
	unsigned int materialCount = 0;
	
	//If the open file operation failed, then...
	if (!fileReader.good())
	{
		//Display an error message.
		std::cerr << "Failed to open file with given name." << std::endl;
		//Close the file.
		fileReader.close();
		//Return false, indicating failure.
		return false;
	}
	
	//s: Stores a string label that defines what data is being presented.
	//tempX: Stores the x value of the vector temporarilty.
	//tempY: Stores the y value of the vector temporarilty.
	//tempZ: Stores the z value of the vector temporarilty.
	//eta: The refraction index.
	//phongConstant: Phong's constant is used to calculate reflection.
	std::string s = "";
	double tempX = 0.0;
	double tempY = 0.0;
	double tempZ = 0.0;
	double eta = 1.0;
	double phongConstant = 0.0;
	
	//While the file has not reached the end...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> s;
		
		//If the input read failed, then...
		if (!fileReader.good())
		{
			//If a file read failure was caused by the file pointer reaching the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Display an error message.
			std::cerr << "Error encounter while parsing file.\n";
			//Close the file.
			fileReader.close();
			//Return false, indicating failure.
			return false;
		}
		
		//If the input label is for a material, and the count is greater than 0, then...
		if (s.compare("newmtl") == 0 && count > 0)
		{
			//Store the material.
			materials[materialCount] = Material(ka, kd, ko, kr, ks, 0, 0, phongConstant, eta);
			//Reset the count to 0.
			count = 0;
			//Increment the material count.
			materialCount++;
		}
		else if (s.compare("Ka") == 0) //If the input read is for ambient shading, then...
		{
			//For the next three times...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Store the first Vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Store the second Vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Store the third Vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the file pointer is at the end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If a file read failure was caused by the file pointer reaching the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Store the retrieved values in the ambient shading vector.
			ka = Vector<double>(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Kd") == 0) //If the input read is for diffuse shading, then...
		{
			//For the next three times...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Store the first Vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Store the second Vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Store the third Vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the file pointer is at the end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
			}
			
			//But if the file was caused by the file pointer reaching the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Store the retrieved values in the diffuse shading vector.
			kd = Vector<double>(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ko") == 0) //If the input read is for refraction shading, then...
		{
			//For the next three times...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Store the first Vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Store the second Vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Store the third Vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the file pointer is at the end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
			}
			
			//Store the values in the refraction shading vector.
			ko = Vector<double>(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ke") == 0) //Attribute to be defined in a later implementation.
		{
			//For the next three times...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Store the first Vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Store the second Vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Store the third Vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the file pointer is at the end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If a file read failure was caused by the file pointer reaching the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Attribute to be defined in a later implementation.
			kr = Vector<double>(1.0, 1.0, 1.0);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ks") == 0) //If the input read is for specular shading, then...
		{
			//For the next three times...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Store the first Vector value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Store the second Vector value.
					fileReader >> tempY;
				}
				else //Third read:
				{
					//Store the third Vector value.
					fileReader >> tempZ;
				}
			
				//If the file read failed, then...
				if (!fileReader.good())
				{
					//If the file pointer is at the end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					
					//Display an error message.
					std::cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
			}
			
			//Store the retrieved values in the specular shading vector.
			ks = Vector<double>(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ni") == 0) //If the input read is for the index of refraction, then...
		{
			//Store the index of refraction.
			fileReader >> eta;
			
			//If the file read failed, then...
			if (!fileReader.good())
			{
				//If a file read failure was caused by the file pointer reaching the end, then...
				if (fileReader.eof())
				{
					//Break out of the loop.
					break;
				}
				
				//Display an error message.
				std::cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Increment the count.
			count++;
		}
		else if (s.compare("Ns") == 0) //If the input read is for the phong constant, then...
		{
			//Store the phong constant.
			fileReader >> phongConstant;
			
			//If the file read failed, then...
			if (!fileReader.good())
			{
				//If a file read failure was caused by the file pointer reaching the end, then...
				if (fileReader.eof())
				{
					//Break out of the loop.
					break;
				}
				
				//Display an error message.
				std::cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Increment the count.
			count++;
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
		//Reset the string variable with an empty string.
		s = "";
	}
	
	//Store the final material after the loop ends.
	materials[materialCount] = Material(ka, kd, ko, kr, ks, 0, 0, phongConstant, eta);

	//Close the material file.
	fileReader.close();
	
	//Return true, indicating success.
	return true;
}

//Method Summary: Reads the model file and its attributes. The only model this implementation will accept is the Wavefront .obj file. 
//Precondtions: The Wavefront .obj filename.
//Postconditions: //Returns true if the execution was successful, false otherwise.
bool Model::readModelData(const char *filename)
{
	//Open the file with the given filename.
	std::ifstream fileReader = std::ifstream(filename, std::ifstream::in);
	
	//If the file failed to open, then...
	if (!fileReader.good())
	{
		//Display an error message.
		std::cerr << "Failed to open file with given name." << std::endl;
		//Close the file.
		fileReader.close();
		//Return false, indicating failure.
		return false;
	}
	
	//s: Reads the next input as a string, which determined the course of action to take.
	//materialFilename: The filename of the material file.
	//numOfV: The number of vertices in the model.
	//numOfF: The number of faces in the model.
	//vXPos, vYPos, fXPos, fYPos, mPos, sPos, and sLen: Various position counters to keep tracking of retrieved attributes.
	//currentV: The currently retrieved vertex.
	std::string s = "", materialFilename = "";
	unsigned int numOfV = numberOfVertices(fileReader);
	unsigned int numOfF = numberOfFaces(fileReader);
	//Resize the vertices vector by the number of vertices.
	vertices.resize(numOfV);
	//Resize the faces vector by the number of faces.
	faceIndices.resize(numOfF * 3);
	unsigned int vPos = 0, fPos = 0, mPos = 0, sPos = 0, sLen = 0;
	double tempX = 0.0, tempY = 0.0, tempZ = 0.0;
	
	//While the file has not reached its end...
	while(!fileReader.eof())
	{	
		//Read the next input as a string.
		fileReader >> s;
		
		//If the next input failed to read, then...
		if (!fileReader.good())
		{
			//If the file has reached its end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			else //Otherwise...
			{
				//Display an error message.
				std::cerr << "Error encountered while parsing the file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
		}
		else if (s.compare("mtllib") == 0) //If the input read is for a material file, then...
		{
			//Store the material filename.
			fileReader >> materialFilename;
			
			//If the next input failed to read, then...
			if (!fileReader.good())
			{
				//If the file has reached its end, then...
				if (fileReader.eof())
				{
					//Break out of the loop.
					break;
				}
				else //Otherwise...
				{
					//Display an error message.
					std::cerr << "Error encountered while parsing the file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
			}
			
			//If the read of the material file fails, then...
			if (!readMaterialData(materialFilename.c_str()))
			{
				//Return an error message.
				std::cerr << "Error encountered while parsing the material file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
		}
		else if (s.compare("v") == 0) //If the input read is for a vertex, then...
		{	
			//While the line has NOT reached its end...
			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 0) //First read:
				{
					//Read the first vertex value.
					fileReader >> tempX;
				}
				else if (i == 1) //Second read:
				{
					//Read the second vertex value.
					fileReader >> tempY;
				}
				else
				{
					//Read the third vertex value.
					fileReader >> tempZ;
				}
				
				//If the next input failed to read, then...
				if (!fileReader.good())
				{
					//If the file has reached its end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					else //Otherwise...
					{
						//Display an error message.
						std::cerr << "Error encountered while parsing the file.\n";
						//Close the file.
						fileReader.close();
						//Return false, indicating failure.
						return false;
					}
				}
			}
			
			//If the file has reached its end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Store the current vertex in the vector of vertices.
			vertices[vPos] = Vector<double>(tempX, tempY, tempZ);
			//Increment the first index.
			vPos++;
		}
		else if (s.compare("f") == 0) //If the input read is for a face, then...
		{	
			//While the line has not reached it's end...
			while (fileReader.peek() != '\n')
			{
				//Read the next input as a string.
				fileReader >> s;
				
				//If the next input failed to read, then...
				if (!fileReader.good())
				{
					//If the file has reached its end, then...
					if (fileReader.eof())
					{
						//Break out of the loop.
						break;
					}
					else //Otherwise...
					{
						//Display an error message.
						std::cerr << "Error encountered while parsing the file.\n";
						//Close the file.
						fileReader.close();
						//Return false, indicating failure.
						return false;
					}
				}
				
				//While a '/' hasn't been encountered while parsing the string...
				while (sLen < s.length())
				{
					//Increment the length of the string before the '/.'
					if (s[sLen] != '/')
					{
						sLen++;
					}
					else
					{
						//Break out of the loop.
						break;
					}
				}
				
				//Convert the string to an unsigned integer.
				sPos = stoul(s.substr(0, sLen)); 
				
				//Set the index of the face. Subtract by 1 to match the indecies in the vertex vector.
				faceIndices[fPos] = sPos - 1;
				
				//Reset the string length.
				sLen = 0;
				//Reset the face index.
				sPos = 0;
				//Increment the first index.
				fPos++;
			}
		}
		else if (s.compare("usemtl") == 0) //If the input is for a material, then...
		{
			//If the material position is NOT 0, then...
			if (mPos != 0)
			{
				//Set the end face index for the previous material to the previous face index.
				materials[mPos - 1].setEndingIndex(fPos / 3 - 1);
			}
			
			//Set the end face index for the current material to the current face index.
			materials[mPos].setBeginningIndex(fPos / 3);
			//Increment the material index.
			mPos++;
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
		//Set the input read string to an empty string.
		s = "";
	}
	
	//At the end of the loop, set the end face index of the previous material to the previous face index.
	materials[mPos - 1].setEndingIndex(fPos / 3 - 1);
	
	//Close the file.
	fileReader.close();
	
	//Return true, indicating success.
	return true;
}

//Method Summary: Transforms the vertices according to the translation, rotation, and scaling matrices.
//Precondtions: The translation, rotation, and scaling matrices.
//Postconditions: None, though the face vertices are permanently altered.
void Model::transformVertices(const Matrix &translation, const Matrix &rotation, const Matrix &scale)
{
	//Multiply the matrices according to this formula: R * S * T. Unlike traditional multiplication operations, it reads right to left 
	//than left to right.
	Matrix translateScaleRotate = translation * scale * rotation;
	//vert: The vertex of the model. An extra value is required for transformation operations.
	Matrix vert = Matrix(4, 1);
	
	//For every vertex...
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		//1 is required for the calculation of the various transformations.
		vert.at(3, 0) = 1.0;
		
		//Fill the above rows of vert with the vertex values.
		vert.at(0, 0) = vertices[i].getX();
		vert.at(1, 0) = vertices[i].getY();
		vert.at(2, 0) = vertices[i].getZ();
		
		//Multiply the transformation matrix with the 4 x 1 matrix, which should result in another 4 x 1 matrix.
		vert = translateScaleRotate * vert;
		
		//Replace the previous values in the vertex with the transformed values.
		vertices[i] = Vector<double>(vert.at(0, 0), vert.at(1, 0), vert.at(2, 0));
	}
}

//Method Summary: Writes the model vertices to a Wavefront .obj file. A carryover from previous assignments not used with this current 
//implementation.
//Precondtions: The Wavefront .obj filename.
//Postconditions: Returns true is the write is successful, false otherwise.
bool Model::writeModelData(const char *filename) const
{
	//Create the Wavefront .obj file.
	std::ofstream fileWriter = std::ofstream(filename, std::ofstream::out);
	
	//If the file creation failed, then...
	if (!fileWriter.good())
	{
		//Display an error message.
		std::cerr << "Failed to open file with the given name." << std::endl;
		//Close the file.
		fileWriter.close();
		//Return false, indicating failure.
		return false;
	}
	
	//For every vertex...
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		//Write the v to indicate it is data for a vertex and the vertex within a set precision (6 decimal places in this case).
		fileWriter << "v " << std::fixed << std::setprecision(6) << vertices[i].getX() << " " << vertices[i].getY() << " " << 
			vertices[i].getZ() << std::endl;
		
		//If the file write failed, then...
		if (!fileWriter.good())
		{
			//Display an error message.
			std::cerr << "Failed to write to the given file." << std::endl;
			//Close the file.
			fileWriter.close();
			//Return false, indicating failure.
			return false;
		}
	}
	
	//For every face...
	for (unsigned int i = 0; i < faceIndices.size(); i++)
	{
		if (i % 3 == 0)
		{
			//Write f to indicate the data is for a face.
			fileWriter << "f ";
			
			//If the file write failed, then...
			if (!fileWriter.good())
			{
				//Display an error message.
				std::cerr << "Failed to write to the given file." << std::endl;
				//Close the file.
				fileWriter.close();
				//Return false, indicating failure.
				return false;
			}
		}
		
		//Write the face index.
		fileWriter << faceIndices[i] + 1;
		
		//If the file write failed, then...
		if (!fileWriter.good())
		{
			//Display an error message.
			std::cerr << "Failed to write to the given file." << std::endl;
			//Close the file.
			fileWriter.close();
			//Return false, indicating failure.
			return false;
		}
		
		//If the current face index isn't the last in the face, then...
		if (((i + 1) % 3) != 0)
		{
			//Write a space to separate face indecies.
			fileWriter << " ";
		}
		else
		{
			//Write the end of the line character.
			fileWriter << std::endl;
		}
		
		//If the file write failed, then...
		if (!fileWriter.good())
		{
			//Display an error message.
			std::cerr << "Failed to write to the given file." << std::endl;
			//Close the file.
			fileWriter.close();
			//Return false, indicating failure.
			return false;
		}
	}
	
	//Close the file.
	fileWriter.close();
	
	//Return true, indicating success.
	return true;
}

//Method Summary: Creates a 1-D data structure of face vertices that coorelate with the face indecies.
//Precondtions: None.
//Postconditions: The face vertices are created.
void Model::createFaces()
{
	//Initialize the data structure for the face vertices using the size of the data structure for the face indecies.
	unsigned int faceIndicesSize = faceIndices.size() / 3;
	faces.resize(faceIndicesSize);
	
	//A, B, and C: The vertex positions.
	Vector<double> A, B, C;
	
	//For every face index...
	for (unsigned int i = 0; i < faceIndicesSize; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			//Create a face out of the proper vertex vectors.
			if (j == 0)
			{
				A = vertices[faceIndices[i * 3 + j]];
			}
			else if (j == 1)
			{
				B = vertices[faceIndices[i * 3 + j]];
			}
			else
			{
				C = vertices[faceIndices[i * 3 + j]];
			}
		}
		
		//Store the face vertex.
		faces[i] = Triangle(A, B, C);
	}
}

//Method Summary: Reports the number of vertices in a model file.
//Precondtions: The open Wavefront .obj file.
//Postconditions: Returns the number of vertices.
unsigned int Model::numberOfVertices(std::ifstream &fileReader) const
{
	//numOfV: The number of vertices.
	unsigned int numOfV = 0;
	std::string next = "";
	
	//While the file has not reached its end...
	while (!fileReader.eof())
	{
		//Read the next input.
		fileReader >> next;
		
		//If the file read failed, then...
		if (!fileReader.good())
		{
			//If the file has reached the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			else //Otherwise...
			{
				//Close the file.
				fileReader.close();
				//Return 0, indicating failure.
				return 0;
			}
		}
		
		//If the next input read is for a vertex, then...
		if (next.compare("v") == 0)
		{
			//Increment the number of vertices.
			numOfV++;
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
		next = "";
	}
	
	//Clear the input flags of the end of line status.
	fileReader.clear();
	//Return to the beginning of the file.
	fileReader.seekg(0, fileReader.beg);
	
	//Return the number of vertices.
	return numOfV;
}

//Method Summary: Reports the number of faces in the model file.
//Precondtions: An open Wavefront .obj file.
//Postconditions: //Returns the number of faces.
unsigned int Model::numberOfFaces(std::ifstream &fileReader) const
{
	//numOfF: The number of faces.
	unsigned int numOfF = 0;
	std::string next = "";
	
	//While the file has not reached its end...
	while (!fileReader.eof())
	{
		//Read the next input.
		fileReader >> next;
		
		//If the file read failed, then...
		if (!fileReader.good())
		{
			//If the file has reached the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			else //Otherwise...
			{
				//Close the file.
				fileReader.close();
				//Return 0, indicating failure.
				return 0;
			}
		}
		
		//If the next input read is for a face, then...
		if (next.compare("f") == 0)
		{
			//Increment the number of faces.
			numOfF += 1;
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
		next = "";
	}
	
	//Clear the input flags of the end of file status.
	fileReader.clear();
	//Return to the beginning of the file.
	fileReader.seekg(0, fileReader.beg);
	
	//Return the number of faces.
	return numOfF;
}

//Method Summary: Reports the number of materials in the model file.
//Precondtions: An open Wavefront .obj file.
//Postconditions: Returns the number of materials. 
unsigned int Model::numberOfMaterials(std::ifstream &fileReader) const
{
	//numOfMa: The number of materials.
	//s: The input read string.
	unsigned int numOfMa = 0;
	std::string s = "";
	
	//While the file has not reached its end, then...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> s;
		
		//If the input read failed, then...
		if (!fileReader.good())
		{
			//Clear the input flags of the negative status.
			fileReader.clear();
			//Return to the beginning of the file.
			fileReader.seekg(0, fileReader.beg);
			//Return the number of materials.
			return numOfMa;
		}
		
		//If the next input read is for a material, then...
		if (s.compare("newmtl") == 0)
		{
			//Increment the number of materials.
			numOfMa++;
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
		//Replace the input read string with an empty string.
		s = "";
	}
	
	//Clear the input flags of the end of file status.
	fileReader.clear();
	//Return to the beginning of the file.
	fileReader.seekg(0, fileReader.beg);
	
	//Return the number of materials.
	return numOfMa;
}
