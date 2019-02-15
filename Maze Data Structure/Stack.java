//Author: coleman7245
//Project: Stack Class
//Last Edit: Thursday, February 14, 2019

public class Stack<T> implements StackQueueInterface<T>
{
   private LinkedList<T> _list;

   public Stack()
   {
	   _list = new LinkedList<T>();
   }

   public int size()
   {
      return _list.size();
   }

   public boolean isEmpty()
   {
      return _list.isEmpty();
   }
   
   public void put(T newItem)
   {
      _list.addFirst(newItem);
   }
   
   public T get() throws StackQueueException
   {
	   if (!isEmpty())
	      return _list.removeFirst();
	   else
	      throw new StackQueueException("Stack is empty!");
   }
   
   /*public T pop() throws StackQueueException
   { 
      if (!isEmpty())
	      return _list.removeFirst();
	   else
	      throw new StackQueueException("Stack is empty!");
   }*/
   
   public String toString()
   {
	  return _list.toString();
   }
   
   public static void main(String[] args)
   {
      Stack<String> stack = new Stack<String>();
      stack.put("Four");
      stack.put("Three");
      stack.put("Two");
      stack.put("One");
      System.out.println(stack);
      
      System.out.println();
      //System.out.println(stack.pop());
      System.out.println();
      System.out.println(stack);
      
      System.out.println();
      System.out.println(stack.get());
      System.out.println();
      System.out.println(stack);
      
      System.out.println();
      stack.put("Five");
      System.out.println();
      System.out.println(stack);
   }
}
