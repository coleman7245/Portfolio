/* 
 * Author: Derek Coleman
 * Project: Linux Shared Memory Example
 * Last Update: 3/4/19
 */ 

#define _XOPEN_SOURCE 700 //Define a linux constant for the latest definition of the Unix kernal.
#include <sys/types.h> //Include the Unix types header for the process ID variable.
#include <unistd.h> //Include the Unix standard header for the fork system. call.
#include <sys/ipc.h> //Include the IPC header for interprocess communications.
#include <sys/shm.h> //Include the shared memory header for requesting and using shared memory.
#include "FileReader.h" //Include the FileReader header file for file reading.

#define BUFFER_SIZE sizeof(float) //Create the size of the local buffer.

//Method Summary: The main method of execution.
int main (int argc, char **argv)
{
	printf("Median process [%d]: Starting.\n", getpid()); //Print the mean process' id.
	
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
	int fd_read = atoi(argv[2]); //Convert the second argument to an integer.
	int fd_write = atoi(argv[3]); //Convert the third argument to an integer.
	char *data = NULL; //A buffer to store and write data.
	int shmid = 0; //The shared memory ID.
	
	if (numbers == NULL) //If NULL was returned from the file read, then...
	{
		return 0; //Return false to indicate failure.
	}
	
	close(fd_write); //Close this end of the shared memory buffer for writing.
	read(fd_read, &shmid, sizeof(int)); //Read the shared memory with the specific ID.
	close(fd_read); //Close this end of the shared memory buffer for reading.
	
	printf("Mean process [%d]: read 4 bytes containing shmid %d\n", getpid(), shmid); //Print the process ID and the shared memory ID.
	
	data = shmat(shmid, 0, 0); //Read the shared memory into the local buffer.
	perror("shmat"); //Print an error message if the read failed.
	
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
	
	printf("Median process[%d]: Median is %f\n", getpid(), median); //Print the median process ID and median.
	
	fclose(file); //Close the file.
	free(numbers); //Free the memory for the array of integers.
	numbers = NULL; //Set the integer pointer to NULL.
	
	sprintf(data, "%f", median); //Print the local data and the mean.
	perror("sprintf"); //Print an error statment is the string copying failed.
	
	if (median < 0) //If the mode is negative, then...
	{
		return -1; //Return -1.
	}
	
	if (median == 0) //If the mode is 0, then...
	{
		return 0; //Return 0.
	}
	
	printf("Median process [%d]: Stopping.\n", getpid()); //Print a message that says the median process is stopping.
	
	shmdt(data); //Attach the shared memory segment to the address of the calling process.
	perror("shmdt"); //Print an error message if the attachment failed.
	
	return 1; //Return true if the program ran successfully.
}

