//Author: coleman7245
//Project: Encryption Program
//Last Edit: Friday, February 14, 2019

#ifndef FILEIO_H
#define FILEIO_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char* readFile(const char *in_filename, int *size);
int writeFile(const char *out_filename, const unsigned char *block, int size);
int findFileSize(FILE *current_file);
int findNumToPad(const unsigned char *block, const int length);
int findNumOfPadding(const unsigned char *padded_block, const int length);
unsigned char byteXOR(unsigned char block_c, unsigned char key_c);

#endif


