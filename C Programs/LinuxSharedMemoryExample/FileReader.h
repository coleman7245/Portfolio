/* 
 * Author: Derek Coleman
 * Assignment: PA3
 * Class: CS370
 * Instructor: Malaiya Yashwart
 * Date: Monday, October 17, 2016
 */ 

#ifndef FILEREADER_H //If the FileReader header is not defined, then...
#define FILEREADER_H //Define the FileReader.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int getFileSize(FILE *file); //Retrieves the file size of the given file.
float *readFile(FILE *file, int *size); //Creates an array of integers out of data read from a file.

#endif //End if.
