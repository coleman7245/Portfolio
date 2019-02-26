/*
 * Author: coleman7245
 * Project: Lab 7 Exercise
 * Last Update: 2/26/19
 */

#include<iostream>

void setDoubleVariable(double &num);
void bubbleSortXYZ(double &num1, double &num2, double &num3);
void printXYZ(const double & _x, const double & _y, const double & _z);

int main()
{
	double x, y, z;
	
	setDoubleVariable(x);
	setDoubleVariable(y);
	setDoubleVariable(z);

	printXYZ(x, y, z);

	bubbleSortXYZ(x, y, z);

	printXYZ(x, y, z);
}

void setDoubleVariable(double &num)
{
	std::cout << "Please enter a number.\n" << std::endl;

	std::cin >> num;

	std::cout << std::endl;
}

void bubbleSortXYZ(double &num1, double &num2, double &num3)
{
	double temp;
	bool done;

	do
	{
		done = true;
		
		if (num2 < num1)
		{
			temp = num2;
			num2 = num1;
			num1 = temp;
			done = false;
		}
		
		if (num3 < num2)
		{
			temp = num3;
			num3 = num2;
			num2 = temp;
			done = false;
		}
		
	} while (!done);
}

void printXYZ(const double & _x, const double & _y, const double & _z)
{
	std::cout << "Number X: " << _x << "\nNumber Y: " << _y << "\nNumber Z: " << _z << "\n" << std::endl;
}
