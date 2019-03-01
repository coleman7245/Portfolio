/*
 * Author: coleman7245
 * Project: Animal Guessing Game with a Binary Tree
 * Last Update: 3/1/19
 */

//Import the Scanner class for input reading.
import java.util.Scanner;
 
public class Node
{
	private Node yesNode;
	private Node noNode;
	private String question;
	 
	public Node()
	{
		yesNode = null;
		noNode = null;
		question = "";
	}
	 
	public Node(Node _yesNode, Node _noNode, String _question)
	{
		yesNode = _yesNode;
		noNode = _noNode;
		question = _question;
	}
	 
	public Node getNoNode()
	{
		return noNode;
	}
	 
	public String getQuestion()
	{
		return question;
	}
	 
	public Node getYesNode()
	{
		return yesNode;
	}
	 
	public void setNoNode(Node _noNode)
	{
		noNode = _noNode;
	}
	 
	public void setQuestion(String _question)
	{
		question = _question;
	}
	 
	public void setYesNode(Node _yesNode)
	{
		yesNode = _yesNode;
	}
	 
	public static Node insertNode(Node parent, String question, String guess, String response)
	{
		Node questionNode = new Node(null, null, question);
		Node guessNode = new Node(null, null, guess);
		 
		if (response.equalsIgnoreCase("Y"))
		{
			questionNode.setYesNode(guessNode);
			questionNode.setNoNode(parent);
		}
		else
		{
			questionNode.setYesNode(parent);
			questionNode.setNoNode(guessNode);
		}
		 
		return questionNode;
	}
	 
	public static Node traverse(Node root, Scanner reader)
	{
		String response = "";
		String question = "";
		String animal = "";
		 
		if (root.getYesNode() == null && root.getNoNode() == null)
		{
			System.out.println("Are you thinking of " + root.getQuestion() + "?");
			response = reader.nextLine();
			
			if (response.equalsIgnoreCase("Y"))
			{
				System.out.println("I win!");
				return null;
			}
			else if (response.equalsIgnoreCase("N"))
			{
				System.out.println("Name the animal you were thinking of.");
				animal = reader.nextLine();
				
				System.out.println("Ask a question that differentiates between a " + animal + " and a " + root.getQuestion() + ".");
				question = reader.nextLine();
				
				System.out.println("Is it a yes or no for " + animal + "?");
				response = reader.nextLine();
				
				return insertNode(root, question, animal, response);
			}
			else
			{
				System.out.println("Error in input!");
				return null;
			}
		}
		else
		{
			System.out.println(root.getQuestion());
			response = reader.nextLine();
			
			if (response.equalsIgnoreCase("Y"))
			{
				Node yesN = traverse(root.getYesNode(), reader);
				
				if (yesN != null)
				{
					root.setYesNode(yesN);
					return null;
				}
				
				return null;
			}
			else if (response.equalsIgnoreCase("N"))
			{
				Node noN = traverse(root.getNoNode(), reader);
				
				if (noN != null)
				{
					root.setNoNode(noN);
					return null;
				}
				
				return null;
			}
			else
			{
				return null;
			}
		}
	}
	 
	public static void playAnimalGuessingGame()
	{
		Scanner reader = new Scanner(System.in);
		String animal = "";
		String response = "Y";
		 
		System.out.println("Name an animal: ");
		animal = reader.nextLine();
		
		Node root = new Node(null, null, animal);
		Node node;
		
		while (response.equalsIgnoreCase("Y"))
		{
			node = traverse(root, reader);
			
			if (node != null)
			{
				root = node;
			}
			
			System.out.println("Try again?");
			response = reader.nextLine();
		}
	}
	 
	public static void main(String[] args)
	{
		playAnimalGuessingGame();
	}
}
