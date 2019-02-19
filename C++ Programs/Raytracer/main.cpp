/* Author: coleman7245
 * File: C++ Main method for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The main thread of execution for the raytracer program. The method first checks to see if the number of arguments is 
 * sufficient. Then it reads the driver file and stores the information found within. If any models are found within the driver file, their 
 * coordinates are transformed according to the specifications. Finally, the recursive raytracer is called to render the objects, which are 
 * then written to a PPM file. 
 */

#include "matrix.h"
#include "fileio.h"
#include "model.h"
#include "sphere.h"
#include "triangle.h"
#include "vector.h"
#include "camera.h"

void writeScene(const Camera &camera, const vector<Model> &models, const vector<Sphere> &spheres, const unsigned int recursionLevel);


//Method Summary: The main thread of execution for the Raytracer program.
//Precondtions: The number of arguments, which must be equal to 3. Aside from program name, the driver filename and the output PPM filename 
//must also be provided.
//Postconditions: An integer value is returned: 0 if the entire execution is successful, -1 otherwise. 
int main(int argc, char *argv[])
{
	//If the number of arguments does not equal 3, then...
	if (argc != 3)
	{
		//Display an error message.
		cerr << "Insufficient arguments. Operation aborted." << endl;
		//Return -1 for a failed execution.
		return -1;
	}
	
	//axes: Stores the rotation axis for each model.
	//degrees: Stores the rotation degrees for each model.
	//scales: Stores the scale axis for each model.
	//translations: Stores the translation axis for each model.
	//modelFilenames: Stores the filenames of each model.
	//spheres: Stores the spheres in the scene.
	//tValues: Stores the intersection values.
	//camera: The camera that renders the scene.
	//recursionLevel: The beginning level of recursion.
	vector< vector<double> > axes;
	vector<double> degrees;
	vector<double> scales;
	vector< vector<double> > translations;
	vector<string> modelFilenames;
	vector<Sphere> spheres;
	vector< vector<double> > tValues;
	Camera camera;
	unsigned int recursionLevel;
	
	//If the read of the driver file is NOT successful, then...
	if (!readDriverData(argv[1], axes, degrees, scales, translations, modelFilenames, spheres, camera, recursionLevel))
	{
		//Display an error message.
		cerr << "Driver file read failed! Operation aborted." << endl;
		//Return -1 for a failed execution.
		return -1;
	}
	
	//RM: Stores the rotation matrix for each model.
	//SM: Stores the scale matrix for each model.
	//TM: Stores the translation matrix for each model.
	//models: Stores the models in the scene.
	vector<Matrix> RM = vector<Matrix>(degrees.size());
	vector<Matrix> SM = vector<Matrix>(scales.size());
	vector<Matrix> TM = vector<Matrix>(translations.size());
	vector<Model> models = vector<Model>(modelFilenames.size());
	
	//For each model...
	for (unsigned int i = 0; i < models.size(); i++)
	{
		//Create the rotation matrix.
		RM[i] = Model::createRotationMatrix(axes[i], degrees[i]);
		//Create the scale matrix.
		SM[i] = Model::createScaleMatrix(scales[i]);
		//Create the translation matrix.
		TM[i] = Model::createTranslationMatrix(translations[i]);
		//Initalize the model.
		models[i] = Model();
		
		//If the read of the model file(s) is NOT successful, then...
		if (!models[i].readModelData(modelFilenames[i].c_str()))
		{
			//Display an error message.
			cerr << "Model file read failed!" << endl;
			//Return -1 for a failed execution.
			return -1;
		}
		
		//Transform the coordinates of the model.
		models[i].transformVertices(TM[i], SM[i], RM[i]);
	}
	
	//attenuation: Color degradation of a single pixel. Not used for this implementation and set to the default of 1.0.
	Vector attenuation = Vector(1.0, 1.0, 1.0);
	//Sets the color of all pixels in the scene using a recursive raytracer.
	camera.setColors(spheres, models, attenuation, recursionLevel);
	
	writeScene(camera, models, spheres, recursionLevel);
	
	//If the write of the graphics data is NOT successful, then...
	if (!writePPMFile(argv[2], camera.getColors()))
	{
		//Display an error message.
		cerr << "Failed to write file! Operation aborted." << endl;
		//Return -1 for a failed operation.
		return -1;
	}
	
	//Return 0 for a successful execution.
	return 0;
}

void writeScene(const Camera &camera, const vector<Model> &models, const vector<Sphere> &spheres, const unsigned int recursionLevel)
{
	ofstream out = ofstream("testold.txt", ofstream::out);
	
	out << "Scene" << endl;
			
	for (unsigned int i = 0; i < models.size(); i++)
	{
		out << models[i] << endl;
	}
			
	for (unsigned int i = 0; i < spheres.size(); i++)
	{
		out << "sphere " << spheres[i] << endl;
	}
			
	for (unsigned int i = 0; i < camera.getLights().size(); i++)
	{
		out << "light " << camera.getLights()[i] << endl;
	}
			
	out << "ambientLight " << camera.getAmbientLight() << endl;
			
	out << "Camera" << endl << camera << endl;
			
	out << "recursion " << recursionLevel;	
	
	out.close();
}
