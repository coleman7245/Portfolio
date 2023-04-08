//Author: coleman7245
//Project: Process Scheduler Algorithms
//File: Scheduler C File

#include "scheduler.h"

/*Main function*/
int main(int argc, char** argv)
{
	if (argc != 3) //If there are two arguments present, then...
	{
		printf("Insufficient number of arguments!\n"); //Print the error message.
		return 0; //Return false;
	}
	
	/*Variables*/
	FILE *input_file = fopen(argv[1], "rb"); //Open the input file with the second argument.
	SchedulerOverhead *overhead = SchedulerOverheadInit(-1, findNewLines(input_file), 1, 0, 0, 0, atoi(argv[2]), 0, 999999); //Allocate and initialize the scheduler overhead.
	Process **data = malloc(overhead->size * sizeof(Process**));
	
	if (data == NULL)
	{
		return 0;
	}
	
	for (int pos = 0; pos < overhead->size; pos++)
	{
		data[pos] = ProcessInit(overhead->size);
	}
	
	if (!readFile(input_file, overhead, data)) //If the input file read failed, then...
	{
		return 0; //Return false.
	}
	
	fclose(input_file); //Close the input file. 
	
	if (data == NULL) //If the readFile function failed to return an array of processes, then...
	{
		printf("Read of file failed!\n");  //Print the error message.
		return 0; //Return false;
	}
	
	if (!displayMenu(data, overhead)) //If the menu wasn't displayed, then...
	{
		printf("Failed to display menu!\n"); //Print the error message.
		return 0; //Return false.
	}
	
	for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the file...
	{
		ProcessDecon(data[pos], overhead->size);
		data[pos] = NULL;
	}

	free(data); //Free the memory allocated for the list of processes.
	data = NULL; //Set the pointer to null.
	SchedulerOverheadDecon(overhead); //Free the memory allocated for the overhead.
	overhead = NULL; //Set the pointer to null.
	
	return 1; //If everything performed accordingly, return true.
}

/*Auxiliary functions*/
int readFile(FILE *input_file, SchedulerOverhead *overhead, Process **processes)
{
	/*Variable*/
	int r_pos = 0; //Position within the process array.
	
	while (!feof(input_file)) //While the pointer is not at the end of the file...
	{	
		if (!fscanf(input_file, "%d,%d,%d,%d,%d - %d\n", &processes[r_pos]->pid, &processes[r_pos]->arrival_time, 
			&processes[r_pos]->burst_duration, &processes[r_pos]->priority, &processes[r_pos]->lower_bound_tickets[0], 
			&processes[r_pos]->upper_bound_tickets[0])) //Read a string according to the specified format, then extract the integers and store them in their proper place. If the read fails...
			{
				if (feof(input_file)) //If the end of file has been reached...
				{
					break; //Break out of the loop, since there is no further input.
				}
				else
				{
					printf("Read of file failed!\n"); //Print the error message.
					return 0; //Return false.
				}
			}
			
		//printf("from %s: processes[%d].lower_bound_tickets[%d] = %d\n", "readFile", r_pos, r_pos, processes[r_pos].lower_bound_tickets[r_pos]);
		//printf("from %s: processes[%d].upper_bound_tickets[%d] = %d\n", "readFile", r_pos, r_pos, processes[r_pos].upper_bound_tickets[r_pos]);
			
		if (processes[r_pos]->lower_bound_tickets[0] < overhead->lowest_ticket)
		{
			overhead->lowest_ticket = processes[r_pos]->lower_bound_tickets[0];
		}
		
		if (processes[r_pos]->upper_bound_tickets[0] > overhead->highest_ticket)
		{
			overhead->highest_ticket = processes[r_pos]->upper_bound_tickets[0];
		}
		
		processes[r_pos]->waiting_time = -processes[r_pos]->arrival_time;
		processes[r_pos]->num_of_tickets = 1; //Initialize the number tickets the process holds to 1.
		processes[r_pos]->duration_left = processes[r_pos]->burst_duration; //Set the burst duration left to the maximum burst duration.
		
		r_pos++; //Increment the position in the array of new processes.
	}
	
	return 1; //Return true if executed correctly.
}

