//Author: coleman7245
//Project: Encryption Program
//Last Edit: Friday, February 14, 2019

#include "encryption.h"

int main(int argc, char**argv)
{
	//argv[1]: A single character representing block or stream style encryption. It must either be an upper case B or an upper case S.
	//argv[2]: The filename of the file to be encrypted.
	//argv[3]: The filename of the file that the encryption will be written to.
	//argv[4]: The filename of the key.
	//argv[5]: A single character representing encryption or decryption. It must either be an upper case E or an upper case D.
	
	if (argc != 6)
	{
		printf("Insufficient number of arguments.\n");
		return -1;
	}
	
	char block_or_stream = argv[1][0];
	char encrypt_or_decrypt = argv[5][0];
	
	if (block_or_stream == 'B')
	{
		if (encrypt_or_decrypt == 'E')
		{
			if (!blockEncrypt(argv[2], argv[4], argv[3]))
			{
				printf("Block encryption failed.\n");
				return -1;
			}
		} 
		else if (encrypt_or_decrypt == 'D')
		{
				if (!blockDecrypt(argv[2], argv[4], argv[3]))
				{
					printf("Block decryption failed.\n");
					return -1;
				}
		}
		else
		{
			printf("Fifth argument is not a valid character.\n");
		}
	}
	else if (block_or_stream == 'S')
	{
		if (!streamEncryptAndDecrypt(argv[2], argv[4], argv[3]))
		{
			perror("Stream failed.\n");
			return -1;
		}
	}
	
	return 1;
}
