/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 3/4/19
 */

import java.lang.Thread; //Import the Thread class for synchronization.
import java.lang.Integer; //Import the Integer class for consuming integers.

public class Consumer extends Thread
{
	/*Member Variable(s)*/
	private BoundedBuffer buffer; //A shared bounded buffer for consumption.
	private int maxWaitTime; //The maximum wait time for a producer to 
	private int idNum; //The identity number for this consumer instance.
	/*End of Member Variable(s)*/
	
	/*Constructor(s)*/
	//Method Summary: Default constructor
	public Consumer()
	{
		buffer = null; //The shared bounded buffer starts at null.
		maxWaitTime = 0; //Set the maximum wait time to 0.
		idNum = 0; //Set the identity number to 0.
	}
	
	//Method Summary: Constructor that requires a bounded buffer.
	public Consumer(BoundedBuffer b, int mwt, int id)
	{
		buffer = b; //The bounded buffer now references the given bounded buffer.
		maxWaitTime = mwt; //Set the maximum wait time to the given parameter.
		idNum = id; //Set the identity number to the given parameter.
	}
	/*End of Constructor(s)*/
	
	/*Member Method(s)*/
	//Method Summary: Runs an instance of the Consumer as a thread.
	public void run()
	{	
		/*Variables*/
		Integer item; //The Double item that will be consumed.
		/*End of Variables*/
		
		while ((item = buffer.consume(idNum, maxWaitTime)) != null) //While the amount of items consumed is less than the maximum production size...
		{}
	}
	/*End of Member Method(s)*/
}
