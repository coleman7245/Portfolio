//Author: coleman7245
//Project: Node Class with Generic Data Type
//Last Edit: Thursday, February 14, 2019

public class Node<T>
{  
   private Node<T> _next;
   private T _data;

   public Node()
   {
      _next = null;
      _data = null;
   }
   
   public Node(T data, Node next)
   {
      setNext(next);
      setData(data);
   }
   
   public void setNext(Node next)
   {
      _next = next;
   }
   
   public void setData(T data)
   {
      _data = data;
   }
   
   public Node getNext()
   {
      return _next;
   }
   
   public T getData()
   {
      return _data;
   }
   
   public static void main(String[] args)
   {
      Node<Double> firstNode = new Node<Double>(99.9, null);
      firstNode = new Node<Double>(55.5, firstNode);
      firstNode = new Node<Double>(11.1, firstNode);
      
      for(Node<Double> current = firstNode; current != null; current = current.getNext())
         System.out.println((double)current.getData());
   }
}
