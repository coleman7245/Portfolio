/* 
 * Author: Derek Coleman
 * Project: Linux Shared Memory Example
 * Last Update: 3/4/19
 */ 

#include "FileReader.h" //Include the FileReader header file.

//Method Summary: Gets the file size of an open file.
int getFileSize(FILE *file)
{
	fseek(file, 0, SEEK_END); //Seek the end of the file.
	int size = ftell(file); //Set the size to the end position of the file. 
	rewind(file); //Reset the file position.
	
	return size; //Return the estimated size.
}

//Method Summary: Reads an open file 
float * readFile(FILE *file, int *size)
{
	int pos = 0; //Position in the array of integers.
	int file_size = getFileSize(file); //Retrieve the size of the file.
	int real_size = 0; //The number of elements in the array of integers.
	char line[100]; //Store the line of an input read.
	
	float *numbers = malloc(file_size * sizeof(int)); //Allocate the memory for the integer array.
	
	if (numbers == NULL) //If the memory failed to allocate properly, then...
	{
		return NULL; //Return NULL.
	}
	
	float current_num = 0; //Stores the current number from the file.
	
	while (!feof(file) && pos < file_size) //While the file position is not at the end, and the position is less than the size, do...
	{
		if (fgets(line, 100, file) == NULL) //If the fscan fails to return proper data, then...
		{
			break; //Break out of the loop.
		}
		
		sscanf(line, "%f", &current_num); //Read the input.
		numbers[pos] = current_num; //Store the number in the array.
		real_size++; //Increment the number of elements in the array of integers.
		pos++; //Increment the position within the array.
	}
	
	*size = real_size; //The value pointed to by size is the number of elements in the array of integers.
	
	return numbers; //Return the integers. 
}

