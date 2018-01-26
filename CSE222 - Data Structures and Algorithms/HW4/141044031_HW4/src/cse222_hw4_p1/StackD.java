package cse222_hw4_p1;

import java.util.EmptyStackException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class StackD<E> implements StackInterface<E> {
    
    private Queue<E> queue = null;
    /**
     * The constructure creates a new linkid list.
     */
    public StackD(){
        this.queue = new LinkedList();
    }
    
    public StackD(Queue<E> other) {
        this.queue = other;
    }
    /**
     * Tests if this stack is empty.
     * @return true if and only if this stack contains no items; false otherwise.
     */
    @Override
    public boolean isEmpty() {
        return queue.isEmpty();
    }
    /**
     * Looks at the object at the top of this stack without removing it from 
     * the stack.
     * @return  the object at the top of this stack (the last item of the Vector object).
     * @throws EmptyStackException  if this stack is empty.
     */
    @Override
    public E peek() throws EmptyStackException {
        if((queue.isEmpty() || queue == null))
            throw new EmptyStackException();
        reverseQueue();
        E temp = queue.peek();
        reverseQueue();
        return temp;
    }
    /**
     * Removes the object at the top of this stack and returns that object as 
     * the value of this function.
     * @return The object at the top of this stack (the last item of the Vector object).
     * @throws EmptyStackException if size is zero.
     */
    @Override
    public E pop() throws EmptyStackException{
        if((queue.isEmpty() || queue == null))
            throw new EmptyStackException();
        reverseQueue();
        E temp = queue.poll();
        reverseQueue();
        return temp;
    }
   /**
    * Pushes an item onto the top of this stack.
    * @param item the item to be pushed onto this stack.
    * @return the item argument.
    */
    @Override
    public E push(E item) {
        if ( queue.add(item) )
            for (E other : queue)
                if(other.equals(item))
                    return other;
        return null;
    }
    /**
     * Returns the 1-based position where an object is on this stack.
     * @param o the desired object.
     * @return the 1-based position from the top of the stack where the object 
     * is located; the return value -1 indicates that the object is not on the stack.
     */
    @Override
    public int search(Object o) {
        
        Queue<E> temp = queue;
        Iterator itr = queue.iterator();
        int i = 1;
        while(itr.hasNext() ){
            if ( queue.contains(o))
                return i;
            itr.next();
            ++i;
        }
        return -1;
    }

    /**
     * To check size of stack.
     * @return size of stack.
     */
    @Override
    public int getSize() {
        return queue.size();
    }
    /**
     * It reverses the queue.
     */
    private void reverseQueue() {
        if(queue.isEmpty())
            return;
        E temp = queue.poll();
        if(!queue.isEmpty()) 
            reverseQueue();
        queue.add(temp);
    }
    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString(){
        
        StringBuilder ret =  new StringBuilder();
        ret.append(queue.toString());
        ret.delete(0, 1);
        ret.delete(ret.length()-1, ret.length());
        return ret.toString();
        
    }
}