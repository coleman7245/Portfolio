//Author: coleman7245
//Project: Stack and Queue Interface
//Last Edit: Thursday, February 14, 2019

public interface StackQueueInterface<T> {

    public boolean isEmpty();

    public void put(T newItem);

    public T get() throws StackQueueException;

    public int size();

    public String toString();
}
