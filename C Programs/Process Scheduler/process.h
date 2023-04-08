//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Process H File

#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	/*Fields of the struct Process*/
	int pid; //Process id.
	int arrival_time; //Arrival time of process in the queue.
	int burst_duration; //CPU work by the process.
	int priority; //Priority of a process to be loaded in first.
	int waiting_time; //Waiting time for the process.
	int turnaround_time; //The total completetion time of a process.
	int duration_left; //The burst duration left during its run.
	int last_runtime; //The last time the process was running.
	int num_of_tickets; //The total number of tickets the process holds.
	int *upper_bound_tickets; //The upper bound values for each ticket.
	int *lower_bound_tickets; //The lower bound values for each ticket.
	
} Process; //Struct for storing process information.

Process* ProcessInit(int size); //Allocates memory for a process.
void ProcessDecon(Process *process, int size);
void initializeTickets(Process *process, int size); //Initialize all ticket values to 0.
void initializeProcess(Process *process, int size); //Initialize all process variables to 0.
void copyTickets(int *ticketsA, int *ticketsB, int size); //Copies the tickets of process A onto the tickets of process B.
void copyProcess(Process *processA, Process *processB, int size); //Copies process A onto process B.
void printTickets(const char *method_name, Process *process, int size); //Prints the ticket values.
void printProcess(const char *method_name, Process *process, int size); //Prints the process attributes.

#endif
