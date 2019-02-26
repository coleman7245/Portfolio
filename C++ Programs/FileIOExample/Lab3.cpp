/*
 * Author: coleman7245
 * Project: Lab 3 Exercise
 * Last Update: 2/26/19
 */

#include <iostream>
#include <fstream>

int main()
{
	std::ifstream inFile;
	std::ofstream outFile;

	float x;

	inFile.open("in.txt");

	if(!inFile.is_open())
	{
		std::cout << "File Error!" << std::endl;
		return 1;
	}

	inFile >> x;

	inFile.close();

	outFile.open("out.txt");

	outFile << "x became " << (x + 6.5) << "." << std::endl;

	outFile.close();

	return 0;
}
