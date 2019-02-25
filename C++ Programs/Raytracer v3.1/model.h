/* Author: coleman7245
 * File: C++ Model header file for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Model class.
 */

//If the header file has been included, then...
#ifndef MODEL_H
//Define the header file.
#define MODEL_H

//Include the Triangle header for face data.
#include "triangle.h"
//Include the Matrix header for vertex transformations.
#include "matrix.h"
//Include the Material header for color calculations.
#include "material.h"
//Include the string header for filename data.
#include <string>
//Include IOManip header for output formatting. 
#include <iomanip>

//Define the Pi constant.
#define PI 3.14159265

/* Class declarations */
class Model
{
	public:
		/* Constructor methods */
		Model();
		Model(const char *filename, const Vector<double> &translation, const Vector<double> &rotation, const double scale, 
			const double degrees);
		~Model();
		/* Get methods */
		inline const std::vector<Triangle> & getFaces() const {return faces;}
		inline const std::vector<unsigned int> & getFaceIndices() const {return faceIndices;}
		inline const std::vector<Material> & getMaterials() const {return materials;}
		inline const std::vector< Vector<double> > & getVertices() const {return vertices;}
		/* Operator overload methods */
		Model & operator=(const Model &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Model object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Model &model)
		{
			//Load the class attribute information to the ostream object reference.
			out << "Model" << std::endl;
			
			for (unsigned int i = 0; i < model.getVertices().size(); i++)
			{
				out << "v " << model.getVertices()[i] << std::endl;
			}
			
			for (unsigned int i = 0; i + 2 < model.getFaceIndices().size(); i += 3)
			{
				out << "f " << model.getFaceIndices()[i] + 1 << " " << model.getFaceIndices()[i + 1] + 1 << " " << 
					model.getFaceIndices()[i + 2] + 1 << std::endl;
			}
			
			for (unsigned int i = 0; i < model.getFaces().size(); i++)
			{
				out << "t " << model.getFaces()[i] << std::endl;
			}
			
			for (unsigned int i = 0; i < model.getMaterials().size(); i++)
			{
				out << "m " << model.getMaterials()[i];
				
				if (i < model.getMaterials().size() - 1)
				{
					out << std::endl;
				}
			}
			
			//Return the ostream object reference.
			return out;
		}
		/* Other methods */
		bool writeModelData(const char *filename) const;
		bool writePPMFile(const char *filename) const;
		
	private:
		/* Class attributes */
		std::vector< Vector<double> > vertices;
		std::vector<unsigned int> faceIndices;
		std::vector<Triangle> faces;
		std::vector<Material> materials;
		/* Other methods */
		void createFaces();
		Matrix createRotationMatrix(const Vector<double> &rotation, const double degrees) const;
		Matrix createScaleMatrix(const double scale) const;
		Matrix createTranslationMatrix(const Vector<double> &translation) const;
		bool readMaterialData(const char *filename);
		bool readModelData(const char *filename);
		unsigned int numberOfFaces(std::ifstream &fileReader) const;
		unsigned int numberOfMaterials(std::ifstream &fileReader) const;
		unsigned int numberOfVertices(std::ifstream &fileReader) const;
		void transformVertices(const Matrix &translation, const Matrix &rotation, const Matrix &scale);
};

#endif
