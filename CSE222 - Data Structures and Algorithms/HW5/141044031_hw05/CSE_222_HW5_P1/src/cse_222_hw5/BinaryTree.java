package cse_222_hw5;

import java.io.*;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;

public class BinaryTree < E > implements Iterable<E> {
    /**
     * This method creates iterator for BinaryTree class
     * @return an iterator of BinaryTree
     */
    @Override
    public Iterator<E> iterator() {
        return new treeIterator();
    }

    protected class treeIterator implements Iterator<E>{

        private final Stack<Node<E>> TreeStack = new Stack<>();

        public treeIterator() {
            if(root != null)
                TreeStack.add(root);
        }
        /**
         * Control the tree's next is null or not
         * @return the tree's next is null or not
         */
        @Override
        public boolean hasNext() {
            return !TreeStack.isEmpty();
        }
        /**
         * Returns next element of tree according to pre-order
         * @return next element of tree according to pre-order
         */
        @Override
        public E next() {
            if (!hasNext())
                throw new NoSuchElementException();

            Node<E> node = TreeStack.pop();

            if (node.right != null)
                TreeStack.push(node.right);
            if (node.left != null)
                TreeStack.push(node.left);

            return node.data;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }

    }
    /**
     * Returns string represantation of object
     * @return string represantation of object
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }
    /**
     * Prints the object to console according to pre-order
     */
    public void traverse() {
        Iterator itr = this.iterator();

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
    private void preOrderTraverse(Node < E > node, int depth,
                                  StringBuilder sb) {
        for (int i = 1; i < depth; i++)
            sb.append("  ");

        if (node == null)
            sb.append("null\n");

        else {
            sb.append(node.toString());
            sb.append("\n");
            preOrderTraverse(node.left, depth + 1, sb);
            preOrderTraverse(node.right, depth + 1, sb);
        }
    }
    /** Class to encapsulate a tree node.
    */
    protected static class Node < E > implements Serializable {
        // Data Fields
        /** The information stored in this node. */
        protected E data;

        /** Reference to the left child. */
        protected Node < E > left;

        /** Reference to the right child. */
        protected Node < E > right;

        // Constructors
        /** Construct a node with given data and no children.
         @param data The data to store in this node
         */
        public Node(E data) {
            this.data = data;
            left = null;
            right = null;
        }

        // Methods
        /** Return a string representation of the node.
         @return A string representation of the data fields
         */
        public String toString() {
            return data.toString();
        }
    }

    // Data Field
    /** The root of the binary tree */
    protected Node < E > root;

    public BinaryTree() {
        root = null;
    }

    protected BinaryTree(Node < E > root) {
        this.root = root;
    }

    /**
     * The constructure creates an object of BinaryTree
     * @param data root's of value
     * @param leftTree root's left subtree
     * @param rightTree root's right subtree
     */
    public BinaryTree(E data, BinaryTree < E > leftTree, BinaryTree < E > rightTree) {

        root = new Node <  > (data);
        if (leftTree != null)
            root.left = leftTree.root;

        else
            root.left = null;

        if (rightTree != null)
            root.right = rightTree.root;

        else
            root.right = null;

    }

    /** Return the left subtree.
     @return The left subtree or null if either the root or
     the left subtree is null
     */
    public BinaryTree < E > getLeftSubtree() {
        if (root != null && root.left != null)
            return new BinaryTree < E > (root.left);

        else
            return null;

    }
    private void setLeftSubtree(BinaryTree leftTree)throws NoSuchElementException{
        if(root == null)
            throw new NoSuchElementException();
        root.left = leftTree.root;
    }
    private void setRightSubtree(BinaryTree rightTree)throws NoSuchElementException{
        if(root == null)
            throw new NoSuchElementException();
        root.right = rightTree.root;
    }
    /** Return the right sub-tree
     @return the right sub-tree or
     null if either the root or the
     right subtree is null.
     */
    public BinaryTree<E> getRightSubtree() {
        if (root != null && root.right != null) {
            return new BinaryTree<>(root.right);
        } else {
            return null;
        }
    }


    /**** BEGIN EXERCISE ****/
    /** Return the data field of the root
     @return the data field of the root
     or null if the root is null
     */
    public E getData() {
        if (root != null) {
            return root.data;
        } else {
            return null;
        }
    }

    /** Determine whether this tree is a leaf.
     @return true if the root has no children
     */
    public boolean isLeaf() {
        return (root.left == null && root.right == null);
    }


    /** Method to read a binary tree.
     pre: The input consists of a preorder traversal
     of the binary tree. The line "null" indicates a null tree.
     @param bR The input file
     @return The binary tree
     @throws IOException If there is an input error
     */
    public static BinaryTree<Integer> readBinaryTree(BufferedReader bR) throws IOException {

        String[] broken_text = null;
        String text = "";
        BinaryTree<Integer> bTree = new BinaryTree (null);
        while((text = bR.readLine()) != null && !text.isEmpty()) {
            broken_text = text.split(" ");
            for(int i=0; i<broken_text.length; ++i)
                bTree.root =  addAnItem( bTree.root, Integer.parseInt( broken_text[i]) );
        }
        return bTree;

    }
    /**
     * Add's an item to tree when creating tree the methods provide perfect
     * tree
     * @param localRoot the root of tree
     * @param item the element to add operation
     * @return the root of tree
     */
    private static Node<Integer> addAnItem( Node<Integer> localRoot, Integer item){

        BinaryTree<Integer> b = new BinaryTree<>(localRoot);

        /**
         * If the element has already added we should do noting
         */
        Iterator itr = b.iterator();
        while(itr.hasNext()){
            if(itr.next().equals(item))
                return localRoot;
        }

        if(localRoot!= null && localRoot.data.equals(item))
            return localRoot;

        if(localRoot == null){
            localRoot = new Node<>(item);
            return localRoot;
        }

        else if(localRoot.left == null){
            localRoot.left = addAnItem(localRoot.left, item);
            return localRoot;
        }
        else if(localRoot.right == null){
            localRoot.right = addAnItem(localRoot.right, item);
            return localRoot;
        }
        else{
            if(heightOfBinaryTreeLeft(localRoot) > heightOfBinaryTreeRight(localRoot))
                addAnItem(localRoot.right, item);
            else
                addAnItem(localRoot.left, item);
        }
        return localRoot;
    }
    /**
     * Returns height of left root
     * @param root the root of tree
     * @return height of left root
     */
    private static int heightOfBinaryTreeLeft(Node<Integer> root){
        if(root == null)
            return 0;
        return 1 + heightOfBinaryTreeLeft(root.left);
    }
    /**
     * Returns height of right root
     * @param root the root of tree
     * @return height of right root
     */
    private static int heightOfBinaryTreeRight(Node<Integer> root){
        if(root == null)
            return 0;
        return 1 + heightOfBinaryTreeRight(root.right);
    }
}
