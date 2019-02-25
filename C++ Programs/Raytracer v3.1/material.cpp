/* Author: coleman7245
 * File: C++ Material class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The class designed for storing information on materials attached to a model in a scene. It has no complex operations, just 
 * rudimentory get and set methods.
 */

#include "material.h"

//Method Summary: Default constructor
Material::Material() : ka(Vector<double>()), kd(Vector<double>()), ko(Vector<double>()), kr(Vector<double>()), ks(Vector<double>()), 
					   beginningIndex(0), endingIndex(0), phongConstant(0.0), eta(0.0) {}

//Method Summary: Constructor using input from the provided parameters.
Material::Material(const Vector<double> &KA, const Vector<double> &KD, const Vector<double> &KO, const Vector<double> &KR, 
				   const Vector<double> &KS, const unsigned int bIndex, const unsigned int eIndex, const double pc,  const double ETA) 
				   : ka(KA), kd(KD), ko(KO), kr(KR), ks(KS), beginningIndex(bIndex), endingIndex(eIndex), phongConstant(pc), eta(ETA) {}

//Method Summary: Deconstructor
Material::~Material() {}

//Method Summary: Copy constructor
//Preconditions: A constant Material object reference.
//Postconditions: The attributes of this Material object are copies of the parameter Material object.
Material & Material::operator=(const Material &rhs)
{
	//If the two references are NOT one in the same, then...
	if (this != &rhs)
	{
		//Copy all attributes to this Material instance.
		ka = rhs.getKA();
		kd = rhs.getKD();
		ko = rhs.getKO();
		kr = rhs.getKR();
		ks = rhs.getKS();
		beginningIndex = rhs.getBeginningIndex();
		endingIndex = rhs.getEndingIndex();
		phongConstant = rhs.getNS();
		eta = rhs.getETA();
	}
	
	//Return this Material object.
	return *this;
}
