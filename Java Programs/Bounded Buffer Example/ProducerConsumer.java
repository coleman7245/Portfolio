/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 3/4/19
 */

import java.lang.Integer; //Import the Integer class for integer numbers.
import java.util.Random; //Import the Random class for generating random numbers.

public class ProducerConsumer
{
	public static final int producerNum = 50; //The number of producers to be created.
	public static final int consumerNum = 50; //The number of consumers to be created.
	
	//Method Summary: Run the main components of the Producer-Consumer scenario.
	public static void main(String[] args)
	{	
		if (args.length == 3) //If the argument list length is 3, then...
		{
			/*Variable(s)*/
			int n = new Integer(args[0]).intValue(); //Set the capacity of the bounded buffer with the first argument.
			int productionSize = new Integer(args[1]).intValue(); //Set the production size with the second argument.
			BoundedBuffer buffer = new BoundedBuffer(n); //The shared bounded buffer for both production and consumption.
			int randomNum = 0; //The random number of items to be produced.
			int amountLeft = productionSize; //The amount of items left to be produced.
			Producer producers[] = new Producer[producerNum]; //The list of producers.
			Consumer consumers[] = new Consumer[consumerNum]; //The list of consumers.
			
			for (int i = 0; i < producerNum; i++) //For every producer instance...
			{
				randomNum = new Random().nextInt(amountLeft); //Generate a random number.
				amountLeft -= randomNum; //Decrease the amount of items left to produce by the random number.
				
				if (i == (producerNum - 1)) //If this producer is the last one.
				{
					producers[i] = new Producer(buffer, amountLeft, new Integer(args[2]).intValue(), i); //Create a new producer a with the remaining items left to produce as the production capacity.
					producers[i].start(); //Start the producer's run method.
				}
				else //There are more than items to produce.
				{
					producers[i] = new Producer(buffer, randomNum, new Integer(args[2]).intValue(), i); //Create a new producer with the random number as the production capacity.
					producers[i].start(); //Start the producer's run method.
				}
			}
			
			for (int i = 0; i < consumerNum; i++) //For every consumer...
			{
				consumers[i] = new Consumer(buffer, new Integer(args[2]).intValue(), i); //Create a new consumer using the iteration number as the ID.
				consumers[i].start(); //Start the consumer's run method.
			}
		}
		else //The argument list is insufficient to execute the program.
		{
			System.out.println("Insufficient arguments."); //Print an error message.
			System.out.println("Proper argument format: <program name> <int> <int> <int>"); //Print the correct form of the argument list.
		}
	}
}
