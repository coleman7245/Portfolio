//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Scheduler Overhead C File

#include "scheduleroverhead.h"

SchedulerOverhead* SchedulerOverheadInit(int current_pos, int size, int time, int winning_ticket, int processes_left, int option, int random_seed, int highest_ticket, int lowest_ticket)
{
	SchedulerOverhead *overhead = malloc(sizeof(SchedulerOverhead)); //Allocate memory for the scheduler overhead according to the given size.
	
	if (overhead == NULL)
	{
		return NULL;
	}
	
	initializeSchedulerOverhead(overhead, current_pos, size, time, winning_ticket, processes_left, option, random_seed, highest_ticket, lowest_ticket); //Set all the variables of the scheduler overhead.
	
	return overhead; //Return the scheduler overhead pointer.
}

void SchedulerOverheadDecon(SchedulerOverhead *overhead)
{
	free(overhead);
}

void initializeSchedulerOverhead(SchedulerOverhead *overhead, int current_pos, int size, int time, int winning_ticket, int processes_left, int option, int random_seed, int highest_ticket, int lowest_ticket)
{
	/*Initialize all struct variables to 0.*/
	overhead->current_pos = current_pos;
	overhead->size = size;
	overhead->time = time;
	overhead->winning_ticket = winning_ticket;
	overhead->processes_left = processes_left;
	overhead->option = option;
	overhead->random_seed = random_seed;
	overhead->highest_ticket = highest_ticket;
	overhead->lowest_ticket = lowest_ticket;
}

void printSchedulerOverhead(const char *method_name, SchedulerOverhead *overhead)
{
	/*Print all variables of the struct */
	printf("from %s: overhead->current_pos = %d\n", method_name, overhead->current_pos);
	printf("from %s: overhead->size = %d\n", method_name, overhead->size);
	printf("from %s: overhead->time = %d\n", method_name, overhead->time);
	printf("from %s: overhead->winning_ticket = %d\n", method_name, overhead->winning_ticket);
	printf("from %s: overhead->processes_left = %d\n", method_name, overhead->processes_left);
	printf("from %s: overhead->option = %d\n", method_name, overhead->option);
}
