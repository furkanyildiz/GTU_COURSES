package cse222_hw6_p2;

import java.io.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.NoSuchElementException;
import java.util.PriorityQueue;
import java.util.Queue;

/** Class to represent and build a Huffman tree.
 *   @author Koffman and Wolfgang
 * */

public class HuffmanTree implements Serializable {

    // Nested Classes
    /** A datum in the Huffman tree. */
    public static class HuffData implements Serializable {
        // Data Fields
        /** The weight or probability assigned to this HuffData. */
        private double weight;

        /** The alphabet symbol if this is a leaf. */
        private Character symbol;

        public HuffData(double weight, Character symbol) {
            this.weight = weight;
            this.symbol = symbol;
        }
        public Character getSymbol(){
            return this.symbol;
        }
    }

    // Data Fields
    /** A reference to the completed Huffman tree. */
    private BinaryTree < HuffData > huffTree;

    /** A Comparator for Huffman trees; nested class. */
    private static class CompareHuffmanTrees implements Comparator < BinaryTree < HuffData >> {
        /** Compare two objects.
         @param treeLeft The left-hand object
         @param treeRight The right-hand object
         @return -1 if left less than right,
         0 if left equals right,
         and +1 if left greater than right
         */
        @Override
        public int compare(BinaryTree < HuffData > treeLeft,
                           BinaryTree < HuffData > treeRight) {
            double wLeft = treeLeft.getData().weight;
            double wRight = treeRight.getData().weight;
            return Double.compare(wLeft, wRight);
        }
    }

    /** Builds the Huffman tree using the given alphabet and weights.
     post:  huffTree contains a reference to the Huffman tree.
     @param symbols An array of HuffData objects
     */
    public void buildTree(ArrayList<HuffData> symbols) {

        Queue < BinaryTree < HuffData >> theQueue = new PriorityQueue < >(symbols.size(), new CompareHuffmanTrees());
        // Load the queue with the leaves.
        for(int i=0; i<symbols.size(); ++i){
            BinaryTree < HuffData > aBinaryTree = new BinaryTree <> (symbols.get(i), null, null);
            theQueue.offer(aBinaryTree);

        }
        // Build the tree.
        while (theQueue.size() > 1) {
            BinaryTree < HuffData > left = theQueue.poll();
            BinaryTree < HuffData > right = theQueue.poll();
            double wl = left.getData().weight;
            double wr = right.getData().weight;
            HuffData sum = new HuffData(wl + wr, null);
            BinaryTree < HuffData > newTree =
                    new BinaryTree <  > (sum, left, right);
            theQueue.offer(newTree);
        }

        // The queue should now contain only one item.
        huffTree = theQueue.poll();
    }
    /** To check given array has illagal(which is no in "freq.txt") or not */
    private Boolean check = false;
    /**
     * The method encodes the given string.
     * @param target the string which will be encode
     * @return the encoded String
     * @throws NoSuchElementException if string has illagel element
     */
    public String encode(String target) throws NoSuchElementException{

        StringBuilder sb = new StringBuilder();
        for(int i=0; i<target.length(); ++i){

            StringBuilder subsb = new StringBuilder();
            check = false;
            encodeAChar(subsb,"",target.charAt(i),this.huffTree);
            if(check == false)
                throw new NoSuchElementException();
            sb.append(subsb);
        }
        return sb.toString();
    }
    /**
     * The method founds a character from Huffman tree and update's the encoded
     * string of given character
     * @param sb encoded string of target character
     * @param code hufman code
     * @param target target character
     * @param tree Hufman tree's root
     */
    public void encodeAChar(StringBuilder sb,String code,Character target, BinaryTree < HuffData > tree) {
        HuffData theData = tree.getData();
        if(tree.isLeaf()){
            if (theData.symbol.equals(target)) {
                sb.append(code);
                check =  true;
            }
        }
        else {
            encodeAChar(sb, code + "0",target, tree.getLeftSubtree());
            encodeAChar(sb, code + "1",target, tree.getRightSubtree());
        }
    }
    /** Outputs the resulting code.
     @param code The code up to this node
     @param tree The current node in the tree
     */
    private void printCode(StringBuilder sb, String code, BinaryTree < HuffData > tree) {
        HuffData theData = tree.getData();
        if (theData.symbol != null) {
            if (theData.symbol.equals(" ")) {
                sb.append("space: ").append(code);
            }
            else {
                sb.append(code);
            }
        }
        else {
            printCode(sb, code + "0", tree.getLeftSubtree());
            printCode(sb, code + "1", tree.getRightSubtree());
        }
    }

    /** Method to decode a message that is input as a string of
     digit characters '0' and '1'.
     @param codedMessage The input message as a String of
     zeros and ones.
     @return The decoded message as a String
     */
    public String decode(String codedMessage) {
        StringBuilder result = new StringBuilder();
        BinaryTree < HuffData > currentTree = huffTree;
        for (int i = 0; i < codedMessage.length(); i++) {
            if (codedMessage.charAt(i) == '1') {
                currentTree = currentTree.getRightSubtree();
            }
            else {
                currentTree = currentTree.getLeftSubtree();
            }
            if (currentTree.isLeaf()) {
                HuffData theData = currentTree.getData();
                result.append(theData.symbol);
                currentTree = huffTree;
            }
        }
        return result.toString();
    }
    //  *********************  Q3  **********************************
    /**
     * The methos traverses huffmantree level-order.
     * @return a String according to level-order traversing the huffman tree.
     */
    public String LevelOrderTraverse(){

        StringBuilder br = new StringBuilder();
        int h = height(huffTree);
        for (int i=0; i<=h; i++)
            LevelOrderTraverseHelper(br,huffTree,i);
        return br.toString();

    }
    /**
     * Traverses tree and appends the elements of tree
     * @param br StrinBuilder to add the nodes of traversed tree
     * @param tree the tree which will be traverse
     * @param level the level of tree which level will be traverse
     */
    private void LevelOrderTraverseHelper (StringBuilder br, BinaryTree < HuffData > tree ,int level)
    {
        if (tree == null)
            return;
        if (level == 1)
            br.append(tree.root.data.symbol).append(" ");
        else if (level > 1){
            LevelOrderTraverseHelper(br,tree.getLeftSubtree(), level-1);
            LevelOrderTraverseHelper(br,tree.getRightSubtree(), level-1);
        }
    }
    /**
     * To calculate heigh of tree
     * @param tree root of tree
     * @return heigh of tree
     */
    private int height(BinaryTree < HuffData > tree)
    {
        if (tree == null)
            return 0;
        else{
            int lheight = height(tree.getLeftSubtree());
            int rheight = height(tree.getRightSubtree());

            if (lheight > rheight)
                return(lheight+1);
            else return(rheight+1);
        }
    }

}
