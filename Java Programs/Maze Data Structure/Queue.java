//Author: coleman7245
//Project: Queue Class
//Last Edit: Thursday, February 14, 2019

public class Queue<T> implements StackQueueInterface<T>
{
   private LinkedList<T> _list;
   
   public Queue()
   {
	   _list = new LinkedList<T>();
   }
   
   public boolean isEmpty()
   {
	   return _list.isEmpty();
   }
   
   public void put(T newItem)
   {
	   _list.addLast(newItem);
   }
   
   /*public T deQueue() throws StackQueueException
   {
	   if (!isEmpty())
		   return _list.removeFirst();
	   else
		   throw new StackQueueException("Queue is empty!");
   }*/
   
   public T get() throws StackQueueException
   {
	   if (!isEmpty())
	       return _list.removeFirst();
      else
		   throw new StackQueueException("Queue is empty!");
   }
   
   public int size()
   {
	   return _list.size();
   }
   
   public String toString()
   {
	   return _list.toString();
   }
   
   public static void main(String[] args)
   {
	  Queue<String> queue = new Queue<String>();
      queue.put("One");
      queue.put("Two");
      queue.put("Three");
      queue.put("Four");
      System.out.println(queue);
      
      System.out.println();
      //System.out.println(queue.deQueue());
      System.out.println();
      System.out.println(queue);
      
      System.out.println();
      System.out.println(queue.get());
      System.out.println();
      System.out.println(queue);
      
      queue.put("Five");
      System.out.println();
      System.out.println(queue);
   }
}
