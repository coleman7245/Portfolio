//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Scheduler H File
//Last Edit: Tuesday, April 4th, 2023

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdlib.h>
#include "process.h"
#include "scheduleroverhead.h"

/*Prototypes for methods*/
int readFile(FILE *input_file, SchedulerOverhead *overhead, Process *processes); //Reads a file for the specific parameters of this assignment. Returns a pointer to an array of processes.
void printProcessInfo(Process *processes, int size, int option); //Prints the process information specific to this assignment in stdout.
int findNewLines(FILE *open_file); //Helper function to find the byte size of a file.
int displayMenu(Process *processes, SchedulerOverhead *overhead); //Displays a menu for the end user.
void FCFS(Process *processes, SchedulerOverhead *overhead); //Schedules the list of processes as first-come, first-serve.
void SJF(Process *processes, SchedulerOverhead *overhead, int preempt);
void PriorityScheduling(Process *processes, SchedulerOverhead *overhead); //Schedules the list of processes according to their individual priority.
void LotteryScheduling(Process *lottery_processes, SchedulerOverhead *overhead); //Schedules the list of processes using a lottery system.
int findProcess(Process *processes, SchedulerOverhead *overhead); //Finds a new process to run in the process list according to the selected scheduler.
int switchProcesses(Process *processes, SchedulerOverhead *overhead); //Switches out a finished process for a fresh one.
int findWinningTicket(Process *process, SchedulerOverhead *overhead); //Finds the process with the winning ticket.
void passTickets(Process *processes, SchedulerOverhead *overhead); //Gives the tickets of a finished process to one with the highest number of tickets.

#endif
