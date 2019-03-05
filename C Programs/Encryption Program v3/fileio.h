//Author: Derek Coleman
//Project: Encryption Program
//Last Update: 3/5/19

#ifndef FILEIO_H //If the file io header was NOT included, then...
#define FILEIO_H //Defne the file io header.
#include <stdio.h> //Include the C standard IO for reading and writing operations.
#include <string.h> //Include the string header for easier management of character arrays.
#include <stdlib.h> //Include the C standard library for basic operations.

/* Function Header Declarattions */
unsigned char* readFile(const char *in_filename, int *size); 
int writeFile(const char *out_filename, const unsigned char *block, int size);
int findFileSize(FILE *current_file);
int findNumToPad(const unsigned char *block, const int length);
int findNumOfPadding(const unsigned char *padded_block, const int length);
unsigned char byteXOR(unsigned char block_c, unsigned char key_c);

#endif //End directive if


