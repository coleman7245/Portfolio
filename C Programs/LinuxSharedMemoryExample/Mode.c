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

#define BUFFER_SIZE sizeof(float) //Definet the size of the shared memory buffer.

//Method Summary: The main thread of execution.
int main (int argc, char **argv)
{
	printf("Mode process [%d]: Starting.\n", getpid()); //Print the mode process' id.
	
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
	
	printf("Mode process [%d]: read 4 bytes containing shmid %d\n", getpid(), shmid); 
	
	data = shmat(shmid, 0, 0); //Read the shared memory into the local buffer.
	perror("shmat"); //Print an error message if the read failed.
	
	mode = numbers[0]; //Initialize the mode.
	
	while (pos1 < size) //While the first position within the array is less than the total size, do...
	{
		current = numbers[pos1]; //Store the the number at the current position.
		
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
	
	printf("Mode process[%d]: Mode is %f\n", getpid(), mode); //Print the process ID and the mode.
	
	fclose(file); //Close the file.
	free(numbers); //Free the memory for the array of integers.
	numbers = NULL; //Set the integer pointer to NULL.
	
	printf("Mode process [%d]: Stopping.\n", getpid()); //Print a message that says the mode process is stopping.
	
	sprintf(data, "%f", mode); //Print the data in local buffer.
	perror("sprintf"); //Print an error statment is the string copying failed.
	
	if (mode < 0) //If the mode is negative, then...
	{
		return -1; //Return -1.
	}
	
	if (mode == 0) //If the mode is 0, then...
	{
		return 0; //Return 0.
	}
	
	shmdt(data); //Attach the shared memory segment to the address of the calling process.
	perror("shmdt"); //Display an error message if the attachment failed.
	
	return 1; //Return 1 if the program ran successfully.
}

