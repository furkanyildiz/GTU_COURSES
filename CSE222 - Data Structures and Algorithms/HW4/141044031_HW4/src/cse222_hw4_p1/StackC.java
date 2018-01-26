package cse222_hw4_p1;

import java.util.EmptyStackException;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class StackC<E> implements StackInterface<E> {
    private Node<E> head = null;
    private int size = 0;
    
    private static class Node<E> {

        /** The data value. */
        private E data = null;
        /** The link to the next node. */
        private Node<E> next = null;


        /**
         * Construct a node with the given data value.
         * @param dataItem The data value
         */
        private Node(E dataItem) {
            data = dataItem;
        }
                /**
         * Construct a node with the given data value and link
         * @param data - The data value 
         * @param next - The link
         */
        private Node(E data, Node<E> next) {
            this.data = data;
            this.next = next;
        }

    } //end class Node

    @Override
    public int getSize() {
        return size;
    }
    
    /**
     * Tests if this stack is empty.
     * @return true if and only if this stack contains no items; false otherwise.
     */
    @Override
    public boolean isEmpty() {
        return (size == 0);
    }
    /**
     * Looks at the object at the top of this stack without removing it from 
     * the stack.
     * @return  the object at the top of this stack (the last item of the Vector object).
     * @throws EmptyStackException  if this stack is empty.
     */
    @Override
    public E peek() throws EmptyStackException {
        if (head == null)
            throw new EmptyStackException();
        return getNode(size-1).data;
    }
    /**
     * Removes the object at the top of this stack and returns that object as 
     * the value of this function.
     * @return The object at the top of this stack (the last item of the Vector object).
     * @throws IndexOutOfBoundsException if size is zero.
     */
    @Override
    public E pop()throws EmptyStackException {
        if (size == 0)
            throw new EmptyStackException();
        return removeAfter(getNode(size-2));
        
    }
   /**
    * Pushes an item onto the top of this stack.
    * @param item the item to be pushed onto this stack.
    * @return the item argument.
    */
    @Override
    public E push(E item) {

        Node<E> newNode = new Node(item);
        
        if(head == null)
            head = newNode;
        else {
            Node<E> node = getNode(size-1);
            node.next = new Node<>(item, node.next);
        }
        ++size;
        return newNode.data;
    }
    /**
     * Returns the 1-based position where an object is on this stack.
     * @param o the desired object.
     * @return the 1-based position from the top of the stack where the object 
     * is located; the return value -1 indicates that the object is not on the 
     * stack. The first data's of stack index is one.
     */
    @Override
    public int search(Object o) {
        
        Node <E> target = new Node(o);
        Node <E> temp = head ;
        boolean found = false;
        int position = -1 ;
        while ( temp!= null && !found ){
            position++;
            if(temp.data.equals(target.data))
                found = true;
            else
                temp = temp.next;
        }
        if(found)
            return size-position;
        return -1;
    }
    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString(){
        
        StringBuilder sb = new StringBuilder();
        Node<E> temp = head;
        while(temp != null){
            sb.append(temp.data).append(" ,");
            temp = temp.next;
        }
        if(sb.length()> 1 )
            sb.delete(sb.length()-1, sb.length());
        return sb.toString();
        
    }
     /**
     * Find the node at a specified index
     * @param index The index of the node sought
     * @returns The node at index or null if it does not exist
     */
    private Node<E> getNode(int index) {
        Node<E> node = head;
        for (int i = 0; i < index && node != null; i++) {
            node = node.next;
        }
        return node;
    }
        /**
     * Remove the node after a given node
     * @param node The node before the one to be removed
     * @returns The data from the removed node, or null
     * if there is no node to remove
     */
    private E removeAfter(Node<E> node) {
        Node<E> temp = node.next;
        if (temp != null) {
            node.next = temp.next;
            size--;
            return temp.data;
        } else {
            return null;
        }
    }
    
}
