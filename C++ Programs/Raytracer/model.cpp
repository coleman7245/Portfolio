/* Author: coleman7245
 * File: C++ Model class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The Model class stores information regarding the model rendered in the scene. Also contains methods for model 
 * transformations, reading wavefront .obj file information, and writing back that very information.
 */

#include "model.h"

//Method Summary: Default constructor
Model::Model()
	: vertices(0), faces(0)
	{}

//Method Summary: Constructor using input from the provided parameters.
Model::Model(const vector< vector<double> > &vdata, const vector< vector<unsigned int> > &fdata)
{
	setVertices(vdata);
	setFaces(fdata);
}

//Method Summary: Deconstructor
Model::~Model() {}

//Method Summary: Creates a rotation matrix to transformed a model's rotation.
//Precondtions: The axis of rotation and the number of degrees to rotate.
//Postconditions: Returns a rotation matrix.
Matrix Model::createRotationMatrix(const vector<double> &axis, const double degrees)
{
	//RMz: Rotation around the z-axis.
	//RWw: General axes of rotation.
	//W: Axis of rotation.
	//U: Heuristic pick for an axis perdindicular to W.
	//V: Axis perpindicular to W and U.
	Matrix RMz = Matrix::identity(4);
	Matrix RMw = Matrix::identity(4);
	vector<double> W = Model::normalizeAxis(axis);
	vector<double> U = Model::normalizeAxis(axis);
	vector<double> V;
	
	//minPos: Position of the minimum value in U.
	unsigned int minPos = 0;
	
	//For every value in U...
	for (unsigned int i = 0; i < U.size(); i++)
	{
		//If the value at the current position in U is less than the value at the prefered position, then...
		if (U[i] < U[minPos])
		{
			//Change the preferred position to the current position.
			minPos = i;
		}
	}
	
	//Change the minimum value of U to 1.
	U[minPos] = 1.0;
	//Create U using the cross product of W and modified U.
	U = crossProduct(W, U);
	//Normalize U.
	U = Model::normalizeAxis(U);
	//Create V using the cross product of W and the normalized U.
	V = crossProduct(W, U);
	
	//Create the rotation matrix for the z-axis.
	for (unsigned int i = 0; i < RMz.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < RMz.getColumnSize(); j++)
		{
			if (i == j && (i == 0 || i == 1))
			{
				RMz[i][j] = cos(degrees * PI / 180.0);
			}
			else if (i == 0 && j == 1)
			{
				RMz[i][j] = sin(degrees * PI / 180.0) * -1.0;
			}
			else if (i == 1 && j == 0)
			{
				RMz[i][j] = sin(degrees * PI / 180.0);
			}
		}
	}
	
	//Create the general rotation matrix with W, U, and V.
	for (unsigned int i = 0; i < RMw.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < RMw.getColumnSize(); j++)
		{
			if (j < 3)
			{
				if (i == 0)
				{
					RMw[i][j] = U[j];
				}
				else if (i == 1)
				{
					RMw[i][j] = V[j];
				}
				else if (i == 2)
				{
					RMw[i][j] = W[j];
				}
			}
		}
	}
	
	//RMwT: Transpose of the general rotation matrix.
	Matrix RMwT = Matrix::transpose(RMw);
	//Multipy all three matricies in this order: RMwT * RMz * RMw
	Matrix RM = Matrix::multiplyMatrices(RMwT, RMz);
	RM = Matrix::multiplyMatrices(RM, RMw);
	
	//Return the rotation matrix.
	return RM;
}

//Method Summary: Creates the matrix to scale the model's size.
//Precondtions: The amount of scaling.
//Postconditions: Returns a scaling matrix.
Matrix Model::createScaleMatrix(const double scale)
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
				SM[i][j] = scale;
			}
			else if (i == j && i == 3)
			{
				SM[i][j] = 1.0;
			}
			else
			{
				SM[i][j] = 0.0;
			}
		}
	}
	
	//Return the scale matrix.
	return SM;
}

//Method Summary: Creates a translation matrix to reposition the model in the scene.
//Precondtions: The axis of translation.
//Postconditions: Returns a translation matrix.
Matrix Model::createTranslationMatrix(const vector<double> &translation)
{
	//TM: The translation matrix.
	Matrix TM = Matrix(4, 4);
	
	//Create the translation matrix.
	for (unsigned int i = 0; i < TM.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < TM.getColumnSize(); j++)
		{
			if (i == j)
			{
				TM[i][j] = 1.0;
			}
			else if (j == 3 && i != 3)
			{
				TM[i][j] = translation[i];
			}
			else
			{
				TM[i][j] = 0.0;
			}
		}
	}
	
	//Return the translation matrix.
	return TM;
}

