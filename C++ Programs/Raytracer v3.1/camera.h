/* Author: coleman7245
 * File: C++ Camera Class Header for Raytracer
 * Last Update: 2/25/19
 * File Summary: Method prototypes and class variables in the Camera class.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "model.h"
#include "sphere.h"
#include "light.h"
#include "viewplane.h"
#include <limits>

//Structure for containing closest intersection data.
struct bestPick
{
	//The closest intersected model.
	unsigned int modelIndex;
	//The closest intersected sphere.
	unsigned int sphereIndex;
	//The closest intersected face of the model.
	unsigned int faceIndex;
	//The intersection value.
	double t;
};

/* Class declaration */
class Camera
{
	public:
		/* Constructor methods */
		Camera();
		Camera(const Vector<double> &lookAtPointP, const Vector<double> &eyePointP, const ViewPlane &viewPlaneP, const double widthP, 
			const double heightP, const int recursionLevelP, const Vector<double> &upP);
		~Camera();
		/* Get methods */
		inline const std::vector< Vector<double> > & getColors() const {return colors;}
		inline const Vector<double> & getEyePoint() const {return eyePoint;}
		inline double getHeight() const {return height;}
		inline unsigned int getHeightInt() const {return heightInt;}
		inline const Vector<double> & getLookAtPoint() const {return lookAtPoint;}
		inline const std::vector<Ray> & getPixelRays() const {return pixelRays;}
		inline const int getRecursionLevel() const {return recursionLevel;}
		inline const Vector<double> & getUp() const {return up;}
		inline const Vector<double> & getU() const {return u;}
		inline const Vector<double> & getV() const {return v;}
		inline const ViewPlane & getViewPlane() const {return viewPlane;}
		inline const Vector<double> & getW() const {return w;}
		inline double getWidth() const {return width;}
		inline unsigned int getWidthInt() const {return widthInt;}
		/* Set methods */
		void setColors(const std::vector<Sphere> &spheres, const std::vector<Model> &models, const Vector<double> &attenuation, 
			const std::vector<Light> &lights, const Vector<double> &ambientLight);
		/* Operator overload methods */
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Camera object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Camera &camera)
		{
			//Load the class attribute information to the ostream object reference.
			out << "Camera" << std::endl;
			out << "look " << camera.getLookAtPoint() << std::endl;
			out << "eye " << camera.getEyePoint() << std::endl;
			out << "view " << camera.getViewPlane() << std::endl;
			out << "width " << camera.getWidth() << std::endl;
			out << "height " << camera.getHeight() << std::endl;
			out << "up " << camera.getUp() << std::endl;
			out << "u " << camera.getU() << std::endl;
			out << "v " << camera.getV() << std::endl;
			out << "w " << camera.getW() << std::endl;
			out << "recursion " << camera.getRecursionLevel() << std::endl;
			
			for (unsigned int i = 0; i < camera.getPixelRays().size(); i++)
			{
				out << "pixelray " << camera.getPixelRays()[i] << std::endl;
			}
			
			for (unsigned int i = 0; i < camera.getColors().size(); i++)
			{
				out << "color " << camera.getColors()[i];
				
				if (i < camera.getColors().size() - 1)
				{
					out << std::endl;
				}
			}
			
			//Return the ostream object reference.
			return out;
		}
		
	private:
		/* Class attributes
		 *  lookAtpoint: The point of interest to the camera.
		 *  eyePoint: The eye, or origin point, of the camera.
		 *  viewPlane: The viewplane of the camera.
		 *  width: The width of the resolution diaplayed by the camera.
		 *  height: The height of the resolution displayed by the camera.
		 *  up: The up direction in the rendered scene.
		 *  u: Basis vector for the camera's coordinate system.
		 *  v: Basis vector for the camera's coordinate system.
		 *  w: Basis vector for the camera's coordinate system.
		 *  pixelRays: Pixel rays cooresponding to each pixel at a given (x,y) position.
		 *  colors: Colors resulting from the recursive ray trace and cooresponding to each pixel at a given (x,y) position.
		*/
		Vector<double> lookAtPoint;
		Vector<double> eyePoint;
		ViewPlane viewPlane;
		double width;
		double height;
		int recursionLevel;
		Vector<double> up;
		unsigned int heightInt;
		unsigned int widthInt;
		Vector<double> u;
		Vector<double> v;
		Vector<double> w;
		std::vector<Ray> pixelRays;
		std::vector< Vector<double> > colors;
		/* Other methods */
		void constructCameraCoordinates();
		void createPixelRays();
		Ray createRefractionExitRay(const Vector<double> &center, const Vector<double> &W, const Vector<double> &pointOfIntersection, 
			const double etai) const;
		Vector<double> createRefractionTVector(const Vector<double> &W, const Vector<double> &N, const double eta1, 
			const double eta2) const;
		bestPick inScene(const Ray &pRay, const std::vector<Sphere> &spheres, const std::vector<Model> &models,
			const unsigned int lastFaceIndex, const unsigned int lastSphereIndex);
		Ray pixelRay(const double x, const double y) const;
		void recursiveTrace(const Ray &pRay, const std::vector<Sphere> &spheres, const std::vector<Model> &models, 
			const std::vector<Light> &lights, const Vector<double> &ambientLight, Vector<double> &accumulation, 
			const Vector<double> &attenuation, int level, const unsigned int lastFaceIndex, const unsigned int lastSphereIndex);
};

#endif
