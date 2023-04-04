//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Scheduler Overhead H File
//Last Edit: Tuesday, April 4th, 2023

#ifndef SCHEDULEROVERHEAD_H
#define SCHEDULEROVERHEAD_H

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

void printSchedulerOverhead(const char *method_name, SchedulerOverhead *overhead); //Prints the scheduler overhead values.

#endif
