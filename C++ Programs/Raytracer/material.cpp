/* Author: coleman7245
 * File: C++ Material class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The class designed for storing information on materials attached to a model in a scene. It has no complex operations, just 
 * rudimentory get and set methods.
 */

#include "material.h"

//Method Summary: Default constructor
Material::Material() : ka(Vector()), kd(Vector()), ko(Vector()), kr(Vector()), ks(Vector()), beginningIndex(0), endingIndex(0), phongConstant(0.0), eta(0.0) {}

//Method Summary: Constructor using input from the provided parameters.
Material::Material(const Vector &KA, const Vector &KD, const Vector &KO, const Vector &KR, const Vector &KS, const unsigned int &bIndex, const unsigned int &eIndex, const double &pc,  const double &ETA) 
: ka(KA), kd(KD), ko(KO), kr(KR), ks(KS), beginningIndex(bIndex), endingIndex(eIndex), phongConstant(pc), eta(ETA) {}

//Method Summary: Deconstructor
Material::~Material() {}

//Method Summary: Get methods for class variables that simply return their value.
const unsigned int & Material::getBeginningIndex() const {return beginningIndex;}

const unsigned int & Material::getEndingIndex() const {return endingIndex;}

const double & Material::getETA() const {return eta;}

const Vector & Material::getKA() const {return ka;}

const Vector & Material::getKD() const {return kd;}

const Vector & Material::getKO() const {return ko;}

const Vector & Material::getKR() const {return kr;}

const Vector & Material::getKS() const {return ks;}

const double & Material::getNS() const {return phongConstant;}

//Method Summary: Set methods that simply set the values for class variables.
void Material::setBeginningIndex(const unsigned int &bIndex) {beginningIndex = bIndex;}

void Material::setEndingIndex(const unsigned int &eIndex) {endingIndex = eIndex;}

//Method Summary: Overloaded ostream operator for debugging purposes.
//Preconditions: An ostream reference and a constant Material reference.
//Postconditions: Outputs traits of the Camera object through the ostream object.
ostream & operator<<(ostream &out, const Material &material)
{
	out <<  material.getKA() << " " << material.getKD() << " " << material.getKO() << " " << material.getKR() << " " << 
				material.getKS() << " " << material.getNS() << " " << material.getETA() << " " << material.getBeginningIndex() << " " << 
				material.getEndingIndex();
			
	return out;
}
