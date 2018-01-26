import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Referance : https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/code/LinkedList.java
 * @param <AnyType> Instance type
 */
public class myLinkedList<AnyType> implements Iterable<AnyType> {
    /*******************************************************
     *
     *  The Node class
     *
     ********************************************************/
    private static class Node<AnyType> {
        /**
         * The value of node
         */
        private AnyType data;
        /**
         * The next Node's referance
         */
        private Node<AnyType> next;
        /**
         * Construct a node with the given data value and link
         * @param data - The data value
         * @param next - The link
         */
        public Node(AnyType data, Node<AnyType> next) {
            this.data = data;
            this.next = next;
        }
        /**
         * Construct a node with the given data value
         * @param data - The data value
         */
        public Node(AnyType data) {
            this(data, null);
        }
        /** The data value.
         *
         * @return data value;
         */
        public AnyType getData() {
            return data;
        }
    }

    /**
     * The first referance of linked list
     */
    private Node<AnyType> head;
    /**
     * The size of linked list.
     */
    private int size = 0;

    /**
     * Constructs an empty list
     */
    public myLinkedList() {
        head = null;
    }


    /**
     * Checks true if the list is empty
     * @return true if the list is empty
     */
    public boolean isEmpty() {
        return head == null;
    }

    /**
     * Inserts a new node at the beginning of this list.
     * @param item the wanting to add element to first node
     * @return first Node of linked list.
     */
    public Node<AnyType> addFirst(AnyType item) {
        head = new Node<AnyType>(item, head);
        ++size;
        return getNode(0);
    }


    /**
     * To access the first element in the list.
     * @return the first element in the list.
     * @throws NoSuchElementException if head is null
     */

    public AnyType getFirst() throws NoSuchElementException{
        if (head == null) throw new NoSuchElementException();

        return head.data;
    }

    /**
     * Removes the first element in the list.
     * @return the removed data
     */
    public AnyType removeFirst() {
        AnyType tmp = getFirst();
        head = head.next;
        --size;
        return tmp;
    }


    /**
     *  Inserts a new node to the end of this list.
     * @param item wanting to add value
     * @return added Node
     */
    public Node<AnyType> add(AnyType item) {
        if (head == null)
            return addFirst(item);
        else {
            ++size;
            Node<AnyType> tmp = head;
            while (tmp.next != null) tmp = tmp.next;

            Node<AnyType> addedNode = new Node<AnyType>(item, null);
            tmp.next = addedNode;
            return addedNode;
        }
    }
    /**
     * Insert the specified item at the specified position in the list.
     * Shifts the element currently at that position (if any) and any
     * subsequent elements to the right (adds one to their indicies)
     * @param index Index at which the specified item is to be inserted
     * @param item The item to be inserted
     * @throws IndexOutOfBoundsException if the index is out of range
     */
    public void add(int index, AnyType item) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        if (index == 0) {
            addFirst(item);
        } else {
            Node node = getNode(index - 1);
            addAfter(node, item);
        }
    }
    /**
     * Add a node after a given node
     * @param node The node which the new item is inserted after
     * @param item The item to insert
     */
    private void addAfter(Node node, AnyType item) {
        node.next = new Node(item, node.next);
        size++;
    }

    /**
     * Returns the last element in the list.
     * @return the last element of linked list.
     */
    public AnyType getLast() {
        if (head == null) throw new NoSuchElementException();

        Node<AnyType> tmp = head;
        while (tmp.next != null) tmp = tmp.next;

        return tmp.data;
    }

    /**
     * Removes all nodes from the list.
     */
    public void clear() {
        head = null;
        size = 0;
    }


    /**
     * Checks the target value is in linked list or not.
     * @param x the target value
     * @return  true if this list contains the specified element.
     */
    public boolean contains(AnyType x) {
        for (AnyType tmp : this)
            if (tmp.equals(x)) return true;

        return false;
    }
    /**
     * Find the node at a specified index
     * @param index The index of the node sought
     * @returns The node at index or null if it does not exist
     */
    private Node<AnyType> getNode(int index) {
        Node<AnyType> node = head;
        for (int i = 0; i < index && node != null; i++) {
            node = node.next;
        }
        return node;
    }

    /**
     * Returns the data at the specified position in the list.
     * @param pos the position of target Node
     * @return the data
     */
    public AnyType get(int pos) {
        if (head == null) throw new IndexOutOfBoundsException();

        Node<AnyType> tmp = head;
        for (int k = 0; k < pos; k++) tmp = tmp.next;

        if (tmp == null) throw new IndexOutOfBoundsException();

        return tmp.data;
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
     * Removes the first occurrence of the specified element in this list.
     * @param key the removing data
     */
    public void remove(AnyType key) {
        if (head == null)
            throw new RuntimeException("cannot delete");

        if (head.data.equals(key)) {
            head = head.next;
            --size;
            return;
        }

        Node<AnyType> cur = head;
        Node<AnyType> prev = null;

        while (cur != null && !cur.data.equals(key)) {
            prev = cur;
            cur = cur.next;
        }

        if (cur == null)
            throw new RuntimeException("cannot delete");

        //delete cur node
        prev.next = cur.next;
        --size;
    }
    /**
     * Remove the node after a given node
     * @param node The node before the one to be removed
     * @returns The data from the removed node, or null
     *          if there is no node to remove
     */
    private String removeAfter(Node node) {
        Node temp = node.next;
        if (temp != null) {
            node.next = temp.next;
            size--;
            return temp.data.toString();
        } else {
            return null;
        }
    }

    /**
     * Returns a deep copy of the list
     * Complexity: O(n^2)
     * @return the copy of list
     */
    public myLinkedList<AnyType> copy1() {
        myLinkedList<AnyType> twin = new myLinkedList<AnyType>();
        Node<AnyType> tmp = head;
        while (tmp != null) {
            twin.add(tmp.data);
            tmp = tmp.next;
        }

        return twin;
    }
    public int getSize(){
        return size;
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
    public Iterator<AnyType> iterator() {
        return new myLinkedListIterator();
    }

    /**
     * The iterator impilemntation of myLinkedList
     */
    private class myLinkedListIterator implements Iterator<AnyType> {
        /**
         * The first node referance of myLinkedList
         */
        private Node<AnyType> nextNode;

        /**
         * Consturcture assings the first node referance of myLinkedList
         */
        public myLinkedListIterator() {
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
        public AnyType next() {
            if (!hasNext()) throw new NoSuchElementException();
            AnyType res = nextNode.data;
            nextNode = nextNode.next;
            return res;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    /**
     * This method is a wrapper method, it calls the helper recursive function
     * and it reverses the myLinkedList copy and return its toString.
     * So the main myLinkedList can not be change.
     * @return The reversed myLinkesList string.
     */
    public String reverseToString(){
        if (getSize() <2)
            return this.toString();
        myLinkedList<AnyType> temp2 = this.copy1();
        temp2.reverseRecursively(0,getSize()-1);
        return temp2.toString();
    }

    /**
     * The method reverses the myLinkedList according to given indexes values
     * @param start the first index to reverse
     * @param end the last index to reverse
     */
     private void reverseRecursively(int start, int end){

        if(start == size/2)
            return;

        if(start == 0){
            AnyType temp = getNode(start).getData();
            addFirst(getNode(end).getData());
            removeAfter(getNode(start));
            removeAfter(getNode(end-1));
            add(end,temp);

        }
        else{
            AnyType temp = getNode(start).getData();
            add(start,getNode(end).getData());
            removeAfter(getNode(start));
            removeAfter(getNode(end-1));
            add(end,temp);


        }
        reverseRecursively(start+1, end-1);
    }




}