//Method Summary: Normalizes the axis by adjusting its values so that the axis' magnitude is 1.
//Precondtions: The axis to be normalized.
//Postconditions: Returns the normalized axis.
vector<double> Model::normalizeAxis(const vector<double> &axis)
{
	//norm: The magnitude of the regular axis.
	//normalizedAxis: The axis after normalization.
	double norm = 0.0;
	vector<double> normalizedAxis = vector<double>(axis.size());
	
	//For every value in the axis...
	for (unsigned int i = 0; i < axis.size(); i++)
	{
		//Sum the squares of each value.
		norm += pow(axis[i], 2.0);
	}
	
	//Take the square root of the sum.
	norm = sqrt(norm);
	
	//For every value in the normalized axis...
	for (unsigned int i = 0; i < axis.size() && i < normalizedAxis.size(); i++)
	{
		//Divide the values of the axis by its magnitude, then place them in the normalized axis.
		normalizedAxis[i] = axis[i] / norm;
	}
	
	//Return the normalized axis.
	return normalizedAxis;
}

//Method Summary: Get methods for class variables that simply return their value.
const vector< vector<unsigned int> > & Model::getFaces() const {return faces;}

vector<Triangle> & Model::getFaceVertices() {return faceVs;}

const vector<Material> & Model::getMaterials() const {return materials;}

const vector< vector<double> > & Model::getVertices() const {return vertices;}

