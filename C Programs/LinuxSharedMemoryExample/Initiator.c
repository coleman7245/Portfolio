/* 
 * Author: Derek Coleman
 * Project: Linux Shared Memory Example
 * Last Update: 3/4/19
 */ 

#define _XOPEN_SOURCE 700
#include <string.h> //Include the string header for storing and reading strings.
#include <stdlib.h> //Include the C standard library for
#include <stdio.h> //Include the C standard IO header for file reading and writing.
#include <sys/types.h> //Include the Unix types header for the process ID variable.
#include <unistd.h> //Include the Unix standard header for the fork system. call.
#include <sys/wait.h> //Include the Unix wait header
#include <sys/ipc.h> //Include the IPC header for interprocess communications.
#include <sys/shm.h> //Include the shared memory header for requesting and using shared memory.

#define BUFFER_SIZE 50 //Define the buffer size.
#define READ_END 0 //Define the read signal.
#define WRITE_END 1 //Define the write signal.

pid_t pid; //Process id number of the child
int instance = 0; //The count of forked programs currently running.
int status = 0; //The return status of the child program.
int retrnMean = 0; //Start the returned mean as 0.
int retrnMode = 0; //Start the returned mode as 0.
int retrnMedian = 0; //Start the returned median as 0.
char *data = NULL; //Start the local buffer as null.
int shmid = 0; //Start thge sharmed memory id as 0.
int fd[2]; //Create the file descriptor.
char readBuffer[50]; //Read buffer.
char writeBuffer[50]; //Write buffer.

//Method Summary: The main method of execution.
int main (int argc, char **argv)
{
	while (instance < 3) //While the instance count is less than three...
	{
		if (pipe(fd) == -1) //If the process pipe creation failed, then...
		{
			return 0; //Return 0, indicating 0.
		}
		
		if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, IPC_CREAT | 0666)) < 0) //If the creation of the shared memory failed, then...
		{
			perror("shmget"); //Print an error message that specifies the type of failure.
			return 0; //Return 0, indicating failure.
		}
		
		data = shmat(shmid, 0, 0); //Attach the shared memory segment with the ID.
		perror("shmat"); //Print an error message if the shared memory attachment failed.
		
		pid = fork(); //Create a forked program, and store the return value as the child process' id number.
		
		if (pid > 0) //If the CPU is running the parent process, then...
		{
			printf("Initiator: forked process with ID %d. \n", pid); //Print forked process ID.
			
			close(fd[READ_END]); //Close the shared memory read on this end.
			write(fd[WRITE_END], &shmid, sizeof(int)); //Write to the shared memory on this end.
			close(fd[WRITE_END]); //Close the shared memory write on this end.
			
			printf("Initiator: waiting for process [%d].\n", pid); //Print a message that says the initiator is waiting for the process with the given ID.
			
			wait(&status); //Wait for the child process to end, then print its return value.
			
			if (instance == 0) //For the first instance...
			{
				retrnMean = atof(data); //Convert the mean to a float from the local buffer.
				printf("Initiator: Result read from shared memory, Mean is %d.\n", retrnMean); //Print the shared memory read result.
			}
			else if (instance == 1) //For the second instance...
			{
				retrnMedian = atof(data); //Convert the median to a float from the local buffer.
				printf("Initiator: Result read from shared memory, Median is %d.\n", retrnMedian); //Print the shared memory read result.
			}
			else //Otherwise...
			{
				retrnMode = atof(data); //Convert the mode to a float from a local buffer.
				printf("Initiator: Result read from shared memory, Mode is %d.\n", retrnMode); //Print the shared memory read result.
			}
			
			shmdt(data); //Detach the shared memory segment.
			shmctl(shmid, IPC_RMID, 0); //Give control to the system for shared memory clean-up.
		}
		else if (pid == 0) //If the CPU is running the child process, then...
		{
			if (instance == 0) //For the first instance...
			{
				memcpy(readBuffer, "\0", 50); //Copy the data from the read buffer.
				memcpy(writeBuffer, "\0", 50); //Write the data to the write buffer.
				sprintf(readBuffer, "%d", fd[READ_END]); //Print the file descriptor on the read end.
				sprintf(writeBuffer, "%d", fd[WRITE_END]); //Print the file descriptor on the write end.
				execlp(".//Mean", ".//Mean", argv[1], readBuffer, writeBuffer, (char *)NULL); //Run the mean program.
				perror("execlp failed!\n"); //Print an error message if the process execution failed.
			}
			else if (instance == 1) //For the second instance...
			{
				memcpy(readBuffer, "\0", 50); //Copy the data from the read buffer.
				memcpy(writeBuffer, "\0", 50); //Write the data to the write buffer.
				sprintf(readBuffer, "%d", fd[READ_END]); //Print the file descriptor on the read end.
				sprintf(writeBuffer, "%d", fd[WRITE_END]); //Print the file descriptor on the write end.
				execlp(".//Median", ".//Median", argv[1], readBuffer, writeBuffer, (char *)NULL); //Run the Median program.
				perror("execlp failed!\n"); //Print an error message if the process execution failed.
			}
			else //Otherwise...
			{
				memcpy(readBuffer, "\0", 50); //Copy the data from the read buffer.
				memcpy(writeBuffer, "\0", 50); //Write the data to the write buffer.
				sprintf(readBuffer, "%d", fd[READ_END]); //Print the file descriptor on the read end.
				sprintf(writeBuffer, "%d", fd[WRITE_END]); //Print the file descriptor on the write end.
				execlp(".//Mode", ".//Mode", argv[1], readBuffer, writeBuffer, (char *)NULL); //Run the Mode program.
				perror("execlp failed!\n"); //Print an error message if the process execution failed.
			}
		}
		else //Otherwise...
		{
			printf("Error: fork failed.\n");
			return 0; //End the program with a return value of 0.
		}
	
		instance++; //Increment the instance count.
	}

	return 1; //Return 1 if the program ran successfully.
}
