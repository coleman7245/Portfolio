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
	printf("Mean process [%d]: Starting.\n", getpid());
	
	FILE *file = fopen(argv[1], "r"); //Open the file with the given filename.
	
	if (file == NULL) //If the file failed to open, then...
	{
		return 0; //Return NULL.
	}
	
	int size = 0; //The number of elements in the array of integers. 
	float *numbers = readFile(file, &size); //Create an array of integers with the data read from the given file.
	int pos = 0; //Position in the array of integers.
	float mean = 0; //The average of the counted numbers.
	float count = 0; //The sum of all numbers.
	int fd_read = atoi(argv[2]);
	int fd_write = atoi(argv[3]);
	char *data;
	int shmid = 0;
	
	if (numbers == NULL) //If NULL was returned from the file read, then...
	{
		return 0; //Return false to indicate failure.
	}
	
	close(fd_write);
	read(fd_read, &shmid, sizeof(int));
	close(fd_read);
	
	printf("Mean process [%d]: read 4 bytes containing shmid %d\n", getpid(), shmid);
	
	//printf("shmid = %d\n", shmid);
	
	data = shmat(shmid, 0, 0);
	perror("shmat");
	
	while (pos < size) //While the position within the array is less than the total size, do...
	{
		mean += numbers[pos]; //Add to the overall sum of integers.
		pos++; //Increment the position within the array of integers. 
	}
	
	if (pos == 0)
	{
		return 0;
	}
	
	count = (float)pos;
	mean /= count; //Divide the sum by the count to find the mean of the integers. 
	
	printf("Mean process[%d]: Mean is %f\n", getpid(), mean);
	
	fclose(file); //Close the file.
	free(numbers); //Free the memory for the array of integers.
	numbers = NULL; //Set the integer pointer to NULL.
	
	sprintf(data, "%f", mean);
	perror("sprintf");
	printf("Mean process [%d]: Stopping.\n", getpid());
	
	if (mean < 0) //If the mode is negative, then...
	{
		return -1; //Return -1.
	}
	
	if (mean == 0) //If the mode is 0, then...
	{
		return 0; //Return 0.
	}
	
	shmdt(data);
	perror("shmdt");
	
	return 1; //Return 1 if the program ran successfully.
}
