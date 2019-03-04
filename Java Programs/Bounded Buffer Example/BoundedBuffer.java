/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 3/4/19
 */

import java.lang.Integer; //Import the Integer class to generate integers.
import java.lang.Object; //Import the Object class for the notify methods.
import java.util.GregorianCalendar; //Import the Gregorian Calendar class for calculating the time delta.
import java.util.Random; //Import the Random class to generate random numbers.
import java.lang.String; //Import the String class to create character strings.

public class BoundedBuffer
{
	/*Member Variable(s)*/
	private int capacity; //Total amount of items for both production and consumption.
	private int size; //Total count of items in the bound buffer at the given moment.
	private Node<Integer> tail; //End node of the queue.
	/*End of Member Variable(s)*/
	
	/*Constructor(s)*/
	//Method Summary: Default constructor
	public BoundedBuffer()
	{
		tail = null; //Set the entire queue to null.
		capacity = 0; //The capacity starts as 0.
		size = 0; //Size starts at zero.
	}
	
	//Method Summary: Constructor that creates n number of node with no data.
	public BoundedBuffer(int c)
	{
		tail = null; //The tail starts as null
		capacity = c; //The capacity strarts as the given integer.
		size = 0; //Size starts at 0.
	}
	/*End of Constructor(s)*/
	
	/*Member Method(s)*/
	//Method Summary: Clears the queue of all nodes and the data contained therein.
	public void clear()
	{
		tail = null; //Set the entire queue to null.
	}
	
	//Method Summary: The synchronized method to consume an item from the shared bounded buffer.
	public synchronized Integer consume(int id, int maxWaitTime)
	{
		/* Variables */
		String message = ""; //Message for communicating the activity of the synchronized method.
		Random rand = new Random(); //Random number generator.
		GregorianCalendar gCalendar = new GregorianCalendar(); //Gregorian calendar for creating the time delta and displaying the date.
		int waitTime = rand.nextInt(maxWaitTime) / 1000000; //The wait time before the next consumption/production.
		Integer item = null; //The item to be consumed/produced.
		long waitTimeDifference = 0; //The time delta.
		int location = 0; //The location of the consumer/producer.
		
		while (isEmpty()) //While the shared bounded buffer is empty...
		{
			//Set a message, saying the consumer is unable to consume since the bounded buffer is empty at the appointed time.
			message = "Consumer " + id + ": Unable to consume, buffer empty, at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + 
				gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + gCalendar.get(GregorianCalendar.SECOND) + "." + 
				gCalendar.get(GregorianCalendar.MILLISECOND);
			System.out.println(message); //Display the message.
			
			
			try //Try to wait for the bounded buffer to refill.
			{
				waitTimeDifference = System.nanoTime(); //Set the wait time to the system's current nano time.
				wait((long)waitTime); //Try waiting for the producer to produce an item.
			}
			catch(InterruptedException e) //Catch the exception that occurs when an interruption causes an error.
			{
				Thread.currentThread().interrupt(); //Interrupt this thread.
				e.printStackTrace(); //Print the stack trace of this error.
			}
			
			waitTimeDifference = (System.nanoTime() - waitTimeDifference); //Calculate the time delta.
			
			
			if (waitTimeDifference >= (maxWaitTime * 10)) //If the wait time exceeds the maximum wait time scaled by 10:
			{
				return null; //Return a null value to break the loop.
			}
		}
		
		location = getHeadLocation(); //Set the location of the bounded buffer's location.
		item = dequeue(); //Grab an item from the bounded buffer.
		
		//Set a message that this consumer has removed an item from the bounded buffer at this location and date.
		message = "Consumer " + id + ": Removed " + item.intValue() + " at Location " + location + " at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + 
			gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + gCalendar.get(GregorianCalendar.SECOND) + "." + 
			gCalendar.get(GregorianCalendar.MILLISECOND);
		System.out.println(message); //Prints out the modified message to the command console.

		notifyAll(); //Notify the producer that the consumer is done with the bounded buffer.
		
		return item; //Return the generic item for consumption.
	}
	
