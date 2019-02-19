/* Author: coleman7245
 * File: C++ Camera Class Header for Raytracer
 * Last Update: 2/18/2019
 * File Summary: Method prototypes and class variables in the Camera class.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "triangle.h"
#include "vector.h"
#include "matrix.h"
#include "model.h"
#include "ray.h"
#include "sphere.h"
#include "light.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

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

class Camera
{
	public:
		Camera();
		Camera(const Vector &look, const Vector &eye, double d, double nr, double fr, double tp, double bm, double lt, double rt, double wh, 
			   double ht, const Vector &_up, const Vector &al);
		~Camera();
		void addLight(const Light &light);
		void constructCameraCoordinates();
		Ray pixelRay(double i, double j);
		void createPixelRays();
		void setColors(vector<Sphere> &spheres, vector<Model> &models, Vector &attenuation, unsigned int recursionLevel);
		const Vector & getAmbientLight() const;
		double getBottom() const;
		const vector< vector<Vector> > & getColors() const;
		double getDistance() const;
		const Vector & getEyePoint() const;
		double getFar() const;
		double getHeight() const;
		double getLeft() const;
		const vector<Light> & getLights() const;
		const Vector & getLookAtPoint() const;
		double getNear() const;
		double getRight() const;
		double getTop() const;
		double getWidth() const;
		const Vector & getU() const;
		const Vector & getUp() const;
		const Vector & getV() const;
		const Vector & getW() const;
		inline const vector< vector<Ray> > & getPixelRays() const {return pixelRays;}
		void recursiveTrace(Ray &pRay, vector<Sphere> &spheres, vector<Model> &models, Vector &accumulation, const Vector &attenuation, 
							int level, unsigned int lastFaceIndex, unsigned int lastSphereIndex);
		Ray createRefractionExitRay(const Vector &center, const Vector &W, const Vector &pointOfIntersection, const double &etai);
		friend ostream & operator<<(ostream &out, const Camera &camera)
		{
			out << "look " << camera.getLookAtPoint() << endl;
			out << "eye " << camera.getEyePoint() << endl;
			out << "view " << camera.getDistance() << " " << camera.getNear() << " " << camera.getFar() << " " << camera.getTop() << " " 
				<< camera.getBottom() << " " << camera.getLeft() << " " << camera.getRight() << endl;
			out << "width " << camera.getWidth() << endl;
			out << "height " << camera.getHeight() << endl;
			out << "up " << camera.getUp() << endl;
			out << "u " << camera.getU() << endl;
			out << "v " << camera.getV() << endl;
			out << "w " << camera.getW() << endl;
			
			for (unsigned int i = 0; i < camera.getPixelRays().size(); i++)
			{
				for (unsigned int j = 0; j < camera.getPixelRays()[i].size(); j++)
				{
					out << "pixelray " << camera.getPixelRays()[i][j] << endl;
				}
			}
			
			for (unsigned int i = 0; i < camera.getColors().size(); i++)
			{
				
				for (unsigned int j = 0; j < camera.getColors()[i].size(); j++)
				{
					out << "color " << camera.getColors()[i][j];
					
					if (i < camera.getColors().size() - 1)
					{
						out << endl;
					}
				}
			}
			
			return out;
		}
		
	private:
		//The point of interest to the camera.
		Vector lookAtPoint;
		//The eye, or origin, of the camera.
		Vector eyePoint;
		//The distance of the view.
		double distance;
		//The near clipping plane.
		double near;
		//The far clipping plane.
		double far;
		//The top clipping plane.
		double top;
		//The bottom clipping plane.
		double bottom;
		//The left clipping plane.
		double left;
		//The right clipping plane.
		double right;
		//The width of the camera.
		double width;
		//The height of the camera.
		double height;
		//The up direction in the rendered scene.
		Vector up;
		//Basis vectors
		Vector u;
		Vector v;
		Vector w;
		//Pixel rays cooresponding to each pixel at a given (x,y) position.
		vector< vector<Ray> > pixelRays;
		//Colors resulting from the recursive ray trace and cooresponding to each pixel at a given (x,y) position.
		vector< vector<Vector> > colors;
		//Point lights for a scene.
		vector<Light> lights;
		//The ambient lighting for a scene.
		Vector ambientLight;
		//Helper functions don't need to be declared public.
		bool inScene(Ray &pRay, vector<Sphere> &spheres, vector<Model> &models, bestPick &best, unsigned int lastFaceIndex, unsigned int lastSphereIndex);
		Vector createRefractionTVector(const Vector &W, const Vector &N, const double &eta1, const double &eta2);
};

ostream & operator<<(ostream &out, const Camera &camera);

#endif
