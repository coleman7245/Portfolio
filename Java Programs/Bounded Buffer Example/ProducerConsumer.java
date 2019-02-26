/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 2/26/19
 */

import java.lang.Integer;
import java.util.Random;

public class ProducerConsumer
{
	public static final int producerNum = 50;
	public static final int consumerNum = 50;
	
	//Run the main components of the Producer-Consumer scenario.
	public static void main(String[] args)
	{	
		if (args.length == 3)
		{
			/*Variable(s)*/
			int n = new Integer(args[0]).intValue(); //The capacity of the bounded buffer.
			int productionSize = new Integer(args[1]).intValue();
			BoundedBuffer buffer = new BoundedBuffer(n); //The shared bounded buffer for both production and consumption.
			int randomNum = 0, amountLeft = productionSize;
			Producer producers[] = new Producer[producerNum];
			Consumer consumers[] = new Consumer[consumerNum];
			
			for (int i = 0; i < producerNum; i++)
			{
				randomNum = new Random().nextInt(amountLeft);
				amountLeft -= randomNum;
				
				if (i == (producerNum - 1))
				{
					producers[i] = new Producer(buffer, amountLeft, new Integer(args[2]).intValue(), i);
					producers[i].start();
				}
				else
				{
					producers[i] = new Producer(buffer, randomNum, new Integer(args[2]).intValue(), i);
					producers[i].start();
				}
			}
			
			for (int i = 0; i < consumerNum; i++)
			{
				consumers[i] = new Consumer(buffer, new Integer(args[2]).intValue(), i);
				consumers[i].start();
			}
		}
		else
		{
			System.out.println("Insufficient arguments.");
			System.out.println("Proper argument format: <program name> <int> <int> <int>");
		}
	}
}
