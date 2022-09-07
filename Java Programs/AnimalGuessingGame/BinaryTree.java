public class BinaryTree<T> extends BinaryTreeBasis<T>
{
	public BinaryTree()
	{
		root = null;
	}
	
	public BinaryTree(T _data)
	{
		super(_data);
	}
	
	public BinaryTree(T _data, BinaryTree<T> _leftSubtree, BinaryTree<T> _rightSubtree)
	{
		root = new TreeNode(_data, null, null);
		attachLeftSubtree(_leftSubtree);
		attachRightSubtree(_rightSubtree);
	}
	
	public void preOrder(TreeNode _next)
	{
		System.out.println(root.getData());
		preOrder(_next.getLeftChild());
		preOrder(_next.getRightChild());
	}
	
	public void inOrder(TreeNode _next)
	{
		inOrder(_next.getLeftChild());
		System.out.println(root.getData());
		inOrder(_next.getRightChild());
	}
	
	public void postOrder(TreeNode _next)
	{
		postOrder(_next.getLeftChild());
		postOrder(_next.getRightChild());
		System.out.println(root.getData());
	}
	
	public void attachLeft(T _data)
	{
		if (!isEmpty() && root.getLeftChild() == null)
		{
			root.setLeftChild(new TreeNode<T>(_data, null, null));
		}
	}
	
	public void attachRight(T _data)
	{
		if (!isEmpty() && root.getRightChild() == null)
		{
			root.setRightChild(new TreeNode<T>(_data, null, null));
		}
	}
	
	public void  attachLeftAt(TreeNode<T> _node, T _data)
	{
		if (!isEmpty() && _node.getLeftChild() == null)
		{
			_node.setLeftChild(new TreeNode<T>(_data, null, null));
		}
	}
	
	public void attachRightAt(TreeNode<T> _node, T _data)
	{
		if (!isEmpty() && _node.getRightChild() == null)
		{
			_node.setRightChild(new TreeNode<T>(_data, null, null));
		}
	}
	
	public void attachLeftSubtree(BinaryTree<T> _leftSubtree)
	{
		if (root == null)
		{
			throw new TreeException("Error: Empty Tree");
		}
		else if (root.getLeftChild() != null)
		{
			throw new TreeException("Error: Cannot override left subtree");
		}
		else if (_leftSubtree == null)
		{
			root.setLeftChild(null);
		}
		else
		{
			root.setLeftChild(_leftSubtree.root);
			_leftSubtree.makeEmpty();
		}
	}
	
	public void attachRightSubtree(BinaryTree<T> _rightSubtree)
	{
		if (root == null)
		{
			throw new TreeException("Error: Empty Tree");
		}
		else if (root.getRightChild() != null)
		{
			throw new TreeException("Error: Cannot override right subtree");
		}
		else if (_rightSubtree == null)
		{
			root.setRightChild(null);
		}
		else
		{
			root.setRightChild(_rightSubtree.root);
			_rightSubtree.makeEmpty();
		}
	}
	
	public void setRootItem(T _data)
	{
		if (root == null)
		{
			throw new TreeException("Error: Empty Tree");
		}
		else
		{
			root.setData(_data);
		}
	}
}
