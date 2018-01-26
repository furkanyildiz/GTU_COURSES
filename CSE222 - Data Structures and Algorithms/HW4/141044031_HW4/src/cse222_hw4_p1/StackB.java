/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cse222_hw4_p1;
import java.util.ArrayList;

import java.util.EmptyStackException;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class StackB<E> implements StackInterface<E> {

 
    private ArrayList<E> arrayList;
    
    public StackB() {
        super();
        arrayList = new ArrayList<>();
    }
    /**
     * To check size of stack.
     * @return size of stack.
     */
    @Override
    public int getSize() {
        return arrayList.size();
    }
    /**
     * 
     * @return 
     */
    @Override
    public boolean isEmpty() {
        return arrayList.isEmpty();
    }
    /**
     * Looks at the object at the top of this stack without removing it from 
     * the stack.
     * @return  the object at the top of this stack (the last item of the Vector object).
     * @throws EmptyStackException  if this stack is empty.
     */
    @Override
    public E peek() throws EmptyStackException {
        if(arrayList.isEmpty())
            throw new EmptyStackException();
        return arrayList.get(arrayList.size()-1);
    }
    /**
     * Removes the object at the top of this stack and returns that object as 
     * the value of this function.
     * @return The object at the top of this stack (the last item of the Vector object).
     * @throws IndexOutOfBoundsException if size is zero.
     */
    @Override
    public E pop() throws EmptyStackException{
    
        if (arrayList.isEmpty())
            throw new EmptyStackException();
        
        E temp = arrayList.get(arrayList.size()-1);
        arrayList.remove(arrayList.size()-1);
        return temp;    
    }
    /**
    * Pushes an item onto the top of this stack.
    * @param item the item to be pushed onto this stack.
    * @return the item argument.
    */
    @Override
    public E push(E item) {
        arrayList.add(item);
        return arrayList.get(arrayList.size()-1);
    }
    /**
     * Returns the 1-based position where an object is on this stack.
     * @param o the desired object.
     * @return the 1-based position from the top of the stack where the object 
     * is located; the return value -1 indicates that the object is not on the stack.
     */
    @Override
    public int search(Object o) {
        return arrayList.indexOf(o);
    }
    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for(int i=0; i<arrayList.size(); ++i)
            sb.append(arrayList.get(i)).append(" ,");
        
        if(sb.length()> 1 )
            sb.delete(sb.length()-1, sb.length());

        return sb.toString();
    }
}
