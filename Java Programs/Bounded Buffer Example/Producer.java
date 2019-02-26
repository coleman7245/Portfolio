/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 2/26/19
 */

import java.lang.Thread;
import java.util.Random;
import java.lang.Integer;

public class Producer extends Thread
{
	/*Member Variable(s)*/
	private BoundedBuffer buffer; //A shared bounded buffer for production.
	private Random rand; //The random number generator that creates new items of the type 'double.'
	private int productionSize; //The amount of items to produce.
	private int numProduced; //The number of items produced at the given moment.
	private int maxWaitTime;
	private int idNum;
	/*End of Member Variable(s)*/
	
	/*Constructor(s)*/
	//Default constructor
	public Producer()
	{
		buffer = null; //The shared bounded buffer starts at null.
		rand = null; //The random number generator starts at null.
		productionSize = 0; //The production size starts at 0.
		numProduced = 0;
		maxWaitTime = 0;
		idNum = 0;
	}
	
	//Constructor that requires a bounded buffer.
	public Producer(BoundedBuffer b, int n, int mwt, int id)
	{
		buffer = b; //The bounded buffer now references the given bounded buffer.
		rand = new Random(); 
		productionSize = n; //The production size is the given number.
		numProduced = 0; 
		maxWaitTime = mwt;
		idNum = id;
	}
	/*End of Constructor(s)*/
	
	/*Member Method(s)*/
	public boolean hasProduced()
	{
		return (numProduced > productionSize);
	}
	
	//Runs an instance of the Producer as a thread.
	public void run()
	{	
		/*Variables*/
		Integer item; //The Double item that will be produced.
		/*End of Variables*/
		
		while (!hasProduced()) //While the amount of items produced is less than the maximum production size...
		{
			item = new Integer(rand.nextInt(100)); //The item is a new Integer value using a random int number as its base. 
			numProduced += buffer.produce(item, idNum, maxWaitTime, productionSize); //The producer produces an item.
		}
	}
	/*End of Member Method(s)*/
}
