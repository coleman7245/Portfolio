/*
 * Author: coleman7245
 * Project: Animal Guessing Game with a Binary Tree
 * Last Update: 3/1/19
 */

//Import the Scanner class for input reading.
import java.util.Scanner;

//Node class for the Binary Tree
public class Node
{
	/* Class Attributes */
	//yesNode: Child node 1 of the root node.
	//noNode: Child node 2 of the root node.
	//question: Store both questions and answers of the user.
	private Node yesNode;
	private Node noNode;
	private String question;
	
	//Method Summary:
	public Node()
	{
		yesNode = null;
		noNode = null;
		question = "";
	}
	
	//Method Summary: 
	public Node(Node _yesNode, Node _noNode, String _question)
	{
		yesNode = _yesNode;
		noNode = _noNode;
		question = _question;
	}
	
	/*Get methods*/
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
	
	/*Set methods*/
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
	
	/*Other methods*/
	//Method Summary: Inserts a node in the binar tree. It's connection to the root node depends on the user response.
	public static Node insertNode(Node parent, String question, String guess, String response)
	{
		//questionNode: Node containing the question that differentiates one animal from another.
		//guessNode: Node containing the next animal.
		Node questionNode;
		Node guessNode = new Node(null, null, guess);
		
		//If the response is yes:
		if (response.equalsIgnoreCase("Y"))
		{
			//Set the question node with the yes node as the guess node and the no node as the parent node.
			questionNode = new Node(guessNode, parent, question);
		}
		else //if the response is no:
		{
			//Set the question node with the yes node as the parent node and the no node as the guess node.
			questionNode = new Node(parent, guessNode, question);
		}
		
		//Return the questionNode.
		return questionNode;
	}
	
	//Method Summary: Traverse the binary tree to guess the user's choice of animal.
	public static Node traverse(Node root, Scanner reader)
	{
		//response: The user's input to the node's question or request.
		//question: The question provided by the user.
		//animal: The animal name provided by the user.
		String response = "";
		String question = "";
		String animal = "";
		 
		//Base case: If the both child nodes of the root node are null:
		if (root.getYesNode() == null && root.getNoNode() == null)
		{
			//Try to guess the user's animal name.
			System.out.println("Are you thinking of " + root.getQuestion() + "?");
			//Read the user's response.
			response = reader.nextLine();
			
			//If the response is yes:
			if (response.equalsIgnoreCase("Y"))
			{
				//The game is over.
				//Print the "I win" message.
				System.out.println("I win!");
				//Return null;
				return null;
			}
			else if (response.equalsIgnoreCase("N")) //If the response is no:
			{
				//The user won.
				//Ask the user for their answer.
				System.out.println("Name the animal you were thinking of.");
				//Read and store the user's response.
				animal = reader.nextLine();
				
				//Request a question that differentiates the current animal and the previous animal.
				System.out.println("Ask a question that differentiates between a " + animal + " and a " + root.getQuestion() + ".");
				//Read and store the user's response.
				question = reader.nextLine();
				
				//Ask if the previously stored question is a yes or no question for the previously stored animal.
				System.out.println("Is it a yes or no for " + animal + "?");
				//Read and store the user's response.
				response = reader.nextLine();
				
				//Return an node inserted into the root.
				return insertNode(root, question, animal, response);
			}
			else //Acknowledge all other user input as failed input.
			{
				//Display an error message.
				System.out.println("Error in input!");
				//Return null.
				return null;
			}
		}
		else //Inductive Step: Both child nodes have valid node objects.
		{
			//A question, not an animal name, will be stored in this node. Ask the user this question.
			System.out.println(root.getQuestion());
			//Read and store the user's response.
			response = reader.nextLine();
			
			//If the response is a yes:
			if (response.equalsIgnoreCase("Y"))
			{
				//Recursively traverse the binary tree starting with the root's yes node.
				Node yesN = traverse(root.getYesNode(), reader);
				
				//If the yes node is NOT null:
				if (yesN != null)
				{
					//Set the root's yes node to the traversed yes node.
					root.setYesNode(yesN);
					//Return null.
					return null;
				}
				
				//Return null.
				return null;
			}
			else if (response.equalsIgnoreCase("N")) //If the response is no:
			{
				//Recursively traverse the binary tree starting with the root node's no node. 
				Node noN = traverse(root.getNoNode(), reader);
				
				//If the travered no node is NOT null:
				if (noN != null)
				{
					//Set the root's no node to the traversed node.
					root.setNoNode(noN);
					//Return null.
					return null;
				}
				
				//Return null.
				return null;
			}
			else //All other user input is considered failed input:
			{
				//Return null.
				return null;
			}
		}
	}
	
	//Method Summary: Initializes the animal guessing game.
	public static void playAnimalGuessingGame()
	{
		//Create a new Scanner object to read user input.
		Scanner reader = new Scanner(System.in);
		//animal: The user's choice of animal name.
		//response: The user's yes or no response, initialized to yes.
		String animal = "";
		String response = "Y";
		
		//Request an animal name from the user.
		System.out.println("Name an animal: ");
		//Read and store the user's response.
		animal = reader.nextLine();
		
		//Create the root node with the animal name as the question.
		Node root = new Node(null, null, animal);
		//Node for binary tree traversal.
		Node node;
		
		//Continue is the user's response is yes:
		while (response.equalsIgnoreCase("Y"))
		{
			//Traverse the binary tree.
			node = traverse(root, reader);
			
			//If the node is NOT null.
			if (node != null)
			{
				//Set the root to the node.
				root = node;
			}
			
			//Ask if the user wants to play again.
			System.out.println("Try again?");
			//Read and store the user's response.
			response = reader.nextLine();
		}
	}
	
	//Method Summary: Main method of execution.
	public static void main(String[] args)
	{
		//Play the animal guessing game.
		playAnimalGuessingGame();
	}
}
