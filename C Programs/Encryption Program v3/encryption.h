//Author: Derek Coleman
//Assignment: Encryption Program
//Last Update: 3/5/19

#ifndef ENCRYPTION_H //If the encryption header hasn't been included, then...
#define ENCRYPTION_H //Define the encryption header.

#include "fileio.h" //Include the file io header.

/* Function Header Declarations */
int XOR (unsigned char *block, const unsigned char *key, const int original_length, const int key_length);
unsigned char *padText(const unsigned char *block, const int original_length, int *new_length);
unsigned char *depadText(const unsigned char* padded_block, const int original_length, int *new_length);
int swap(unsigned char *block, const unsigned char *key, const int original_length, const int key_length);
int streamEncryptAndDecrypt(const char *infile_filename, const char *key_filename, const char *out_filename);
int blockEncrypt(const char *block_filename, const char *key_filename, const char *out_filename);
int blockDecrypt(const char *decrypt_filename, const char *key_filename, const char *out_filename);

#endif //End of directive branch.
