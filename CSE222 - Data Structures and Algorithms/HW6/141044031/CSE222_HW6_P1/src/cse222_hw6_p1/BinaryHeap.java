package cse222_hw6_p1;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.NoSuchElementException;
import java.util.Queue;

/**
 *
 * @author yldzf
 * @param <E>
 */
public class BinaryHeap<E> extends BinaryTree<E> implements Queue<E>{
    /** An optional reference to a Comparator object. */
    private Comparator < E > comparator = null;
    /** To select Bottom right element of tree for removing operation  */
    private final ArrayList<Node<E>> items = new ArrayList();
    /** Size of tree  */
    private int size = 0;
    /** When creating Concrete tree this variables are helper variables */
    private int count = 0, temp2 = 0;
    /** The element of tree which is last added to tree */
    private Node<E> lastAdded;
    /** The element of tree which is paret of last added to tree */
    private Node<E> lastAddedParent;
    /**
     * No param constructure does not do anyhing
     */
    public BinaryHeap() {
    }
    /**
     * The constucture creates a tree according to given root.
     * @param root root of tree
     */
    public BinaryHeap(Node<E> root) {
        super(root);
    }
    /**
     * The constucture creates a tree according to given root ans given comparator.
     * @param root root of tree
     * @param comp to select priority element.
     */
    public BinaryHeap(Node<E> root, Comparator < E > comp) {

        super(root);
        comparator = comp;

    }

    private void swap(Node<E> node1,Node<E> node2){

        E temp = node1.data;
        node1.data = node2.data;
        node2.data = temp;

    }
    /**
     * The method creates concreate tree.
     * Method yazılırken şu siteden yardım alındı:
     * http://stackoverflow.com/questions/20890929/how-to-implement-a-complete-binary-tree-using-recursion-without-comparing-the-va
     * @param localRoot root of tree
     * @param item The name of the new element to add.
     * @return
     */
    private Node<E> createNode(Node<E> localRoot, E item) {

        if (localRoot == null) {
            localRoot = new Node(item);
            lastAdded = localRoot;
        }
        else {

            int k = 0, temp = 0;
            for (int j = 0; j < temp2; j++) {
                temp = (int) (temp + Math.pow(2, j));
                k = j;
                if (temp2 - temp <= 0) {
                    temp = (int) (temp - Math.pow(2, j));
                    break;
                }
            }
            if (temp2 - temp <= Math.pow(2, k) / 2) {
                temp = 1;
                for (int j = 1; j < k; j++) {
                    temp = (int) (temp + Math.pow(2, j) / 2);
                }
                temp2 = temp2 - temp;
                lastAddedParent = localRoot;

                localRoot.setLeft(createNode(localRoot.getLeft(), item));

            } else {
                temp = 1;
                for (int j = 1; j <= k; j++) {
                    temp = (int) (temp + Math.pow(2, j) / 2);
                }
                temp2 = temp2 - temp;
                lastAddedParent = localRoot;

                localRoot.setRight(createNode(localRoot.getRight(), item));
            }
        }
        return localRoot;
    }
    /** Compare two items using either a Comparator object’s compare method
     or their natural ordering using method compareTo.
     pre: If comparator is null, left and right implement Comparable.
     @param left One item
     @param right The other item
     @return Negative int if left less than right,
     0 if left equals right,
     positive int if left greater than right
     @throws ClassCastException if items are not Comparable
     */
    private int compare(E left, E right) {
        if (comparator != null) { // A Comparator is defined.
            return comparator.compare(left, right);
        }
        else { // Use left’s compareTo method.
            return ( (Comparable < E > ) left).compareTo(right);
        }
    }
    /**
     * Inserts the specified element into this tree if it is possible. When
     * adding new element, care is taken to ensure that the tree is concreate.
     * @param item the element to add
     * @return true
     * @throws NullPointerException if the specified element is null and this tree does not permit null elements
     */
    @Override
    public boolean add(E item) throws NullPointerException{
        if(item == null)
            throw new NullPointerException();

        count++;
        temp2 = count;

        root = createNode(root, item);
        lastAdded.parent = lastAddedParent;

        Node<E> temp;
        while(lastAdded!= null && lastAddedParent != null && compare(lastAddedParent.data,lastAdded.data ) > 0 ){
            swap(lastAdded,lastAddedParent);
            temp = lastAddedParent;
            lastAddedParent = lastAddedParent.parent;
            lastAdded = temp;
        }
        size++;
        return true;
    }
    /**
     * Inserts the specified element into this tree if it is possible
     * @param e the element to add
     * @return true
     * @throws NullPointerException if the specified element is null and this tree does not permit null elements
     */
    @Override
    public boolean offer(E e) throws NullPointerException{
        return add(e);
    }
    /**
     * To fill List of Node's
     */
    public void fillItems(){

        int h = height(this.root);
        items.clear();
        for (int i=1; i<=h; i++)
            LevelOrderTraverse(this.root,i);

    }
    /**
     * Adds Nodes to Node array, according to level order traverse.
     * @param localRoot the root of tree which will be traverse
     * @param level the level of tree which level will be traverse
     */
    private void LevelOrderTraverse ( Node < E > localRoot ,int level)
    {
        if (localRoot == null)
            return;
        if (level == 1)
            items.add(localRoot);
        else if (level > 1){
            LevelOrderTraverse(localRoot.left, level-1);
            LevelOrderTraverse(localRoot.right, level-1);
        }
    }
    /**
     * To calculate heigh of tree
     * @param localRoot root of tree
     * @return heigh of tree
     */
    private int height(Node < E > localRoot)
    {
        if (localRoot == null)
            return 0;
        else{
            int lheight = height(localRoot.left);
            int rheight = height(localRoot.right);

            if (lheight > rheight)
                return(lheight+1);
            else return(rheight+1);
        }
    }

