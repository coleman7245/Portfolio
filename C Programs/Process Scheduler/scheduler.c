//Author: coleman7245
//Project: Encryption Program
<<<<<<< HEAD
//Last Edit: Monday, March 28, 2023
=======
//Last Edit: Thursday, February 14, 2019
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360

#include<stdlib.h>
#include<stdio.h>

typedef struct
{
	/*Fields of the struct Process*/
	int pid; //Process id.
	int arrival_time; //Arrival time of process in the queue.
	int burst_duration; //CPU work by the process.
	int remaining_time; //Remaining time to complete the process workload.
	int priority; //Priority of a process to be loaded in first.
	int waiting_time; //Waiting time for the process.
	int turnaround_time; //The total completetion time of a process.
	int duration_left; //The burst duration left during its run.
	int last_runtime; //The last time the process was running.
	int num_of_tickets; //The total number of tickets the process holds.
	int *upper_bound_tickets;
	int *lower_bound_tickets;
	
} Process; //Struct for storing process information.

<<<<<<< HEAD
typedef struct
{
	int current_pos;
	int size;
	int time;
	int winning_ticket;
	int processes_left;
	int option;
} AlgorithmOverhead;

=======
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
/*Prototypes for methods*/
void readFile(FILE *input_file, int size, Process *processes); //Reads a file for the specific parameters of this assignment. Returns a pointer to an array of processes.
void printProcessInfo(Process *processes, int size, int option); //Prints the process information specific to this assignment in stdout.
int findNewLines(FILE *open_file); //Helper function to find the byte size of a file.
int displayMenu(Process *processes, int size, int random_seed); //Displays a menu for the end user.
void FCFS(Process *processes, int size); //Schedules the list of processes as first-come, first-serve.
void SJF(Process *processes, int size, int preempt);
void PriorityScheduling(Process *processes, int size); //Schedules the list of processes according to their individual priority.
void LotteryScheduling(Process *lottery_processes, int size, int random_seed); //Schedules the list of processes using a lottery system.
<<<<<<< HEAD
int findProcess(Process *processes, AlgorithmOverhead *overhead);
int switchProcesses(Process *processes, AlgorithmOverhead *overhead);
void swapProcess(Process *processA, Process *processB, int size);
void swapTickets(int *ticketsA, int *ticketsB, int size);
int findWinningTicket(Process *processes, AlgorithmOverhead *overhead);
void passTickets(Process *processes, AlgorithmOverhead *overhead);
void printAlgorithmOverhead(AlgorithmOverhead *overhead);
=======
int findProcess(Process *processes, int size, int time, int option);
int switchProcesses(Process *processes, int size, int current_pos, int time, int *processes_left, int option);
void mergeSort(Process *array, int size, int start, int end);
void merge(Process *array, int size, int start, int end, int mid, Process *tempArray);
void swapProcess(Process *processA, Process *processB, int size);
void swapTickets(int *ticketsA, int *ticketsB, int size);
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360

