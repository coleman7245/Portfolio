public abstract class BinaryTreeBasis<T>
{
	protected TreeNode<T> root;
	
	public BinaryTreeBasis()
	{
		root = null;
	}
	
	public BinaryTreeBasis(T _data)
	{
		root = new TreeNode<T>(_data, null, null);
	}
	
	public boolean isEmpty()
	{
		return root == null;
	}
	
	public void makeEmpty()
	{
		root = null;
	}
	
	public T getRootItem()
	{
		if (root == null)
		{
			throw new TreeException("Error: Empty Tree");
		}
		else
		{
			return root.getData();
		}
	}
	
	public abstract void setRootItem(T _data);
}
