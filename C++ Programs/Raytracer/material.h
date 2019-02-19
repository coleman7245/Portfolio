/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include <iostream>
#include <fstream>

using namespace std;

class Material
{
	public:
		Material();
		Material(const Vector &KA, const Vector &KD, const Vector &KO, const Vector &KR, const Vector &KS, const unsigned int &bIndex, 
				 const unsigned int &eIndex, const double &pc, const double &ETA);
		~Material();
		const unsigned int & getBeginningIndex() const;
		const unsigned int & getEndingIndex() const;
		const double & getETA() const;
		const Vector & getKA() const;
		const Vector & getKD() const;
		const Vector & getKO() const;
		const Vector & getKR() const;
		const Vector & getKS() const;
		const double & getNS() const;
		void setBeginningIndex(const unsigned int &bIndex);
		void setEndingIndex(const unsigned int &eIndex);
		friend ofstream & operator<<(ofstream &out, const Material &material)
		{
			out <<  material.getKA() << " " << material.getKD() << " " << material.getKO() << " " << material.getKR() << " " << 
				material.getKS() << " " << material.getNS() << " " << material.getETA() << " " << material.getBeginningIndex() << " " << 
				material.getEndingIndex();
			
			return out;
		}
		
	private:
		Vector ka;
		Vector kd;
		Vector ko;
		Vector kr;
		Vector ks;
		unsigned int beginningIndex;
		unsigned int endingIndex;
		double phongConstant;
		double eta;
};

ostream & operator<<(ostream &out, const Material &material);

#endif
