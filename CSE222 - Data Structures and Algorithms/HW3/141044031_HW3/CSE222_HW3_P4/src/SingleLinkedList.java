import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * SingleLinkedList is a class that provides some of the
 * capabilities required by the List interface using
 * a single linked list data structure.
 * Only the following methods are provided:
 * get, set, add, remove, size, toString
 * @author Furkan, Koffman and Wolfgang
 */
public class SingleLinkedList<E> implements Iterable<E>{


    // Nested Class
    /**
     A Node is the building block for the SingleLinkedList
     * @param <E> The instance of Node class
     */
    private static class Node<E> {

        /** The data value. */
        private E data;
        /** The link */
        private Node<E> next = null;

        /**
         * Construct a node with the given data value and link
         * @param data - The data value
         * @param next - The link
         */
        public Node(E data, Node<E> next) {
            this.data = data;
            this.next = next;
        }

        /**
         * Construct a node with the given data value
         * @param data - The data value
         */
        public Node(E data) {
            this(data, null);
        }

        /**
         * To set Node's data
         * @param item notes data
         */
        void setData(E item){
            data = item;
        }

        /**
         * To access Node's data
         * @return Node's data
         */
        E getData(){
            return data;
        }

        /**
         * To set Node's next node
         * @param item node's next item.
         */
        void setNext(Node<E> item){
            next = item;
        }
    }
    // Data fields
    /** A reference to the head of the list */
    private Node<E> head = null;
    /** The size of the list */
    private int size = 0;
    /** A reference to the head of the deleted nodes */
    private Node<E> deletedHead = null;
    /** The size of the deleted list */
    private int deletesSize = 0;

    // Helper Methods

    /**
     * Query the size of the list
     * @return The number of objects in the list
     */
    public int getSize() {
        return size;
    }
    /**
     * Query the size of the deleted list
     * @return The number of objects in the list
     * @return The number of objects in the list
     */
    public int deletedSize(){
        return deletesSize;
    }
    /** Insert an item as the first item of the list.
     *	@param item The item to be inserted
     * @throws IndexOutOfBoundsException if deleted nodes not accesibable
     */
    public void addFirst(E item) throws IndexOutOfBoundsException {
        if (deletedHead == null)
            head = new Node<E>(item, head);
        else{
            head = removeDeletedNode(item);
            if (head == null) {
                throw new IndexOutOfBoundsException();
            }
        }
        size++;
    }


    /**
     * Add a node after a given node
     * If there is a deleted node, this method will not create
     * new Node object, it uses the deleted object
     * otherwise it will be create new Node
     * @param node The node which the new item is inserted after
     * @param item The item to insert
     */
    private void addAfter(Node<E> node, E item) {
        if(deletedHead == null)
            node.next = new Node<E>(item, node.next);
        else{
            node.next = removeDeletedNode(item);
            if (head == null) {
                System.err.println("Error addFirst!");
                System.exit(0);
            }
        }
        size++;
    }

    /**
     * Remove the first node from the list
     * @return The removed node's data or null if the list is empty
     */

    public E removeFirst() {
        Node<E> temp = head;
        Node<E> temp2 = head.next;

        if (head != null) {
            /* And adds the removed object to deleted nodes */
            addToDeleted(head);
            head = temp2;
        }
        if (temp != null) {
            size--;
            return temp.data;
        } else {
            return null;
        }
    }

    /**
     *  Removes the first occurrence of the specified element in this list.
     *  And adds the removed object to deleted nodes
     *  https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/code/LinkedList.java
     * @param key to remove element
     * @throws RuntimeException if linkedlist is empty or key is not in linked list.
     */
    public void remove(E key) throws RuntimeException
    {
        Node<E> temp = head.next;
        if(head == null)
            throw new RuntimeException("cannot delete");

        if( head.data.equals(key) )
        {
            addToDeleted(head);
            head = temp;
            --size;
            return;
        }

        Node<E> cur  = head;
        Node<E> prev = null;

        while(cur != null && !cur.data.equals(key) )
        {
            prev = cur;
            cur = cur.next;
        }

        if(cur == null)
            throw new RuntimeException("cannot delete");

        //delete cur node
        prev.next = cur.next;
        addToDeleted(cur);
        --size;

    }
    /**
     * Remove the node after a given node
     * And adds the removed object to deleted nodes
     * @param node The node before the one to be removed
     * @return The data from the removed node, or null
     *          if there is no node to remove
     */
    private E removeAfter(Node<E> node) {
        Node<E> temp = node.next;
        if (temp != null) {
            node.next = temp.next;
            size--;
            addToDeleted(node.next);
            return temp.data;
        } else {
            return null;
        }
    }

    /**
     * Find the node at a specified index
     * @param index The index of the node sought
     * @return The node at index or null if it does not exist
     */
    private Node<E> getNode(int index) {
        Node<E> node = head;
        for (int i = 0; i < index && node != null; i++) {
            node = node.next;
        }
        return node;
    }
    /**
     * Find the node at a specified index for Deleted Nodes
     * @param index The index of the node sought
     * @return The node at index or null if it does not exist
     */
    private Node<E> getDeletedNode(int index) {
        Node<E> node = deletedHead;
        for (int i = 0; i < index && node != null; i++) {
            node = node.next;
        }
        return node;
    }

