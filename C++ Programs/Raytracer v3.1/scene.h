/* Author: coleman7245
 * File: C++ Scene header file for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides function and class declarations for the Scene class. 
 */

//If the Scene header isn't include, then...
#ifndef SCENE_H
//Define the Scene header.
#define SCENE_H

//Include the camera header for rendering the scene.
#include "camera.h"

/* Class declaration */
class Scene
{
	public:
		/* Constructor methods */
		Scene();
		Scene(const char *driverFilename);
		~Scene();
		/* Get methods */
		inline const std::vector<Model> & getModels() const {return models;}
		inline const std::vector<Sphere> & getSpheres() const {return spheres;}
		inline const std::vector<Light> & getLights() const {return lights;}
		inline const Vector<double> & getAmbientLight() const {return ambientLight;}
		inline const Camera & getCamera() const {return camera;}
		/* Operator overload methods */
		Scene & operator=(const Scene &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Scene object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Scene &scene)
		{
			//Load the class attribute information to the ostream object reference.
			out << "Scene" << std::endl;
			
			for (unsigned int i = 0; i < scene.getModels().size(); i++)
			{
				out << scene.getModels()[i] << std::endl;
			}
			
			for (unsigned int i = 0; i < scene.getSpheres().size(); i++)
			{
				out << "sphere " << scene.getSpheres()[i] << std::endl;
			}
			
			for (unsigned int i = 0; i < scene.getLights().size(); i++)
			{
				out << "light " << scene.getLights()[i] << std::endl;
			}
			
			out << "ambientLight " << scene.getAmbientLight() << std::endl;
			
			out << scene.getCamera() << std::endl;
			
			out << "recursion " << scene.getCamera().getRecursionLevel();
			
			//Return the ostream object reference.
			return out;
		}
		/* Other methods */
		inline bool isInitialized() const {return initialized;}
		bool writePPMFile(const char *ppmFilename);
	
	private:
		/* Class Attributes
		 *  models: All models to be rendered in the scene.
		 *  spheres: All spheres to be rendered in the scene.
		 *  lights: All point lights to be used in rendering the scene.
		 *  ambientLight: The overall lighting in the scene.
		 *  camera: The camera that will render the scene.
		 *  initialized: Informs the main program if the scene object is properly initialized.
		 */
		std::vector<Model> models;
		std::vector<Sphere> spheres;
		std::vector<Light> lights;
		Vector<double> ambientLight;
		Camera camera;
		bool initialized;
		/* Other methods */
		void constructScene();
		unsigned int numberOfModels(std::ifstream &fileReader);
		unsigned int numberOfLights(std::ifstream &fileReader);
		unsigned int numberOfSpheres(std::ifstream &fileReader);
		bool readDriverData(const char *driverFilename);
};

#endif