/*Main function*/
int main(int argc, char** argv)
{
	if (argc != 3) //If there are two arguments present, then...
	{
		printf("Insufficient number of arguments!\n");
		return 0; //Return false;
	}
	
	/*Variables*/
	FILE *input_file = fopen(argv[1], "rb");
	int size = findNewLines(input_file);
	Process *data = malloc(sizeof(Process) * size); //Allocates memory for an array of processes.
	int r_seed = atoi(argv[2]); //The random seed for lottery shceduling.
	
	for (int pos = 0; pos < size; pos++) //From the beginning to the end of the file...
	{
		//Initialize all values of the processes in the list to 0.
		data[pos].pid = 0;
		data[pos].arrival_time = 0;
		data[pos].burst_duration = 0;
		data[pos].priority = 0;
		data[pos].waiting_time = 0;
		data[pos].turnaround_time = 0;
		data[pos].duration_left = 0;
		data[pos].last_runtime = 0;
		data[pos].num_of_tickets = 0;
		data[pos].lower_bound_tickets = malloc(sizeof(int) * size);
		data[pos].upper_bound_tickets = malloc(sizeof(int) * size);
		
		for (int t_pos = 0; t_pos < size; t_pos++)
		{
			data[pos].lower_bound_tickets[t_pos] = 0;
			data[pos].upper_bound_tickets[t_pos] = 0;
		}
	}
	
	readFile(input_file, size, data); //Create an array of processes by invoking the readFile function.
	
	fclose(input_file);
	
	if (data == NULL) //If the readFile function failed to return an array of processes, then...
	{
		printf("Read of file failed!\n"); 
		return 0; //Return false;
	}
	
	if (!displayMenu(data, size, r_seed)) //If the menu wasn't displayed, then...
	{
		printf("Failed to display menu!\n");
		return 0; //Return false.
	}
	
	for (int pos = 0; pos < size; pos++) //From the beginning to the end of the file...
	{
		free(data[pos].lower_bound_tickets); //Free the memory allocated for the list of lower ticket ranges.
		data[pos].lower_bound_tickets = NULL;
		free(data[pos].upper_bound_tickets); //Free the memory allocated for the list of upper ticket ranges.
		data[pos].upper_bound_tickets = NULL;
	}

	free(data); //Free the memory allocated for the list of processes.
	data = NULL; //Set the pointer to NULL.
	
	return 1; //If everything performed accordingly, return true.
}

