/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 2/26/19
 */

import java.lang.Integer;
import java.lang.Object;
import java.util.GregorianCalendar;
import java.util.Random;
import java.lang.String;

public class BoundedBuffer
{
	/*Member Variable(s)*/
	private int capacity; //Total amount of items for both production and consumption.
	private int size; //Total count of items in the bound buffer at the given moment.
	private Node<Integer> tail; //End node of the queue.
	/*End of Member Variable(s)*/
	
	/*Constructor(s)*/
	//Default constructor
	public BoundedBuffer()
	{
		tail = null; //Set the entire queue to null.
		capacity = 0; //The capacity starts as 0.
		size = 0; //Size starts at zero.
	}
	
	//Constructor that creates n number of node with no data.
	public BoundedBuffer(int c)
	{
		tail = null; //The tail starts as null
		capacity = c; //The capacity strarts as the given integer.
		size = 0; //Size starts at 0.
	}
	/*End of Constructor(s)*/
	
	/*Member Method(s)*/
	//Clears the queue of all nodes and the data contained therein.
	public void clear()
	{
		tail = null; //Set the entire queue to null.
	}
	
	public synchronized Integer consume(int id, int maxWaitTime)
	{
		String message = "";
		Random rand = new Random();
		GregorianCalendar gCalendar = new GregorianCalendar();
		int waitTime = rand.nextInt(maxWaitTime) / 1000000;
		Integer item = null;
		long waitTimeDifference = 0;
		int location = 0;
		
		//While the shared bounded buffer is empty...
		while (isEmpty())
		{
			message = "Consumer " + id + ": Unable to consume, buffer empty, at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + 
				gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + gCalendar.get(GregorianCalendar.SECOND) + "." + 
				gCalendar.get(GregorianCalendar.MILLISECOND);
			System.out.println(message);
			
			try
			{
				waitTimeDifference = System.nanoTime();
				wait((long)waitTime); //Try waiting for the producer to produce an item.
			}
			catch(InterruptedException e) //Catch the exception that occurs when an interruption causes an error.
			{
				Thread.currentThread().interrupt();
				e.printStackTrace();
			}
			
			waitTimeDifference = (System.nanoTime() - waitTimeDifference);
			
			if (waitTimeDifference >= (maxWaitTime * 10))
			{
				return null;
			}
		}
		
		location = getHeadLocation();
		item = dequeue();
		
		message = "Consumer " + id + ": Removed " + item.intValue() + " at Location " + location + " at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + 
			gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + gCalendar.get(GregorianCalendar.SECOND) + "." + 
			gCalendar.get(GregorianCalendar.MILLISECOND);
		System.out.println(message); //Prints out the modified message to the command console.

		notifyAll(); //Notify the producer that the consumer is done with the bounded buffer.
		
		return item; //Return the generic item for consumption.
	}
	
	//Returns the first item from the first node in the queue, while permanantly removing it.
	public Integer dequeue()
	{
		/*Variable(s)*/
		Integer firstItem;
		/*End of Variable(s)*/
		
		if (isEmpty())
		{
			firstItem = null;
		}
		else
		{
			firstItem = tail.getNext().getData(); //A temporary space for the leaving item.
			
			if (tail.getNext() == tail) //Else, if the first item in the queue is equal to the last, then...
			{
				tail = null; //Set the entire queue to null.
			}
			else //Else...
			{
				tail.setNext(tail.getNext().getNext()); //Set the tail to the node that follows the head node.
			}
			
			size--; //Decrement the size of the bound buffer.
		}
		
		return firstItem; //Return the first item in the queue.
	}
	
	//Adds an element to the end of the queue.
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
		else
		{
			new_node.setNext(tail.getNext()); //Tie the back end of the new node to the back end of the tail node.
			tail.setNext(new_node); //Tie the back end of the tail node to the new node.
			tail = tail.getNext(); //Set the tail node to the new_node.
		}
		
		tail.setLocation(size);
		size++; //Increment the count of items.
		
		return true; //Return true to indicate success.
	}
	
	/*Accessor(s)*/
	public int capacity()
	{
		return capacity;
	}
	
	public int getHeadLocation()
	{
		return tail.getNext().getLocation();
	}
	
	public int getTailLocation()
	{
		return tail.getLocation();
	}
	
	public int size()
	{
		return size; 
	}
	/*End of Accessor(s)*/
	
	//Checks to see if the bounded buffer is empty or not.
	public boolean isEmpty()
	{
		return (size() == 0); //Return a boolean check if the tail node is null.
	}
	
	//Checks to see if the bounded buffer is full or not.
	public boolean isFull()
	{
		return (size() == capacity()); //Return a boolean check if the size is equal to the capacity.
	}
	
	//Produces a generic item to be stored in the bounded buffer.
	public synchronized int produce(Integer i, int id, int maxWaitTime, int productionSize)
	{
		String message = "";
		Random rand = new Random();
		GregorianCalendar gCalendar = new GregorianCalendar();
		int waitTime = rand.nextInt(maxWaitTime) / 1000000;
		int numOfWaits = 0;
		
		
		//While the bounded buffer is full...
		while (isFull())
		{
			message = "Producer " + id + ": Unable to insert, buffer full, at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + 
				gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + gCalendar.get(GregorianCalendar.SECOND) + "." + 
				gCalendar.get(GregorianCalendar.MILLISECOND);
			System.out.println(message);
			
			try
			{
				wait((long)waitTime); //Try waiting for the consumer to consume an item.
			}
			catch(InterruptedException e) //Catch the exception that occurs when an interruption causes an error.
			{
				Thread.currentThread().interrupt();
			}
			
			numOfWaits++;
			
			if (numOfWaits > productionSize)
			{
				return numOfWaits;
			}
		}
		
		enqueue(i); //Place the produced item at the tail of the bounded buffer.
		message = "Producer " + id + ": Placed " + i.intValue() + " at Location " + getTailLocation() + " at Time: " + gCalendar.get(GregorianCalendar.MONTH) + "/" + 
			gCalendar.get(GregorianCalendar.DAY_OF_MONTH) + "/" + gCalendar.get(GregorianCalendar.YEAR) + " " + gCalendar.get(GregorianCalendar.HOUR) + ":" + gCalendar.get(GregorianCalendar.MINUTE) + ":" + 
			gCalendar.get(GregorianCalendar.SECOND) + "." + gCalendar.get(GregorianCalendar.MILLISECOND);
		System.out.println(message);
		notifyAll(); //Notify the consumer that the producer is done with the bounded buffer.
		
		return 1;
	}
	/*End of Member Method(s)*/
}