    /**
     * Get the data value at index
     * @param index The index of the element to return
     * @return The data at index
     * @throws IndexOutOfBoundsException if the index is out of range
     */
    public E get(int index) throws IndexOutOfBoundsException{
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        Node<E> node = getNode(index);
        return node.data;
    }
    /**
     * Get the data value at index for deleted Linked List
     * @param index The index of the element to return
     * @return The data at index
     * @throws IndexOutOfBoundsException if the index is out of range
     */
    private E getDeleted(int index) {
        if (index < 0 || index >= deletesSize) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        Node<E> node = getDeletedNode(index);
        return node.data;
    }


    /**
     * Set the data value at index
     * @param index The index of the item to change
     * @param newValue The new value
     * @return The data value priviously at index
     * @throws IndexOutOfBoundsException if the index is out of range
     */
    private E set(int index, E newValue) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        Node<E> node = getNode(index);
        E result = node.data;
        node.data = newValue;
        return result;
    }

    /**
     * Insert the specified item at the specified position in the list.
     * Shifts the element currently at that position (if any) and any
     * subsequent elements to the right (adds one to their indicies)
     * @param index Index at which the specified item is to be inserted
     * @param item The item to be inserted
     * @throws IndexOutOfBoundsException if the index is out of range
     */
    public void add(int index, E item) throws IndexOutOfBoundsException {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        if (index == 0) {
                addFirst(item);
        } else {
            Node<E> node = getNode(index - 1);
            addAfter(node, item);
        }
    }

    /**
     * Insert the specified item at the specified position in the deletedList
     * When adding some referance it's adds to last of single linked list
     * @param index Index at which the specified item is to be inserted
     * @param item The item to be inserted
     * @throws IndexOutOfBoundsException if the index is out of range
     */
    private void addToDeleted(int index, Node<E> item){
        if (index < 0 || index > deletesSize) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        if (index == 0 || deletedHead == null) {
            addDeleteFirst(item);
        } else {
            Node<E> tmp = deletedHead;
            while (tmp.next != null) tmp = tmp.next;

            tmp.next = new Node<E>(item.data, null);
            ++deletesSize;

        }
    }

    /**
     * Add's a deleted node which is removed from single linked list
     * to first position of deleted node's.
     * @param item the deleted node from single linked list
     */
    private void addDeleteFirst(Node<E> item){
        item.setNext(null);
        deletedHead = item;
        ++deletesSize;
    }

    /**
     * To remove deleted node which is the first position of the deleted single linked list
     * @param newItem to change nodes data
     * @return deleted object
     */
    private Node<E> removeDeletedNode(E newItem) {
        Node<E> temp = deletedHead;
        if (deletedHead != null) {
            deletedHead = deletedHead.next;
        }
        if (temp != null) {
            --deletesSize;
            temp.setData(newItem);
            temp.setNext(null);
            return temp;
        } else {
            return null;
        }
    }
    /**
     * Append the specified item to the end of the list
     * @param item The item to be appended
     * @return true (as specified by the Collection interface)
     */
    public boolean add(E item) {
        add(size, item);
        return true;
    }

    /**
     * Append the specified item to the end of the Deletedlist
     * @param item The item to be appended
     * @return true (as specified by the Collection interface)
     */
    private boolean addToDeleted(Node<E> item) {
        addToDeleted(deletesSize, item);
        return true;
    }

    /**
     * Returns a string representation
     */
    public String toString() {
        StringBuffer result = new StringBuffer("[");
        for (Object x : this)
            result.append(String.valueOf(x) + ", ");
        if(getSize() != 0)
            result.delete(result.length()-2,result.length()); //To delete last ', '
        result.append("]");
        return result.toString();
    }

    /**
     * The method creates a String of deleted nodes.
     * @return String of deleted nodes.
     */
    public String deletedToString() {
        StringBuilder sb = new StringBuilder("[");
        Node p = deletedHead;
        if (p != null) {
            while (p.next != null) {
                sb.append(p.data.toString());
                sb.append(", ");
                p = p.next;
            }
            sb.append(p.data.toString());
        }
        sb.append("]");
        return sb.toString();

    }
    /*******************************************************
     *
     *  The Iterator class
     *
     ********************************************************/
    /**
     * Creates iterator class
     * @return Iterator
     */
    public Iterator<E> iterator() {
        return new SingleLinkedListIterator();
    }

    /**
     * The iterator impilemntation of myLinkedList
     */
    private class SingleLinkedListIterator implements Iterator<E> {
        /**
         * The first node referance of myLinkedList
         */
        private Node<E> nextNode;

        /**
         * Consturcture assings the first node referance of myLinkedList
         */
        public SingleLinkedListIterator() {
            nextNode = head;
        }

        /**
         * The method checks is there any element next or not
         * @return true if there is a element next otherwise false
         */
        public boolean hasNext() {
            return nextNode != null;
        }

        /**
         * return next element of myLinkedList
         * @return next element of myLinkedList
         */
        public E next() {
            if (!hasNext()) throw new NoSuchElementException();
            E res = nextNode.data;
            nextNode = nextNode.next;
            return res;
        }
        public void remove() {
            throw new UnsupportedOperationException();
        }

    }
}

