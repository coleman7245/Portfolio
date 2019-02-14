//Author: coleman7245
//Project: Encryption Program
//Last Edit: Friday, February 14, 2019

#include "encryption.h"

int XOR (unsigned char *block, const unsigned char *key, const int original_length, const int key_length)
{
	if (block == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}
	
	if (key == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}
	
	if (original_length <= 0)
	{
		perror("Size is less than or equal to zero!\n");
		return 0;
	}
	
	int key_pos = 0;
	unsigned char result = '\0';
	
	for (int block_pos = 0; block_pos < original_length; block_pos++)
	{
		if (key_pos >= key_length)
		{
			key_pos = 0;
		}
			
		result = block[block_pos] & key[key_pos];
		result = ~result;
		result &= (block[block_pos] | key[key_pos]);
		block[block_pos] = result;
		key_pos++;
	}
	
	return 1;
}

unsigned char *padText(const unsigned char *block, const int original_length, int *new_length)
{
	if (block == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return NULL;
	}
	
	int size = original_length + findNumToPad(block, original_length);
	
	if (size <= 0)
	{
		perror("size is less than or equal to zero!\n");
		return NULL;
	}
	
	unsigned char *padded_block = malloc((size_t)(size + 1));
	
	if (padded_block == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return NULL;
	}
	
	int byte_count = 0;
	int pad_pos = 0;
	int multi_of_eight = 0;
	
	for (int block_pos = 0; block_pos < original_length; block_pos++)
	{	
		if (block[block_pos] != ' ' && block[block_pos] != '\n' && block[block_pos] != '\r')
		{	
			byte_count++;
			padded_block[pad_pos] = block[block_pos];
			pad_pos++;
		}
		else
		{
			if (byte_count % 8 != 0)
			{
				while (multi_of_eight < byte_count)
				{
					multi_of_eight += 8;	
				}
				
				for (int bytes_to_fill = (multi_of_eight - byte_count); bytes_to_fill > 0; bytes_to_fill--)
				{
					padded_block[pad_pos] = 0x80;
					pad_pos++;	
				}
			}
				
			byte_count = 0;	
			multi_of_eight = 0;
		}	
	}
	
	padded_block[pad_pos] = '\0';
	*new_length = pad_pos;
	
	return padded_block;
}

unsigned char *depadText(const unsigned char* padded_block, const int original_length, int *new_length)
{
	if (padded_block == (unsigned char *)NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return NULL;
	}
	
	int size = original_length - findNumOfPadding(padded_block, original_length);
	
	if (size <= 0)
	{
		perror("size is less than or equal to zero!\n");
		return NULL;
	}
	
	unsigned char *block = (unsigned char *)malloc((size_t)(size + 1));
	
	if (block == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return NULL;
	}
	
	int block_pos = 0;
	
	for (int pad_pos = 0; pad_pos < original_length; pad_pos++)
	{	
		if (padded_block[pad_pos] != 0x80)
		{			
			block[block_pos] = padded_block[pad_pos];
			block_pos++;
		}
	}
	
	block[block_pos] = '\0';
	*new_length = block_pos;
		
	return block;
}

int swap(unsigned char *block, const unsigned char *key, const int original_length, const int key_length)
{
	if (block == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}
	
	if (key == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}
	
	if (original_length <= 0)
	{
		perror("size is less than or equal to zero!\n");
		return 0;
	}
	
	int mod_value = 0;
	char temp = '\0';
	int key_pos = 0;
	int srt = 0;
	int fin = 0;
	
	if (original_length <= 7)
	{
		fin = original_length - 1;
	}
	else
	{
		fin = 7;
	}
	
	for (int block_pos = 0; block_pos < original_length; block_pos++)
	{	
		if (key_pos >= key_length)
		{	
			key_pos = 0;
		}
		
		if (srt < fin)
		{	
			mod_value = key[key_pos] % 2;
			key_pos++;
		
			if (mod_value == 1)
			{	
				temp = block[srt];
				block[srt] = block[fin];
				block[fin] = temp;	
				srt++;
				fin--;	
			}
			else
			{
				srt++;	
			}
		}
		else
		{
			if (block_pos % 8 != 0)
			{
				block_pos += (8 - (block_pos % 8));
			}
			
			srt = block_pos;
				
			if (block_pos >= original_length)
			{
				break;
			}
			else if ((block_pos + 7) >= original_length)
			{
				fin = (original_length - 1);
			}
			else
			{
				fin = (srt + 7);
			}
				
			key_pos = 0;
		}	
	}
	
	return 1;
}

