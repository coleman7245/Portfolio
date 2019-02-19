/* Author: coleman7245
 * File: 
 * Last Update: 2/18/2019
 * File Summary:
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
	public:
		Matrix();
		Matrix(const unsigned int r, const unsigned int c);
		~Matrix();
		double determinant();
		unsigned int getRowSize() const;
		unsigned int getColumnSize() const;
		static Matrix multiplyMatrices(const Matrix &lhs, const Matrix &rhs);
		static Matrix identity(const unsigned int size);
		Matrix inverse();
		const vector<double> & operator[](int r) const;
		vector<double> & operator[] (int r);
		void setColumnSize(unsigned int c);
		void setDimensions(unsigned int r, unsigned int c);
		void setRowSize(unsigned int r); 
		static Matrix transpose(const Matrix &A);
		static Matrix zero(const unsigned int r, const unsigned int c);
			
	private:
		unsigned int rows;
		unsigned int columns;
		vector< vector<double> > matrix;
};

ostream & operator<<(ostream &out, const Matrix &matrix);
bool operator==(const Matrix &rhs, const Matrix &lhs);
bool operator!=(const Matrix &rhs, const Matrix &lhs);

#endif
