/* Author: coleman7245
 * File: C++ Matrix class for the Raytracer program.
 * Last Update: 2/18/2019
 * File Summary: The Matrix class provides the main mathematical means to compute intersections of rays, as well as face transformations. 
 * The C++ vector class is used for the rows and columns. 
 */

#include "matrix.h"

//Method Summary: Default constructor
Matrix::Matrix() : rows(0), columns(0), matrix(rows) {}

//Method Summary: Constructor using input from the provided parameters.
Matrix::Matrix(const unsigned int r, const unsigned int c) : rows(r), columns(c) {Matrix::setDimensions(r, c);}

//Method Summary: Deconstructor
Matrix::~Matrix() {}

//Method Summary: Calculates a value used to create an inverse matrix.
//Precondtions: None.
//Postconditions: Returns the determinant of the matrix.
double Matrix::determinant()
{
	//If the matrix is a simple 2 x 2 matrix...
	if (getRowSize() == 2 && getRowSize() == getColumnSize())
	{
		//Return a simple, but effective, calculation as the determinant.
		return (((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]));
	}
	
	//If the matrix is 3 x 3, then...
	if (getRowSize() == 3 && getRowSize() == getColumnSize())
	{
		//Break down the 3 x 3 matrix into a series of 2 x 2 matrices. 
		Matrix A = Matrix(2, 2);
		Matrix B = Matrix(2, 2);
		Matrix C = Matrix(2, 2);
		
		//Fill in the values accordingly. 
		A[0][0] = (*this)[1][1];
		A[0][1] = (*this)[1][2];
		A[1][0] = (*this)[2][1];
		A[1][1] = (*this)[2][2];
		B[0][0] = (*this)[1][0];
		B[0][1] = (*this)[1][2];
		B[1][0] = (*this)[2][0];
		B[1][1] = (*this)[2][2];
		C[0][0] = (*this)[1][0];
		C[0][1] = (*this)[1][1];
		C[1][0] = (*this)[2][0];
		C[1][1] = (*this)[2][1];
		
		//Calculate the determinant of the 3 x 3 matrix by using the determinants of the 2 x 2 matrices, then return it.
		return ((*this)[0][0] * A.determinant()) - ((*this)[0][1] * B.determinant()) + ((*this)[0][2] * C.determinant());
	}
	
	return 0.0;
}

//Method Summary: Get methods for class variables that simply return their value.
unsigned int Matrix::getRowSize() const {return rows;}
		
unsigned int Matrix::getColumnSize() const {return columns;}

//Method Summary: Multiplies two matrices together, provided that the column size of the left matrix match the row size of the right matrix.
//Precondtions: Two matrices, one for the left and one for the right.
//Postconditions: The product of the matrices is returned, which has the column size of the left matrix and the row size of the right 
//matrix.
Matrix Matrix::multiplyMatrices(const Matrix &lhs, const Matrix &rhs)
{
	//If the column size of the left matrix does NOT equal the row size of the right matrix, then...
	if (lhs.getColumnSize() != rhs.getRowSize())
	{
		//Return a default matrix.
		return Matrix();
	}
	
	//result: The product of the matrices.
	//i1, i2, j1, j2: Positions of the rows and columns of the two matrices.
	//dotProduct: The dot product required in calculating the product of two matrices.
	Matrix result = Matrix(lhs.getRowSize(), rhs.getColumnSize());
	unsigned int i1 = 0, i2 = 0, j1 = 0, j2 = 0;
	double dotProduct = 0.0;
	
	//For every row and column in the product of the two matrices...
	for (unsigned int i = 0; i < result.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < result.getColumnSize(); j++)
		{
			//While left column and right row positions haven't reached their limit yet...
			while (j1 < lhs.getColumnSize() && i2 < rhs.getRowSize())
			{
				//Compute the dot product for this set of numbers and add it to the total.
				dotProduct += (lhs[i1][j1] * rhs[i2][j2]);
				//Move to the next column on the left matrix.
				j1++;
				//Move to the next row on the right matrix.
				i2++;
			}
			
			//Store the dot product in the correct position of the product matrix.
			result[i][j] = dotProduct;
			//Reset the dot product value.
			dotProduct = 0.0;
			//Reset the column position on the left matrix.
			j1 = 0;
			//Reset the row position on the right matrix.
			i2 = 0;
			//Move to the next column on the right matrix.
			j2++;
		}
		
		//Move to the next row on the left matrix.
		i1++;
		//Reset the column position on the right matrix.
		j2 = 0;
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
	for (unsigned int i = 0; i < I.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < I.getColumnSize(); j++)
		{
			//If the column is equal to the row, then...
			if (i == j)
			{
				//Set the element to 1.
				I[i][j] = 1.0;
			}
			else //Otherwise...
			{
				//Set the element to 0.
				I[i][j] = 0.0;
			}
		}
	}
	
	//Return the identity matrix.
	return I;
}