    /**
     * Retrieves and removes the head of this Heap Tree. This method differs from
     * poll only in that it throws an exception if this Heap Tree is empty.
     * @return the head of this Heap Tree
     * @throws NoSuchElementException if this tree is empty
     */
    @Override
    public E remove() throws NoSuchElementException{
        if (isEmpty())
            throw new NoSuchElementException();
        E result =  super.getData();
        if (size() == 1) {
            super.root = null;
            --size;
            return result;
        }
        Node<E> parent = super.root;
        // En sağ alttaki elemanı bulmak için fillItems metgıdu çağırılıyor.
        fillItems();
        // En sağ alttaki eleman, items elemanının en sonundaki elamandır.
        lastAdded = items.get(items.size()-1);
        lastAddedParent = lastAdded.parent;
        parent.data = lastAdded.data;
        //En son elemanı silmek için
        if(lastAdded.data.equals(lastAddedParent.left.data))
            lastAddedParent.left = null;
        else
            lastAddedParent.right = null;

        while(true){
            Node<E> leftChildNode = parent.left;
            Node<E> rightChildNode =  parent.right;
            Node<E> minChildNode = leftChildNode;
            if(minChildNode == null)
                break;

            if (rightChildNode != null && compare(leftChildNode.data, rightChildNode.data) > 0)
                minChildNode = rightChildNode;

            if(compare(parent.data, minChildNode.data) > 0){
                E temp = parent.data;
                parent.data = minChildNode.data;
                minChildNode.data = temp;
                parent = minChildNode;
                E tempParent = parent.parent.data;
                parent.parent.data =  minChildNode.parent.data;
                minChildNode.parent.data = tempParent;
                lastAddedParent = parent.parent;
            }
            else
                break;
            if(minChildNode.left == null && minChildNode.right == null)
                break;
        }
        --size;
        return result;
    }

    /**
     * Retrieves and removes the head of this Heap Tree, or returns null if this
     * Heap Tree is empty.
     * @return the head of this Heap Tree, or null if this Heap Tree is empty
     */
    @Override
    public E poll() {
        if (isEmpty())
            return null;
        E result =  super.getData();
        if (size() == 1) {
            super.root = null;
            --size;
            return result;
        }
        Node<E> parent = super.root;
        fillItems();
        lastAdded = items.get(items.size()-1);
        lastAddedParent = lastAdded.parent;
        parent.data = lastAdded.data;
        //En son elemanı silmek için
        if(lastAdded.data.equals(lastAddedParent.left.data))
            lastAddedParent.left = null;
        else
            lastAddedParent.right = null;

        while(true){
            Node<E> leftChildNode = parent.left;
            Node<E> rightChildNode =  parent.right;
            Node<E> minChildNode = leftChildNode;
            if(minChildNode == null)
                break;
            boolean minLeft = true;

            if (rightChildNode != null && compare(leftChildNode.data, rightChildNode.data) > 0){
                minChildNode = rightChildNode;
                minLeft = false;
            }
            if(compare(parent.data, minChildNode.data) > 0){

                E temp = parent.data;
                parent.data = minChildNode.data;
                minChildNode.data = temp;
                parent = minChildNode;
                //parentleri ayarlamak
                E tempParent = parent.parent.data;
                parent.parent.data =  minChildNode.parent.data;
                minChildNode.parent.data = tempParent;
                lastAddedParent = parent.parent;

            }
            else
                break;
            if(minChildNode.left == null && minChildNode.right == null)
                break;

        }
        --size;
        return result;
    }
    /**
     * Retrieves, but does not remove, the head of this Heap Tree. This method
     * differs from peek only in that it throws an exception if this Heap Tree is empty.
     * @return the root of this heap tree
     * @throws NoSuchElementException if this tree is empty
     */
    @Override
    public E element() throws NoSuchElementException{

        if(isEmpty())
            throw new NoSuchElementException();
        return super.root.data;
    }
    /**
     * Retrieves, but does not remove, the head of this Heap Tree, or returns null if this Heap Tree is empty.
     * @return the root of this heap tree, or null if this tree is empty
     */
    @Override
    public E peek() {
        if(isEmpty())
            return null;
        return super.root.data;

    }
    /**
     * Retunrs size of the tree
     * @return size of the tree
     */
    @Override
    public int size() {
        return size;
    }
    /**
     * Checks the tree is empty or not
     * @return true if tree is empty else false
     */
    @Override
    public boolean isEmpty() {
        return size == 0;
    }
    /**
     * Clears the tree
     */
    @Override
    public void clear(){
        size = 0;
        super.root = null;
    }

}