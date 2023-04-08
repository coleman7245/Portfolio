//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Scheduler Overhead H File

#ifndef SCHEDULEROVERHEAD_H
#define SCHEDULEROVERHEAD_H
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int current_pos; //The process that is currently running.
	int size; //The size of the process list.
	int time; //The current time.
	int winning_ticket; //The winning ticket in the lottery scheduler.
	int processes_left; //The number of processes left.
	int option; //The number representing the scheduler algorithm.
	int random_seed; //The random seed used in the random integer generator for the lottery scheduler.
	int highest_ticket; //The highest ticket value in the ticket list.
	int lowest_ticket; //The lowest ticket value in the ticket list.
} SchedulerOverhead; //Struct containing scheduler information.

SchedulerOverhead* SchedulerOverheadInit(int current_pos, int size, int time, int winning_ticket, int processes_left, int option, int random_seed, int highest_ticket, int lowest_ticket); //Allocates memory for the scheduler overhead struct.
void SchedulerOverheadDecon(SchedulerOverhead *overhead);
void initializeSchedulerOverhead(SchedulerOverhead *overhead, int current_pos, int size, int time, int winning_ticket, int processes_left, int option, int random_seed, int highest_ticket, int lowest_ticket); //Initializes all struct variables to 0.
void printSchedulerOverhead(const char *method_name, SchedulerOverhead *overhead); //Prints the scheduler overhead values.

#endif
