/* Author: coleman7245
 * File: C++ Matrix class for the Raytracer program.
 * Last Update: 2/25/19
 * File Summary: The Matrix class provides the main mathematical means to compute intersections of rays, as well as face transformations. 
 * The C++ vector class is used for the rows and columns. 
 */

#include "matrix.h"

//Method Summary: Default constructor
Matrix::Matrix() : rows(0), columns(0), matrix(rows) {}

//Method Summary: Constructor using input from the provided parameters.
Matrix::Matrix(const unsigned int r, const unsigned int c) : rows(r), columns(c) 
{
	//Set the dimensions of the matrix with the given parameters.
	setDimensions(r, c);
}

//Method Summary: Copy Constructor
Matrix & Matrix::operator=(const Matrix &rhs)
{
	//If the rows of this matrix and the right hand matrix aren't the same size, then...
	if (rhs.getRowSize() != getRowSize() || rhs.getColumnSize() != getColumnSize())
	{
		//Set the dimensions of this matrix to those of the right hand matrix.
		setDimensions(rhs.getRowSize(), rhs.getColumnSize());
	}
	
	//For every row and every column of this matrix...
	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			//Set the value at this position with the corresponding value in the right hand matrix.
			(*this).at(r, c) = rhs.at(r, c);
		}
	}
	
	//Return the reference to this matrix.
	return *this;
}

//Method Summary: Deconstructor
Matrix::~Matrix() {}

//Method Summary: Calculates a value used to create an inverse matrix.
//Precondtions: None.
//Postconditions: Returns the determinant of the matrix.
double Matrix::determinant() const
{
	//If the matrix is a simple 2 x 2 matrix...
	if (getRowSize() == 2 && getRowSize() == getColumnSize())
	{
		//Return a simple, but effective, calculation as the determinant.
		return (((*this).at(0, 0) * (*this).at(1, 1)) - ((*this).at(0, 1) * (*this).at(1, 0)));
	}
	
	//If the matrix is 3 x 3, then...
	if (getRowSize() == 3 && getRowSize() == getColumnSize())
	{
		//Break down the 3 x 3 matrix into a series of 2 x 2 matrices. 
		Matrix A = Matrix(2, 2);
		Matrix B = Matrix(2, 2);
		Matrix C = Matrix(2, 2);
		
		//Fill in the values accordingly. 
		A.at(0, 0) = (*this).at(1, 1);
		A.at(0, 1) = (*this).at(1, 2);
		A.at(1, 0) = (*this).at(2, 1);
		A.at(1, 1) = (*this).at(2, 2);
		B.at(0, 0) = (*this).at(1, 0);
		B.at(0, 1) = (*this).at(1, 2);
		B.at(1, 0) = (*this).at(2, 0);
		B.at(1, 1) = (*this).at(2, 2);
		C.at(0, 0) = (*this).at(1, 0);
		C.at(0, 1) = (*this).at(1, 1);
		C.at(1, 0) = (*this).at(2, 0);
		C.at(1, 1) = (*this).at(2, 1);
		
		//Calculate the determinant of the 3 x 3 matrix by using the determinants of the 2 x 2 matrices, then return it.
		return ((*this).at(0, 0) * A.determinant()) - ((*this).at(0, 1) * B.determinant()) + ((*this).at(0, 2) * C.determinant());
	}
	
	//Return 0, indicating failure.
	return 0;
}

