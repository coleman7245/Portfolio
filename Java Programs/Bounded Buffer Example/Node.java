/*
 * Author: coleman7245
 * Project: Bound Buffer Example
 * Last Update: 3/4/19
 */
 
public class Node<T>
{
	/*Variables*/
	Node<T> next; //The next node after this one.
	T data; //The data contained within the node.
	int location; //The location of the Node.
	
	/*Constructors*/
	//Method Summary: Sets data with the parameters and leaves the next and previous nodes as null.
	public Node(T d)
	{
		data = d; //Sets the data with the firstg parameter.
		next = null; //Sets the next node to null.
	}
	
	//Method Summary: Sets the data, next node and previous node with the parameters.
	public Node(T d, Node<T> n)
	{
		data = d; //Sets the data with the first parameter.
		next = n; //Sets the next node with the second parameter.
	}
	
	/*Mutators*/
	//Method Summary: Sets the data to the parameter.
	public void setData(T d)
	{
		data = d; //Set data with the first and only parameter.
	}
	
	//Method Summary: Sets the location of the Node.
	public void setLocation(int l)
	{
		location = l; //Sets the location with the given parameter.
	}
	
	//Method Summary: Sets the next node to the parameter.
	public void setNext(Node<T> n)
	{
		next = n; //Sets the next node to the first and only parameter.
	}
	/*End of Mutators*/
	
	/*Accessors*/
	//Method Summary: Returns the data within the node.
	public T getData()
	{
		return data; //Returns the data.
	}
	
	//Method Summary: Gets the location of this Node.
	public int getLocation()
	{
		return location; //Returns the location of this Node.
	}
	
	//Method Summary: Returns the next node after this one.
	public Node<T> getNext()
	{
		return next; //Returns the next node.
	}
	/*End of Accessors*/
}
