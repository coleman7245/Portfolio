/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 2/26/19
 */
 
public class Node<T>
{
	/*Variables*/
	Node<T> next; //The next node after this one.
	T data; //The data contained within the node.
	int location;
	
	/*Constructors*/
	//Sets data with the parameters and leaves the next and previous nodes as null.
	public Node(T d)
	{
		setData(d); //Sets the data with the firstg parameter.
		setNext(null); //Sets the next node to null.
	}
	
	//Sets the data, next node and previous node with the parameters.
	public Node(T d, Node<T> n)
	{
		setData(d); //Sets the data with the first parameter.
		setNext(n); //Sets the next node with the second parameter.
	}
	
	/*Mutators*/
	//Sets the data to the parameter.
	public void setData(T d)
	{
		data = d; //Set data with the first and only parameter.
	}
	
	public void setLocation(int l)
	{
		location = l;
	}
	
	//Sets the next node to the parameter.
	public void setNext(Node<T> n)
	{
		next = n; //Sets the next node to the first and only parameter.
	}
	/*End of Mutators*/
	
	/*Accessors*/
	//Returns the data within the node.
	public T getData()
	{
		return data; //Returns the data.
	}
	
	public int getLocation()
	{
		return location;
	}
	
	//Returns the next node after this one.
	public Node<T> getNext()
	{
		return next; //Returns the next node.
	}
	/*End of Accessors*/
}