void printProcessInfo(Process *processes, int size, int option)
{
	/*Variables*/
	double average_waiting_time = 0; //The average waiting time for a process.
	double throughput = 0; //The throughput of the list of processes.
	double average_turnaround_time = 0; //The average turnaround time for a process.
	int choiceChar = (int)'y';
	
	//Displays menu titles for scheduling algorithms depending on what option is chosen.
	switch(option)
	{
		case 1:
			printf("************************************************************\n\nFCFS SCHEDULING ALGORITHM:\n\n==============================================================\n\n");
			break;
		case 2:
			printf("************************************************************\n\nSJF NON-PREEMPTIVE SCHEDULING ALGORITHM:\n\n==============================================================\n\n");
			break;
		case 3:
			printf("************************************************************\n\nSJF PREEMPTIVE SCHEDULING ALGORITHM:\n\n==============================================================\n\n");
			break;
		case 4:
			printf("************************************************************\n\nPRIORITY SCHEDULING ALGORITHM:\n\n==============================================================\n\n");
			break;
		case 5:
			printf("************************************************************\n\nLOTTERY SCHEDULING ALGORITHM:\n\n==============================================================\n\n");
			break;
		default:
			break;
	}
	
	if (option == 4)
	{
		printf("Process	AT	BT	Prio	WT	TAT\n"); //Lists the process table columns.
	}
	else
	{
		printf("Process	AT	BT	WT	TAT\n"); //Lists the process table columns.
	}
	
	for (int pos = 0; pos < size; pos++) //From the beginning to the end of the array of processes...
	{
		if (option == 4)
		{
			printf("P%d	%d	%d	%d	%d	%d\n", processes[pos].pid, processes[pos].arrival_time, processes[pos].burst_duration, processes[pos].priority, processes[pos].waiting_time, processes[pos].turnaround_time); //Print statistics of the process scheduling.
		}
		else
		{
			printf("P%d	%d	%d	%d	%d\n", processes[pos].pid, processes[pos].arrival_time, processes[pos].burst_duration, processes[pos].waiting_time, processes[pos].turnaround_time); //Print statistics of the process scheduling.
		}
		
		average_waiting_time += processes[pos].waiting_time; //Calculate the average waiting time of a process during this instance of scheduling.
		average_turnaround_time += processes[pos].turnaround_time; //Calculate the average turnaround time of a process during this instance of scheduling.

		if (processes[pos].turnaround_time > throughput) //If the array of processes is at the end, then...
		{
			throughput = processes[pos].turnaround_time; //Calculate the throughput of this instance of scheduling.
		}
		
		if ((pos + 1) % 10 == 0 && pos != 0 && (choiceChar == (int)'y' || choiceChar == (int)'Y'))
		{
			printf("Press y to continue or any other key to finish the list.\n");
			choiceChar = getchar();
			choiceChar = getchar();
		}
	}
	
	average_waiting_time /= size; //Finish the calculation of the average wait time.
	average_turnaround_time /= size; //Finish the calculation of the average turnaround time.
	throughput = size / throughput; //Finish the calculation of the throughput.
	
	printf("\naverage waiting time: %f\n\n", average_waiting_time); //Print the average wait time of a process during this instance of scheduling.
	printf("average turnaround time: %f\n\n", average_turnaround_time); //Print the average turnaround time of a process during this instance of scheduling.
	printf("throughput: %f\n\n", throughput); //Print the throughput of this instance of scheduling.
	printf("============================================================\n\n"); //Border for formatting.
}

