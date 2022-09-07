import java.util.Scanner;

public class AnimalGuessingGame
{
	public static void playAnimalGuessingGame()
	{
		Scanner scanner = new Scanner(System.in);
		BinaryTree<String> answerTree = null;
		boolean quit = false;
		String answer = "";
		
		do
		{
			if (answerTree == null)
			{
				System.out.println("Give me the name of the animal.");
				//scanner.nextLine();
				answer = scanner.nextLine();
				System.out.println("Debug: answer = " + answer);
				BinaryTree<String> leftSubtree = new BinaryTree<String>("Is it a(n) " + 
					answer + "?");
				System.out.println("Give me a clue to that animal.");
				//scanner.nextLine();
				answer = scanner.nextLine();
				System.out.println("Debug: answer = " + answer);
				answerTree = new BinaryTree<String>(answer, leftSubtree, null);
			}
			
			answerTree = traverseTree(answerTree, answerTree.root, scanner);
			System.out.println("Play again?");
			//scanner.nextLine();
			answer = scanner.nextLine();
			System.out.println("Debug: answer = " + answer);
			
			if (answer.charAt(0) != 'Y' && answer.charAt(0) != 'y')
			{
				quit = true;
			}
			
		} while (!quit);
	}
	
	public static BinaryTree<String> traverseTree(BinaryTree<String> _answerTree, 
		TreeNode<String> _node, Scanner _input)
	{
		String answer = "";
		
		System.out.println(_node.getData());
		//_input.nextLine();
		answer = _input.nextLine();
		System.out.println("Debug: answer = " + answer);
		
		if (answer.charAt(0) == 'Y' || answer.charAt(0) == 'y')
		{
			if (_node.getLeftChild() != null)
			{
				return traverseTree(_answerTree, _node.getLeftChild(), _input);
			}
			else
			{
				System.out.println("I win!");
				return _answerTree;
			}
		}
		else
		{
			if (_node.getRightChild() != null)
			{
				return traverseTree(_answerTree, _node.getRightChild(), _input);
			}
			else
			{
				String temp = _node.getData();
				System.out.println("Give me the name of the animal.");
				//_input.nextLine();
				String animalName = _input.nextLine();
				System.out.println("Debug: animalName = " + animalName);
				System.out.println("Give me a clue that distingues a(n) " + animalName + 
				"from the other animal.");
				//_input.nextLine();
				answer = _input.nextLine();
				System.out.println("Debug: answer = " + answer);
				_node.setData(answer);
				_answerTree.attachRightAt(_node, temp);
				_answerTree.attachLeftAt(_node, "Is it a(n) " + 
					animalName + "?");
				return _answerTree;
			}
		}
	}
	
	public static void main(String[] args)
	{
		playAnimalGuessingGame();
	}
}
