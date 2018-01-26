package cse222_hw4_p3;

import java.util.LinkedList;
import java.util.NoSuchElementException;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class PriorityQueueA<E extends Comparable> extends LinkedList<E>{
    
    /**
     * the highest priority element.
     */
    E minValue = null;
    /**
     * The constructure is empty.
     */
    public PriorityQueueA(){
    }
    /**
     * Appends the specified element to the end of this list.
     * @param e element to be appended to this list
     * @return true (as specified by Collection.add(E))
     */
    @Override
    public boolean add(E e){
        boolean retVal;
        retVal = super.add(e);
        if(retVal)
            updateMin(e);
        return retVal;   
    }
    /**
     * Inserts the specified element at the specified position in this list. 
     * Shifts the element currently at that position (if any) and any subsequent 
     * elements to the right (adds one to their indices).
     * @param index at which the specified element is to be inserted
     * @param element - element to be inserted 
     * @throws IndexOutOfBoundsException  if the index is out of range
     */
    @Override
    public void add(int index,E element)throws IndexOutOfBoundsException{
        try{
            super.add(index,element);
        }catch(IndexOutOfBoundsException e){
            throw e;
        }
        updateMin(element);
    }
    /**
     * Inserts the specified element at the beginning of this list.
     * @param e the element to add
     */
    @Override
    public void addFirst(E e){
        super.addFirst(e);
        updateMin(e);
    }
    /**
     * Replaces the element at the specified position in this list with the specified element.
     * @param index index of the element to replace
     * @param element element to be stored at the specified position
     * @return the element previously at the specified position
     * @throws IndexOutOfBoundsException  if the index is out of range
     */
    @Override
    public E set(int index,E element)throws IndexOutOfBoundsException{
        E rtVal;
        try{
            rtVal = super.set(index,element);
        }catch(IndexOutOfBoundsException e){
            throw e;
        }
        findMin();
        return rtVal;
    }
    /**
     * Appends the specified element to the end of this list.
     * @param e the element to add
     */
    @Override
    public void addLast(E e){
        super.addLast(e);
        updateMin(e);
    }
    /**
     * Removes all of the elements from this list. The list will be empty after this call returns.
     */
    @Override
    public void clear(){
        super.clear();
        minValue = null;
    }
    /**
     * Adds the specified element as the tail (last element) of this list.
     * @param e the element to add
     * @return true (as specified by Queue.offer(E))
     */
    @Override
    public boolean offer(E e){
        boolean retVal;
        retVal = super.offer(e);
        if(retVal)
            updateMin(e);
        return retVal;   
        
    }
    /**
     * Inserts the specified element at the front of this list.
     * @param e the element to insert
     * @return true (as specified by Deque.offerFirst(E))
     */
    @Override
    public boolean offerFirst(E e){
        boolean retVal;
        retVal = super.offerFirst(e);
        if(retVal)
            updateMin(e);
        return retVal;   
    }
    /**
     * Inserts the specified element at the end of this list.
     * @param e the element to insert
     * @return true
     */
    @Override
    public boolean offerLast(E e){
        boolean retVal;
        retVal = super.offerLast(e);
        if(retVal)
            updateMin(e);
        return retVal;   
    }
    /**
     * Retrieves and removes the head (first element) of this list.
     * @return the head of this list, or null if this list is empty
     */
    @Override
    public E poll(){
        E retVal = super.poll();
        findMin();
        return retVal;
    }
    /**
     * Retrieves and removes the first element of this list, or returns null if 
     * this list is empty.
     * @return the first element of this list, or null if this list is empty
     */
    @Override
    public E pollFirst(){
        E retVal = super.pollFirst();
        findMin();
        return retVal;
    }
    /**
     * Retrieves and removes the last element of this list, or returns null if this list is empty.
     * @return the last element of this list, or null if this list is empty
     */
    @Override
    public E pollLast(){
        E retVal = super.pollLast();
        findMin();
        return retVal;
    }
    /**
     * Pops an element from the stack represented by this list. In other words, 
     * removes and returns the first element of this list.
     * @return the element at the front of this list (which is the top of the stack represented by this list)
     * @throws NoSuchElementException  if this list is empty
     */
    @Override
    public E pop() throws NoSuchElementException{
        E retVal;
        try{
            retVal = super.pop();
        }catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
    }
    /**
     * Removes the first occurrence of the specified element in this list 
     * (when traversing the list from head to tail). If the list does not 
     * contain the element, it is unchanged.
     * @param o - element to be removed from this list, if present
     * @return true if the list contained the specified element
     */
    @Override
    public boolean removeFirstOccurrence(Object o){
        boolean retVal;
        try{
            retVal = super.removeFirstOccurrence(o);
        }
        catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
    }
    /**
     * Removes the last occurrence of the specified element in this list 
     * (when traversing the list from head to tail). If the list does not 
     * contain the element, it is unchanged.
     * @param o element to be removed from this list, if present
     * @return true if the list contained the specified element
     */
    @Override
    public boolean removeLastOccurrence(Object o){
        boolean retVal;
        try{
            retVal = super.removeLastOccurrence(o);
        }
        catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
    }

    /**
     * Retrieves and removes the head (first element) of this list.
     * @return the head of this list
     * @throws NoSuchElementException  if this list is empty
     */
    @Override
    public E remove()throws NoSuchElementException {
        E retVal;
        try{
            retVal = super.remove();}
        catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
    }
    @Override
    public E removeLast()throws NoSuchElementException{
        E retVal;
        try{
            retVal = super.removeLast();}
        catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
    }
    /**
     * Removes and returns the first element from this list.
     * @return the first element from this list
     * @throws NoSuchElementException 
     */
    @Override
    public E removeFirst()throws NoSuchElementException{
        E retVal;
        try{
            retVal = super.removeFirst();}
        catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
        
    }
    /**
     * Removes the first occurrence of the specified element from this list, 
     * if it is present. If this list does not contain the element, it is unchanged. 
     * @param o element to be removed from this list, if present
     * @return true if this list contained the specified element
     */
    @Override
    public boolean remove(Object o){
        boolean retVal = super.remove(o);
        findMin();
        return retVal;
    }
    /**
     * Removes the element at the specified position in this list. 
     * Shifts any subsequent elements to the left (subtracts one from their 
     * indices). Returns the element that was removed from the list.
     * @param index the index of the element to be removed
     * @return the element previously at the specified position
     * @throws IndexOutOfBoundsException if the index is out of range 
     */
    @Override
    public E remove(int index)throws IndexOutOfBoundsException{
        E retVal; 
        try{
             retVal = super.remove(index);
        }
        catch(IndexOutOfBoundsException e){
            throw e;
        }
        findMin();
        return retVal;
    }
    /**
     * Pushes an element onto the stack represented by this list. In other 
     * words, inserts the element at the front of this list.
     * @param e the element to push
     */
    @Override
    public void push(E e){
        super.push(e);
        updateMin(e);
    }
    /**
     * The method is check the given value is lower or not when we compare with
     * the highest priority element.
     * @param e 
     */
    private void updateMin(E e){
        if(minValue == null)
            minValue = e;
        else if( e.compareTo(minValue) == -1 )
            minValue = e;
    }
    /**
     * Returns the number of elements in this list.
     * @return the number of elements in this list
     */
    @Override
    public int size(){
        return super.size();
    }
    /**
     * Returns true if this collection contains no elements.
     * @return true if this collection contains no elements
     */
    @Override
    public boolean isEmpty(){
        return super.isEmpty();
    }
    /**
     * This metod deletes and returns the highest priority element. Lower values have higher priority.
     * @return  the highest priority element.
     */
    public E deleteMin(){
        E min = null;
        try{
            min = findMin();
        }catch(NoSuchElementException e){
            return null;
        }
        if(min != null)
            if (super.remove(min)){
                //update new min
                findMin();
                return min;
            }
        return null;
    }
    /**
     * The method search the highest priority element in the queue.
     * @return the the highest priority element.
     * @throws NoSuchElementException if queue is empty.
     */
    private E findMin()throws NoSuchElementException{
        
        E min;
        
        if(super.isEmpty())
            throw new NoSuchElementException();
        else
            min = super.get(0);
            

        for(int i=0; i<super.size(); ++i){

            if( super.get(i).compareTo(min) < 0 ){
                min = super.get(i);
            }
        }
        return min;
    }
    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString(){
        StringBuilder temp = new StringBuilder(super.toString());
        temp.delete(0, 1);
        temp.delete(temp.length()-1, temp.length());
        return temp.toString();
    }
    
}
