/* 
 * Author: coleman7245
 * Project: Linux Shared Memory Example
 * Last Update: 2/25/19
 */ 

#define _XOPEN_SOURCE 700
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFFER_SIZE 50
#define READ_END 0
#define WRITE_END 1

pid_t pid; //Process id number of the child
int instance = 0; //The count of forked programs currently running.
int status = 0; //The return status of the child program.
int retrnMean = 0, retrnMode = 0, retrnMedian = 0;
char *data = NULL;
int shmid = 0;
int fd[2];
char readBuffer[50];
char writeBuffer[50];

int main (int argc, char **argv)
{
	while (instance < 3) //While the instance count is less than three...
	{
		if (pipe(fd) == -1)
		{
			return 0;
		}
		
		if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, IPC_CREAT | 0666)) < 0)
		{
			return 0;
		}
		
		perror("shmget");
		//printf("shmid = %d\n", shmid);
		
		data = shmat(shmid, 0, 0);
		perror("shmat");
		
		pid = fork(); //Create a forked program, and store the return value as the child process' id number.
		
		if (pid > 0) //If the CPU is running the parent process, then...
		{
			printf("Initiator: forked process with ID %d. \n", pid);
			
			close(fd[READ_END]);
			write(fd[WRITE_END], &shmid, sizeof(int));
			close(fd[WRITE_END]);
			
			printf("Initiator: waiting for process [%d].\n", pid);
			
			wait(&status); //Wait for the child process to end, then print its return value.
			
			if (instance == 0) //For the first instance...
			{
				retrnMean = atof(data);
				printf("Initiator: Result read from shared memory, Mean is %d.\n", retrnMean);
			}
			else if (instance == 1) //For the second instance...
			{
				retrnMedian = atof(data);
				printf("Initiator: Result read from shared memory, Median is %d.\n", retrnMedian);
			}
			else //Otherwise...
			{
				retrnMode = atof(data);
				printf("Initiator: Result read from shared memory, Mode is %d.\n", retrnMode);
			}
			
			shmdt(data);
			shmctl(shmid, IPC_RMID, 0);
		}
		else if (pid == 0) //If the CPU is running the child process, then...
		{
			if (instance == 0) //For the first instance...
			{
				memcpy(readBuffer, "\0", 50);
				memcpy(writeBuffer, "\0", 50);
				sprintf(readBuffer, "%d", fd[READ_END]);
				sprintf(writeBuffer, "%d", fd[WRITE_END]);
				execlp(".//Mean", ".//Mean", argv[1], readBuffer, writeBuffer, (char *)NULL); //Run the mean program.
				perror("execlp failed!\n");
			}
			else if (instance == 1) //For the second instance...
			{
				memcpy(readBuffer, "\0", 50);
				memcpy(writeBuffer, "\0", 50);
				sprintf(readBuffer, "%d", fd[READ_END]);
				sprintf(writeBuffer, "%d", fd[WRITE_END]);
				execlp(".//Median", ".//Median", argv[1], readBuffer, writeBuffer, (char *)NULL); //Run the Median program.
				perror("execlp failed!\n");
			}
			else //Otherwise...
			{
				memcpy(readBuffer, "\0", 50);
				memcpy(writeBuffer, "\0", 50);
				sprintf(readBuffer, "%d", fd[READ_END]);
				sprintf(writeBuffer, "%d", fd[WRITE_END]);
				execlp(".//Mode", ".//Mode", argv[1], readBuffer, writeBuffer, (char *)NULL); //Run the Mode program.
				perror("execlp failed!\n");
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
