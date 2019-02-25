/* 
 * Author: coleman7245
 * Project: Linux Shared Memory Example
 * Last Update: 2/25/19
 */ 
 
Description of Files:
 
Mean.c: Calculates the mean, then stores it in shared memory. 
Median.c: Calculates the median, then stores it in shared memory. 
Mode.c: Calculates the mode, then stores it in shared memory.
Initiator.c: Forks itself three times, then executes the aforementioned programs--once each time. After the processes are done, the Initiator reads the results from shared memory. 
FileReader.c: Reads the text file given, then stores the data in an array for the Mean, Median, and Mode programs. 
FileReader.h: Header file for the FileReader.

Notes:

-The Initiator program takes a filename as an argument from the command console. It doesn't function any other way.
-The program segments, because the permissions are denied to attach the shared memory segment, despite the correct flag being set in the smhget function. 
 I tried my best to understand and fix the problem, but to no avail. I went to the CS120 lab during Sam's office hours to see if he could solve this issue, 
 but he couldn't find a solution either.
