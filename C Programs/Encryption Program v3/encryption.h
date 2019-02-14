//Author: Derek Coleman
//Assignment: PA1
//Class: CS356
//Instructor: Dr. Joseph Gersch
//Last Edit: Tuesday, May 17, 2016

#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include "fileio.h"

int XOR (unsigned char *block, const unsigned char *key, const int original_length, const int key_length);
unsigned char *padText(const unsigned char *block, const int original_length, int *new_length);
unsigned char *depadText(const unsigned char* padded_block, const int original_length, int *new_length);
int swap(unsigned char *block, const unsigned char *key, const int original_length, const int key_length);
int streamEncryptAndDecrypt(const char *infile_filename, const char *key_filename, const char *out_filename);
int blockEncrypt(const char *block_filename, const char *key_filename, const char *out_filename);
int blockDecrypt(const char *decrypt_filename, const char *key_filename, const char *out_filename);

#endif
