//Author: Derek Coleman
//Project: Encryption Program
//Last Update: 3/5/19

#include "encryption.h" //If the encryption header is include, then...

//Method Summary: Performs a bitwise XOR operation on an entire text block.
int XOR (unsigned char *block, const unsigned char *key, const int original_length, const int key_length)
{
	if (block == NULL) //If the text block is invalid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (key == NULL) //If the key is invalid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (original_length <= 0) //If the original length of the text block is invalid, then...
	{
		perror("Size is less than or equal to zero!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	int key_pos = 0; //Initialize the key position to 0.
	unsigned char result = '\0'; //Initialize the result to a null charater.
	
	for (int block_pos = 0; block_pos < original_length; block_pos++) //For every character in the block...
	{
		if (key_pos >= key_length) //If the key position is out of bounds, then...
		{
			key_pos = 0; //Reset the key position.
		}
			
		result = block[block_pos] & key[key_pos]; //AND the block and key characters.
		result = ~result; //NOT the result.
		result &= (block[block_pos] | key[key_pos]); //AND the ORing of the block and key characters.
		block[block_pos] = result; //Store the result in the current position within the block.
		key_pos++; //Increment the key position.
	}
	
	return 1; //Return 1, indicating success.
}

//Method Summary: Creates and returns a padded text block using the original text block.
unsigned char *padText(const unsigned char *block, const int original_length, int *new_length)
{
	if (block == NULL) //If the block is invalid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	int size = original_length + findNumToPad(block, original_length); //The size of the new padded block is the sum of the original size and the number of padding needed.
	
	if (size <= 0) //If the size is invalid, then...
	{
		perror("size is less than or equal to zero!\n"); //Print an error message, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	unsigned char *padded_block = malloc((size_t)(size + 1)); //Allocate memory for the padded block.
	
	if (padded_block == NULL) //If the memory allocation failed, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	int byte_count = 0; //Initialize the byte count to 0.
	int pad_pos = 0; //Initialize the padded block position to 0.
	int multi_of_eight = 0; //Initialize the multiple of 8 to 0.
	
	for (int block_pos = 0; block_pos < original_length; block_pos++) //For every character in the original block...
	{	
		if (block[block_pos] != ' ' && block[block_pos] != '\n' && block[block_pos] != '\r') //If the character is NOT a space or an end of line character, then...
		{	
			byte_count++; //Increment the byte count.
			padded_block[pad_pos] = block[block_pos]; //Add the non-padding character to the padded block.
			pad_pos++; //Increment the padded block position.
		}
		else //The character string has ended, so pad the rest of the line.
		{
			if (byte_count % 8 != 0) //If the byte count is NOT divisible by 8, then...
			{
				while (multi_of_eight < byte_count) //While the multiple of 8 is less than the byte count...
				{
					multi_of_eight += 8; //Increment the multiple of 8 by 8.	
				}
				
				for (int bytes_to_fill = (multi_of_eight - byte_count); bytes_to_fill > 0; bytes_to_fill--) //For every byte left to fill on the line...
				{
					padded_block[pad_pos] = 0x80; //Add the padding character.
					pad_pos++; //Increment the padded block position.
				}
			}
				
			byte_count = 0;	//Reset the byte count to 0.
			multi_of_eight = 0; //Reset the multiple of 8 to 0.
		}	
	}
	
	padded_block[pad_pos] = '\0'; //Place a null character at the end of the padded block.
	*new_length = pad_pos; //Place the padded block position as the new length to be sent back.
	
	return padded_block; //Return the padded block.
}

//Method Summary: Depads a text block, leaving the original characters without spaces.
unsigned char *depadText(const unsigned char* padded_block, const int original_length, int *new_length)
{
	if (padded_block == NULL) //If the padded block is invalid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	int size = original_length - findNumOfPadding(padded_block, original_length); //The size is the padded length minus the number of padding characters.
	
	if (size <= 0) //If the size is invalid, then...
	{
		perror("size is less than or equal to zero!\n"); //Print an error message, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	unsigned char *block = malloc((size + 1)); //Allocate memory for the unpadded block.
	
	if (block == NULL) //If the unpadded block is invalid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return NULL; //Return null, indicating failure.
	}
	
	int block_pos = 0; //Initialize the block position to 0.
	
	for (int pad_pos = 0; pad_pos < original_length; pad_pos++) //For every character in the padded block.
	{	
		if (padded_block[pad_pos] != 0x80) //If the character is NOT a padding character.
		{			
			block[block_pos] = padded_block[pad_pos]; //Set the character to the current position within the unpadded block.
			block_pos++; //Increment the position within the block.
		}
	}
	
	block[block_pos] = '\0'; //Set the last character in the unpadded block to a null character.
	*new_length = block_pos; //Set the new length as the final position within the block.
		
	return block; //Return the unpadded block.
}

//Method Summary: Swap the current character with another depending on the key character.
int swap(unsigned char *block, const unsigned char *key, const int original_length, const int key_length)
{
	if (block == NULL) //If the block is invalid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (key == NULL) //If the key is invaid, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (original_length <= 0) //If the original length is invalid, then...
	{
		perror("size is less than or equal to zero!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	int mod_value = 0; //Tells if the character's ascii value is even or odd.
	char temp = '\0'; //Temporarily holds a block character for evaluation.
	int key_pos = 0; //The current position within the key.
	int srt = 0; //The start position of a section within the text block.
	int fin = 0; //The end position of a section within the text block.
	
	if (original_length <= 7) //If the original length is less than or equal to the upper bound, then...
	{
		fin = original_length - 1; //Set the end position to the original length - 1.
	}
	else //The original length is greater than the upper bounds.
	{
		fin = 7; //Set the end position to the upper bounds.
	}
	
	for (int block_pos = 0; block_pos < original_length; block_pos++) //For every character in the text block...
	{	
		if (key_pos >= key_length) //If the current position within the key is out of bounds, then...
		{	
			key_pos = 0; //Reset the current position within the key to 0.
		}
		
		if (srt < fin) //If the start position is less than the end position, then...
		{	
			mod_value = key[key_pos] % 2; //See if the current position within the key is even or odd.
			key_pos++; //Increment the current position within the key.
		
			if (mod_value == 1) //If the key character's ascii value is odd, then...
			{	
				//Swap the character at the start position with the character at the end position.
				temp = block[srt]; 
				block[srt] = block[fin];
				block[fin] = temp;	
				srt++; //Increment the start position.
				fin--; //Increment the end position.
			}
			else //The key character's ascii value is even.
			{
				srt++; //Increment the start position.
			}
		}
		else //The start position has exceeded its bounds.
		{
			if (block_pos % 8 != 0) //If the current position within the text block is divisible by 8, then...
			{
				block_pos += (8 - (block_pos % 8)); //Increment the current position within the block by the maximum section size minus the remainder of the current position divided by the maximum section size.
			}
			
			srt = block_pos; //Revert the start position to the current position within the block.
				
			if (block_pos >= original_length) //If the current position within the block is greater than or equal to the original length, then...
			{
				break; //Break out of the loop.
			}
			else if ((block_pos + 7) >= original_length) //If the current position within the block, advanced by the maximum section minus 1, is greater than or equal to the original length, then...
			{
				fin = (original_length - 1); //Set the end position to the original length minus 1.
			}
			else //The current position within the block, advanced by the maximum section size minus 1, is less than the original length.
			{
				fin = (srt + 7); //Set the end position to the start position advanced by the maximum section size minus 1.
			}
				
			key_pos = 0; //Reset the current position within the key.
		}	
	}
	
	return 1; //Return 1, indicating success.
}

//Method Summary: Encrypts or decrypts a stream of characters from a file.
int streamEncryptAndDecrypt(const char *infile_filename, const char *key_filename, const char *out_filename)
{
	unsigned char in_c = '\0'; //The current character being read.
	unsigned char key_c = '\0'; //The current key character.
	unsigned char xor_c = '\0'; //The result of the bitwise XOR operation.
	
	FILE *in_file = fopen(infile_filename, "rb"); //Open the input file with the given filename.
	
	if (in_file == NULL) //If the file failed to open, then...
	{
		perror("Failed to open input file!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	FILE *key_file = fopen(key_filename, "rb"); //Open the key file with the given key filename.
	
	if (key_file == NULL) //If the key file failed to open, then...
	{
		perror("Failed to open key file!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	FILE *out_file = fopen(out_filename, "wb"); //Open the output file with the given output filename.
	
	if (out_file == NULL) //If the output file failed to open, then...
	{
		perror("Failed to open output file!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	while (!feof(in_file)) //While the file has not reached the end...
	{
		if (!fread(&in_c, 1, 1, in_file)) //If the read of the input file failed, then...
		{
			if (feof(in_file)) //If the input file has reached the end, then...
			{
				break; //Break out of the loop.
			}
			else //The input file has NOT reached the end.
			{
				perror("Failed to read from input file!\n"); //Print an error message, specifying the reason.
				return 0; //Return 0, indicating failure.
			}
		}
		
		if (!fread(&key_c, 1, 1, key_file)) //If the read of the key file failed, then...
		{
			if (feof(key_file)) //If the key file has reached the end, then...
			{
				rewind(key_file); //Return to the beginnning of the key file.
			}
			else //The key file has NOT reached the end.
			{
				perror("Failed to read from key file!\n"); //Print an error message, specifying the reason.
				return 0; //Return 0, indicating failure.
			}
		}
		
		xor_c = byteXOR(in_c, key_c); //XOR the input and key characters, then store the result.
			
		if (!fwrite(&xor_c, 1, 1, out_file)) //If the write to the output file failed, then...
		{
			perror("Failed to write to output file!\n"); //Print an error message, specifying the reason.
			return 0; //Return 0, indicating failure.
		}
	}
	
	fclose(in_file); //Close the input file.
	fclose(out_file); //Close the output file.
	fclose(key_file); //Close the key file.
	
	return 1; //Return 1, indicating success.
}

//Method Summary: Encrypts a block of text extracted from a file, then writes the encryption back to an output file.
int blockEncrypt(const char *block_filename, const char *key_filename, const char *out_filename)
{
	int old_length = 0; //Length of the text block before padding.
	int key_length = 0; //Length of the key.
	int new_length = 0; //Length of the text block after padding.
	unsigned char *text = readFile(block_filename, &old_length); //Read the text file contents into the block.
	
	if (text == NULL) //If the file read failed, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}

	unsigned char *key = readFile(key_filename, &key_length); //Read the contents of the key file into the key.
	
	if (key == NULL) //If the read of the key file failed, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	unsigned char *padded_text = padText(text, old_length, &new_length); //Pad the text block for symmetrical block encryption.
	
	if (padded_text == NULL) //If the padding of the text block failed, then...
	{
		perror("Unsigned char pointer is NULL!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure. 
	}
	
	if (!XOR(padded_text, key, new_length, key_length)) //If the XORing of the padded text failed, then...
	{
		perror("XOR failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (!swap(padded_text, key, new_length, key_length)) //If the swapping of characters failed, then...
	{
		perror("Swap failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (!writeFile(out_filename, padded_text, new_length)) //If the write to the output file failed, then...
	{
		perror("Failed to write to encryption file!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	free(text); //Free the memory of the text block.
	text = NULL; //Set to null to prevent a stale pointer.
	free(key); //Free the memory of the key.
	key = NULL; //Set to null to prevent a stale pointer.
	free(padded_text); //Free the memory of the padded text block.
	padded_text = NULL; //Set to null to prevent a stale pointer.
	
	return 1; //Return 1, indicating success.
}

//Method Summary: Decrypts a block of encrypted text, then writes the results to an output file.
int blockDecrypt(const char *decrypt_filename, const char *key_filename, const char *out_filename)
{	
	int key_length = 0; //The length of the key.
	int old_length = 0; //The length of the padded block.
	int new_length = 0; //The length of the block after de-padding.
	
	unsigned char *key = readFile(key_filename, &key_length); //Read the contents of the key file.
	
	if (key == NULL) //If the read of the key file failed, then...
	{
		perror("Key read failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
			
	unsigned char *encrypted_text = readFile(decrypt_filename, &old_length); //Read the contents of the encrypted file.
	
	if (encrypted_text == NULL) //If the read of the encrypted file failed, then...
	{
		perror("File read failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
		
	if (!swap(encrypted_text, key, old_length, key_length)) //If the swapping of characters in the encrypted text block failed, then...
	{
		perror("Swap failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
		
	if (!XOR(encrypted_text, key, old_length, key_length)) //If the XORing of the encrypted text block failed, then...
	{
		perror("XOR failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
		
	unsigned char *depadded_text = depadText(encrypted_text, old_length, &new_length); //Depad the encrypted text block.
		
	if (depadded_text == NULL) //If the depadding of the encrypted text block failed, then...
	{
		perror("Depadding failed!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	if (!writeFile(out_filename, depadded_text, new_length)) //If the write of the decrypted text block to an output failed, then...
	{
		perror("Failed to write to decryption file!\n"); //Print an error message, specifying the reason.
		return 0; //Return 0, indicating failure.
	}
	
	free(encrypted_text); //Free the memory of the encrypted text block.
	encrypted_text = NULL; //Set to null to avoid a stale pointer.
	free(key); //Free the memory of the key.
	key = NULL; //Set to null to avoid a stale pointer.
	free(depadded_text); //Free the memory of the depadded text block.
	depadded_text = NULL; //Set to null to avoid a stale pointer.
		
	return 1; //Return 1, indicating success.
}