int streamEncryptAndDecrypt(const char *infile_filename, const char *key_filename, const char *out_filename)
{
	unsigned char in_c = '\0';
	unsigned char key_c = '\0';
	unsigned char xor_c = '\0';
	
	FILE *in_file = fopen(infile_filename, "rb");
	
	if (in_file == NULL)
	{
		perror("Failed to open input file!\n");
		return 0;
	}
	
	FILE *key_file = fopen(key_filename, "rb");
	
	if (key_file == NULL)
	{
		perror("Failed to open key file!\n");
		return 0;
	}
	
	FILE *out_file = fopen(out_filename, "wb");
	
	if (out_file == NULL)
	{
		perror("Failed to open output file!\n");
		return 0;
	}
	
	while (!feof(in_file))
	{
		//printf("Here!");
		
		if (!fread(&in_c, 1, 1, in_file))
		{
			if (feof(in_file))
			{
				break;
			}
			else
			{
				perror("Failed to read from input file!\n");
				return 0;
			}
		}
		
		if (!fread(&key_c, 1, 1, key_file))
		{
			if (feof(key_file))
			{
				rewind(key_file);
			}
			else
			{
				perror("Failed to read from key file!\n");
				return 0;
			}
		}
		
		xor_c = byteXOR(in_c, key_c);
			
		if (!fwrite(&xor_c, 1, 1, out_file))
		{
			perror("Failed to write to output file!\n");
			return 0;
		}
	}
	
	fclose(in_file);
	fclose(out_file);
	fclose(key_file);
	
	return 1;
}

int blockEncrypt(const char *block_filename, const char *key_filename, const char *out_filename)
{
	int old_length = 0;
	int key_length = 0;
	int new_length = 0;
	unsigned char *text = readFile(block_filename, &old_length);
	
	if (text == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}

	unsigned char *key = readFile(key_filename, &key_length);
	
	if (key == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}
	
	unsigned char *padded_text = padText(text, old_length, &new_length);
	
	if (padded_text == NULL)
	{
		perror("Unsigned char pointer is NULL!\n");
		return 0;
	}
	
	if (!XOR(padded_text, key, new_length, key_length))
	{
		perror("XOR failed!\n");
		return 0;
	}
	
	if (!swap(padded_text, key, new_length, key_length))
	{
		perror("Swap failed!\n");
		return 0;
	}
	
	if (!writeFile(out_filename, padded_text, new_length))
	{
		perror("Failed to write to encryption file!\n");
		return 0;
	}
	
	free(text);
	text = NULL;
	free(key);
	key = NULL;
	free(padded_text);
	padded_text = NULL;
	
	return 1;
}

int blockDecrypt(const char *decrypt_filename, const char *key_filename, const char *out_filename)
{	
	int key_length = 0;
	int old_length = 0;
	int new_length = 0;
	unsigned char *key = readFile(key_filename, &key_length);
	
	if (key == NULL)
	{
		perror("Key read failed!\n");
		return 0;
	}
			
	unsigned char *encrypted_text = readFile(decrypt_filename, &old_length);
	
	if (encrypted_text == NULL)
	{
		perror("File read failed!\n");
		return 0;
	}
		
	if (!swap(encrypted_text, key, old_length, key_length))
	{
		perror("Swap failed!\n");
		return 0;
	}
		
	if (!XOR(encrypted_text, key, old_length, key_length))
	{
		perror("XOR failed!\n");
		return 0;
	}
		
	unsigned char *depadded_text = depadText(encrypted_text, old_length, &new_length);
		
	if (depadded_text == NULL)
	{
		perror("Depadding failed!\n");
		return 0;
	}
	
	if (!writeFile(out_filename, depadded_text, new_length))
	{
		perror("Failed to write to decryption file!\n");
		return 0;
	}
	
	free(encrypted_text);
	encrypted_text = NULL;
	free(key);
	key = NULL;
	free(depadded_text);
	depadded_text = NULL;
		
	return 1;
}