//Method Summary: Multiplies two matrices together, provided that the column size of the left matrix match the row size of the right matrix.
//Precondtions: Two matrices, one for the left and one for the right.
//Postconditions: The product of the matrices is returned, which has the column size of the left matrix and the row size of the right 
//matrix.
Matrix Matrix::operator*(const Matrix &rhs) const
{
	//If the column size of the left matrix does NOT equal the row size of the right matrix, then...
	if (getColumnSize() != rhs.getRowSize())
	{
		//Return a default matrix.
		return Matrix();
	}
	
	//result: The product of the matrices.
	//i1, i2, j1, j2: Positions of the rows and columns of the two matrices.
	//dotProduct: The dot product required in calculating the product of two matrices.
	Matrix result = Matrix(getRowSize(), rhs.getColumnSize());
	unsigned int r1 = 0, r2 = 0, c1 = 0, c2 = 0;
	double dotProduct = 0;
	
	//For every row and column in the product of the two matrices...
	for (unsigned int r = 0; r < result.getRowSize(); r++)
	{
		for (unsigned int c = 0; c < result.getColumnSize(); c++)
		{
			//While left column and right row positions haven't reached their limit yet...
			while (c1 < getColumnSize() && r2 < rhs.getRowSize())
			{
				//Compute the dot product for this set of numbers and add it to the total.
				dotProduct += ((*this).at(r1, c1) * rhs.at(r2, c2));
				//Move to the next column on the left matrix.
				c1++;
				//Move to the next row on the right matrix.
				r2++;
			}
			
			//Store the dot product in the correct position of the product matrix.
			result.at(r, c) = dotProduct;
			//Reset the dot product value.
			dotProduct = 0.0;
			//Reset the column position on the left matrix.
			c1 = 0;
			//Reset the row position on the right matrix.
			r2 = 0;
			//Move to the next column on the right matrix.
			c2++;
		}
		
		//Move to the next row on the left matrix.
		r1++;
		//Reset the column position on the right matrix.
		c2 = 0;
	}
	
	//Return the product matrix.
	return result;
}

//Method Summary: Creates an identity matrix, which is a matrix defined by a principal diagonal of 1s surrounded by 0s. 
//Precondtions: The size of the identity matrix, which is for both the row and column size.
//Postconditions: The identity matrix is returned.
Matrix Matrix::identity(const unsigned int size)
{
	//Initialize the identity matrix with the parameter.
	Matrix I = Matrix(size, size);
	
	//For every row and column in the identity matrix...
	for (unsigned int r = 0; r < I.getRowSize(); r++)
	{
		for (unsigned int c = 0; c < I.getColumnSize(); c++)
		{
			//If the column is equal to the row, then...
			if (r == c)
			{
				//Set the element to 1.
				I.at(r, c) = 1.0;
			}
			else //Otherwise...
			{
				//Set the element to 0.
				I.at(r, c) = 0.0;
			}
		}
	}
	
	//Return the identity matrix.
	return I;
}

//Method Summary: Creates an inverse matrix of this matrix.
//Precondtions: None.
//Postconditions: An inverse matrix is returned.
Matrix Matrix::inverse() const
{
	//d: The determinant of the this matrix.
	double d = determinant();
	
	//If the determinant is 0, then...
	if (d == 0)
	{
		//Return a zero matrix.
		return zero(3, 3);
	}
	
	//minors: The 2 x 2 matrices formed out of the 3 x 3 matrix.
	//inverse: The inverse matrix.
	//cofactor: Scalar that helps compute the elements of the inverse matrix.
	Matrix minors = Matrix(getRowSize(), getColumnSize()), inverse = Matrix(getRowSize(), getColumnSize());	
	double cofactor = 1.0;
	
	//For every element in the matrix...
	for (unsigned int r = 0; r < getRowSize(); r++)
	{
		for (unsigned int c = 0; c < getColumnSize(); c++)
		{
			//Different column and row positions require slight alterations in the calculations.
			if (r == 0 && c == 0)
			{
				minors.at(r, c) = ((*this).at(1, 1) * (*this).at(2, 2)) - ((*this).at(1, 2) * (*this).at(2, 1));
			}
			else if (r == 0 && c == 1)
			{
				minors.at(r, c) = ((*this).at(1, 0) * (*this).at(2, 2)) - ((*this).at(1, 2) * (*this).at(2, 0));
			}
			else if (r == 0 && c == 2)
			{
				minors.at(r, c) = ((*this).at(1, 0) * (*this).at(2, 1)) - ((*this).at(1, 1) * (*this).at(2, 0));
			}
			else if (r == 1 && c == 0)
			{
				minors.at(r, c) = ((*this).at(0, 1) * (*this).at(2, 2)) - ((*this).at(0, 2) * (*this).at(2, 1));
			}
			else if (r == 1 && c == 1)
			{
				minors.at(r, c) = ((*this).at(0, 0) * (*this).at(2, 2)) - ((*this).at(0, 2) * (*this).at(2, 0));
			}
			else if (r == 1 && c == 2)
			{
				minors.at(r, c) = ((*this).at(0, 0) * (*this).at(2, 1)) - ((*this).at(0, 1) * (*this).at(2, 0));
			}
			else if (r == 2 && c == 0)
			{
				minors.at(r, c) = ((*this).at(0, 1) * (*this).at(1, 2)) - ((*this).at(0, 2) * (*this).at(1, 1));
			}
			else if (r == 2 && c == 1)
			{
				minors.at(r, c) = ((*this).at(0, 0) * (*this).at(1, 2)) - ((*this).at(0, 2) * (*this).at(1, 0));
			}
			else
			{
				minors.at(r, c) = ((*this).at(0, 0) * (*this).at(1, 1)) - ((*this).at(0, 1) * (*this).at(1, 0));
			}
			
			//Scale the element by the cofactor.
			minors.at(r, c) *= cofactor;
			//Reverse polarity on the cofactor.
			cofactor *= -1.0;
		}
	}
	
	//Transpose the minor matrix.
	minors = minors.transpose();
	
	//For every element in the matrix...
	for (unsigned int r = 0; r < getRowSize(); r++)
	{
		for (unsigned int c = 0; c < getColumnSize(); c++)
		{
			//Set the element of the inverse by the quotient of the element of the transposed minor and the determinant.
			inverse.at(r, c) = minors.at(r, c) / d;
		}
	}
	
	//Return the inverse matrix.
	return inverse;
}

