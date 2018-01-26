package cse222_hw4_p3;


import java.util.LinkedList;
import java.util.NoSuchElementException;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class PriorityQueueB<E extends Comparable>{
    /**
     * The linkeslist for save values.
     */
    LinkedList<E> linkedList = new LinkedList<>();
    /**
     * the highest priority element.
     */
    E minValue = null;
    /**
     * The constructure is empty.
     */
    public PriorityQueueB(){
    }
    /**
     * Appends the specified element to the end of this list.
     * @param e element to be appended to this list
     * @return true (as specified by Collection.add(E))
     */
     
    public boolean add(E e){
        boolean retVal;
        retVal =  linkedList.add(e);
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
     
    public void add(int index,E element)throws IndexOutOfBoundsException{
        try{
             linkedList.add(index,element);
        }catch(IndexOutOfBoundsException e){
            throw e;
        }
        updateMin(element);
    }
    /**
     * Inserts the specified element at the beginning of this list.
     * @param e the element to add
     */
     
    public void addFirst(E e){
        linkedList.addFirst(e);
        updateMin(e);
    }
    /**
     * Replaces the element at the specified position in this list with the specified element.
     * @param index index of the element to replace
     * @param element element to be stored at the specified position
     * @return the element previously at the specified position
     * @throws IndexOutOfBoundsException  if the index is out of range
     */
     
    public E set(int index,E element)throws IndexOutOfBoundsException{
        E rtVal;
        try{
            rtVal =  linkedList.set(index,element);
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
     
    public void addLast(E e){
         linkedList.addLast(e);
        updateMin(e);
    }
    /**
     * Removes all of the elements from this list. The list will be empty after this call returns.
     */
     
    public void clear(){
         linkedList.clear();
        minValue = null;
    }
    /**
     * Adds the specified element as the tail (last element) of this list.
     * @param e the element to add
     * @return true (as specified by Queue.offer(E))
     */
     
    public boolean offer(E e){
        boolean retVal;
        retVal =  linkedList.offer(e);
        if(retVal)
            updateMin(e);
        return retVal;   
        
    }
    /**
     * Inserts the specified element at the front of this list.
     * @param e the element to insert
     * @return true (as specified by Deque.offerFirst(E))
     */
     
    public boolean offerFirst(E e){
        boolean retVal;
        retVal =  linkedList.offerFirst(e);
        if(retVal)
            updateMin(e);
        return retVal;   
    }
    /**
     * Inserts the specified element at the end of this list.
     * @param e the element to insert
     * @return true
     */
     
    public boolean offerLast(E e){
        boolean retVal;
        retVal =  linkedList.offerLast(e);
        if(retVal)
            updateMin(e);
        return retVal;   
    }
    /**
     * Retrieves and removes the head (first element) of this list.
     * @return the head of this list, or null if this list is empty
     */
     
    public E poll(){
        E retVal =  linkedList.poll();
        findMin();
        return retVal;
    }
    /**
     * Retrieves and removes the first element of this list, or returns null if 
     * this list is empty.
     * @return the first element of this list, or null if this list is empty
     */
     
    public E pollFirst(){
        E retVal =  linkedList.pollFirst();
        findMin();
        return retVal;
    }
    /**
     * Retrieves and removes the last element of this list, or returns null if this list is empty.
     * @return the last element of this list, or null if this list is empty
     */
     
    public E pollLast(){
        E retVal =  linkedList.pollLast();
        findMin();
        return retVal;
    }
    /**
     * Pops an element from the stack represented by this list. In other words, 
     * removes and returns the first element of this list.
     * @return the element at the front of this list (which is the top of the stack represented by this list)
     * @throws NoSuchElementException  if this list is empty
     */
     
    public E pop() throws NoSuchElementException{
        E retVal;
        try{
            retVal =  linkedList.pop();
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
     
    public boolean removeFirstOccurrence(Object o){
        boolean retVal;
        try{
            retVal =  linkedList.removeFirstOccurrence(o);
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
     
    public boolean removeLastOccurrence(Object o){
        boolean retVal;
        try{
            retVal =  linkedList.removeLastOccurrence(o);
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
     
    public E remove()throws NoSuchElementException {
        E retVal;
        try{
            retVal =  linkedList.remove();}
        catch(NoSuchElementException e){
            throw e;
        }
        findMin();
        return retVal;
    }
     
    public E removeLast()throws NoSuchElementException{
        E retVal;
        try{
            retVal =  linkedList.removeLast();}
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
     
    public E removeFirst()throws NoSuchElementException{
        E retVal;
        try{
            retVal =  linkedList.removeFirst();}
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
     
    public boolean remove(Object o){
        boolean retVal =  linkedList.remove(o);
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
     
    public E remove(int index)throws IndexOutOfBoundsException{
        E retVal; 
        try{
             retVal =  linkedList.remove(index);
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
     
    public void push(E e){
         linkedList.push(e);
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
     
    public int size(){
        return  linkedList.size();
    }
    /**
     * Returns true if this collection contains no elements.
     * @return true if this collection contains no elements
     */
     
    public boolean isEmpty(){
        return  linkedList.isEmpty();
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
            if ( linkedList.remove(min))
                return min;
        return null;
    }
    /**
     * The method search the highest priority element in the queue.
     * @return the the highest priority element.
     * @throws NoSuchElementException if queue is empty.
     */
    private E findMin()throws NoSuchElementException{
        
        E min;
        
        if( linkedList.isEmpty())
            throw new NoSuchElementException();
        else
            min =  linkedList.get(0);
            

        for(int i=0; i< linkedList.size(); ++i){

            if(  linkedList.get(i).compareTo(min) < 0 ){
                min =  linkedList.get(i);
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
        StringBuilder temp = new StringBuilder(linkedList.toString());
        temp.delete(0, 1);
        temp.delete(temp.length()-1, temp.length());
        return temp.toString();
    }
    
}
