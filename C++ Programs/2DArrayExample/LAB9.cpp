/*
 * Author: coleman7245
 * Project: Lab 9 Exercise
 * Last Update: 2/26/19
 */

#include<iostream>

const int ROWS = 3;
const int COL = 2;

void initialize(int (&list)[ROWS][COL]);
void addNumber(int (&list)[ROWS][COL]); 
void printTwoDimensionalArray(int (&list)[ROWS][COL]);

int main()
{
	int scroll[ROWS][COL];

	initialize(scroll);
	addNumber(scroll);
	printTwoDimensionalArray(scroll);

	return 0;
}

void initialize(int (&list)[ROWS][COL])
{
	int currentRow, currentColumn;

	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		for (currentColumn = 0; currentColumn < COL; currentColumn++)
		{
			list[currentRow][currentColumn] = 0;
			std::cout << "\nRow: " << currentRow << "\nColumn: " << currentColumn << std::endl;
		}
	}
}

void addNumber(int (&list)[ROWS][COL])
{
	int currentRow, currentColumn;

	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		for (currentColumn = 0; currentColumn < COL; currentColumn++)
		{
			std::cout << "Please enter a number.\n" << std::endl;
			std::cin >> list[currentRow][currentColumn];
		}
	}
}

void printTwoDimensionalArray(int (&list)[ROWS][COL])
{
	int currentRow, currentColumn;

	for (currentRow = 0; currentRow < ROWS; currentRow++)
	{
		for (currentColumn = 0; currentColumn < COL; currentColumn++)
		{
			std::cout << "\n The value at row " << currentRow << " and column " << currentColumn << " is " << 
				list[currentRow][currentColumn] << "\n" << std::endl;
		}
	}
}