//Method Summary: Creates a transpose of a given matrix.
//Precondtions: The matrix that will be transposed.
//Postconditions: Returns the transposed matrix.
Matrix Matrix::transpose() const
{
	//At: The transpose of Matrix A.
	Matrix At = Matrix(columns, rows);
	
	//For every element in the matrix.
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			//Set the element of the transposed matrix with the element of the matrix at the appropriate position.
			At.at(j, i) = (*this).at(i, j);
		}
	}
	
	//Return the transposed matrix.
	return At;
}

//Method Summary: An overloaded boolean operator that checks if two matrices are equal.
//Precondtions: A right matrix and a left matrix.
//Postconditions: Returns a true or false value depending on if the every element in the right matrix matches every element in the left 
//matrix.
bool Matrix::operator==(const Matrix &rhs) const
{
	//If the dimensions of both matrices are NOT the same, then...
	if ((getRowSize() != rhs.getRowSize()) || (getColumnSize() != rhs.getColumnSize()))
	{
		//Return false, indicating the matrices are NOT the same.
		return false;
	}
	
	//For every element in the matrix...
	for (unsigned int r = 0; r < getRowSize() && r < rhs.getRowSize(); r++)
	{
		for (unsigned int c = 0; c < getColumnSize() && c < rhs.getColumnSize(); c++)
		{
			//If the elements are NOT equal, then...
			if ((*this).at(r, c) != rhs.at(r, c))
			{
				//Return false, indicating the matrices are NOT equal. 
				return false;
			}
		}
	}
	
	//Return true, indicating the matrices are equal.
	return true;
}

//Method Summary: An overloaded boolean operator that checks if two matrices are NOT equal.
//Precondtions: A right matrix and a left matrix.
//Postconditions: Returns a true or false value depending on if the every element in the right matrix fails to match every element in the 
//left matrix.
bool Matrix::operator!=(const Matrix &rhs) const
{
	//If the dimensions of both matrices are NOT the same, then...
	if ((getRowSize() != rhs.getRowSize()) || (getColumnSize() != rhs.getColumnSize()))
	{
		//Return true, indicating the matrices are NOT the same.
		return true;
	}
	
	//For every element in the matrix...
	for (unsigned int r = 0; r < getRowSize() && r < rhs.getRowSize(); r++)
	{
		for (unsigned int c = 0; c < getColumnSize() && c < rhs.getColumnSize(); c++)
		{
			//If the elements are NOT equal, then...
			if ((*this).at(r, c) != rhs.at(r, c))
			{
				//Return true, indicating the matrices are NOT equal.
				return true;
			}
		}
	}
	
	//Return false, indicating the matrices are equal.
	return false;
}