//Method Summary: Reads the material attached to a specific model. The model could have 1 or more materials attached, which is considered 
//by the algorithm.
//Precondtions: The filename of the model.
//Postconditions: Returns true if the execution was successful, false otherwise. 
bool Model::readMaterialData(const char *filename)
{
	//Create a vector to store the materials.
	materials = vector<Material>();
	//Create an ifstream file object for reading the material file.
	ifstream fileReader = ifstream(filename, ifstream::in);
	//ka: Ambient shading.
	//kd: Diffuse shading.
	//kr: To be used for a later date.
	//ks: Specular shading.
	//ko: Refraction shading. Not used for models and set to a default vector of (1, 1, 1).
	Vector ka, kd, kr, ks, ko = Vector(1.0, 1.0, 1.0);
	//What vector is file with the retrieved data depends on the count.
	unsigned int count = 0;
	
	//If the open file operation failed, then...
	if (!fileReader.good())
	{
		//Display an error message.
		cerr << "Failed to open file with given name." << endl;
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
	string s = "";
	double tempX = 0.0, tempY = 0.0, tempZ = 0.0;
	double eta = 1.0, phongConstant = 0.0;
	
	//While the file has not reached the end...
	while (!fileReader.eof())
	{
		//Read the next input as a string.
		fileReader >> s;
		
		//If the input read failed, then...
		if (fileReader.fail() || fileReader.bad())
		{
			//But if the file was caused by the file pointer reaching the end, then...
			if (fileReader.eof())
			{
				//Break out of the loop.
				break;
			}
			
			//Display an error message.
			cerr << "Error encounter while parsing file.\n";
			//Close the file.
			fileReader.close();
			//Return false, indicating failure.
			return false;
		}
		
		//If the input label is for a material, and the count is greater than 0, then...
		if (s.compare("newmtl") == 0 && count > 0)
		{
			//Store the material.
			materials.push_back(Material(ka, kd, ko, kr, ks, 0, 0, phongConstant, eta));
			//Reset the count to 0.
			count = 0;
		}
		else if (s.compare("Ka") == 0) //If the input read is for ambient shading, then...
		{
			//Store the x value.
			fileReader >> tempX;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the y value.
			fileReader >> tempY;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the z value.
			fileReader >> tempZ;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the retrieved values in the ambient shading vector.
			ka = Vector(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Kd") == 0) //If the input read is for diffuse shading, then...
		{
			//Store the x value.
			fileReader >> tempX;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the y value.
			fileReader >> tempY;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the z value.
			fileReader >> tempZ;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the retrieved values in the diffuse shading vector.
			kd = Vector(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ko") == 0) //If the input read is for refraction shading, then...
		{
			//Store the x value.
			fileReader >> tempX;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the y value.
			fileReader >> tempY;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the z value.
			fileReader >> tempZ;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the values in the refraction shading vector.
			ko = Vector(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ke") == 0) //Attribute to be defined in a later implementation.
		{
			//Store the x value.
			fileReader >> tempX;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the y value.
			fileReader >> tempY;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the z value.
			fileReader >> tempZ;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Attribute to be defined in a later implementation.
			kr = Vector(1.0, 1.0, 1.0);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ks") == 0) //If the input read is for specular shading, then...
		{
			//Store the x value.
			fileReader >> tempX;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the y value.
			fileReader >> tempY;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the z value.
			fileReader >> tempZ;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
			
			//Store the retrieved values in the specular shading vector.
			ks = Vector(tempX, tempY, tempZ);
			//Increment the count.
			count++;
		}
		else if (s.compare("Ni") == 0) //If the input read is for the index of refraction, then...
		{
			//Store the index of refraction.
			fileReader >> eta;
			
			//If the file read failed, then...
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
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
			if (fileReader.fail() || fileReader.bad())
			{
				//Display an error message.
				cerr << "Error encounter while parsing file.\n";
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
	materials.push_back(Material(ka, kd, ko, kr, ks, 0, 0, phongConstant, eta));

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
	ifstream fileReader = ifstream(filename, ifstream::in);
	
	//If the file failed to open, then...
	if (!fileReader.good())
	{
		//Display an error message.
		cerr << "Failed to open file with given name." << endl;
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
	string s = "", materialFilename = "";
	unsigned int numOfV = numberOfVertices(fileReader);
	unsigned int numOfF = numberOfFaces(fileReader);
	//Resize the vertices vector by the number of vertices.
	vertices.resize(numOfV);
	//Resize the faces vector by the number of faces.
	faces.resize(numOfF);
	unsigned int vXPos = 0, vYPos = 0, fXPos = 0, fYPos = 0, mPos = 0, sPos = 0, sLen = 0;
	double currentV = 0.0;
	
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
				cerr << "Error encountered while parsing the file.\n";
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
			
			//If the read of the material file fails, then...
			if (!readMaterialData(materialFilename.c_str()))
			{
				//Return an error message.
				cerr << "Error encountered while parsing the material file.\n";
				//Close the file.
				fileReader.close();
				//Return false, indicating failure.
				return false;
			}
		}
		else if (s.compare("v") == 0) //If the input read is for a vertex, then...
		{
			//Resize the vertices vector to hold a vertex with 3 values.
			vertices[vXPos].resize(3);
			
			//While the line has NOT reached its end...
			while (fileReader.peek() != '\n')
			{
				//Store the current vertex.
				fileReader >> currentV;
				
				//If the input read fails, then...
				if (fileReader.fail() || fileReader.bad())
				{
					//Display an error message.
					cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
				
				//Store the current vertex in the vector of vertices.
				vertices[vXPos][vYPos] = currentV;
				//Increment the second index.
				vYPos++;
			}
			
			//Reset the second index.
			vYPos = 0;
			//Increment the first index.
			vXPos++;
		}
		else if (s.compare("f") == 0) //If the input read is for a face, then...
		{
			//Resize the face vector to hold aface with 3 values.
			faces[fXPos].resize(3);
			
			//While the line has not reached it's end...
			while (fileReader.peek() != '\n')
			{
				//Read the next input as a string.
				fileReader >> s;
				
				//If the input read fails, then...
				if (fileReader.fail() || fileReader.bad())
				{
					//Display an error message.
					cerr << "Error encounter while parsing file.\n";
					//Close the file.
					fileReader.close();
					//Return false, indicating failure.
					return false;
				}
				
				//While a '/' hasn't been encountered while parsing the string...
				while (s[sLen] != '/')
				{
					//Increment the length of the string before the '/.'
					sLen++;
				}
				
				//Convert the string to an unsigned integer.
				sPos = stoul(s.substr(0, sLen)); 
				
				//Set the index of the face. Subtract by 1 to match the indecies in the vertex vector.
				faces[fXPos][fYPos] = sPos - 1;
				
				//Increment the second index.
				fYPos++;
				//Reset the string length.
				sLen = 0;
				//Reset the face index.
				sPos = 0;
			}
			
			//Reset the second index.
			fYPos = 0;
			//Increment the first index.
			fXPos++;
		}
		else if (s.compare("usemtl") == 0) //If the input is for a material, then...
		{
			//If the material position is NOT 0, then...
			if (mPos != 0)
			{
				//Set the end face index for the previous material to the previous face index.
				materials[mPos - 1].setEndingIndex(fXPos - 1);
			}
			
			//Set the end face index for the current material to the current face index.
			materials[mPos].setBeginningIndex(fXPos);
			//Increment the material index.
			mPos++;
		}
		
		//Skip the rest of the line.
		fileReader.ignore(256, '\n');
		//Set the input read string to an empty string.
		s = "";
	}
	
	//At the end of the loop, set the end face index of the previous material to the previous face index.
	materials[mPos - 1].setEndingIndex(fXPos - 1);
	
	//Close the file.
	fileReader.close();
	
	//Create the face vertices out of the vector of vertices.
	createFaceVertices();
	
	//Return true, indicating success.
	return true;
}

//Method Summary: Set methods that simply set the values for class variables.
void Model::setFaces(const vector< vector<unsigned int> > &fdata)
{
	faces.resize(fdata.size());
	
	for (unsigned int i = 0; i < fdata.size(); i++)
	{
		faces[i].resize(fdata[i].size());
		
		for (unsigned int j = 0; j < fdata[i].size(); j++)
		{
			faces[i][j] = fdata[i][j];
		}
	}
}

void Model::setVertices(const vector< vector<double> > &vdata)
{
	vertices.resize(vdata.size());
	
	for (unsigned int i = 0; i < vdata.size(); i++)
	{
		vertices[i].resize(vdata[i].size());
		
		for (unsigned int j = 0; j < vdata[i].size(); j++)
		{
			vertices[i][j] = vdata[i][j];
		}
	}
}

//Method Summary: Transforms the vertices according to the translation, rotation, and scaling matrices.
//Precondtions: The translation, rotation, and scaling matrices.
//Postconditions: None, though the face vertices are permanently altered.
void Model::transformVertices(const Matrix &translation, const Matrix &scale, const Matrix &rotation)
{
	//Multiply the matrices according to this formula: R * S * T. Unlike traditional multiplication operations, it reads right to left 
	//than left to right.
	Matrix translateScaleRotate = Matrix::multiplyMatrices(translation, scale);
	translateScaleRotate = Matrix::multiplyMatrices(translateScaleRotate, rotation);
	//vert: The vertex of the model. An extra value is required for transformation operations.
	Matrix vert = Matrix(4, 1);
	
	//For every vertex...
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		//1 is required for the calculation of the various transformations.
		vert[3][0] = 1.0;
		
		for (unsigned int j = 0; j < vertices[i].size(); j++)
		{
			//Fill the above rows of vert with the vertex values.
			vert[j][0] = vertices[i][j];
		}
		
		//Multiply the transformation matrix with the 4 x 1 matrix, which should result in another 4 x 1 matrix.
		vert = Matrix::multiplyMatrices(translateScaleRotate, vert);
		
		for (unsigned int j = 0; j < vertices[i].size(); j++)
		{
			//Replace the previous values in the vertex with the transformed values.
			vertices[i][j] = vert[j][0];
		}
	}
	
	//Recreate the face vertices, since the vertices are now transformed.
	createFaceVertices();
}

//Method Summary: Writes the model vertices to a Wavefront .obj file. A carryover from previous assignments not used with this current 
//implementation.
//Precondtions: The Wavefront .obj filename.
//Postconditions: Returns true is the write is successful, false otherwise.
bool Model::writeModelData(const char *filename)
{
	//Create the Wavefront .obj file.
	ofstream fileWriter = ofstream(filename, ofstream::out);
	
	//If the file creation failed, then...
	if (!fileWriter.good())
	{
		//Display an error message.
		cerr << "Failed to open file with the given name." << endl;
		//Close the file.
		fileWriter.close();
		//Return false, indicating failure.
		return false;
	}
	
	//For every vertex...
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		//Write the v to indicate it is data for a vertex.
		fileWriter << "v ";
		
		//For every vertex value...
		for (unsigned int j = 0; j < vertices[i].size(); j++)
		{
			//Write the vertex within a set precision (6 decimal places in this case).
			fileWriter << fixed << setprecision(6) << vertices[i][j];
			
			//If the current vertex value isn't the last one in the vertex, then...
			if ((j + 1) != vertices[i].size())
			{
				//Leave a space between vertex values.
				fileWriter << " ";
			}
		}
		
		//Write the end of the line character.
		fileWriter << endl;
	}
	
	//For every face...
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		//Write f to indicate the data is for a face.
		fileWriter << "f ";
		
		//For every face index...
		for (unsigned int j = 0; j < faces[i].size(); j++)
		{
			//Write the face index.
			fileWriter << faces[i][j];
			
			//If the current face index isn't the last in the face, then...
			if ((j + 1) != faces[i].size())
			{
				//Write a space to separate face indecies.
				fileWriter << " ";
			}
		}
		
		//Write the end of the line character.
		fileWriter << endl;
	}
	
	//Close the file.
	fileWriter.close();
	
	//Return true, indicating success.
	return true;
}

//Method Summary: Creates a 1-D data structure of face vertices that coorelate with the face indecies.
//Precondtions: None.
//Postconditions: The face vertices are created.
void Model::createFaceVertices()
{
	//Initialize the data structure for the face vertices using the size of the data structure for the face indecies.
	faceVs = vector<Triangle>(faces.size());
	
	//A, B, and C: The vertex positions.
	Vector A, B, C;
	
	//For every face index...
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		for (unsigned int j = 0; j < faces[i].size(); j++)
		{
			//Place the vertex positions according to their order.
			if (j == 0)
			{
				A = Vector(vertices[faces[i][j]][0], vertices[faces[i][j]][1], vertices[faces[i][j]][2]);
			}
			else if (j == 1)
			{
				B = Vector(vertices[faces[i][j]][0], vertices[faces[i][j]][1], vertices[faces[i][j]][2]);
			}
			else
			{
				C = Vector(vertices[faces[i][j]][0], vertices[faces[i][j]][1], vertices[faces[i][j]][2]);
			}
		}
		
		//Store the face vertex.
		faceVs[i] = Triangle(A, B, C);
	}
}

//Method Summary: Reports the number of vertices in a model file.
//Precondtions: The open Wavefront .obj file.
//Postconditions: Returns the number of vertices.
unsigned int Model::numberOfVertices(ifstream &fileReader)
{
	//numOfV: The number of vertices.
	unsigned int numOfV = 0;
	string next = "";
	
	//While the file has not reached its end...
	while (!fileReader.eof())
	{
		fileReader >> next;
		
		if (!fileReader.good())
		{
			if (fileReader.eof())
			{
				break;
			}
			else
			{
				fileReader.close();
				return 0;
			}
		}
		
		//If the next input read is for a vertex, then...
		if (next.compare("v") == 0)
		{
			//Increment the number of vertices.
			numOfV += 1;
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
unsigned int Model::numberOfFaces(ifstream &fileReader)
{
	//numOfF: The number of faces.
	unsigned int numOfF = 0;
	string next = "";
	
	//While the file has not reached its end...
	while (!fileReader.eof())
	{
		fileReader >> next;
		
		if (!fileReader.good())
		{
			if (fileReader.eof())
			{
				break;
			}
			else
			{
				fileReader.close();
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
unsigned int numberOfMaterials(ifstream &fileReader)
{
	//numOfMa: The number of materials.
	//s: The input read string.
	unsigned int numOfMa = 0;
	string s = "";
	
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
		if (s.compare("mtllib") == 0)
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

//Method Summary: Performs the multiplication and sum of the values of 2 vectors.
//Precondtions: Two vectors of the double data type.
//Postconditions: Returns the dot product of the 2 vectors.
double dotProduct(const vector<double> &lhs, const vector<double> &rhs)
{
	//dProduct: The dot product of the 2 vectors.
	double dProduct = 0.0;
	
	//For every value in both vectors...
	for (unsigned int i = 0; i < lhs.size() && i < rhs.size(); i++)
	{
		//Multiply the parallel values, then add them to the overall sum.
		dProduct += (lhs[i] * rhs[i]);
	}
	
	//Return the dot product.
	return dProduct;
}

//Method Summary: Creates a new vector that is perpindiclular to the given vectors.
//Precondtions: 2 vectors of the double data type.
//Postconditions: Returns the cross product of the 2 vectors.
vector<double> crossProduct(const vector<double> &lhs, const vector<double> &rhs)
{
	//cross: The new vector created from the cross product of the given vectors.
	vector<double> cross = vector<double>(lhs.size());
	
	//For evert value in the new vector.
	for (unsigned int i = 0; i < cross.size(); i++)
	{
		//Cross multiply the values, then subtract them.
		if (i == 0)
		{
			cross[i] = (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]);
		}
		else if (i == 1)
		{
			cross[i] = (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]);
		}
		else if (i == 2)
		{
			cross[i] = (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
		}
	}
	
	//Return the cross product.
	return cross;
}