//Method Summary: Creates an inverse matrix of this matrix.
//Precondtions: None.
//Postconditions: An inverse matrix is returned.
Matrix Matrix::inverse()
{
	//d: The determinant of the this matrix.
	double d = determinant();
	
	//If the determinant is 0, then...
	if (d == 0)
	{
		//Return a zero matrix.
		return Matrix::zero(3, 3);
	}
	
	//minors: The 2 x 2 matrices formed out of the 3 x 3 matrix.
	//inverse: The inverse matrix.
	//cofactor: Scalar that helps compute the elements of the inverse matrix.
	Matrix minors = Matrix(getRowSize(), getColumnSize()), inverse = Matrix(getRowSize(), getColumnSize());	
	double cofactor = 1.0;
	
	//For every element in the matrix...
	for (unsigned int i = 0; i < getRowSize(); i++)
	{
		for (unsigned int j = 0; j < getColumnSize(); j++)
		{
			//Different column and row positions require slight alterations in the calculations.
			if (i == 0 && j == 0)
			{
				minors[i][j] = ((*this)[1][1] * (*this)[2][2]) - ((*this)[1][2] * (*this)[2][1]);
			}
			else if (i == 0 && j == 1)
			{
				minors[i][j] = ((*this)[1][0] * (*this)[2][2]) - ((*this)[1][2] * (*this)[2][0]);
			}
			else if (i == 0 && j == 2)
			{
				minors[i][j] = ((*this)[1][0] * (*this)[2][1]) - ((*this)[1][1] * (*this)[2][0]);
			}
			else if (i == 1 && j == 0)
			{
				minors[i][j] = ((*this)[0][1] * (*this)[2][2]) - ((*this)[0][2] * (*this)[2][1]);
			}
			else if (i == 1 && j == 1)
			{
				minors[i][j] = ((*this)[0][0] * (*this)[2][2]) - ((*this)[0][2] * (*this)[2][0]);
			}
			else if (i == 1 && j == 2)
			{
				minors[i][j] = ((*this)[0][0] * (*this)[2][1]) - ((*this)[0][1] * (*this)[2][0]);
			}
			else if (i == 2 && j == 0)
			{
				minors[i][j] = ((*this)[0][1] * (*this)[1][2]) - ((*this)[0][2] * (*this)[1][1]);
			}
			else if (i == 2 && j == 1)
			{
				minors[i][j] = ((*this)[0][0] * (*this)[1][2]) - ((*this)[0][2] * (*this)[1][0]);
			}
			else
			{
				minors[i][j] = ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);
			}
			
			//Scale the element by the cofactor.
			minors[i][j] *= cofactor;
			//Reverse polarity on the cofactor.
			cofactor *= -1.0;
		}
	}
	
	//Transpose the minor matrix.
	minors = transpose(minors);
	
	//For every element in the matrix...
	for (unsigned int i = 0; i < getRowSize(); i++)
	{
		for (unsigned int j = 0; j < getColumnSize(); j++)
		{
			//Set the element of the inverse by the quotient of the element of the transposed minor and the determinant.
			inverse[i][j] = minors[i][j] / d;
		}
	}
	
	//Return the inverse matrix.
	return inverse;
}

