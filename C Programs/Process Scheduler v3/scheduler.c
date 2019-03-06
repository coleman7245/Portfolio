//Author: Derek Coleman
//Project: Encryption Program
//Last Update: 3/6/19

#include<stdlib.h> //Include the C standard library header.
#include<stdio.h> //Include the C standard IO header.

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
	int num_of_tickets; //The total number of tickets the process holds.
	int *upper_bound_tickets; //The upper tier of tickets in the lottery.
	int *lower_bound_tickets; //The lower tier of tickets in the lottery.
	
} Process; //Struct for storing process information.

/*Prototypes for methods*/
void readFile(FILE *input_file, int size, Process *processes); //Reads a file for the specific parameters of this assignment. Returns a pointer to an array of processes.
void printProcessInfo(Process *processes, int size, int option); //Prints the process information specific to this assignment in stdout.
int findNewLines(FILE *open_file); //Helper function to find the byte size of a file.
int displayMenu(Process *processes, int size, int random_seed); //Displays a menu for the end user.
void FCFS(Process *fcfs_processes, int size); //Schedules the list of processes as first-come, first-serve.
void SJFnonPre(Process *sjf_non_pre_processes, int size); //Schedules the list of processes as short job first without preemption.
void SJFPre(Process *sjf_pre_processes, int size); //Schedules the list of processes as short job first with preemption.
void PriorityScheduling(Process *priority_processes, int size); //Schedules the list of processes according to their individual priority.
void LotteryScheduling(Process *lottery_processes, int size, int random_seed); //Schedules the list of processes using a lottery system.

//Method Summary: The main method of execution.
int main(int argc, char** argv)
{
	if (argc != 3) //If there are two arguments present, then...
	{
		return 0; //Return false, indicating failure;
	}
	
	/*Variables*/
	FILE *input_file = fopen(argv[1], "rb"); //Open the file with the filename in the argument list.
	int size = findNewLines(input_file); //Find the size of the file.
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
	
	fclose(input_file); //Close the input file.
	
	if (data == NULL) //If the readFile function failed to return an array of processes, then...
	{
		printf("Read of file failed!\n"); //Print an error message, specifying the file.
		return 0; //Return false, indicating failure.
	}
	
	if (!displayMenu(data, size, r_seed)) //If the menu wasn't displayed, then...
	{
		printf("Failed to display menu!\n"); //Print an error message, specifying the file.
		return 0; //Return false, indicating failure.
	}
	
	for (int pos = 0; pos < size; pos++) //From the beginning to the end of the file...
	{
		free(data[pos].lower_bound_tickets); //Free the memory allocated for the list of lower ticket ranges.
		free(data[pos].upper_bound_tickets); //Free the memory allocated for the list of upper ticket ranges.
	}

	free(data); //Free the memory allocated for the list of processes.
	data = NULL; //Set the pointer to NULL.
	
	return 1; //If everything performed accordingly, return true.
}

/*Auxiliary functions*/
//Method Summary: Reads the contents of the input file.
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
				else //An unspecified error occured.
				{
					return; //Return to the calling function.
				}
			}
		
		processes[r_pos].num_of_tickets = 1; //Initialize the number tickets the process holds to 1.
		processes[r_pos].duration_left = processes[r_pos].burst_duration; //Set the burst duration left to the maximum burst duration.
		
		r_pos++; //Increment the position in the array of new processes.
	}
}

