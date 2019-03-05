/* 
 * Author: Derek Coleman
 * Project: Linux Shared Memory Example
 * Last Update: 3/4/19
 */ 

#ifndef FILEREADER_H //If the FileReader header is not defined, then...
#define FILEREADER_H //Define the FileReader.

#include <stdlib.h> //Include the C standard library for
#include <stdio.h> //Include the C standard IO header for file reading and writing.
#include <string.h> //Include the string header for storing and reading strings.

int getFileSize(FILE *file); //Retrieves the file size of the given file.
float *readFile(FILE *file, int *size); //Creates an array of integers out of data read from a file.

#endif //End if.
