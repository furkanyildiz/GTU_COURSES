package cse222_hw6_p2;

import cse222_hw6_p2.HuffmanTree.HuffData;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 *
 * @author yldzf
 */
public class CSE222_HW6_P2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        try {
            create("freq.txt");
        } catch (FileNotFoundException ex) {
            System.err.println("File not found!");
            System.exit(0);
        }

    }

    public static void create(String filename) throws FileNotFoundException{
        File file = new File(filename);
        Scanner scanner = new Scanner(file);
        HuffmanTree ht = new HuffmanTree();
        ArrayList<HuffData> hd = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String s = line.substring(2, line.length());
            double freq  = Double.parseDouble(s);
            char character = character = line.charAt(0);
            hd.add(new HuffData(freq, character));
        }
        ht.buildTree(hd);
        scanner.close();
        try{
            System.out.println(ht.encode("furkan yildiz gtu"));
            System.out.println(ht.decode("11001100001001011000011101001111111000110110101101011101101100001011111100001110100001"));
        }catch(NoSuchElementException e){
            System.err.println("The element is not found in HuffmanTree");
            System.exit(0);
        }

    }

}
