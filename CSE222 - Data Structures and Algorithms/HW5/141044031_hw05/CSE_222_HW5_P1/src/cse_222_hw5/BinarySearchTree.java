package cse_222_hw5;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

public class BinarySearchTree < E
        extends Comparable < E >>
        extends BinaryTree < E >
        implements SearchTree < E > {
    // Data Fields
    /** Return value from the public add method. */
    protected boolean addReturn;

    /** Return value from the public delete method. */
    protected E deleteReturn;
    /**
     * The constructure creates an object of BinarySearchTree
     * @param data root's of value
     * @param leftTree root's left subtree
     * @param rightTree root's right subtree
     */
    public BinarySearchTree(E data, BinarySearchTree < E > leftTree,
                            BinarySearchTree < E > rightTree){
        super(data,leftTree,rightTree);
    }
    /**
     * The constructure creates an object of BinarySearchTree
     * @param root root of tree
     */
    private BinarySearchTree(Node < E > root) {
        this.root = root;
    }

    /**
     * The method creates level order iterator for BinarySearchTree
     * @return level order iterator for BinarySearchTree
     */
    public Iterator levelOrderIterator(){
        return new LevelOrderIteratorClass();
    }
    protected class LevelOrderIteratorClass implements Iterator<E>{

        private final Queue<Node<E>> treeQueue ;

        public LevelOrderIteratorClass(){
            treeQueue = new LinkedList();
            if(root != null)
                treeQueue.add(root);

        }
        /**
         * Control the tree's next is null or not
         * @return the tree's next is null or not
         */
        @Override
        public boolean hasNext() {
            return !treeQueue.isEmpty();
        }
        /**
         * Returns the element according to binary tree pre-order.
         * @return the element of tree according to binary tree pre-order.
         * @throws NoSuchElementException if tree's next is null
         */
        @Override
        public E next() throws NoSuchElementException{
            if(!hasNext())
                throw new NoSuchElementException("No elements found in Tree.");

            Node<E> first =  treeQueue.peek();
            if(first.left != null)
                treeQueue.add(first.left);
            if(first.right != null)
                treeQueue.add(first.right);

            return treeQueue.remove().data;

        }
    }
    /**
     pre: The target object must implement
     the Comparable interface.
     @param target The Comparable object being sought
     @return The object, if found, otherwise null
     */
    @Override
    public E find(E target) {
        return find(root, target);
    }

    /** Recursive find method.
     @param localRoot The local subtree’s root
     @param target The object being sought
     @return The object, if found, otherwise null
     */
    private E find(Node < E > localRoot, E target) {
        if (localRoot == null)
            return null;
        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.data);
        if (compResult == 0)
            return localRoot.data;
        else if (compResult < 0)
            return find(localRoot.left, target);
        else
            return find(localRoot.right, target);
    }

    /** Starter method add.
     pre: The object to insert must implement the
     Comparable interface.
     @param item The object being inserted
     @return true if the object is inserted, false
     if the object already exists in the tree
     */
    @Override
    public boolean add(E item) {
        root = add(root, item);
        return addReturn;
    }

    /** Recursive add method.
     post: The data field addReturn is set true if the item is added to
     the tree, false if the item is already in the tree.
     @param localRoot The local root of the subtree
     @param item The object to be inserted
     @return The new local root that now contains the
     inserted item
     */
    private Node < E > add(Node < E > localRoot, E item) {
        if (localRoot == null) {
            // item is not in the tree — insert it.
            addReturn = true;
            return new Node <  > (item);
        }
        else if (item.compareTo(localRoot.data) == 0) {
            // item is equal to localRoot.data
            addReturn = false;
            return localRoot;
        }
        else if (item.compareTo(localRoot.data) < 0) {
            // item is less than localRoot.data
            localRoot.left = add(localRoot.left, item);
            return localRoot;
        }
        else {
            // item is greater than localRoot.data
            localRoot.right = add(localRoot.right, item);
            return localRoot;
        }
    }

    /** Starter method delete.
     post: The object is not in the tree.
     @param target The object to be deleted
     @return The object deleted from the tree
     or null if the object was not in the tree
     @throws ClassCastException if target does not implement
     Comparable
     */
    @Override
    public E delete(E target) {
        root = delete(root, target);
        return deleteReturn;
    }

    /** Recursive delete method.
     post: The item is not in the tree;
     deleteReturn is equal to the deleted item
     as it was stored in the tree or null
     if the item was not found.
     @param localRoot The root of the current subtree
     @param item The item to be deleted
     @return The modified local root that does not contain
     the item
     */
    private Node < E > delete(Node < E > localRoot, E item) {
        if (localRoot == null) {
            // item is not in the tree.
            deleteReturn = null;
            return localRoot;
        }

        // Search for item to delete.
        int compResult = item.compareTo(localRoot.data);
        if (compResult < 0) {
            // item is smaller than localRoot.data.
            localRoot.left = delete(localRoot.left, item);
            return localRoot;
        }
        else if (compResult > 0) {
            // item is larger than localRoot.data.
            localRoot.right = delete(localRoot.right, item);
            return localRoot;
        }
        else {
            // item is at local root.
            deleteReturn = localRoot.data;
            if (localRoot.left == null) {
                // If there is no left child, return right child
                // which can also be null.
                return localRoot.right;
            }
            else if (localRoot.right == null) {
                // If there is no right child, return left child.
                return localRoot.left;
            }
            else {
                // Node being deleted has 2 children, replace the data
                // with inorder predecessor.
                if (localRoot.left.right == null) {
                    // The left child has no right child.
                    // Replace the data with the data in the
                    // left child.
                    localRoot.data = localRoot.left.data;
                    // Replace the left child with its left child.
                    localRoot.left = localRoot.left.left;
                    return localRoot;
                }
                else {
                    // Search for the inorder predecessor (ip) and
                    // replace deleted node’s data with ip.
                    localRoot.data = findLargestChild(localRoot.left);
                    return localRoot;
                }
            }
        }
    }

    /** Removes target from tree.
     @param target Item to be removed
     @return true if the object was in the tree, false otherwise
     @throws ClassCastException if target is not Comparable
     */
    @Override
    public boolean remove(E target) {
        return delete(target) != null;
    }

    /** Determine if an item is in the tree
     @param target Item being sought in tree
     @return true If the item is in the tree, false otherwise
     @throws ClassCastException if target is not Comparable
     */
    @Override
    public boolean contains(E target) {
        return find(target) != null;
    }

    /**** END EXERCISE ****/

    /** Find the node that is the
     inorder predecessor and replace it
     with its left child (if any).
     post: The inorder predecessor is removed from the tree.
     @param parent The parent of possible inorder
     predecessor (ip)
     @return The data in the ip
     */
    private E findLargestChild(Node < E > parent) {
        // If the right child has no right child, it is
        // the inorder predecessor.
        if (parent.right.right == null) {
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            return returnValue;
        }
        else {
            return findLargestChild(parent.right);
        }
    }
    /**
     * The method read's text file (with given bufferReader) and split's its
     * as spaces and convert integer then add's tree.
     * @param bR BufferedReader of reading text file
     * @return BinarySearchTree which is created with reading file.
     * @throws IOException If there is an input error
     */
    public static BinarySearchTree<Integer> readBinaryTree(BufferedReader bR) throws IOException {

        String[] broken_text = null;
        String text = "";
        BinarySearchTree<Integer> bTree = new BinarySearchTree (null);
        while((text = bR.readLine()) != null && !text.isEmpty()) {
            broken_text = text.split(" ");
            for(int i=0; i<broken_text.length; ++i)
                bTree.root =  addAnItem( bTree.root, Integer.parseInt( broken_text[i]) );
        }
        return bTree;

    }
    /**
     * The method add's the given item to given tree according to relative of
     * numbers (bigger-smaller)
     * @param localRoot the root of tree
     * @param item the element which will add to tree
     * @return the root of tree
     */
    private static Node<Integer> addAnItem( Node<Integer> localRoot, Integer item){

        if(localRoot == null){
            localRoot = new Node<>(item);
            return localRoot;
        }
        else if(item.compareTo(localRoot.data) < 0){
            localRoot.left = addAnItem(localRoot.left, item);
            return localRoot;
        }
        else if(item.compareTo(localRoot.data) > 0){
            localRoot.right = addAnItem(localRoot.right, item);
            return localRoot;
        }
        return localRoot;
    }
    /**
     * Prints the object to console according to level order
     */
    @Override
    public void traverse() {
        Iterator itr = this.levelOrderIterator();

        while(itr.hasNext()){

            System.out.printf(" %d",itr.next());
        }
        System.out.println();

    }

    /** Perform a preorder traversal.
     @param node The local root
     @param depth The depth
     @param sb The string buffer to save the output
     */
    private void levelOrderTraverse(BinaryTree < E > tree, int depth,
                                    StringBuilder sb) {
        for (int i = 1; i < depth; i++) {
            sb.append("  ");
        }
        int i = 0;
        Iterator itr = tree.iterator();

        while(itr.hasNext()){
            for(int j=0; j<i; ++j)
                sb.append("  ");

            sb.append(itr.next().toString());
            sb.append("\n");
            ++i;
        }

    }
}