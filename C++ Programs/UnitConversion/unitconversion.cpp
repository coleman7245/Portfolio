/*
 * Author: coleman7245
 * Project: Exercise 16.1
 * Last Update: 2/26/19
 */

#include <iostream> 

const double CENTIMETERS_PER_INCH = 2.54;
const double INCHES_PER_FOOT = 12.0;
const double FEET_PER_YARD = 3.0;

int main()
{
	double centimeters, inches, feet, yards, y;

	std::cout << "Please enter the length in centimeters: " << std::endl;

	std::cin >> centimeters;

	std::cout << std::endl;

	yards = centimeters / (CENTIMETERS_PER_INCH * INCHES_PER_FOOT * FEET_PER_YARD);
	
	feet = yards- static_cast<int>(yards);
	feet = feet * FEET_PER_YARD;

	inches = feet - static_cast<int>(feet);
	inches = inches * INCHES_PER_FOOT + .5;
	
	std::cout << "The length of " << centimeters  << " cm. converts to " <<  static_cast<int>(yards)
	<< " yrds., " << static_cast<int>(feet) << " ft., and " << 
	static_cast<int>(inches) << " in.." << std::endl;

	std::cout << "Press q to quit." << std::endl;
	std::cin >> y;

	return 0;
}


