//Author: Derek Coleman
//Project: Encryption Program
//Last Update: 3/5/19

This program contains three c files and two header files: 

fileio.h
fileio.c
encryption.h
encryption.c
main.c

fileio has helper functions to parse strings and files before the encryption fuctions do their work.

fileo contains the following fuctions:

readFile: This fuction takes in a filename c-string, reads data into from the 
		  opened input file, then returns a c-string of data. It begins by taking 
		  the filename c-string and opens an input filestream with it. It then 
		  loops until the EOF is reach, with each interation resulting in a 1-byte 
		  binary read into the input file. The data from the binary read is then 
		  placed in a c-string that had memory allocated to it at the beginning of 
		  the function. Once EOF is reached, the input file is closed and the 
		  c-string containing the data is returned. 

writeFile: This function takes a c-string of data and a filename c-string, writes 
		   data to an open output file, then an integer indicating a successful 
		   operation. It begins by taking the filename c-string and opens an output 
		   filestream with it. It then loops repeatedly, writing 1-byte data from 
		   the data c-string and to the output file with each iteration. When EOF 
		   is reached, the output file is closed and a positive integer is 
		   returned if successful. Otherwise, a negative integer is returned. 

findFileSize: Finds and returns the file size attached to the filename c-string 
			  argument. After the file is opened with the filename c-string, 
			  the input filestream pointer is placed at the end of the file, then 
			  its position is stored and, after closing the input file, returned 
			  as the size.  

findNumToPad: Finds and returns the total sum of bytes to fill that are not 
			  divisible by 8.  A for loop is established that runs through the 
			  entire c-string. With each iteration, an if-else statement checks the
			  character at the current position to see if it is white space or not. If it is 
			  If it is not, then the byte count increments.
			  
			  If it is white space, then an if-else statement checks to see if it 
			  is divisible by 8. If it isn't, then the function finds a multiple 
			  of eight that is greater than the byte count. The difference between 
			  that number and the byte count is number of spaces to pad, which is 
			  added to the total sum. After the for loop ends, the total sum of 
			  white spaces to pad is returned.

findNumOfPadding: Finds the total sum of padding in an already padded c-string. A for
				  loop is established to inspect every element in the c-string. If 
				  any padding is found, a count is incremented, and after the for 
				  loop ends, returned.

byteXOR: Takes two characters, XORs them, and then returns the result. The two 
		 characters and ANDed and bits of the result are flipped. That result is 
		 then ANDed with the results of an ORing between the initial two characters.

The encryption c-file contains functions for encrypting and decrypting blocks of data. 
The following functions are held within:

XOR: Takes a c-string of data and a c-string key, XORs every element in the data, 
	 then returns a c-string pointer to the results. A for loop is established to 
	 inspect every element in the c-string. A character in the current position 
	 in both the data and key c-strings and ANDed and bits of the result are 
	 flipped. That result is then ANDed with the results of an ORing between the 
	 data and key characters. After the for loop ends, a c-string pointer that 
	 points to the XOR results is returned.

padText: Pads a c-string with padding characters, removes the white space, then 
		 returns a pointer to the results. A for loop is established to cycle 
		 through every element in the c-string. An if-else statement check to see 
		 if the current character in the c-string is white space or not. If it is 
		 not, then the both the padding position and byte count are incremented, 
		 and the current character remains in its initial place. 
		 
		 If the current data character is white space, then an if-else statement 
		 checks to see if it is divisible by 8. If it is not, then the function 
		 finds a multiple of eight that is greater than the byte count. Another 
		 for loop is established within the current one that adds a padding 
		 number in the current position of the padded array. It stops when the 
		 difference between the byte count and the multiple of eight is reached.
		 
		 After the for loop ends, a pointer to a padded c-string is returned.
		 

depadText: Depads a c-string of padded data, then returns a pointer to a c-string 
		   of the results. A for loop is established to cycle through every 
		   element in the c-string. If the current character in the data c-string 
		   is not a padding number, then the aforementioned character is placed 
		   in the same position within the results c-string. 

		   After the for loop ends, a pointer to a padded c-string is returned.

swap: Swaps charcters in a c-string of data, depending on a calculated integer 
	  value from the adjacent key character. A pointer to c-string of the 
	  results is returned. 
	  
	  A for loop is established to inspect every element in the c-string. Start 
	  and finish positions are established to guide the swapping process. If the 
	  calculated integer value is 0, then no swap takes place and the next 
	  character is processed. The start position is then incremented.
	  
	  If the calculated integer value is 1, then a swap is performed. The start 
	  position is incremented, while the finish position is decremented. The next character is then processed.
	  
	  This method of swapping continues until the start and finish positions 
	  collide or crossover. Additionally, it will also end when the last 
	  character of the given eight is reached. 
	  
	  After the for loop ends, a pointer to a padded c-string is returned.

streamEncryptAndDecrypt: Encrypts and decrypts data through a continuous stream 
						 rather than a block. Both input and output filestreams 
						 are opended, and a while loop cycles through the file's 
						 characters. 
						 
						 One character is read one at a time throughout the loop. 
						 Each character is paired with its parallel key character
						 to be XORed--the results of which are written to the 
						 output file. This process ends when the end of the 
						 input file is reached.
						 
						 This fuction works for both encryption and decryption. 
						 The same process decrypts the file to its original state.
						 An integer value is then returned to indicate a 
						 successful operation.

blockEncrypt: Combines all the fuctions of the encryption and fileio c-files to 
			  encrypt a file with an adjacent key. Also, performs memory
			  management at the end of the function.
			  
			  The function deplays a number of c-string pointers to carry the 
			  data from function to function. The order of the functions is as 
			  follows: readFile, padText, XOR, swap, and writeFile.

blockDecrypt: Combines all the fuctions of the encryption and fileio c-files to 
			  decrypt a file with an adjacent key. Also, performs memory 
			  management at the end of the function.
			  
			  The function deplays a number of c-string pointers to carry the 
			  data from function to function. The order of the functions is as 
			  follows: readFile, swap, XOR, depadText, and writeFile.