//Method Summary: Overloaded operator for accessing the element of the matrix.
//Precondtions: The position of the element.
//Postconditions: The element is returned.
const vector<double> & Matrix::operator[](int r) const {return matrix[r];}

//Method Summary: Overloaded operator for accessing the element of the matrix.
//Precondtions: The position of the element.
//Postconditions: The element is returned.
vector<double> & Matrix::operator[](int r) {return matrix[r];}

//Method Summary: Set methods that simply set the values for class variables.
void Matrix::setColumnSize(unsigned int c)
{
	columns = c;
	
	for (unsigned int i = 0; i < rows; i++)
	{
		matrix[i].resize(columns, 0.0);
	}
}	
		
void Matrix::setDimensions(unsigned int r, unsigned int c)
{
	Matrix::setRowSize(r);
	Matrix::setColumnSize(c);		
}

void Matrix::setRowSize(unsigned int r)
{
	rows = r;
	matrix.resize(rows);
}

//Method Summary: Creates a transpose of a given matrix.
//Precondtions: The matrix that will be transposed.
//Postconditions: Returns the transposed matrix.
Matrix Matrix::transpose(const Matrix &A)
{
	//At: The transpose of Matrix A.
	Matrix At = Matrix(A.getColumnSize(), A.getRowSize());
	
	//For every element in the matrix.
	for (unsigned int i = 0; i < A.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < A.getColumnSize(); j++)
		{
			//Set the element of the transposed matrix with the element of the matrix at the appropriate position.
			At[j][i] = A[i][j];
		}
	}
	
	//Return the transposed matrix.
	return At;
}

//Method Summary:
//Precondtions:
//Postconditions:
Matrix Matrix::zero(const unsigned int r, const unsigned int c) {return Matrix(r, c);}

//Method Summary: Overloaded ostream operator for debugging purposes.
//Precondtions: An ostream object and a matrix.
//Postconditions: Every element of the matrix is displayed.
ostream & operator<<(ostream &out, const Matrix &matrix)
{
	for (unsigned int i = 0; i < matrix.getRowSize(); i++)
	{
		out << "| ";
		
		for (unsigned int j = 0; j < matrix.getColumnSize(); j++)
		{
			out << matrix[i][j] << " ";
		}
		
		out << "|" << endl;
	}
	
	return out;
}

//Method Summary: An overloaded boolean operator that checks if two matrices are equal.
//Precondtions: A right matrix and a left matrix.
//Postconditions: Returns a true or false value depending on if the every element in the right matrix matches every element in the left 
//matrix.
bool operator==(const Matrix &lhs, const Matrix &rhs)
{
	//If the dimensions of both matrices are NOT the same, then...
	if ((lhs.getRowSize() != rhs.getRowSize()) || (lhs.getColumnSize() != rhs.getColumnSize()))
	{
		//Return false, indicating the matrices are NOT the same.
		return false;
	}
	
	//For every element in the matrix...
	for (unsigned int i = 0; i < lhs.getRowSize() && i < rhs.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < lhs.getColumnSize() && j < rhs.getColumnSize(); j++)
		{
			//If the elements are NOT equal, then...
			if (lhs[i][j] != rhs[i][j])
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
bool operator!=(const Matrix &lhs, const Matrix &rhs)
{
	//If the dimensions of both matrices are NOT the same, then...
	if ((lhs.getRowSize() != rhs.getRowSize()) || (lhs.getColumnSize() != rhs.getColumnSize()))
	{
		//Return true, indicating the matrices are NOT the same.
		return true;
	}
	
	//For every element in the matrix...
	for (unsigned int i = 0; i < lhs.getRowSize() && i < rhs.getRowSize(); i++)
	{
		for (unsigned int j = 0; j < lhs.getColumnSize() && j < rhs.getColumnSize(); j++)
		{
			//If the elements are NOT equal, then...
			if (lhs[i][j] != rhs[i][j])
			{
				//Return true, indicating the matrices are NOT equal.
				return true;
			}
		}
	}
	
	//Return false, indicating the matrices are equal.
	return false;
}
