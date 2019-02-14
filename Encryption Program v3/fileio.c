//Author: coleman7245
//Project: Encryption Program
//Last Edit: Friday, February 14, 2019

#include "fileio.h"

unsigned char* readFile(const char *in_filename, int *size)
{
	FILE *in_file = fopen(in_filename, "rb");
	
	if (in_file == NULL)
	{
		perror("Failed to open input file!\n");
		return NULL;
	}
	
	*size = findFileSize(in_file);
	
	if (*size <= 0)
	{
		perror("File size is less than or equal to zero!\n");
		return NULL;
	}
	
	unsigned char *block = malloc((size_t)(size + 1));
	block[*size] = '\0';
	
	if (block == NULL)
	{
		perror("Memory allocation for text block failed!\n");
		return NULL;
	}
	
	int block_pos = 0;
	
	while (!feof(in_file))
	{
		if (block_pos >= *size)
		{
			break;
		}
	
		if (!fread(&block[block_pos], 1, 1, in_file))
		{
			if (feof(in_file))
			{
				break;
			}
			else
			{
				perror("Failed to read from input file!\n");
				return NULL;
			}
		}
				
		block_pos++;
	}
	
	fclose(in_file);
	
	return block;
}

int writeFile(const char *out_filename, const unsigned char *block, const int size)
{
	if (size <= 0)
	{
		perror("File size is less than or equal to zero!\n");
		return 0;
	}
	
	FILE *out_file = fopen(out_filename, "wb");
	
	if (out_file == NULL)
	{
		perror("Failed to open output file!\n");
		return 0;
	}
		
	int block_pos = 0;
	
	while (block_pos < size)
	{
		if (!fwrite(&block[block_pos], 1, 1, out_file))
		{
			perror("Failed to write to output file!\n");
			return 0;
		}
				
		block_pos++;
	}

	fclose(out_file);
	
	return 1;
}

int findFileSize(FILE *current_file)
{
	int size = 0;
		
	fseek(current_file, 0, SEEK_END);
	size = ftell(current_file);
	rewind(current_file);
	
	return size;
}

int findNumToPad(const unsigned char *block, const int length)
{
	if (block == NULL)
	{
		perror("Unpadded text block is NULL!\n");
		return 0;
	}
	
	int padding_num = 0;
	int multi_of_eight = 0;
	int byte_count = 0;
	
	for (int block_pos = 0; block_pos < length; block_pos++)
	{
		if (block[block_pos] == ' ' || block[block_pos] == '\n' || 
			block[block_pos] == '\r')
		{
			if (byte_count % 8 != 0)
			{
				while (multi_of_eight < byte_count)
				{
					multi_of_eight += 8;
				}
				
				padding_num += (multi_of_eight - byte_count);
				multi_of_eight = 0;
			}
		}
		else
		{
			byte_count++;
		}
	}
	
	return padding_num;
}

int findNumOfPadding(const unsigned char *padded_block, const int length)
{
	if (padded_block == NULL)
	{
		printf("Padded text block is NULL!\n");
		return 0;
	}
	
	int num_of_padding = 0;
	
	for (int pad_pos = 0; pad_pos < length; pad_pos++)
	{
		if (padded_block[pad_pos] == 0x80)
		{
			num_of_padding++;
		}
	}
	
	return num_of_padding;
}

unsigned char byteXOR(unsigned char block_c, unsigned char key_c)
{
	unsigned char result = '\0';
	
	result = block_c & key_c;
	result = ~result;
	result &= (block_c | key_c);
	
	return result;
}
