/* Author: coleman7245
 * File: C++ Material header for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Material class.
 */

//If the material header hasn't been included, then...
#ifndef MATERIAL_H
//Define the header file.
#define MATERIAL_H

//Include the Vector header for the lighting vectors.
#include "vector.h"

/* Class declaration */
class Material
{
	public:
		/* Constructor methods */
		Material();
		Material(const Vector<double> &KA, const Vector<double> &KD, const Vector<double> &KO, const Vector<double> &KR, 
				 const Vector<double> &KS, const unsigned int bIndex, const unsigned int eIndex, const double pc, const double ETA);
		~Material();
		/* Get methods */
		inline unsigned int getBeginningIndex() const {return beginningIndex;}
		inline unsigned int getEndingIndex() const {return endingIndex;}
		inline const double getETA() const {return eta;}
		inline const Vector<double> & getKA() const {return ka;}
		inline const Vector<double> & getKD() const {return kd;}
		inline const Vector<double> & getKO() const {return ko;}
		inline const Vector<double> & getKR() const {return kr;}
		inline const Vector<double> & getKS() const {return ks;}
		inline double getNS() const {return phongConstant;}
		/* Set methods */
		inline void setBeginningIndex(const unsigned int bIndex) {beginningIndex = bIndex;}
		inline void setEndingIndex(const unsigned int eIndex) {endingIndex = eIndex;}
		/* Operator overload methods */
		Material & operator=(const Material &rhs);
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Material object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Material &material)
		{
			//Load the class attribute information to the ostream object reference.
			out <<  material.getKA() << " " << material.getKD() << " " << material.getKO() << " " << material.getKR() << " " << 
				material.getKS() << " " << material.getNS() << " " << material.getETA() << " " << material.getBeginningIndex() << " " << 
				material.getEndingIndex();
			
			//Return the ostream object reference.
			return out;
		}
		
	private:
		/* Class attributes
		 *  ka: Ambient shading vector.
		 *  kd: Diffuse shading vector.
		 *  ko: Refraction shading vector.
		 *  kr: Attenuation shading vector.
		 *  ks: Specular shading vector.
		 *  beginningIndex: The index to the beginning vertex that uses this material.
		 *  endingIndex: The index to the ending vertex that uses this material. 
		 *  phongConstant: Constant named after Phong that is used to calculate specular shading.
		 *  eta: The refraction index.
		 */
		Vector<double> ka;
		Vector<double> kd;
		Vector<double> ko;
		Vector<double> kr;
		Vector<double> ks;
		unsigned int beginningIndex;
		unsigned int endingIndex;
		double phongConstant;
		double eta;
};

#endif
