//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Scheduler Overhead C File
//Last Edit: Tuesday, April 4th, 2023

#include "scheduleroverhead.h"
#include <stdio.h>

void printSchedulerOverhead(const char *method_name, SchedulerOverhead *overhead)
{
	printf("from %s: overhead->current_pos = %d\n", method_name, overhead->current_pos);
	printf("from %s: overhead->size = %d\n", method_name, overhead->size);
	printf("from %s: overhead->time = %d\n", method_name, overhead->time);
	printf("from %s: overhead->winning_ticket = %d\n", method_name, overhead->winning_ticket);
	printf("from %s: overhead->processes_left = %d\n", method_name, overhead->processes_left);
	printf("from %s: overhead->option = %d\n", method_name, overhead->option);
}
