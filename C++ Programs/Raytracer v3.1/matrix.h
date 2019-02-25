/* Author: coleman7245
 * File: C++ Matrix header file for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: Provides the function and class declarations for the Matrix class.
 */

//If the Matrix header hasn't been included, then...
#ifndef MATRIX_H
//Define the header file.
#define MATRIX_H

//Include the vector header for the matrix values.
#include <vector>
//Include the iostream header for displaying class attributes.
#include <iostream>

/* Class declaration */
class Matrix
{
	public:
		/* Constructor methods */
		Matrix();
		Matrix(const unsigned int r, const unsigned int c);
		~Matrix();
		/* Get methods */
		inline unsigned int getColumnSize() const {return columns;}
		inline unsigned int getRowSize() const {return rows;}
		/* Set methods */
		inline void setDimensions(const unsigned int r, const unsigned int c) {matrix.resize(r * c);}
		/* Operator overload methods */
		Matrix & operator=(const Matrix &rhs);
		Matrix operator*(const Matrix &rhs) const;
		//Method Summary: Displays the class object and its attributes.
		//Precondtions: An ostream object reference and a constant Matrix object reference.
		//Postconditions: Returns the ostream object reference loaded with the desired output.
		friend std::ostream & operator<<(std::ostream &out, const Matrix &m)
		{
			//Load the class attribute information to the ostream object reference.
			for (unsigned int r = 0; r < m.getRowSize(); r++)
			{
				out << "Matrix" << std::endl;
				
				for (unsigned int c = 0; c < m.getColumnSize(); c++)
				{
					out << m.at(r, c);
					
					if (c < m.getColumnSize() - 1)
					{
						out << " ";
					}
				}
				
				if (r < m.getRowSize() - 1)
				{
					out << std::endl;
				}
			}
			
			//Return the ostream object reference.
			return out;
		}
		bool operator==(const Matrix &rhs) const;
		bool operator!=(const Matrix &rhs) const;
		/* Other methods */
		inline double & at(const unsigned int r, const unsigned int c) {return matrix.at(r * columns + c);}
		inline const double & at(const unsigned int r, const unsigned int c) const {return matrix.at(r * columns + c);}
		double determinant() const;
		static Matrix identity(unsigned int size);
		Matrix inverse() const;
		Matrix transpose() const;
		static inline Matrix zero(const unsigned int r, const unsigned int c) {return Matrix(r, c);}
			
	private:
		/* Class attributes
		 *  rows: The row size of the matrix.
		 *  columns: The column size of the matrix.
		 *  matrix: The vector representing the matrix anbd storing its values.
		 */
		unsigned int rows;
		unsigned int columns;
		std::vector<double> matrix;
};

#endif
