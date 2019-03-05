//Author: Derek Coleman
//Project: Encryption Program
//Last Update: 3/5/19

#include "encryption.h" //Include the encryption header for encryption and decryption.

//Method Summary: The main thread of execution.
int main(int argc, char**argv)
{
	//argv[1]: A single character representing block or stream style encryption. It must either be an upper case B or an upper case S.
	//argv[2]: The filename of the file to be encrypted.
	//argv[3]: The filename of the file that the encryption will be written to.
	//argv[4]: The filename of the key.
	//argv[5]: A single character representing encryption or decryption. It must either be an upper case E or an upper case D.
	
	if (argc != 6) //If the argument list length is NOT 6, then...
	{
		printf("Insufficient number of arguments.\n"); //Print an error message, specifying the reason.
		return -1; //Return -1, indicating failure.
	}
	
	char block_or_stream = argv[1][0]; //Read the block or stream character.
	char encrypt_or_decrypt = argv[5][0]; //Read the encrypt or decrypt character.
	
	if (block_or_stream == 'B') //If block encryption is requested, then...
	{
		if (encrypt_or_decrypt == 'E') //If encryption is requested, then...
		{
			if (!blockEncrypt(argv[2], argv[4], argv[3])) //If the block encryption fails, then...
			{
				printf("Block encryption failed.\n"); //Print an error message, specifying the reason.
				return -1; //Return -1, indicating failure.
			}
		} 
		else if (encrypt_or_decrypt == 'D') //If decryption is requested, then...
		{
				if (!blockDecrypt(argv[2], argv[4], argv[3])) //If the block decryption failed, then...
				{
					printf("Block decryption failed.\n"); //Print an error message, specifying the reason.
					return -1; //Return -1, indicating failure.
				}
		}
		else //Neither option is requested, which is an error.
		{
			printf("Fifth argument is not a valid character.\n"); //Print an error message, specifying the reason.
		}
	}
	else if (block_or_stream == 'S') //If stream is requesed, then...
	{
		if (!streamEncryptAndDecrypt(argv[2], argv[4], argv[3])) //If the stream encryption or decryption is requested, then...
		{
			perror("Stream failed.\n"); //Print an error message, specifying the reason.
			return -1; //Return -1, indicating failure.
		}
	}
	
	return 1; //Return 1, indicating success.
}
