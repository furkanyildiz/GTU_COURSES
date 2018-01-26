
package cse222_hw4_p2;

import java.util.ListIterator;
import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.Stack;

/**
 *
 * @author furkan
 * @param <E>
 */
public class myQueue<E> extends KWLinkedList<E> {
    
    /**
     * Call's the KWLinkedList constructure.
     */
    public myQueue() {
        super();
    }
    /**
     * Inserts the specified element into this queue if it is possible to do so 
     * immediately without violating capacity restrictions, returning true upon 
     * success and throwing an IllegalStateException if no space is currently 
     * available.
     * @param item
     * @return true 
     * @throws NullPointerException if the specified element is null and this 
     * queue does not permit null elements
     */
    @Override
    public boolean add(E item) throws NullPointerException {
        if(item == null)
            throw new NullPointerException();
        if(getSize() == 0)
            addFirst(item);
        else
            addLast(item);
        return true;
    }
    /**
     * Inserts item at the rear of the queue. Returns true if successful; 
     * returns false if the item could not be inserted
     * @param item  the element to add
     * @return if the element was added to this queue, else false
     * @throws NullPointerException if the specified element is null and this 
     * queue does not permit null elements
     */
    public boolean offer(E item) throws NullPointerException{
        if(item == null)
            throw new NullPointerException();
        if(getSize() == 0)
            addFirst(item);
        else
            addLast(item);
        return true;
        
    }
    /**
     * Retrieves and removes the head of this queue. This method differs from 
     * poll only in that it throws an exception if this queue is empty.
     * @return the head of this queue
     * @throws NoSuchElementException  if this queue is empty
     */

    public E remove() throws NoSuchElementException{
        if(getSize() == 0)
            throw new NoSuchElementException();
        E temp = get(0);
        remove(0);
        return temp;
    }
    /**
     * Retrieves and removes the head of this queue, or returns null if this 
     * queue is empty.
     * @return the entry at the front of the queue
     */
    public E poll(){
        if(getSize() == 0)
            return null;
        E temp = get(0);
        remove(0);
        return temp;
    }
    /**
     * Returns the entry at the front of the queue without removing it; 
     * returns null if the queue is empty
     * @return the entry at the front of the queue
     */
    public E peek(){
        if(getSize() == 0)
            return null;
        return get(0);
        
    }
    /**
     * Returns the entry at the front of the queue without removing it. 
     * If the queue is empty, throws a NoSuchElementException
     * @return the entry at the front of the queue
     * @throws NoSuchElementException if this queue is empty
     */

    public E element() throws NoSuchElementException{
        
        if(getSize() == 0)
            throw new NoSuchElementException();
        return get(0);
    }
    /**
     * Reverses the queue.
     */
    public void reverse(){
        Stack temp = new Stack();
        ListIterator<E> itr = super.listIterator(0);
        while(itr.hasNext()){
            Object push = temp.push(itr.next());
        }
        itr = super.listIterator(0);

        while(itr.hasNext()){
            itr.next();
            itr.set((E) temp.pop());
        }
    }
    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString(){
       return super.toString();
    }
    /**
     * 2. sorunun 2. şıkkı
     * @param que 
     */
    public void reverseQueue(Queue<E> que) {
        if(que.isEmpty())
            return;
        E temp = que.poll();
        if(!que.isEmpty()) 
            reverseQueue(que);
        que.add(temp);
    }
}
