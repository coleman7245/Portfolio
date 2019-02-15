//Author: coleman7245
//Project: Linked List Interface
//Last Edit: Thursday, February 14, 2019

public interface LinkedListInterface<T> {

    public boolean isEmpty();

    public int size();

    public void addFirst(T newItem);

    public void addLast(T newItem);

    public T removeFirst() throws LinkedListException;

    public String toString();
}
