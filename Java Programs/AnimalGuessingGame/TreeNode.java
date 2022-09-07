public class TreeNode<T>
{
	private T data;
	private TreeNode<T> leftChild;
	private TreeNode<T> rightChild;
	
	public TreeNode()
	{
		leftChild = null;
		rightChild = null;
		data = null;
	}
	
	public TreeNode(T _data, TreeNode<T> _leftChild,TreeNode<T> _rightChild)
	{
		data = _data;
		leftChild = _leftChild;
		rightChild = _rightChild;
	}
	
	public T getData()
	{
		return data;
	}
	
	public TreeNode<T> getLeftChild()
	{
		return leftChild;
	}
	
	public TreeNode<T> getRightChild()
	{
		return rightChild;
	}
	
	public void setData(T _data)
	{
		data = _data;
	}
	
	public void setLeftChild(TreeNode<T> _leftChild)
	{
		leftChild = _leftChild;
	}
	
	public void setRightChild(TreeNode<T> _rightChild)
	{
		rightChild = _rightChild;
	}
}