	//Method Summary: Returns the first item from the first node in the queue, while permanantly removing it.
	public Integer dequeue()
	{
		/*Variable(s)*/
		Integer firstItem;
		/*End of Variable(s)*/
		
		if (isEmpty()) //If the bounded buffer is empty, then...
		{
			firstItem = null; //The first item is null.
		}
		else //The bounded buffer contains items.
		{
			firstItem = tail.getNext().getData(); //A temporary space for the leaving item.
			
			if (tail.getNext() == tail) //If the first item in the queue is equal to the last, then...
			{
				tail = null; //Set the entire queue to null.
			}
			else //The next Node of the tail is the head.
			{
				tail.setNext(tail.getNext().getNext()); //Set the tail to the node that follows the head node.
			}
			
			size--; //Decrement the size of the bound buffer.
		}
		
		return firstItem; //Return the first item in the queue.
	}
	
	//Method Summary: Adds an element to the end of the queue.
	public boolean enqueue(Integer e)
	{	
		/*Variable(s)*/
		Node<Integer> new_node = new Node<Integer>(e);
		/*End of Variable(s)*/
		
		if (isEmpty()) //If the queue is empty, then...
		{
			new_node.setNext(new_node); //Tie the back end of the tail node to itself.
			tail = new_node; //Set the tail node as the new node.
		}
		else //The queue contains items.
		{
			new_node.setNext(tail.getNext()); //Tie the back end of the new node to the back end of the tail node.
			tail.setNext(new_node); //Tie the back end of the tail node to the new node.
			tail = tail.getNext(); //Set the tail node to the new_node.
		}
		
		tail.setLocation(size); //Set the location of the tail to the current size.
		size++; //Increment the count of items.
		
		return true; //Return true to indicate success.
	}
	
	/*Accessor(s)*/
	//Method Summary: Get the capacity of the bounded buffer.
	public int capacity()
	{
		return capacity; //Return the capacity.
	}
	
	//Method Summary: Get the head location.
	public int getHeadLocation()
	{
		return tail.getNext().getLocation(); //Return the location of the head.
	}
	
	//Method Summary: Get the tail location.
	public int getTailLocation()
	{
		return tail.getLocation(); //Return the location of the tail.
	}
	
	//Method Summary: get the size of the bounded buffer.
	public int size()
	{
		return size; //Return the size of the bounded buffer.
	}
	/*End of Accessor(s)*/
	
	//Method Summary: Checks to see if the bounded buffer is empty or not.
	public boolean isEmpty()
	{
		return (size() == 0); //Return a boolean check if the tail node is null.
	}
	
	//Method Summary: Checks to see if the bounded buffer is full or not.
	public boolean isFull()
	{
		return (size() == capacity()); //Return a boolean check if the size is equal to the capacity.
	}
	
	//Produces a generic item to be stored in the bounded buffer.
	public synchronized int produce(Integer i, int id, int maxWaitTime, int productionSize)
	{
		String message = ""; //Message for communicating the activity of the synchronized method.
		Random rand = new Random(); //Random number generator.
		GregorianCalendar gCalendar = new GregorianCalendar(); //Gregorian calendar for creating the time delta and displaying the date.
		int waitTime = rand.nextInt(maxWaitTime) / 1000000; //The item to be consumed/produced.
		int numOfWaits = 0; //The number of waits before giving up.
		
		while (isFull()) //While the bounded buffer is full...
		{
			//Set a message that the producer is unable to produce anymore items since the bounded buffer is full at a location and date.
			message = "Producer " + id + ": Unable to insert, buffer full, at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + 
				gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + gCalendar.get(GregorianCalendar.SECOND) + "." + 
				gCalendar.get(GregorianCalendar.MILLISECOND);
			System.out.println(message); //Display the message.
			
			try
			{
				wait((long)waitTime); //Try waiting for the consumer to consume an item.
			}
			catch(InterruptedException e) //Catch the exception that occurs when an interruption causes an error.
			{
				Thread.currentThread().interrupt(); //Interrupt the thread.
			}
			
			numOfWaits++; //Increase the number of waits.
			
			if (numOfWaits > productionSize) //If the number of waits exceeds the production size, then...
			{
				return numOfWaits; //Return the number of waits.
			}
		}
		
		enqueue(i); //Place the produced item at the tail of the bounded buffer.
		//Set a message that the producer has produced the given value at a location and date.
		message = "Producer " + id + ": Placed " + i.intValue() + " at Location " + getTailLocation() + " at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + 
			gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + 
			gCalendar.get(GregorianCalendar.SECOND) + "." + gCalendar.get(GregorianCalendar.MILLISECOND);
		System.out.println(message); //Display the message.
		notifyAll(); //Notify the consumer that the producer is done with the bounded buffer.
		
		return 1; //Return 1 to indicate success.
	}
	/*End of Member Method(s)*/
}
