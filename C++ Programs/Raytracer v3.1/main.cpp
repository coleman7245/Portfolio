/* Author: coleman7245
 * File: C++ Main method for the Raytracer program.
 * Last Update: 2/25/2018
 * File Summary: The main thread of execution for the raytracer program. The method first checks to see if the number of arguments is 
 * sufficient. Then it reads the driver file and stores the information found within. If any models are found within the driver file, their 
 * coordinates are transformed according to the specifications. Finally, the recursive raytracer is called to render the objects, which are 
 * then written to a PPM file. 
 */

#include "scene.h"

//Method Summary: The main thread of execution for the Raytracer program.
//Precondtions: The number of arguments, which must be equal to 3. Aside from program name, the driver filename and the output PPM filename 
//must also be provided.
//Postconditions: An integer value is returned: 0 if the entire execution is successful, -1 otherwise. 
int main(int argc, char *argv[])
{
	//If the number of arguments does not equal 3, then...
	if (argc != 3)
	{
		//Display an error message.
		std::cerr << "Insufficient arguments. Operation aborted." << std::endl;
		//Return -1 for a failed execution.
		return -1;
	}
	
	//Create the Scene object with the driver filename.
	Scene scene = Scene(argv[1]);
	
	//If the read of the driver file is NOT successful, then...
	if (!scene.isInitialized())
	{
		//Display an error message.
		std::cerr << "Driver file read failed! Operation aborted." << std::endl;
		//Return -1 for a failed execution.
		return -1;
	}
	
	//If the write of the graphics data is NOT successful, then...
	if (!scene.writePPMFile(argv[2]))
	{
		//Display an error message.
		std::cerr << "Failed to write file! Operation aborted." << std::endl;
		//Return -1 for a failed operation.
		return -1;
	}
	
	//Return 0 for a successful execution.
	return 0;
}
