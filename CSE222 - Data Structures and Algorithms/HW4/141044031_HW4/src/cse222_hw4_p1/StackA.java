package cse222_hw4_p1;

import java.util.ArrayList;
import java.util.EmptyStackException;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class StackA<E> extends ArrayList<E> implements StackInterface<E>  {

    public StackA() {
        super();
    }
    @Override
    public int getSize() {
        return super.size();
    }
    /**
     * Tests if this stack is empty.
     * @return true if and only if this stack contains no items; false otherwise.
     */
    @Override
    public boolean isEmpty() {
        return super.isEmpty();
    }
    /**
     * Looks at the object at the top of this stack without removing it from 
     * the stack.
     * @return  the object at the top of this stack (the last item of the Vector object).
     * @throws EmptyStackException  if this stack is empty.
     */
    @Override
    public E peek() throws EmptyStackException {
        if(super.isEmpty())
            throw new EmptyStackException();
        return super.get(super.size()-1);
    }
    /**
     * Removes the object at the top of this stack and returns that object as 
     * the value of this function.
     * @return The object at the top of this stack (the last item of the Vector object).
     * @throws IndexOutOfBoundsException if size is zero.
     */
    @Override
    public E pop() throws EmptyStackException{
        if (super.isEmpty())
            throw new EmptyStackException();
        
        E temp = super.get(super.size()-1);
        super.remove(super.size()-1);
        return temp;
    }
   /**
    * Pushes an item onto the top of this stack.
    * @param item the item to be pushed onto this stack.
    * @return the item argument.
    */
    @Override
    public E push(E item) {
        super.add(item);
        return super.get(super.size()-1);
    }
    /**
     * Returns the 1-based position where an object is on this stack.
     * @param o the desired object.
     * @return the 1-based position from the top of the stack where the object 
     * is located; the return value -1 indicates that the object is not on the stack.
     */
    @Override
    public int search(Object o) {
        return super.indexOf(o);
    }
    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for(int i=0; i<super.size(); ++i)
            sb.append(super.get(i)).append(" ,");
        if(sb.length()> 1 )
            sb.delete(sb.length()-1, sb.length());

        return sb.toString();
    }
}
