/* 
 * Author: coleman7245
 * Project: Linux Shared Memory Example
 * Last Update: 2/25/19
 */ 

#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "FileReader.h"

#define BUFFER_SIZE sizeof(float)

int main (int argc, char **argv)
{
	printf("Median process [%d]: Starting.\n", getpid());
	
	FILE *file = fopen(argv[1], "r"); //Open the file with the given filename.
	
	if (file == NULL) //If the file failed to open, then...
	{
		return 0; //Return NULL.
	}
	
	int size = 0; //The number of elements in the array of integers. 
	float *numbers = readFile(file, &size); //Create an array of integers with the data read from the given file.
	int pos = 0; //Position in the array of integers.
	float min; //The minimum integer in the array.
	float max; //The maximum integer in the array.
	float median = 0; //The median of the array of integers.
	int fd_read = atoi(argv[2]);
	int fd_write = atoi(argv[3]);
	char *data = NULL;
	int shmid = 0;
	
	if (numbers == NULL) //If NULL was returned from the file read, then...
	{
		return 0; //Return false to indicate failure.
	}
	
	close(fd_write);
	read(fd_read, &shmid, sizeof(int));
	close(fd_read);
	
	data = shmat(shmid, 0, 0);
	perror("shmat");
	
	if (size == 1) //If there is only one integer, then...
	{
		median = numbers[0]; //The median is the lone integer.
	}
	else //Otherwise...
	{
		min = numbers[0]; //The minimum is the first integer.
		max = numbers[1]; //The maximum is the second integer.
	
		while (pos < size) //While the position within the array is less than the total size, do...
		{
			if (min > numbers[pos]) //If the minimum is greater than the current integer, then...
			{
				min = numbers[pos]; //The mimimum is the current integer.
			}
			
			if (max < numbers[pos]) //If the maximum is less than the current integer, then...
			{
				max = numbers[pos]; //The maximum is the current integer.
			}
		
			pos++; //Increment the position within the array of integers. 
		}
		
		if (min == max) //If the mimimum is equal to the maximum, then...
		{
			median = max; //The median is the maximum.
		}
		else //Otherwise...
		{
			median = ((max - min) / 2) + min; //THe median is the sum of the minimum and the quotient of the difference between the maximum and the minimum and two.
		}
	}
	
	printf("Median process[%d]: Median is %f\n", getpid(), median);
	
	fclose(file); //Close the file.
	free(numbers); //Free the memory for the array of integers.
	numbers = NULL; //Set the integer pointer to NULL.
	
	sprintf(data, "%f", median);
	
	printf("Median process [%d]: Stopping.\n", getpid());
	
	if (median < 0) //If the mode is negative, then...
	{
		return -1; //Return -1.
	}
	
	if (median == 0) //If the mode is 0, then...
	{
		return 0; //Return 0.
	}
	
	shmdt(data);
	perror("shmdt");
	
	return 1; //Return true if the program ran successfully.
}

