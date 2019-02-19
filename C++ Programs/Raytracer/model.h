/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef MODEL_H
#define MODEL_H

#include "triangle.h"
#include "matrix.h"
#include "vector.h"
#include "material.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>

#define PI 3.14159265

class Model
{
	public:
		Model();
		Model(const vector< vector<double> > &vdata, const vector< vector<unsigned int> > &fdata);
		~Model();
		static Matrix createRotationMatrix(const vector<double> &axis, const double degrees);
		static Matrix createScaleMatrix(const double scale);
		static Matrix createTranslationMatrix(const vector<double> &translation);
		static vector<double> normalizeAxis(const vector<double> &axis);
		const vector< vector<unsigned int> > & getFaces() const;
		vector<Triangle> & getFaceVertices();
		const vector<Material> & getMaterials() const;
		const vector< vector<double> > & getVertices() const;
		bool readMaterialData(const char *filename);
		bool readModelData(const char *filename);
		void setFaces(const vector< vector<unsigned int> > &fdata);
		void setVertices(const vector< vector<double> > &vdata);
		void transformVertices(const Matrix &translation, const Matrix &scale, const Matrix &rotation);
		bool writeModelData(const char *filename);
		bool writePPMFile(const char *filename);
		void createFaceVertices();
		friend ofstream & operator<<(ofstream &out, const Model &model)
		{	
			out << "Model" << endl;
			
			for (unsigned int i = 0; i < model.getVertices().size(); i++)
			{
				out << "v ";

				for (unsigned int j = 0; j < model.getVertices()[i].size(); j++)
				{
					out << model.getVertices()[i][j];
					
					if (j < model.getVertices()[i].size() - 1)
					{
						out << " ";
					}
				}
				
				out << endl;
			}
			
			for (unsigned int i = 0; i < model.getFaces().size(); i++)
			{
				out << "f ";
				
				for (unsigned int j = 0; j < model.getFaces()[i].size(); j++)
				{
					out << model.getFaces()[i][j] + 1;
					
					if (j < model.getFaces()[i].size() - 1)
					{
						out << " ";
					}
				}
				
				out << endl;
			}
			
			for (unsigned int i = 0; i < model.getMaterials().size(); i++)
			{
				out << "m " << model.getMaterials()[i];
				
				if (i < model.getMaterials().size() - 1)
				{
					out << endl;
				}
			}
			
			return out;
		}
		
	private:
		vector< vector<double> > vertices;
		vector< vector<unsigned int> > faces;
		vector<Triangle> faceVs;
		unsigned int numberOfVertices(ifstream &fileReader);
		unsigned int numberOfFaces(ifstream &fileReader);
		unsigned int numberOfMaterials(ifstream &fileReader);
		vector<Material> materials;
};

double dotProduct(const vector<double> &lhs, const vector<double> &rhs);
vector<double> crossProduct(const vector<double> &lhs, const vector<double> &rhs);

#endif
