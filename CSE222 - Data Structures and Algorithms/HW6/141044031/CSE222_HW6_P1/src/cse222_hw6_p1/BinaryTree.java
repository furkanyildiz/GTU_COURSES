package cse222_hw6_p1;

import java.io.*;
import java.util.AbstractCollection;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;

/** Class for a binary tree that stores type E objects.
 *   @author Koffman and Wolfgang
 * @param <E>
 * */

public class BinaryTree < E > extends AbstractCollection<E> implements Serializable {

    // Data Field
    /** The root of the binary tree */
    protected Node < E > root;
    /** Size of tree   */
    private int size = 0;
    /**
     * No param constructure assing null to root
     */
    public BinaryTree() {
        root = null;
    }
    /**
     * The constructure assigns given root to tree's root.
     * @param root tree's new root.
     */
    protected BinaryTree(Node < E > root) {
        this.root = root;
    }
    /** Constructs a new binary tree with data in its root,leftTree
     as its left subtree and rightTree as its right subtree.
     * @param data
     * @param leftTree
     * @param rightTree
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
        root.parent = null;
    }

    /**
     * This method creates iterator for BinaryTree class
     * @return an iterator of BinaryTree
     */
    @Override
    public Iterator<E> iterator() {
        return new treeIterator();
    }
    /**
     * Returns the size of tree
     * @return size of tree
     */
    @Override
    public int size() {
        size = 0;
        int h = height(root);
        for (int i=0; i<=h; i++)
            preOrderTraverseAndCount(root,i);
        return size;
    }

    protected class treeIterator implements Iterator<E>{

        private final Stack<Node<E>> TreeStack = new Stack();

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
    /** Class to encapsulate a tree node.
     * @param <E> */
    protected static class Node < E > implements Serializable {
        // Data Fields
        /** The information stored in this node. */
        protected E data;

        /** Reference to the left child. */
        protected Node < E > parent;

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
            parent = null;
        }
        /** Return a string representation of the node.
         @return A string representation of the data fields
         */
        @Override
        public String toString() {
            return data.toString();
        }
        public Node getLeft() {
            return left;
        }
        protected void setParent(Node<E> parent){
            this.parent = parent;
        }
        protected void setLeft(Node<E> left) {
            this.left = left;
        }

        protected Node<E> getRight() {
            return right;
        }

        protected void setRight(Node<E> right) {
            this.right = right;
        }

        protected E getData() {
            return data;
        }

        protected void setData(E data) {
            this.data = data;
        }
    }





    /** Return the left subtree.
     @return The left subtree or null if either the root or
     the left subtree is null
     */
    public BinaryTree < E > getLeftSubtree() {

        if (root != null && root.left != null)
            return new BinaryTree <  > (root.left);

        else
            return null;

    }

    /** Return the right sub-tree
     @return the right sub-tree or
     null if either the root or the
     right subtree is null.
     */
    public BinaryTree<E> getRightSubtree() {
        if (root != null && root.right != null)
            return new BinaryTree<>(root.right);
        else
            return null;

    }

    /** Return the data field of the root
     @return the data field of the root
     or null if the root is null
     */
    public E getData() {
        if (root != null)
            return root.data;
        else
            return null;

    }

    /** Determine whether this tree is a leaf.
     @return true if the root has no children
     */
    public boolean isLeaf() {
        return (root.left == null && root.right == null);
    }
    /**
     * Returns string representation of BinaryTree object
     * @return string representation of BinaryTree object
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }

    /** Perform a preorder traversal.
     @param node The local root
     @param depth The depth
     @param sb The string buffer to save the output
     */
    private void preOrderTraverse(Node < E > node, int depth,
                                  StringBuilder sb) {
        for (int i = 1; i < depth; i++) {
            sb.append("  ");
        }
        if (node == null) {
            sb.append("null\n");
        }
        else {
            sb.append(node.toString());
            sb.append("\n");
            preOrderTraverse(node.left, depth + 1, sb);
            preOrderTraverse(node.right, depth + 1, sb);
        }
    }

    /** Method to read a binary tree.
     pre: The input consists of a preorder traversal
     of the binary tree. The line "null" indicates a null tree.
     @param bR The input file
     @return The binary tree
     @throws IOException If there is an input error
     */
    public static BinaryTree < String > readBinaryTree(BufferedReader bR) throws IOException {
        // Read a line and trim leading and trailing spaces.
        String data = bR.readLine().trim();
        if (data.equals("null")) {
            return null;
        }
        else {
            BinaryTree < String > leftTree = readBinaryTree(bR);
            BinaryTree < String > rightTree = readBinaryTree(bR);
            return new BinaryTree <  > (data, leftTree, rightTree);
        }
    }
    /**
     * The method treverses tree (pre-order) and calculates size for each level
     * of tree
     * @param node root of tree
     * @param level level of tree to traverse
     */
    private void preOrderTraverseAndCount(Node < E > node, int level) {

        if (node == null)
            return;
        if (level == 1) {
            ++size;
        }
        else {
            preOrderTraverseAndCount(node.left, level-1);
            preOrderTraverseAndCount(node.right, level-1);
        }
    }
    /**
     * To calculate heigh of tree
     * @param localRoot root of tree
     * @return heigh of tree
     */
    private int height(Node <E> localRoot){
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
}