int findNewLines(FILE *open_file)
{
	/*Variables*/
	int carriageReturnNum = 0;
	int newLineNum = 0;
	int c = '\0';
	
	while (!feof(open_file)) //While the pointer is not at the end of the file...
	{
		if (!fread(&c, sizeof(char), 1, open_file))
		{
			if (feof(open_file)) //If the end of file has been reached...
			{
				break; //Break out of the loop, since there is no further input.
			}
			else
			{
				return 0; //Return a null Process pointer.
			}
		}
		
		if (c == '\n')
		{
			newLineNum++;
		}
		
		if (c == '\r')
		{
			carriageReturnNum++;
		}
	}
	
	rewind(open_file); //Place the pointer at the beginning of the file.
	
	if (carriageReturnNum > newLineNum)
	{
		return carriageReturnNum;
	}
	else
	{
		return newLineNum;
	}
}

int displayMenu(Process **processes, SchedulerOverhead *overhead)
{
	/*Variables*/
	Process *current_list = malloc(sizeof(Process) * overhead->size); //List of processes.
	int option = 0; //Storage for menu options.;
		
	if (current_list == NULL) //If the SJFnonPre method failed, then...
	{
		return 0; //Return false;
	}
	
	for (int pos = 0; pos < overhead->size; pos++)
	{
		current_list[pos].lower_bound_tickets = malloc(sizeof(int) * overhead->size);
		
		if (current_list[pos].lower_bound_tickets == NULL) //If the SJFnonPre method failed, then...
		{
			return 0; //Return false;
		}
		
		current_list[pos].upper_bound_tickets = malloc(sizeof(int) * overhead->size);
			
		if (current_list[pos].upper_bound_tickets == NULL) //If the SJFnonPre method failed, then...
		{
			return 0; //Return false;
		}
		
		initializeProcess(&current_list[pos], overhead->size);
	}
	
	do
	{	
		for (int pos = 0; pos < overhead->size; pos++)
		{
			copyProcess(processes[pos], &current_list[pos], overhead->size);
		}
		
		//Prints out the menu on the command console.
		printf("Welcome to the CPU Scheduler!\n\n");
		printf("Please select from the following options using the corresponding integer.\n\n");
		printf("(1) FCFS \n");
		printf("(2) SJF non-preemtive\n");
		printf("(3) SJF preemtive\n");
		printf("(4) Priority scheduling\n");
		printf("(5) Lottery scheduling\n");
		printf("(6) Exit\n");
		
		scanf("%d", &option); //Scan for user input to determine the outcome of the program's actions.
		
		printf("\n\n"); //New lines for formatting.
		
		switch(option) //If the chosen option by the user is...
		{
			case 1:
				FCFS(current_list, overhead); //Sort the current list of processes by first-come, first-serve order.
				break;		
			case 2:
				SJF(current_list, overhead, 0); //Sort the current list of processes by the shortest job first with no preemption.
				break;
			case 3:
				SJF(current_list, overhead, 1); //Sort the current list of processes by the shortest job first with preemption.
				break;
			case 4:
				PriorityScheduling(current_list, overhead); //Sort the current list of processes by the highest priority.
				break;
			case 5:
				LotteryScheduling(current_list, overhead); //Sort the current list of processes by a lottery system.
				break;
			default:
				//Do nothing.
				break;
		}
		
		if (option >= 1 && option <= 5)
		{
			printProcessInfo(current_list, overhead->size, option); //Print the process info on the command console.
		}
		
	} while(option >= 1 && option <= 5); //While the user has chosen an option other than exit...
	
	for (int pos = 0; pos < overhead->size; pos++)
	{
		free(current_list[pos].lower_bound_tickets);
		current_list[pos].lower_bound_tickets = NULL;
		free(current_list[pos].upper_bound_tickets);
		current_list[pos].upper_bound_tickets = NULL;
	}
		
	free(current_list);
	current_list = NULL;
	
	return 1;
}

