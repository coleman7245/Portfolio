//Author: coleman7245
//Project: Linked List Class
//Last Edit: Thursday, February 14, 2019

public class LinkedList<T> implements LinkedListInterface<T>
{
   private Node<T> _head;
   private Node<T> _tail;
   private Node<T> _previous;
   private Node<T> _current;
   private int _numOfNodes;
   
   public LinkedList()
   {
      _head = null;
      _tail = null;
      _numOfNodes = 0;
   }
   
   public boolean isEmpty()
   {
      return _head == null;
   }
   
   public String toString()
   {
      String s = "";
      
      for(Node<T> current = _head; current != null; current = current.getNext())
         s += current.getData() + " ";
      
      return s;
   }
   
   public int size()
   {
      return _numOfNodes;
   }
   
   public Node find(int pos)
   {
      int i = 0;
      Node current = _head;
      
      while (current != null && i < pos)
      {
         current = current.getNext();
         i++;
      }
         
      return current;
   }
   
   public T get(int pos)
   {
      if (pos == 0)
         return _head.getData();
      else
      {
         _current = find(pos);
         return _current.getData();
      }
   }
   
   public void addFirst(T data)
   {
      if (isEmpty())
      {
         _head = new Node<T>(data, _head);
         _tail = _head;
         _numOfNodes++;
      }
      else
      {
         _head = new Node<T>(data, _head);
         _numOfNodes++;
      }
   }
   
   public void addLast(T data)
   {
      Node newNode = new Node<T>(data, null);
      
      if (isEmpty())
      {
         _head = new Node<T>(data, _head);
         _tail = _head;
         _numOfNodes++;
      }
      else
      {
         _tail.setNext(newNode);
         _tail = _tail.getNext();
         _numOfNodes++;
      }
   }
   
   public void insert(int pos, T data)
   {
      int i = 0;
      _current = _head;
      
      if (isEmpty())
      {
         _head = new Node<T>(data, _head);
         _tail = _head;
         _numOfNodes++;
      }
      else if (pos == 0)
      {
         _head = new Node<T>(data, _head);
         _numOfNodes++;
      }
      else
      {
         _previous = find(pos-1);
      
         if (_previous != null)
            _previous.setNext(new Node(data, _previous.getNext()));
         else
            _previous = new Node<T>(data, null);
            
         _numOfNodes++;
      }
   }
   
   public T removeFirst() throws LinkedListException
   {
      if (!isEmpty())
      {
         Node<T> temp = _head;
         _head = _head.getNext();
         _numOfNodes--;
         return temp.getData();
      }
      else
         throw new LinkedListException("List is empty!");
   }
   
   public void remove(int pos) throws LinkedListException
   {
      if (isEmpty())
         throw new LinkedListException("List is empty!");
      else if (pos == 0 && size() == 1)
      {
         _head = null;
         _tail = null;
         _numOfNodes--;
      }
      else if (pos == 0)
      {
         _head = _head.getNext();
         _numOfNodes--;
      }
      else
      {
         _previous = find(pos-1);
         _current = _previous.getNext();
         
         if (_previous != null && _current != null)
            _previous.setNext(_current.getNext());
         
         _numOfNodes--;
       }
    }
}
