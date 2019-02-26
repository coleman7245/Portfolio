/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 2/26/19
 */

import java.lang.Thread;
import java.lang.Integer;

public class Consumer extends Thread
{
	/*Member Variable(s)*/
	private BoundedBuffer buffer; //A shared bounded buffer for consumption.
	private int maxWaitTime;
	private int idNum;
	/*End of Member Variable(s)*/
	
	/*Constructor(s)*/
	//Default constructor
	public Consumer()
	{
		buffer = null; //The  shared bounded buffer starts at null.
		maxWaitTime = 0;
		idNum = 0;
	}
	
	//Constructor that requires a bounded buffer.
	public Consumer(BoundedBuffer b, int mwt, int id)
	{
		buffer = b; //The bounded buffer now references the given bounded buffer.
		maxWaitTime = mwt;
		idNum = id;
	}
	/*End of Constructor(s)*/
	
	/*Member Method(s)*/
	//Runs an instance of the Consumer as a thread.
	public void run()
	{	
		/*Variables*/
		Integer item; //The Double item that will be consumed.
		/*End of Variables*/
		
		while ((item = buffer.consume(idNum, maxWaitTime)) != null) //While the amount of items consumed is less than the maximum production size...
		{
			//System.out.println("numOfWaits: " + numOfWaits);
		    //The item is a new Double value using a consumed Double item as its base.
		}
	}
	/*End of Member Method(s)*/
}