/*Auxiliary functions*/
void readFile(FILE *input_file, int size, Process *processes)
{
	/*Variable*/
	int r_pos = 0; //Position within the process array.
	
	while (!feof(input_file)) //While the pointer is not at the end of the file...
	{	
		if (!fscanf(input_file, "%d,%d,%d,%d,%d - %d\n", &processes[r_pos].pid, &processes[r_pos].arrival_time, 
			&processes[r_pos].burst_duration, &processes[r_pos].priority, &processes[r_pos].lower_bound_tickets[r_pos], 
			&processes[r_pos].upper_bound_tickets[r_pos])) //Read a string according to the specified format, then extract the integers and store them in their proper place. If the read fails...
			{
				if (feof(input_file)) //If the end of file has been reached...
				{
					break; //Break out of the loop, since there is no further input.
				}
				else
				{
					printf("Read of file failed!\n");
					return;
				}
			}
		
		processes[r_pos].waiting_time = -processes[r_pos].arrival_time;
		processes[r_pos].num_of_tickets = 1; //Initialize the number tickets the process holds to 1.
		processes[r_pos].duration_left = processes[r_pos].burst_duration; //Set the burst duration left to the maximum burst duration.
		
		r_pos++; //Increment the position in the array of new processes.
	}
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

int displayMenu(Process *processes, int size, int random_seed)
{
	/*Variables*/
	Process *current_list; //List of processes.
	int option = 0; //Storage for menu options.
	
	current_list = malloc(sizeof(Process) * size);
		
	if (current_list == (Process *)NULL) //If the SJFnonPre method failed, then...
	{
		return 0; //Return false;
	}
	
	for (int pos = 0; pos < size; pos++)
	{
		current_list[pos].lower_bound_tickets = malloc(sizeof(int) * size);
		
		if (current_list[pos].lower_bound_tickets == (int *)NULL) //If the SJFnonPre method failed, then...
		{
			return 0; //Return false;
		}
		
		current_list[pos].upper_bound_tickets = malloc(sizeof(int) * size);
			
		if (current_list[pos].upper_bound_tickets == (int *)NULL) //If the SJFnonPre method failed, then...
		{
			return 0; //Return false;
		}
	}
	
	do
	{
		for (int pos = 0; pos < size; pos++)
		{
			current_list[pos].pid = processes[pos].pid;
			current_list[pos].arrival_time = processes[pos].arrival_time;
			current_list[pos].burst_duration = processes[pos].burst_duration;
			current_list[pos].priority = processes[pos].priority;
			current_list[pos].waiting_time = processes[pos].waiting_time;
			current_list[pos].turnaround_time = processes[pos].turnaround_time;
			current_list[pos].duration_left = processes[pos].duration_left;
			current_list[pos].last_runtime = processes[pos].last_runtime;
			current_list[pos].num_of_tickets = processes[pos].num_of_tickets;
			
			for (int t_pos = 0; t_pos < size; t_pos++)
			{
				current_list[pos].lower_bound_tickets[t_pos] = processes[pos].upper_bound_tickets[t_pos]; //Reset the lower bound ticket range to the original value for each process.
				current_list[pos].lower_bound_tickets[t_pos] = processes[pos].lower_bound_tickets[t_pos]; //Reset the upper bound ticket range to the original value for each process.
			}
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
				FCFS(current_list, size); //Sort the current list of processes by first-come, first-serve order.
				break;		
			case 2:
				SJF(current_list, size, 0); //Sort the current list of processes by the shortest job first with no preemption.
				break;
			case 3:
				SJF(current_list, size, 1); //Sort the current list of processes by the shortest job first with preemption.
				break;
			case 4:
				PriorityScheduling(current_list, size); //Sort the current list of processes by the highest priority.
				break;
			case 5:
				LotteryScheduling(current_list, size, random_seed); //Sort the current list of processes by a lottery system.
				break;
			default:
				//Do nothing.
				break;
		}
		
		if (option >= 1 && option <= 5)
		{
			printProcessInfo(current_list, size, option); //Print the process info on the command console.
		}
		
<<<<<<< HEAD
	} while(option >= 1 && option <= 5); //While the user has chosen an option other than exit...
=======
	} while(option != 6); //While the user has chosen an option other than exit...
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
	
	for (int pos = 0; pos < size; pos++)
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

<<<<<<< HEAD
int findProcess(Process *processes, AlgorithmOverhead *overhead)
{
	int new_pos = -1;
	
	printAlgorithmOverhead(overhead);
	
	if (overhead->option == 1)
	{
		for (int pos = 0; pos <= overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].duration_left > 0 &&
				processes[pos].arrival_time <= overhead->time) //Check if the process arrived on time, has work left to be done, and has yet to run.
=======
int findProcess(Process *processes, int size, int time, int option)
{
	int new_pos = -1;
	
	if (option == 1)
	{
		for (int pos = 0; pos <= size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].duration_left > 0 &&
				processes[pos].arrival_time <= time) //Check if the process arrived on time, has work left to be done, and has yet to run.
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
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
<<<<<<< HEAD
	else if (overhead->option == 2)
	{
		for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= overhead->time &&
=======
	else if (option == 2)
	{
		for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= time &&
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
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
<<<<<<< HEAD
	else if (overhead->option == 3)
	{
		for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= overhead->time &&
=======
	else if (option == 3)
	{
		for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= time &&
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
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
<<<<<<< HEAD
	else if (overhead->option == 4)
	{	
		for (int pos = 0; pos < overhead->size; pos++) //From the beginning to the end of the list of processes...
		{
			if (processes[pos].arrival_time <= overhead->time &&
				processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
			{
				new_pos = findWinningTicket(processes, overhead);
			}
		}
	}
	
	printf("From findProcess: processes[new_pos].waiting_time = %d\n", processes[new_pos].waiting_time);
	printf("From findProcess: time = %d\n", overhead->time);
=======
	else if (option == 4)
	{
		
	}
	else
	{
		
	}
	
	printf("From findProcess: processes[new_pos].waiting_time = %d\n", processes[new_pos].waiting_time);
	printf("From findProcess: time = %d\n", time);
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
	printf("From findProcess: processes[new_pos].last_runtime = %d\n", processes[new_pos].last_runtime);
	
	if (new_pos != -1)
	{
<<<<<<< HEAD
		processes[new_pos].waiting_time += overhead->time - processes[new_pos].last_runtime;
=======
		processes[new_pos].waiting_time += time - processes[new_pos].last_runtime;
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
	}
	
	printf("From findProcess: new_pos = %d\n", new_pos);
	printf("From findProcess: processes[new_pos].waiting_time = %d\n", processes[new_pos].waiting_time);
	
	return new_pos;
}

<<<<<<< HEAD
int switchProcesses(Process *processes, AlgorithmOverhead *overhead)
{
	int new_pos = findProcess(processes, overhead);
	processes[overhead->current_pos].turnaround_time = overhead->time - processes[overhead->current_pos].arrival_time;
	overhead->processes_left--; //Decrement the number of processes left to run.
	
	if (overhead->option == 4)
	{
		passTickets(processes, overhead);
	}
	
	return new_pos;
=======
int switchProcesses(Process *processes, int size, int current_pos, int time, int *processes_left, int option)
{
	processes[current_pos].turnaround_time = time - processes[current_pos].arrival_time;
	(*processes_left)--; //Decrement the number of processes left to run.
	
	return findProcess(processes, size, time, option);
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
}

void FCFS(Process *processes, int size)
{
	/*Variables*/
<<<<<<< HEAD
	AlgorithmOverhead *overhead = malloc(sizeof(AlgorithmOverhead));
	overhead->size = size;
	overhead->processes_left = size; //The number of processes left to complete their run.
	overhead->time = 1; //Time of execution.
	overhead->option = 1;
	overhead->current_pos = findProcess(processes, overhead); //Current position of the running process within the new array.
	
	while (overhead->processes_left > 0) //While the number of processes left is greater than 0...
	{	
		printf("From FCFS: Current Process ID = %d\n", processes[overhead->current_pos].pid);
		printf("From FCFS: processes[%d].duration_left = %d\n", overhead->current_pos, processes[overhead->current_pos].duration_left);
		printf("From FCFS: time = %d\n", overhead->time);
		
		if (processes[overhead->current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			overhead->current_pos = switchProcesses(processes, overhead);
		}
			
		overhead->time++; //Increment the time.
		processes[overhead->current_pos].duration_left--; //Decrement the workload.
	}
	
	free(overhead);
	overhead = NULL;
=======
	int processes_left = size; //The number of processes left to complete their run.
	int time = 1; //Time of execution.
	int current_pos = findProcess(processes, size, time, 1); //Current position of the running process within the new array.
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{	
		printf("From FCFS: Current Process ID = %d\n", processes[current_pos].pid);
		printf("From FCFS: processes[%d].duration_left = %d\n", current_pos, processes[current_pos].duration_left);
		printf("From FCFS: time = %d\n", time);
		
		if (processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			current_pos = switchProcesses(processes, size, current_pos, time, &processes_left, 1);
		}
			
		time++; //Increment the time.
		processes[current_pos].duration_left--; //Decrement the workload.
	}
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
}

void SJF(Process *processes, int size, int preempt)
{
	/*Variables*/
<<<<<<< HEAD
	AlgorithmOverhead *overhead = malloc(sizeof(AlgorithmOverhead));
	overhead->size = size;
	overhead->processes_left = size; //The number of processes left to complete their run.
	overhead->time = 1; //Time of execution.
	overhead->option = 2;
	overhead->current_pos = findProcess(processes, overhead); //Current position of the running process within the new array. 
	
	while (overhead->processes_left > 0) //While the number of processes left is greater than 0...
	{
		printf("From SJF: Current Process ID = %d\n", processes[overhead->current_pos].pid);
		printf("From SJF: processes[%d].duration_left = %d\n", overhead->current_pos, processes[overhead->current_pos].duration_left);
		printf("From SJF: time = %d\n", overhead->time);
		
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
	
	free(overhead);
	overhead = NULL;
=======
	int processes_left = size; //The number of processes left to complete their run.
	int time = 1; //Time of execution.
	int current_pos = findProcess(processes, size, time, 2); //Current position of the running process within the new array. 
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{
		printf("From SJF: Current Process ID = %d\n", processes[current_pos].pid);
		printf("From SJF: processes[%d].duration_left = %d\n", current_pos, processes[current_pos].duration_left);
		printf("From SJF: time = %d\n", time);
		
		if (processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			current_pos = switchProcesses(processes, size, current_pos, time, &processes_left, 2);
		}
		else if (preempt == 1)
		{
			processes[current_pos].last_runtime = time;
			current_pos = findProcess(processes, size, time, 2);
		}
		
		time++; //Increment the time.
		processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
	}
}

void mergeSort(Process *array, int size, int start, int end)
{
	Process *tempArray = malloc(sizeof(Process) * size);
	
	if (start < end)
	{
		int mid = (start + end) / 2;
		mergeSort(array, size, start, mid);
		mergeSort(array, size, mid+1, end);
		merge(array, size, start, end, mid, tempArray);
	}
	
	for (int i = 0; i < size; i++)
	{
		free(tempArray->upper_bound_tickets);
		tempArray->upper_bound_tickets = NULL;
		free(tempArray->lower_bound_tickets);
		tempArray->lower_bound_tickets = NULL;
	}
	
	free(tempArray);
	tempArray = NULL;
}

void merge(Process *array, int size, int start, int end, int mid, Process *tempArray)
{
	int start1 = start;
	int start2 = mid+1;
	int end1 = mid;
	int end2 = end;
	int index = start1;
	
	while (start1 <= end1 && start2 <= end2)
	{
		if (array[start1].arrival_time < array[start2].arrival_time)
		{
			swapProcess(&array[start1++], &tempArray[index++], size);
		}
		else
		{
			swapProcess(&array[start2++], &tempArray[index++], size);
		}
	}
	
	while (start1 <= end1)
	{
		swapProcess(&array[start1++], &tempArray[index++], size);
	}
	
	while (start2 <= end2)
	{
		swapProcess(&array[start2++], &tempArray[index++], size);
	}
	
	for (int i = 0; i < size; i++)
	{
		swapProcess(&tempArray[i], &array[i], size);
	}
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
}

void swapProcess(Process *processA, Process *processB, int size)
{
	processB->pid = processA->pid;
	processB->arrival_time = processA->arrival_time;
	processB->burst_duration = processA->burst_duration;
	processB->priority = processA->priority;
	processB->waiting_time = processA->waiting_time;
	processB->turnaround_time = processA->turnaround_time;
	processB->duration_left = processA->duration_left;
	processB->num_of_tickets = processA->num_of_tickets;
	swapTickets(processB->lower_bound_tickets, processA->lower_bound_tickets, size);
	swapTickets(processB->upper_bound_tickets, processA->upper_bound_tickets, size);
}

void swapTickets(int *ticketsA, int *ticketsB, int size)
{
	for (int i = 0; i < size; i++)
	{
		ticketsB[i] = ticketsA[i];
	}
}

<<<<<<< HEAD
void passTickets(Process *processes, AlgorithmOverhead *overhead)
{	
	int greatest_num = 0;
	int next_pos = 0;
	
	for (int pos = 0; pos < overhead->size; pos++)
	{
		if (greatest_num < processes[pos].num_of_tickets)
		{
			greatest_num = processes[pos].num_of_tickets;
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

void PriorityScheduling(Process *processes, int size)
{
	/*Variables*/
	AlgorithmOverhead *overhead = malloc(sizeof(overhead));
	overhead->size = size;
	overhead->processes_left = size; //The number of processes left to complete their run.
	overhead->time = 1; //Time of execution.
	overhead->option = 3;
	overhead->current_pos = findProcess(processes, overhead); //Current position of the running process within the new array. 
	
	while (overhead->processes_left > 0) //While the number of processes left is greater than 0...
	{	
		printf("From PriorityScheduling: Current Process ID = %d\n", processes[overhead->current_pos].pid);
		printf("From PriorityScheduling: processes[%d].duration_left = %d\n", overhead->current_pos, processes[overhead->current_pos].duration_left);
		printf("From PriorityScheduling: time = %d\n", overhead->time);
		
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

int findWinningTicket(Process *processes, AlgorithmOverhead *overhead)
{
	int winning_pos = -1;
	
	for (int pos = 0; pos < overhead->size; pos++)
	{
		for (int t_pos = 0; t_pos < processes[pos].num_of_tickets; t_pos++)
		{
			if (processes[pos].lower_bound_tickets[t_pos] >= overhead->winning_ticket &&
				processes[pos].upper_bound_tickets[t_pos] <= overhead->winning_ticket)
				{
					winning_pos = pos;
				}
		}
	}
	
	return winning_pos;
}

void LotteryScheduling(Process *processes, int size, int random_seed)
{
	AlgorithmOverhead *overhead = malloc(sizeof(AlgorithmOverhead));
	overhead->size = size;
	overhead->processes_left = size;
	overhead->time = 1;
	overhead->option = 4;
	overhead->current_pos = findProcess(processes, overhead);
	
	srand(random_seed);
	overhead->winning_ticket = rand();
	
	while (overhead->processes_left > 0)
	{
		if (processes[overhead->current_pos].duration_left <= 0)
		{
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
=======
void PriorityScheduling(Process *processes, int size)
{
	/*Variables*/
	int processes_left = size; //The number of processes left to complete their run.
	int time = 1; //Time of execution.
	int current_pos = findProcess(processes, size, time, 3); //Current position of the running process within the new array. 
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{	
		printf("From PriorityScheduling: Current Process ID = %d\n", processes[current_pos].pid);
		printf("From PriorityScheduling: processes[%d].duration_left = %d\n", current_pos, processes[current_pos].duration_left);
		printf("From PriorityScheduling: time = %d\n", time);
		
		if (processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			current_pos = switchProcesses(processes, size, current_pos, time, &processes_left, 3);
		}
		
		time++; //Increment the time.
		processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
	}
}

void LotteryScheduling(Process *lottery_processes, int size, int random_seed)
{
	/*Variables*/
	Process temp; //Temporary processes for swapping.
	int winner_pos = 0; //Position of the process that won the lottery.
	int most_tickets = 0; //Count of the most tickets held by a process.
	int most_tickets_pos = 0; //Positon of the process that has the most tickets.
	int winning_num = 0; //The winning number of the lottery.
	int time = 1; //Time of execution.
	int processes_left = size; //The number of processes left to complete their run.
	int lot_pos = -1;  //Position of sorting by lottery.
	int highest_ticket = 0;
	int lowest_ticket = lottery_processes[0].lower_bound_tickets[0];
	
	srand((unsigned int)random_seed); //Set the random number generator with the random_seed parameter.
	
	for (int pos = 0; pos < size; pos++)
	{
		for (int t_pos = 0; t_pos < size; t_pos++)
		{
			if (lottery_processes[pos].upper_bound_tickets[t_pos] > highest_ticket)
			{
				highest_ticket = lottery_processes[pos].upper_bound_tickets[t_pos];
			}
			
			if (lottery_processes[pos].lower_bound_tickets[t_pos] < lowest_ticket)
			{
				lowest_ticket = lottery_processes[pos].lower_bound_tickets[t_pos];
			}
		}
	}
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{
		//printf("processes_left = %d\n", processes_left);
		
		if (lot_pos == -1)
		{
			do
			{
				winning_num = (rand() % (highest_ticket - lowest_ticket)) + lowest_ticket; //Set the winning lottery number with a random number.
			} while (winning_num > highest_ticket || winning_num < lowest_ticket);
			
			for (int pos = 0; pos < size; pos++) //For the beginning of the old array, don't stop cycling through processes until the current position is equal or greater to irs size.
			{
				if (lottery_processes[pos].duration_left > 0 &&
					lottery_processes[pos].arrival_time <= time) //If the current process has tickets in its posession, then...
					{
						for (int t_pos = 0; t_pos < size; t_pos++) //From the beginning to the end of the list of tickets..
						{
							if (winning_num >= lottery_processes[pos].lower_bound_tickets[t_pos] && 
								winning_num <= lottery_processes[pos].upper_bound_tickets[t_pos]) //If the lottery number is within the current process' winning range, then...
								{
										winner_pos = pos; //Declare it the winner and store its position.
								}
						}
					}
			}
			
			for (int pos = 0; pos < size; pos++)
			{
				if (lottery_processes[pos].num_of_tickets > most_tickets && lottery_processes[pos].pid != lottery_processes[winner_pos].pid) //If the current process has a greater amount of tickets than the highet number of tickets, then...
					{
						most_tickets = lottery_processes[pos].num_of_tickets;
						most_tickets_pos = pos; //Set the position of the process with the highest amount of tickets to that of the current process.
					}
			}
			
			for (int t_pos = 0; t_pos < size; t_pos++) //From the beginning to the end of the winning process' list of tickets...
			{
				if (lottery_processes[most_tickets_pos].lower_bound_tickets[t_pos] == 0 && lottery_processes[most_tickets_pos].upper_bound_tickets[t_pos] == 0)
				{
					lottery_processes[most_tickets_pos].lower_bound_tickets[t_pos] = lottery_processes[winner_pos].lower_bound_tickets[t_pos]; //Add the winner's lower bound tickets to the process that carries the most tickets.
					lottery_processes[most_tickets_pos].upper_bound_tickets[t_pos] = lottery_processes[winner_pos].upper_bound_tickets[t_pos]; //Add the winner's upper bound tickets to the process that carries the most tickets.
					lottery_processes[most_tickets_pos].num_of_tickets++; //Increment the number of tickets the receiving process has.
					lottery_processes[winner_pos].lower_bound_tickets[t_pos] = 0; //Empty the lower ticket range of the winning process at this position.
					lottery_processes[winner_pos].upper_bound_tickets[t_pos] = 0; //Empty the upper ticket range of the winning process at this position.
				}
			}
			
			lottery_processes[winner_pos].num_of_tickets = 0; //Empty the number of tickets of the winning process.
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (lottery_processes[pos].arrival_time <= time && 
					lottery_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (lottery_processes[pos].pid != lottery_processes[winner_pos].pid) 
						{
							lottery_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							lottery_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			lottery_processes[winner_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			lottery_processes[winner_pos].turnaround_time++; //Increment the turnaround time for the process.
			lot_pos = 0; //Set the sorting position to 0.
		}
		else if (lottery_processes[winner_pos].duration_left <= 0)
		{
			//Swap out the process that is occupying the sorting position with that of the recently finished process.
			temp = lottery_processes[lot_pos]; 
			lottery_processes[lot_pos] = lottery_processes[winner_pos];
			lottery_processes[winner_pos] = temp;
			lot_pos++; //Increment the sorting position.
			processes_left--; //Decrement the number of processes left to run.
		
			most_tickets = 0;
			
			do
			{
				winning_num = (rand() % (highest_ticket - lowest_ticket)) + lowest_ticket; //Set the winning lottery number with a random number.
			} while (winning_num > highest_ticket || winning_num < lowest_ticket);
			
			for (int pos = 0; pos < size; pos++) //For the beginning of the old array, don't stop cycling through processes until the current position is equal or greater to irs size.
			{
				if (lottery_processes[pos].duration_left > 0 &&
					lottery_processes[pos].arrival_time <= time) //If the current process has tickets in its posession, then...
					{
						for (int t_pos = 0; t_pos < size; t_pos++) //From the beginning to the end of the list of tickets..
						{
							if (lottery_processes[pos].num_of_tickets != 0 && 
								winning_num >= lottery_processes[pos].lower_bound_tickets[t_pos] && 
								winning_num <= lottery_processes[pos].upper_bound_tickets[t_pos]) //If the lottery number is within the current process' winning range, then...
								{
									winner_pos = pos; //Declare it the winner and store its position.
								}
						}
					}
			}
				
			if (processes_left > 1)
			{
				for (int pos = 0; pos < size; pos++)
				{
					if (lottery_processes[pos].num_of_tickets > most_tickets && lottery_processes[pos].pid != lottery_processes[winner_pos].pid) //If the current process has a greater amount of tickets than the highet number of tickets, then...
						{
							most_tickets = lottery_processes[pos].num_of_tickets;
							most_tickets_pos = pos; //Set the position of the process with the highest amount of tickets to that of the current process.
						}
				}
				
				for (int t_pos = 0; t_pos < size; t_pos++) //From the beginning to the end of the winning process' list of tickets...
				{
					if (lottery_processes[winner_pos].lower_bound_tickets[t_pos] != 0 && lottery_processes[winner_pos].upper_bound_tickets[t_pos] != 0)
					{
						lottery_processes[most_tickets_pos].lower_bound_tickets[t_pos] = lottery_processes[winner_pos].lower_bound_tickets[t_pos]; //Add the winner's lower bound tickets to the process that carries the most tickets.
						lottery_processes[most_tickets_pos].upper_bound_tickets[t_pos] = lottery_processes[winner_pos].upper_bound_tickets[t_pos]; //Add the winner's upper bound tickets to the process that carries the most tickets.
						lottery_processes[most_tickets_pos].num_of_tickets++; //Increment the number of tickets the receiving process has.
						lottery_processes[winner_pos].lower_bound_tickets[t_pos] = 0; //Empty the lower ticket range of the winning process at this position.
						lottery_processes[winner_pos].upper_bound_tickets[t_pos] = 0; //Empty the upper ticket range of the winning process at this position.
					}
					else if (lottery_processes[winner_pos].lower_bound_tickets[t_pos] == 0 && lottery_processes[winner_pos].upper_bound_tickets[t_pos] != 0)
					{
						lottery_processes[most_tickets_pos].lower_bound_tickets[t_pos] = lottery_processes[winner_pos].lower_bound_tickets[t_pos]; //Add the winner's lower bound tickets to the process that carries the most tickets.
						lottery_processes[most_tickets_pos].upper_bound_tickets[t_pos] = lottery_processes[winner_pos].upper_bound_tickets[t_pos]; //Add the winner's upper bound tickets to the process that carries the most tickets.
						lottery_processes[most_tickets_pos].num_of_tickets++; //Increment the number of tickets the receiving process has.
						lottery_processes[winner_pos].lower_bound_tickets[t_pos] = 0; //Empty the lower ticket range of the winning process at this position.
						lottery_processes[winner_pos].upper_bound_tickets[t_pos] = 0; //Empty the upper ticket range of the winning process at this position.
					}
				}
			
				lottery_processes[winner_pos].num_of_tickets = 0; //Empty the number of tickets of the winning process.	
			}
					
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (lottery_processes[pos].arrival_time <= time && 
					lottery_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (lottery_processes[pos].pid != lottery_processes[winner_pos].pid) 
						{
							lottery_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							lottery_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			lottery_processes[winner_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			lottery_processes[winner_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		else
		{
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (lottery_processes[pos].arrival_time <= time && 
					lottery_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (lottery_processes[pos].pid != lottery_processes[winner_pos].pid) 
						{
							lottery_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							lottery_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			lottery_processes[winner_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			lottery_processes[winner_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		
		/*if ((*lottery_processes)[winner_pos].duration_left < 0)
		{
			printf("HERE!!!!!\n");
			printf("(*lottery_processes)[%d].burst_duration = %d\n", winner_pos, (*lottery_processes)[winner_pos].burst_duration);
			printf("processes_left = %d\n", processes_left);
		}*/
		
		//printf("(*lottery_processes)[%d].duration_left = %d\n", winner_pos, (*lottery_processes)[winner_pos].duration_left);

		time++; //Increment the time.
	}
>>>>>>> 60f8e5bebf8cad69c9849c9b76f9512f04bea360
}
