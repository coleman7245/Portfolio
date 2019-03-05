//Author: Derek Coleman
//Project: Encryption Program
//Last Update: 3/5/19

#include "fileio.h" //Include the fileio header.

//Method Summary: Reads a file with the parameter filename and passes on the size of the character block.
unsigned char* readFile(const char *in_filename, int *size)
{
	FILE *in_file = fopen(in_filename, "rb"); //Open the file with the parameter filename.
	
	if (in_file == NULL) //If opening the file failed, then...
	{
		perror("Failed to open input file!\n"); //Print out an error, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	*size = findFileSize(in_file); //Find the size of the input file.
	
	if (*size <= 0) //If the file is empty, then...
	{
		perror("File size is less than or equal to zero!\n"); //Print out an error, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	unsigned char *block = malloc((size + 1)); //Allocate a block of memory to the text block.
	block[*size] = '\0'; //Place a null character at the end of the block.
	
	if (block == NULL) //If the memory allocation failed, then...
	{
		perror("Memory allocation for text block failed!\n"); //Print out an error message, specifying the reason.
		return NULL; //Return null, indicating the failure.
	}
	
	int block_pos = 0; //Initialize the current block position to 0.
	
	while (!feof(in_file)) //While the file is not at the end...
	{
		if (block_pos >= *size) //If the current block position is out of bounds, then...
		{
			break; //Break out of the loop.
		}
	
		if (!fread(&block[block_pos], 1, 1, in_file)) //If the file read failed, then...
		{
			if (feof(in_file)) //If the file was at the end, then...
			{
				break; //Break out of the loop.
			}
			else //The file failed to due an unknown error.
			{
				perror("Failed to read from input file!\n"); //Print an error, specifying the reason.
				return NULL; //Return null, indicating failure.
			}
		}
				
		block_pos++; //Increment the current block position.
	}
	
	fclose(in_file); //Close the file.
	
	return block; //Return the text block.
}

//Method Summary: Write the text block to a file.
int writeFile(const char *out_filename, const unsigned char *block, const int size)
{
	if (size <= 0) //If the file is empty, then...
	{
		perror("File size is less than or equal to zero!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	FILE *out_file = fopen(out_filename, "wb"); //Open the write file with the parameter filename.
	
	if (out_file == NULL) //If the opening of the file failed, then...
	{
		perror("Failed to open output file!\n"); //Print an error message, specifying the reason.
		return 0; //Return null, indicating failure.
	}
		
	int block_pos = 0; //Initialize the current block position to 0.
	
	while (block_pos < size) //While the current block position is within bounds...
	{
		if (!fwrite(&block[block_pos], 1, 1, out_file)) //If the file write failed, then...
		{
			perror("Failed to write to output file!\n"); //Print an error message, specifying the reason.
			return 0; //Return 0, indicating failure.
		}
				
		block_pos++; //Increment the current block position.
	}

	fclose(out_file); //Close the file.
	
	return 1; //Return 1, indicating success.
}

//Method Summary: Finds the size of an open file.
int findFileSize(FILE *current_file)
{
	int size = 0; //Initialize the size to 0.
		
	fseek(current_file, 0, SEEK_END); //Seek the end of the file.
	size = ftell(current_file); //The current position in the file stream is the size of the file.
	rewind(current_file); //Bring the position in the file stream to the beginning.
	
	return size; //Return the file size.
}

//Method Summary: Finds the number of padding at append to the text block.
int findNumToPad(const unsigned char *block, const int length)
{
	if (block == NULL) //If the text block is null, then...
	{
		perror("Unpadded text block is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	int padding_num = 0; //Initialize the padding number to 0.
	int multi_of_eight = 0; //Initialize the multiple of 8 to 0.
	int byte_count = 0; //Initialize the byte count to 0.
	
	for (int block_pos = 0; block_pos < length; block_pos++) //For every position within the block...
	{
		if (block[block_pos] == ' ' || block[block_pos] == '\n' || 
			block[block_pos] == '\r') //If the current block position contains either a space, carrage return, or new line character, then...
		{
			if (byte_count % 8 != 0) //If the byte count is divisible by 8, then...
			{
				while (multi_of_eight < byte_count) //While the multiple of 8 is less than the byte cout...
				{
					multi_of_eight += 8; //Increment the multiple of 8 by 8.
				}
				
				padding_num += (multi_of_eight - byte_count); //Increment the padding count by the difference of the multiple of 8 and the byte count.
				multi_of_eight = 0; //Reset the multiple of 8 to 0.
			}
		}
		else //An entire character section remains unexplored.
		{
			byte_count++; //Increment the byte count.
		}
	}
	
	return padding_num; //Return the padding number.
}

//Method Summary: Finds the padding already present in the block.
int findNumOfPadding(const unsigned char *padded_block, const int length)
{
	if (padded_block == NULL) //If the padded block is null, then...
	{
		printf("Padded text block is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	int num_of_padding = 0; //Initialize the number of padding to 0.
	
	for (int pad_pos = 0; pad_pos < length; pad_pos++) //For every character within the block...
	{
		if (padded_block[pad_pos] == 0x80) //If the character is equal to the padding character, then...
		{
			num_of_padding++; //Increment the number of padding.
		}
	}
	
	return num_of_padding; //Return the number of padding.
}

//Method Summary: Performs a bitwise XOR on a character and a key character.
unsigned char byteXOR(unsigned char block_c, unsigned char key_c)
{
	unsigned char result = '\0'; //Initialize the result with a null character.
	
	result = block_c & key_c; //AND the block character and the key character.
	result = ~result; //NOT the result.
	result &= (block_c | key_c); //AND the result with the block character ORed with the key character.
	
	return result; //Return the result.
}
