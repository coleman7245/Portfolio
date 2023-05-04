//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Process C File

#include "process.h"

Process* ProcessInit(int size)
{
	Process *process = malloc(sizeof(Process)); //Allocate memory for a process according to the size.
  
	if (process == NULL)
	{
		return NULL;
	}

	process->lower_bound_tickets = malloc(size * sizeof(int));

	if (process->lower_bound_tickets == NULL)
	{
		free(process);
		return NULL;
	}

	process->upper_bound_tickets = malloc(size * sizeof(int));

	if (process->upper_bound_tickets == NULL)
	{
		free(process->lower_bound_tickets);
		free(process);
		return NULL;
	}

	initializeProcess(process, size); //Set the variables of the process.
	initializeTickets(process, size); //Set the ticket values.

	return process; //Return the process pointer.
}

void ProcessDecon(Process *process, int size)
{
	free(process->lower_bound_tickets);
	process->lower_bound_tickets = NULL;
	free(process->upper_bound_tickets);
	process->upper_bound_tickets = NULL;
	free(process);
}

void initializeTickets(Process *process, int size)
{
	/*Set all ticket values to 0.*/
	for (int pos = 0; pos < size; pos++)
	{
		process->lower_bound_tickets[pos] = 0;
		process->upper_bound_tickets[pos] = 0;
	}
}

void initializeProcess(Process *process, int size)
{
	/*Initialize all process variables to 0. */
	process->pid = 0;
	process->arrival_time = 0;
	process->burst_duration = 0;
	process->priority = 0;
	process->waiting_time = 0;
	process->turnaround_time = 0;
	process->duration_left = 0;
	process->last_runtime = 0;
	process->num_of_tickets = 0;
	initializeTickets(process, size);
	initializeTickets(process, size);
}

void copyTickets(int *ticketsA, int *ticketsB, int size)
{
	for (int i = 0; i < size; i++)
	{
		ticketsB[i] = ticketsA[i];
	}
}

void copyProcess(Process *processA, Process *processB, int size)
{
	processB->pid = processA->pid;
	processB->arrival_time = processA->arrival_time;
	processB->burst_duration = processA->burst_duration;
	processB->priority = processA->priority;
	processB->waiting_time = processA->waiting_time;
	processB->turnaround_time = processA->turnaround_time;
	processB->duration_left = processA->duration_left;
	processB->last_runtime = processA->last_runtime;
	processB->num_of_tickets = processA->num_of_tickets;
	copyTickets(processB->lower_bound_tickets, processA->lower_bound_tickets, size);
	copyTickets(processB->upper_bound_tickets, processA->upper_bound_tickets, size);
}

void printTickets(const char *method_name, Process *process, int size)
{
	for (int pos = 0; pos < size; pos++)
	{
		printf("from %s: lower_bound_tickets[%d] = %d\n", method_name, pos, process->lower_bound_tickets[pos]);
		printf("from %s: upper_bound_tickets[%d] = %d\n", method_name, pos, process->upper_bound_tickets[pos]);
	}
}

void printProcess(const char *method_name, Process *process, int size)
{
	printf("from %s: process->pid = %d\n", method_name, process->pid);
	printf("from %s: process->arrival_time = %d\n", method_name, process->arrival_time);
	printf("from %s: process->burst_duration = %d\n", method_name, process->burst_duration);
	printf("from %s: process->priority = %d\n", method_name, process->priority);
	printf("from %s: process->waiting_time = %d\n", method_name, process->waiting_time);
	printf("from %s: process->turnaround_time = %d\n", method_name, process->turnaround_time);
	printf("from %s: process->duration_left = %d\n", method_name, process->duration_left);
	printf("from %s: process->last_runtime = %d\n", method_name, process->last_runtime);
	printf("from %s: process->num_of_tickets = %d\n", method_name, process->num_of_tickets);
	printTickets(method_name, process, size);
}