//Method Summary: Prints the characteristics of the processes in the process list.
void printProcessInfo(Process *processes, int size, int option)
{
	/*Variables*/
	double average_waiting_time = 0; //The average waiting time for a process.
	double throughput = 0; //The throughput of the list of processes.
	double average_turnaround_time = 0; //The average turnaround time for a process.
	int choiceChar = (int)'y'; //Captures the menu choice from the user.
	
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
			//List the first 10 processes before asking the user to continue.
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

//Method Summary: Finds the new line characters in a file.
int findNewLines(FILE *open_file)
{
	/*Variables*/
	int size = 0; //The number of lines in a file.
	int c = '\0'; //Captures a character from the file stream.
	
	while (!feof(open_file)) //While the pointer is not at the end of the file...
	{
		if (!fread(&c, sizeof(char), 1, open_file)) //If the file read failed, then...
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
		
		if (c == '\n' || c == '\r') //If the character is a new line character, then...
		{
			size++; //Increment the number of lines.
		}
	}
	
	rewind(open_file); //Place the pointer at the beginning of the file.
	
	return size; //Return the size of the file.
}

//Method Summary: Displays the menu for the user.
int displayMenu(Process *processes, int size, int random_seed)
{
	/*Variables*/
	Process *current_list; //List of processes.
	int option = 0; //Storage for menu options.
	
	current_list = malloc(sizeof(Process) * size); //Allocate memory for the current list of processes.
		
	if (current_list == NULL) //If the memory allocation failed, then...
	{
		return 0; //Return false;
	}
	
	for (int pos = 0; pos < size; pos++) //For every 
	{
		current_list[pos].lower_bound_tickets = malloc(sizeof(int) * size); //Allocate memory to the lower bound ticket list.
		
		if (current_list[pos].lower_bound_tickets == (int *)NULL) //If the SJFnonPre method failed, then...
		{
			return 0; //Return false, indicating failure;
		}
		
		current_list[pos].upper_bound_tickets = malloc(sizeof(int) * size); //Allocate memory to the upper bound ticket list.
			
		if (current_list[pos].upper_bound_tickets == (int *)NULL) //If the memory allocation failed, then...
		{
			return 0; //Return false, indicating failure.;
		}
	}
	
	//Initialize a processor list meant to be displayed and altered by the scheduler algorithms.
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
				SJFnonPre(current_list, size); //Sort the current list of processes by the shortest job first with no preemption.
				break;
			case 3:
				SJFPre(current_list, size); //Sort the current list of processes by the shortest job first with preemption.
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
		
	} while(option != 6); //While the user has chosen an option other than exit...
	
	//Free the memory of each process and set the ticket list pointers to null afterward.
	for (int pos = 0; pos < size; pos++)
	{
		free(current_list[pos].lower_bound_tickets);
		current_list[pos].lower_bound_tickets = NULL;
		free(current_list[pos].upper_bound_tickets);
		current_list[pos].upper_bound_tickets = NULL;
	}
	
	//Free the memory of the processor list and set its pointer to null.
	free(current_list);
	current_list = NULL;
	
	return 1; //Return 1, indicating success.
}

