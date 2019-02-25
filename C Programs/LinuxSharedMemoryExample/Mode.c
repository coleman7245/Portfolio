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
	printf("Mode process [%d]: Starting.\n", getpid());
	
	FILE *file = fopen(argv[1], "r"); //Open the file with the given filename.
	
	if (file == NULL) //If the file failed to open, then...
	{
		return 0; //Return NULL.
	}
	
	int size = 0; //The number of elements in the array of integers. 
	float *numbers = readFile(file, &size); //Create an array of integers with the data read from the given file.
	int pos1 = 0, pos2 = 0; //Positions in the array of integers.
	int highest_freq = 0; //The current highest frequency.
	int freq = 0; //The frequency of one particular integer amongst the rest.
	float mode = 0; //The most frequent integer amongst the rest.
	float current = 0; //The current integer being evaluated.
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
	
	mode = numbers[0];
	
	while (pos1 < size) //While the first position within the array is less than the total size, do...
	{
		current = numbers[pos1];
		
		while (pos2 < size) //While the second position within the array is less than the total size, do...
		{
			if (numbers[pos2] == current) //If the current integer is equal to the current contender for mode, then...
			{
				freq++; //Increment the frequency.
			}
			
			pos2++; //Increment the second position within the array of integers. 
		}
		
		if (freq > highest_freq) //If the current frequency is the highest frequency, then...
		{
			highest_freq = freq; //The highest frequency is the current frequency. 
			mode = current; //The mode is the current integer.
		} 
		
		freq = 0; //Reset the current frequency.
		pos2 = 0; //Reset the second position.
		pos1++; //Increment the first position within the array of integers. 
	}
	
	printf("Mode process[%d]: Mode is %f\n", getpid(), mode);
	
	fclose(file); //Close the file.
	free(numbers); //Free the memory for the array of integers.
	numbers = NULL; //Set the integer pointer to NULL.
	
	printf("Mode process [%d]: Stopping.\n", getpid());
	
	sprintf(data, "%f", mode);
	
	if (mode < 0) //If the mode is negative, then...
	{
		return -1; //Return -1.
	}
	
	if (mode == 0) //If the mode is 0, then...
	{
		return 0; //Return 0.
	}
	
	shmdt(data);
	perror("shmdt");
	
	return 1; //Return 1 if the program ran successfully.
}

