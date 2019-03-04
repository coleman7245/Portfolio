/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 3/4/19
 */

import java.lang.Thread; //Import the Thread class for synchronization.
import java.util.Random; //Import the Random class for random item generation.
import java.lang.Integer; //Import the Integer class for producing integers.

public class Producer extends Thread
{
	/*Member Variable(s)*/
	private BoundedBuffer buffer; //A shared bounded buffer for production.
	private Random rand; //The random number generator that creates new items of the type 'double.'
	private int productionSize; //The amount of items to produce.
	private int numProduced; //The number of items produced at the given moment.
	private int maxWaitTime; //The maximum wait time a Producer endures before making a new item.
	private int idNum; //Instance ID to identify this particular instance of the Producer class.
	/*End of Member Variable(s)*/
	
	/*Constructor(s)*/
	//Method Summary: Default constructor
	public Producer()
	{
		buffer = null; //The shared bounded buffer starts at null.
		rand = null; //The random number generator starts at null.
		productionSize = 0; //The production size starts at 0.
		numProduced = 0; //The number of items produced starts at 0.
		maxWaitTime = 0; //Maximum wait time starts out at 0.
		idNum = 0; //Producer ID starts at 0.
	}
	
	//Method Summary: Constructor that requires a bounded buffer.
	public Producer(BoundedBuffer b, int n, int mwt, int id)
	{
		buffer = b; //The bounded buffer now references the given bounded buffer.
		rand = new Random(); //Create a new random number generator.
		productionSize = n; //The production size is the given number.
		numProduced = 0; //Number of produced items starts out at 0.
		maxWaitTime = mwt; //Set the maximum wait time to the given wait time.
		idNum = id; //Set the ID number to the given ID number.
	}
	/*End of Constructor(s)*/
	
	/*Member Method(s)*/
	//Method Summary: Checks if the production limit has been reached.
	public boolean hasProduced()
	{
		return (numProduced > productionSize); //Return true if the production limit has been reached, false otherwise.
	}
	
	//Method Summary: Runs an instance of the Producer as a thread.
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