//Method Summary: First come, first serve algorithm that prioritizes the first process to enter the queue.
void FCFS(Process *fcfs_processes, int size)
{
	/*Variables*/
	Process temp; //Temporary processes for swapping.
	int processes_left = size; //The number of processes left to complete their run.
	int fcfs_pos = -1; //Position of sorting by fist come, first serve.
	int time = 1; //Time of execution.
	int current_pos = -1; //Current position of the running process within the new array. 
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{	
		if (fcfs_pos == -1) //If this is the first process to run, then...
		{
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (fcfs_processes[pos].arrival_time <= time && 
					fcfs_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if ((current_pos == -1) || 
							(fcfs_processes[current_pos].burst_duration > fcfs_processes[pos].burst_duration)) 
							{
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (fcfs_processes[pos].arrival_time <= time && 
					fcfs_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (fcfs_processes[pos].pid != fcfs_processes[current_pos].pid) 
						{
							fcfs_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							fcfs_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			fcfs_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			fcfs_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
			fcfs_pos++; //Increment the sorting position.
		}
		else if (fcfs_processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			//Swap out the process that is occupying the sorting position with that of the recently finished process.
			temp = fcfs_processes[fcfs_pos]; 
			fcfs_processes[fcfs_pos] = fcfs_processes[current_pos];
			fcfs_processes[current_pos] = temp;
			
			fcfs_pos++; //Increment the sorting position.
			processes_left--; //Decrement the number of processes left to run.
			current_pos = -1; //Reset the current position within the list of processes to the default position.
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((fcfs_processes[pos].arrival_time <= time) &&
					(fcfs_processes[pos].duration_left > 0)) //Check if the process arrived on time and has CPU bursts to spend.
					{
						//If a canidate has yet to be found OR 
						//the currently running process arrived after the canidate process OR 
						//both processes arrived at the same time, but the currently running process has a longer burst duration, then...
						if (current_pos == -1 ||
							(fcfs_processes[current_pos].arrival_time > fcfs_processes[pos].arrival_time) ||
							(fcfs_processes[current_pos].arrival_time == fcfs_processes[pos].arrival_time && fcfs_processes[current_pos].burst_duration > fcfs_processes[pos].burst_duration))
							{
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (fcfs_processes[pos].arrival_time <= time && 
					fcfs_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (fcfs_processes[pos].pid != fcfs_processes[current_pos].pid) 
						{
							fcfs_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							fcfs_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			fcfs_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			fcfs_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		else //Otherwise...
		{
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (fcfs_processes[pos].arrival_time <= time && 
					fcfs_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (fcfs_processes[pos].pid != fcfs_processes[current_pos].pid) 
						{
							fcfs_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							fcfs_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			fcfs_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			fcfs_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		
		time++; //Increment the time.
	}
}

//Method Summary: Shortest job first algorithm that prioritizes the shortest job without preemption.
void SJFnonPre(Process *sjf_non_pre_processes, int size)
{
	/*Variables*/
	Process temp; //Temporary processes for swapping.
	int processes_left = size; //The number of processes left to complete their run.
	int shortest_job = 0; //The shortest job in the array of processes.
	int sjf_non_pre_pos = -1;  //Position of sorting by shortest job first (non-preemption).
	int time = 1; //Time of execution.
	int current_pos = -1; //Current position of the running process within the new array. 
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{	
		if (sjf_non_pre_pos == -1) //If this is the first process to run, then...
		{
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((sjf_non_pre_processes[pos].arrival_time <= time) &&
					(sjf_non_pre_processes[pos].duration_left > 0)) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the canidate process is shorter in duration than the currently running process, then...
						if ((current_pos == -1) || 
							(sjf_non_pre_processes[pos].burst_duration < shortest_job))
							{
								shortest_job = sjf_non_pre_processes[pos].burst_duration; //The shortest job is the burst duration of the current process.
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (sjf_non_pre_processes[pos].arrival_time <= time && 
					sjf_non_pre_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (sjf_non_pre_processes[pos].pid != sjf_non_pre_processes[current_pos].pid) 
						{
							sjf_non_pre_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							sjf_non_pre_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			sjf_non_pre_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			sjf_non_pre_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
			sjf_non_pre_pos++; //Increment the sorting position.
		}
		else if (sjf_non_pre_processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			//Swap out the process that is occupying the sorting position with that of the recently finished process.
			temp = sjf_non_pre_processes[sjf_non_pre_pos];
			sjf_non_pre_processes[sjf_non_pre_pos] = sjf_non_pre_processes[current_pos];
			sjf_non_pre_processes[current_pos] = temp;
			
			sjf_non_pre_pos++; //Increment the sorting position.
			processes_left--; //Decrement the number of processes left to run.
			current_pos = -1; //Reset the current position within the list of processes to the default position.
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((sjf_non_pre_processes[pos].arrival_time <= time) && 
					(sjf_non_pre_processes[pos].duration_left > 0)) //Check if the process arrived on time and has CPU bursts to spend.
					{
						//If a canidate has yet to be found OR 
						//the canidate process is shorter than the currently running process OR
						//the canidate process is as short as the currently running process, but the currently running process arrived later, then...
						if ((current_pos == -1) ||
							(sjf_non_pre_processes[pos].burst_duration < shortest_job) ||
							(sjf_non_pre_processes[pos].burst_duration == shortest_job && sjf_non_pre_processes[current_pos].arrival_time > sjf_non_pre_processes[pos].arrival_time))
							{
								shortest_job = sjf_non_pre_processes[pos].burst_duration; //The shortest job is the burst duration of the canidate process.
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (sjf_non_pre_processes[pos].arrival_time <= time && 
					sjf_non_pre_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (sjf_non_pre_processes[pos].pid != sjf_non_pre_processes[current_pos].pid) 
						{
							sjf_non_pre_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							sjf_non_pre_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			sjf_non_pre_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			sjf_non_pre_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		else //Otherwise...
		{	
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (sjf_non_pre_processes[pos].arrival_time <= time && 
					sjf_non_pre_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (sjf_non_pre_processes[pos].pid != sjf_non_pre_processes[current_pos].pid) 
						{
							sjf_non_pre_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							sjf_non_pre_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			sjf_non_pre_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			sjf_non_pre_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		
		time++; //Increment the time.
	}
}

//Method Summary; The shortest job first algorithm that prioritizes the the shortest job first with preemption.
void SJFPre(Process *sjf_pre_processes, int size)
{
	/*Variables*/
	Process temp; //Temporary processes for swapping.
	int time = 1; //Time of execution.
	int sjf_pre_pos = -1;  //Position of sorting by shortest job first (preemptive).
	int current_pos = -1; //Current position of the running process within the new array. 
	int processes_left = size; //The number of processes left to complete their run.
	int shortest_job = 0; //The shortest job in the array of processes.
	int isPresent = 0; //Check to see if the currently running process was already swapped before.
	int swapped = 0; //Check to see if a swap occured.
		
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{	
		if (sjf_pre_pos == -1) //If this is the first process to run, then...
		{
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((sjf_pre_processes[pos].arrival_time <= time) &&
					(sjf_pre_processes[pos].duration_left > 0)) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the canidate process is shorter in duration than the currently running process, then...
						if ((current_pos == -1) || 
							(sjf_pre_processes[pos].burst_duration < shortest_job))
							{
								shortest_job = sjf_pre_processes[pos].burst_duration; //The shortest job is the burst duration of the canidate process.
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (sjf_pre_processes[pos].arrival_time <= time && 
					sjf_pre_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (sjf_pre_processes[pos].pid != sjf_pre_processes[current_pos].pid) 
						{
							sjf_pre_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							sjf_pre_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			sjf_pre_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			sjf_pre_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
			
			sjf_pre_pos++; //Increment the sorting position.
			
			//printf("Swapped P%d at sjf_pre_pos = %d with P%d at current_pos = %d\n", sjf_pre_processes[sjf_pre_pos].pid, sjf_pre_pos, sjf_pre_processes[current_pos].pid, current_pos);
			//Swap out the process that is occupying the sorting position with that of the recently finished process.
			temp = sjf_pre_processes[sjf_pre_pos];
			sjf_pre_processes[sjf_pre_pos] = sjf_pre_processes[current_pos];
			sjf_pre_processes[current_pos] = temp;
			
			current_pos = sjf_pre_pos; //The position of the currently running process is the sorting position.
			sjf_pre_pos++; //Increment the sorting position.
		}
		else if (sjf_pre_processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			processes_left--; //Decrement the number of processes left to run.
			current_pos = -1; //Reset the current position within the list of processes to the default position.
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((sjf_pre_processes[pos].arrival_time <= time) && 
					(sjf_pre_processes[pos].duration_left > 0)) //Check if the process arrived on time and has CPU bursts to spend.
					{
						//If a canidate has yet to be found OR 
						//the canidate process has less time left than the currently running process OR
						//the canidate process has as much time left as the currently running process, but the currently running process arrived later, then...
						if ((current_pos == -1) ||
							(sjf_pre_processes[pos].duration_left < shortest_job) ||
							(sjf_pre_processes[pos].duration_left == shortest_job && sjf_pre_processes[current_pos].arrival_time > sjf_pre_processes[pos].arrival_time))
							{
								shortest_job = sjf_pre_processes[pos].duration_left; //The shortest job is the burst duration of the current process.
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = sjf_pre_pos; pos >= 0; pos--) //From the end to the beginning of the list... 
			{
				if (sjf_pre_processes[pos].pid == sjf_pre_processes[current_pos].pid) //If the pid of the current process is present in the previously run entries, then...
				{
					isPresent = 1; //Is present is true.
				}
			} 
			
			if (!isPresent && current_pos != -1) //If the currently running process was NOT already sorted, then...
			{
				//printf("Swapped P%d at sjf_pre_pos = %d with P%d at current_pos = %d\n", sjf_pre_processes[sjf_pre_pos].pid, sjf_pre_pos, sjf_pre_processes[current_pos].pid, current_pos);
				//Swap out the process that is occupying the sorting position with that of the recently finished process.
				temp = sjf_pre_processes[sjf_pre_pos];
				sjf_pre_processes[sjf_pre_pos] = sjf_pre_processes[current_pos];
				sjf_pre_processes[current_pos] = temp;
				
				current_pos = sjf_pre_pos; //The position of the currently running process is the sorting position.
				sjf_pre_pos++; //Increment the sorting position.
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (sjf_pre_processes[pos].arrival_time <= time && 
					sjf_pre_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (sjf_pre_processes[pos].pid != sjf_pre_processes[current_pos].pid) 
						{
							sjf_pre_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							sjf_pre_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			sjf_pre_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			sjf_pre_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		else
		{
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((sjf_pre_processes[pos].arrival_time <= time) && 
					(sjf_pre_processes[pos].duration_left > 0)) //Check if the process arrived on time and has CPU bursts to spend.
					{
						if (sjf_pre_processes[pos].burst_duration < sjf_pre_processes[current_pos].duration_left) //If the canidate process has less total maximum time duration than the currently running process has time duration left, then...
						{
							current_pos = pos; //Switch the current position to that of the canidate process.
							swapped = 1; //Signal that swap has taken place.
						}
					}
			}
			
			if (swapped && current_pos != -1) //If a swap occured, then...
			{
				for (int pos = sjf_pre_pos; pos >= 0; pos--) //From the end to the beginning of the list... 
				{
					if (sjf_pre_processes[pos].pid == sjf_pre_processes[current_pos].pid) //If the pid of the current process is present in the previously run entries, then...
					{
						isPresent = 1; //Is present is true.
					}
				} 
				
				if (!isPresent) //If the currently running process was NOT already sorted, then...
				{
					//Swap out the process that is occupying the sorting position with that of the recently finished process.
					temp = sjf_pre_processes[sjf_pre_pos];
					sjf_pre_processes[sjf_pre_pos] = sjf_pre_processes[current_pos];
					sjf_pre_processes[current_pos] = temp;
				
					current_pos = sjf_pre_pos; //The position of the currently running process is the sorting position.
					sjf_pre_pos++; //Increment the sorting position.
				}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (sjf_pre_processes[pos].arrival_time <= time && 
					sjf_pre_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (sjf_pre_processes[pos].pid != sjf_pre_processes[current_pos].pid) 
						{
							sjf_pre_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							sjf_pre_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			sjf_pre_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			sjf_pre_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		
		time++; //Increment the time.
		isPresent = 0; //Reset to false.
		swapped = 0; //Reset to false.
	}
}

//Method Summary: The priority scheduling algorithm that prioritizes processes with higher priority.
void PriorityScheduling(Process *priority_processes, int size)
{
	/*Variables*/
	Process temp; //Temporary processes for swapping.
	int processes_left = size; //The number of processes left to complete their run.
	int time = 1; //Time of execution.
	int priority_pos = -1;  //Position of sorting by priority.
	int highest_priority = 9999; //The highest priority held by a process within the list.
	int current_pos = -1; //Current position of the running process within the new array. 
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{	
		if (priority_pos == -1) //If this is the first process to run, then...
		{	
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((priority_processes[pos].arrival_time <= time) && 
					(priority_processes[pos].duration_left > 0)) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the canidate process has a higher priority than the currently running process, then...
						if ((current_pos == -1) || 
						(priority_processes[pos].priority < highest_priority))
						{
							highest_priority = priority_processes[pos].priority; //The priority of the canidate process is the highest priority.
							current_pos = pos; //Switch the current position to that of the canidate process.
						}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (priority_processes[pos].arrival_time <= time && 
					priority_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (priority_processes[pos].pid != priority_processes[current_pos].pid) 
						{
							priority_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							priority_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			priority_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			priority_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
			priority_pos = 0; //Increment the sorting position.
		}
		else if (priority_processes[current_pos].duration_left <= 0) //Else, if the process has finished with the CPU, then...
		{	
			//Swap out the process that is occupying the sorting position with that of the recently finished process.
			temp = priority_processes[priority_pos];
			priority_processes[priority_pos] = priority_processes[current_pos];
			priority_processes[current_pos] = temp;
			priority_pos++; //Increment the sorting position.
			
			processes_left--; //Decrement the number of processes left to run.
			current_pos = -1; //Reset the current position within the list of processes to the default position.
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if ((priority_processes[pos].arrival_time <= time) && 
					(priority_processes[pos].duration_left > 0)) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the canidate process has a higher priority than the currently running process OR
						//the canidate process is as important as the currently running process, but the current running process arrived later, then...
						if ((current_pos == -1) ||
							(priority_processes[pos].priority < highest_priority) ||
							(priority_processes[pos].priority == highest_priority && priority_processes[current_pos].arrival_time > priority_processes[pos].arrival_time))
							{
								highest_priority = priority_processes[pos].priority; //The priority of the canidate process is the highest priority.
								current_pos = pos; //Switch the current position to that of the canidate process.
							}
					}
			}
			
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (priority_processes[pos].arrival_time <= time && 
					priority_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (priority_processes[pos].pid != priority_processes[current_pos].pid) 
						{
							priority_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							priority_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			priority_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			priority_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		else
		{	
			for (int pos = 0; pos < size; pos++) //From the beginning to the end of the list of processes...
			{
				if (priority_processes[pos].arrival_time <= time && 
					priority_processes[pos].duration_left > 0) //Check if the process arrived on time and has yet to run.
					{
						//If a canidate has yet to be found OR 
						//the currently running process is shorter in duration than the canidate process, then...
						if (priority_processes[pos].pid != priority_processes[current_pos].pid) 
						{
							priority_processes[pos].waiting_time++; //Increment the waiting time of the processes that have arrived, but haven't yet run.
							priority_processes[pos].turnaround_time++; //Increment the turnaround time for the process.
						}
					}
			}
			
			priority_processes[current_pos].duration_left--; //Decrement the time remaining for the process to finish its task.
			priority_processes[current_pos].turnaround_time++; //Increment the turnaround time for the process.
		}
		
		time++; //Increment the time.
	}
}

//Method Summary: Lottery scheduling algorithm that picks a process based on a randomized lottery system.
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
	
	for (int pos = 0; pos < size; pos++) //For every process in the list...
	{
		for (int t_pos = 0; t_pos < size; t_pos++) //For every ticket in the process...
		{
			if (lottery_processes[pos].upper_bound_tickets[t_pos] > highest_ticket) //If the current upper bound ticket is higher than the current highest ticket, then...
			{
				highest_ticket = lottery_processes[pos].upper_bound_tickets[t_pos]; //Replace the previous highest ticket with the current ticket.
			}
			
			if (lottery_processes[pos].lower_bound_tickets[t_pos] < lowest_ticket) //If the current lower bound ticket is lower than the current lowest ticket, then...
			{
				lowest_ticket = lottery_processes[pos].lower_bound_tickets[t_pos]; //Replace the previous lowest ticket with the current ticket.
			}
		}
	}
	
	while (processes_left > 0) //While the number of processes left is greater than 0...
	{
		if (lot_pos == -1) //If the current postion within the lottery is the initial value, then...
		{
			do
			{
				winning_num = (rand() % (highest_ticket - lowest_ticket)) + lowest_ticket; //Set the winning lottery number with a random number.
			} while (winning_num > highest_ticket || winning_num < lowest_ticket); //Loop until the winning ticket is within bounds.
			
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
			
			for (int pos = 0; pos < size; pos++) //For every process in the list...
			{
				if (lottery_processes[pos].num_of_tickets > most_tickets && lottery_processes[pos].pid != lottery_processes[winner_pos].pid) //If the current process has a greater amount of tickets than the highet number of tickets, then...
					{
						most_tickets = lottery_processes[pos].num_of_tickets; //Set the most tickets to this process' number of tickets.
						most_tickets_pos = pos; //Set the position of the process with the highest amount of tickets to that of the current process.
					}
			}
			
			for (int t_pos = 0; t_pos < size; t_pos++) //From the beginning to the end of the winning process' list of tickets...
			{
				if (lottery_processes[most_tickets_pos].lower_bound_tickets[t_pos] == 0 && lottery_processes[most_tickets_pos].upper_bound_tickets[t_pos] == 0) //If the process has no tickets at this position, then...
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
		else if (lottery_processes[winner_pos].duration_left <= 0) //If the winning process has finish its task, then...
		{
			//Swap out the process that is occupying the sorting position with that of the recently finished process.
			temp = lottery_processes[lot_pos]; 
			lottery_processes[lot_pos] = lottery_processes[winner_pos];
			lottery_processes[winner_pos] = temp;
			lot_pos++; //Increment the sorting position.
			processes_left--; //Decrement the number of processes left to run.
		
			most_tickets = 0; //Reset the most tickets to 0.
			
			do
			{
				winning_num = (rand() % (highest_ticket - lowest_ticket)) + lowest_ticket; //Set the winning lottery number with a random number.
			} while (winning_num > highest_ticket || winning_num < lowest_ticket); //Loop until the winning ticket is within bounds.
			
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
				
			if (processes_left > 1) //If there are still processes left to run, then...
			{
				for (int pos = 0; pos < size; pos++) //For every process in the list...
				{
					if (lottery_processes[pos].num_of_tickets > most_tickets && lottery_processes[pos].pid != lottery_processes[winner_pos].pid) //If the current process has a greater amount of tickets than the highet number of tickets, then...
						{
							most_tickets = lottery_processes[pos].num_of_tickets; //Set the most tickets this the current process' number of tickets.
							most_tickets_pos = pos; //Set the position of the process with the highest amount of tickets to that of the current process.
						}
				}
				
				for (int t_pos = 0; t_pos < size; t_pos++) //From the beginning to the end of the winning process' list of tickets...
				{
					if (lottery_processes[winner_pos].lower_bound_tickets[t_pos] != 0 && lottery_processes[winner_pos].upper_bound_tickets[t_pos] != 0) //If the winning process has tickets to give, then...
					{
						lottery_processes[most_tickets_pos].lower_bound_tickets[t_pos] = lottery_processes[winner_pos].lower_bound_tickets[t_pos]; //Add the winner's lower bound tickets to the process that carries the most tickets.
						lottery_processes[most_tickets_pos].upper_bound_tickets[t_pos] = lottery_processes[winner_pos].upper_bound_tickets[t_pos]; //Add the winner's upper bound tickets to the process that carries the most tickets.
						lottery_processes[most_tickets_pos].num_of_tickets++; //Increment the number of tickets the receiving process has.
						lottery_processes[winner_pos].lower_bound_tickets[t_pos] = 0; //Empty the lower ticket range of the winning process at this position.
						lottery_processes[winner_pos].upper_bound_tickets[t_pos] = 0; //Empty the upper ticket range of the winning process at this position.
					}
					else if (lottery_processes[winner_pos].lower_bound_tickets[t_pos] == 0 && lottery_processes[winner_pos].upper_bound_tickets[t_pos] != 0) //If the winning process only has upper bound tickets to give, then...
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

		time++; //Increment the time.
	}
}
