/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cse222_hw4_p1;

import java.util.EmptyStackException;

/**
 *
 * @author yldzf
 * @param <E>
 */
public interface StackInterface<E> {
    /**
     * Tests if this stack is empty.
     * @return true if and only if this stack contains no items; false otherwise.
     */
    public boolean isEmpty();
    /**
     * Looks at the object at the top of this stack without removing it from 
     * the stack.
     * @return  the object at the top of this stack (the last item of the Vector object).
     * @throws EmptyStackException  if this stack is empty.
     */
    public E peek() throws EmptyStackException;
    /**
     * Removes the object at the top of this stack and returns that object as 
     * the value of this function.
     * @return The object at the top of this stack (the last item of the Vector object).
     * @throws IndexOutOfBoundsException if size is zero.
     */
    public E pop() throws EmptyStackException;
   /**
    * Pushes an item onto the top of this stack.
    * @param item the item to be pushed onto this stack.
    * @return the item argument.
    */
    public E push(E item);
    /**
     * Returns the 1-based position where an object is on this stack.
     * @param o the desired object.
     * @return the 1-based position from the top of the stack where the object 
     * is located; the return value -1 indicates that the object is not on the stack.
     */
    public int search(Object o);
    /**
     * To check size of stack.
     * @return size of stack.
     */
    public int getSize();
}
