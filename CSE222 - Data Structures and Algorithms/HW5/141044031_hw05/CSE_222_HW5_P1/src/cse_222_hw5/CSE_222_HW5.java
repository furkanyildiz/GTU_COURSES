/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cse_222_hw5;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author yldzf
 */
public class CSE_222_HW5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        String testFile = "test.txt";

        try{
            BufferedReader reader = new BufferedReader(new FileReader(testFile));
            BinaryTree<Integer> binaryTreeTest = BinaryTree.readBinaryTree(reader);
            // It traverses tree pre order
            binaryTreeTest.traverse();



            ////////////////////////////////////////////

            BufferedReader reader2 = new BufferedReader(new FileReader(testFile));

            BinarySearchTree<Integer> binarySearchTreeTest = BinarySearchTree.readBinaryTree(reader2);
            // It traverses tree level order
            binarySearchTreeTest.traverse();

            reader.close();
            reader2.close();
        }
        catch(FileNotFoundException e){
            System.err.println("File not found!");
        }
        catch(IOException e){
            System.err.println("File error!");
        }

    }

}