int findProcess(Process *processes, SchedulerOverhead *overhead)
{
	int new_pos = -1;
	
	if (overhead->option == 1)
	{
		for (int pos = 0; pos <= overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].duration_left > 0 &&
				processes[pos].arrival_time <= overhead->time) //Check if the process arrived on time, has work left to be done, and has yet to run.
			{
				if (new_pos == -1 || processes[pos].arrival_time < processes[new_pos].arrival_time ||
					(processes[pos].arrival_time == processes[new_pos].arrival_time &&
					processes[pos].duration_left < processes[new_pos].duration_left))
				{
					new_pos = pos; //Switch the current position to that of the canidate process.
				}
			}
		}
	}
	else if (overhead->option == 2)
	{
		for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= overhead->time &&
				processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
			{
				if (new_pos == -1 || processes[pos].duration_left < processes[new_pos].duration_left ||
					(processes[pos].duration_left == processes[new_pos].duration_left &&
					processes[pos].arrival_time < processes[new_pos].arrival_time))
				{
					new_pos = pos; //Switch the current position to that of the canidate process.
				}
			}
		}
	}
	else if (overhead->option == 3)
	{
		for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= overhead->time &&
				processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
			{
				if (new_pos == -1 || processes[pos].priority > processes[new_pos].priority ||
					(processes[pos].priority == processes[new_pos].priority &&
					processes[pos].duration_left < processes[new_pos].duration_left) ||
					(processes[pos].priority == processes[new_pos].priority &&
					processes[pos].duration_left == processes[new_pos].duration_left &&
					processes[pos].arrival_time < processes[new_pos].arrival_time))
				{
					new_pos = pos; //Switch the current position to that of the canidate process.
				}
			}
		}
	}
	else if (overhead->option == 4)
	{		
		for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= overhead->time &&
				processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
			{
				if (new_pos == -1)
				{
					new_pos = pos;
				}
				else if (findWinningTicket(&processes[pos], overhead) == 1)
				{
					new_pos = pos;
					break;
				}
			}
		}
	}
	
	if (new_pos != -1)
	{
		processes[new_pos].waiting_time += overhead->time - processes[new_pos].last_runtime;
	}
	
	return new_pos;
}

int switchProcesses(Process *processes, SchedulerOverhead *overhead)
{
	int new_pos = findProcess(processes, overhead);
	processes[overhead->current_pos].turnaround_time = overhead->time - processes[overhead->current_pos].arrival_time;
	overhead->processes_left--; //Decrement the number of processes left to run.
	
	if (overhead->option == 4)
	{
		passTickets(processes, overhead);
	}
	
	return new_pos;
}

void FCFS(Process *processes, SchedulerOverhead *overhead)
{
	/*Variables*/
	overhead->processes_left = overhead->size; //The number of processes left to complete their run.
	overhead->time = 1; //Time of execution.
	overhead->option = 1;
	overhead->current_pos = findProcess(processes, overhead); //Current position of the running process within the new array.
	
	while (overhead->processes_left > 0) //While the number of processes left is greater than 0...
	{	
		if (processes[overhead->current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			overhead->current_pos = switchProcesses(processes, overhead);
		}
			
		overhead->time++; //Increment the time.
		processes[overhead->current_pos].duration_left--; //Decrement the workload.
	}
	
	free(overhead);
	overhead = NULL;
}

void SJF(Process *processes, SchedulerOverhead *overhead, int preempt)
{
	/*Variables*/
	overhead->processes_left = overhead->size; //The number of processes left to complete their run.
	overhead->time = 1; //Time of execution.
	overhead->option = 2;
	overhead->current_pos = findProcess(processes, overhead); //Current position of the running process within the new array. 
	
	while (overhead->processes_left > 0) //While the number of processes left is greater than 0...
	{
		if (processes[overhead->current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			overhead->current_pos = switchProcesses(processes, overhead);
		}
		else if (preempt == 1)
		{
			processes[overhead->current_pos].last_runtime = overhead->time;
			overhead->current_pos = findProcess(processes, overhead);
		}
		
		overhead->time++; //Increment the time.
		processes[overhead->current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
	}
}

void passTickets(Process *processes, SchedulerOverhead *overhead)
{	
	int greatest_num = 0;
	int next_pos = 0;
	
	for (int pos = 0; pos < overhead->size; pos++)
	{
		if (greatest_num < processes[pos].num_of_tickets && pos != overhead->current_pos)
		{
			greatest_num = processes[pos].num_of_tickets;
			next_pos = pos;
		}
	}
	
	for (int t_pos = 0; t_pos < processes[overhead->current_pos].num_of_tickets; t_pos++)
	{
		processes[next_pos].lower_bound_tickets[processes[next_pos].num_of_tickets] = processes[overhead->current_pos].lower_bound_tickets[t_pos];
		processes[overhead->current_pos].lower_bound_tickets[t_pos] = 0;
		processes[next_pos].upper_bound_tickets[processes[next_pos].num_of_tickets] = processes[overhead->current_pos].upper_bound_tickets[t_pos];
		processes[overhead->current_pos].upper_bound_tickets[t_pos] = 0;
		processes[next_pos].num_of_tickets++;
	}
	
	processes[overhead->current_pos].num_of_tickets = 0;
}

void PriorityScheduling(Process *processes, SchedulerOverhead *overhead)
{
	/*Variables*/
	overhead->processes_left = overhead->size; //The number of processes left to complete their run.
	overhead->time = 1; //Time of execution.
	overhead->option = 3;
	overhead->current_pos = findProcess(processes, overhead); //Current position of the running process within the new array. 
	
	while (overhead->processes_left > 0) //While the number of processes left is greater than 0...
	{	
		if (processes[overhead->current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			overhead->current_pos = switchProcesses(processes, overhead);
		}
		
		overhead->time++; //Increment the time.
		processes[overhead->current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
	}
	
	free(overhead);
	overhead = NULL;
}

int findWinningTicket(Process *process, SchedulerOverhead *overhead)
{	
	for (int t_pos = 0; t_pos < process->num_of_tickets; t_pos++)
	{
		if (overhead->winning_ticket >= process->lower_bound_tickets[t_pos] && 
			overhead->winning_ticket <= process->upper_bound_tickets[t_pos])
			{
				return 1;
			}
	}
	
	return 0;
}

void LotteryScheduling(Process *processes, SchedulerOverhead *overhead)
{
	overhead->processes_left = overhead->size;
	overhead->time = 1;
	overhead->option = 4;
	srand(overhead->random_seed);
	overhead->winning_ticket = (rand() % (overhead->highest_ticket - overhead->lowest_ticket)) + overhead->lowest_ticket;
	overhead->current_pos = findProcess(processes, overhead);
	
	while (overhead->processes_left > 0)
	{
		if (processes[overhead->current_pos].duration_left <= 0)
		{
			overhead->winning_ticket = (rand() % (overhead->highest_ticket - overhead->lowest_ticket)) + overhead->lowest_ticket;
			passTickets(processes, overhead);
			overhead->current_pos = switchProcesses(processes, overhead);
		}
		
		overhead->time++;
		processes[overhead->current_pos].duration_left--;
	}
	
	free(overhead);
	overhead = NULL;
}

void printAlgorithmOverhead(AlgorithmOverhead *overhead)
{
	printf("overhead->current_pos = %d\n", overhead->current_pos);
	printf("overhead->size = %d\n", overhead->size);
	printf("overhead->time = %d\n", overhead->time);
	printf("overhead->winning_ticket = %d\n", overhead->winning_ticket);
	printf("overhead->processes_left = %d\n", overhead->processes_left);
	printf("overhead->option = %d\n", overhead->option);
}
