package cse222_hw4_p3;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;

/**
 *
 * @author yldzf
 */
public class CSE244_HW4_P3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        String inputFile = "test.csv";
        String outputFile = "testResult_3.csv";
        
        //testDeleteMınMethod();
        PriorityQueueA<Integer> ai = new PriorityQueueA();
        PriorityQueueA<Float> af = new PriorityQueueA();
        PriorityQueueA<Character> ac = new PriorityQueueA();
        PriorityQueueA<String> as = new PriorityQueueA();

        ArrayList<PriorityQueueA> arrListA = new ArrayList();
        arrListA.add(ai);
        arrListA.add(af);
        arrListA.add(ac);
        arrListA.add(as);


        PriorityQueueB<Integer> bi = new PriorityQueueB();
        PriorityQueueB<Float> bf = new PriorityQueueB();
        PriorityQueueB<Character> bc = new PriorityQueueB();
        PriorityQueueB<String> bs = new PriorityQueueB();
        
        ArrayList<PriorityQueueB> arrListB = new ArrayList();
        arrListB.add(bi);
        arrListB.add(bf);
        arrListB.add(bc);
        arrListB.add(bs);
            
        
        long startTime = System.currentTimeMillis();

        
        try{
            ReadA(inputFile,arrListA);
        }catch(FileNotFoundException e){
            System.err.println("File not found!");
            System.exit(1);
        }
        
        WriteResultsA(outputFile, arrListA);
        
        long endTime = System.currentTimeMillis();

        System.out.println("PriorityQueueA operations took " + (endTime - startTime) + " milliseconds");
        
        
        startTime = System.currentTimeMillis();
        try{
            ReadB(inputFile,arrListB);
        }catch(FileNotFoundException e){
            System.err.println("File not found!");
            System.exit(1);
        }
        WriteResultsB(outputFile, arrListB);
        
        endTime = System.currentTimeMillis();

        System.out.println("PriorityQueueB operations took " + (endTime - startTime) + " milliseconds");
    }
    
    
    /**
     * The methods writes PriorityQueueA to given file
     * @param filename the filename to write
     * @param queArr the array of queue's
     */
    public static void WriteResultsA(String filename, ArrayList<PriorityQueueA> queArr){

        try{
            FileWriter writer = new FileWriter(filename,true);
            for(int i=0; i<queArr.size(); ++i){
                int sizeOfObject = queArr.get(i).size();
                if(sizeOfObject != 0){
                    writer.write(Integer.toString(queArr.get(i).size()));
                    writer.write(',');
                    writer.write(queArr.get(i).toString());
                    writer.write('\n');
                    writer.flush();
                }
            }
            writer.close();
        } catch (IOException ex) {
            System.err.println("File error!");
            System.exit(1);
        }
        
    }
    /**
     * The method's read csv file's line and according to line types it
     * add's the readed elements to array.
     * @param filename the filename to write
     * @param queArray the array of queue's 
     * @throws FileNotFoundException if file can not be found
     */
    public static void ReadA(String filename,ArrayList<PriorityQueueA> queArray) throws FileNotFoundException{
                    
        File file = new File(filename);
        Scanner scanner1 = new Scanner(file);
        String line ;
        Scanner scanner;
        int a;
        float f;
        String temp ;
        while(scanner1.hasNextLine()){
            line = scanner1.nextLine();
            scanner = new Scanner(line);
            scanner.useDelimiter(",|\\n");
            /* Float sayıları tanıtabilmek için yapıldır,eğer yapılmaz ise
             * float sayıları '.' lı değil ',' olarak tanıyor.
             */
            Locale locale = Locale.ENGLISH;
            scanner.useLocale(locale );

            while (scanner.hasNext()){

                if (scanner.hasNextInt()){
                    a = scanner.nextInt();
                    queArray.get(0).add(a);
                }
                else if(scanner.hasNextFloat()){
                    f = scanner.nextFloat();
                    queArray.get(1).add(f);
                }
                else {
                    temp = scanner.next();
                    if(temp.length() == 1)
                        queArray.get(2).add(temp);
                    else
                        queArray.get(3).add(temp);
                }
            }
            System.err.printf("\n");

            scanner.close();
        } 

  
    }
    /**
     * The methods writes PriorityQueueB to given file
     * @param filename the filename to write
     * @param queArr the array of queue's
     */
    public static void WriteResultsB(String filename, ArrayList<PriorityQueueB> queArr){

        try{
        
            FileWriter writer = new FileWriter(filename,true);
            for(int i=0; i<queArr.size(); ++i){
                int sizeOfObject = queArr.get(i).size();
                if(sizeOfObject != 0){
                    writer.write(Integer.toString(queArr.get(i).size()));
                    writer.write(',');
                    writer.write(queArr.get(i).toString());
                    writer.write('\n');
                    writer.flush();
                }
            }
            writer.close();
        } catch (IOException ex) {
            System.err.println("File error!");
            System.exit(1);
        }
        
    }
    /**
     * The method's read csv file's line and according to line types it
     * add's the readed elements to array.
     * @param filename the filename to write
     * @param queArray the array of queue's 
     * @throws FileNotFoundException if file can not be found
     */
    public static void ReadB(String filename,ArrayList<PriorityQueueB> queArray) throws FileNotFoundException{
                    
        File file = new File(filename);
        Scanner scanner1 = new Scanner(file);
        String line ;
        Scanner scanner;
        int a;
        float f;
        String temp ;
        while(scanner1.hasNextLine()){
            line = scanner1.nextLine();
            scanner = new Scanner(line);
            scanner.useDelimiter(",|\\n");
            /* Float sayıları tanıtabilmek için yapıldır,eğer yapılmaz ise
             * float sayıları '.' lı değil ',' olarak tanıyor.
             */
            Locale locale = Locale.ENGLISH;
            scanner.useLocale(locale );

            while (scanner.hasNext()){

                if (scanner.hasNextInt()){
                    a = scanner.nextInt();
                    queArray.get(0).add(a);
                }
                else if(scanner.hasNextFloat()){
                    f = scanner.nextFloat();
                    queArray.get(1).add(f);
                }
                else {
                    temp = scanner.next();
                    if(temp.length() == 1)
                        queArray.get(2).add(temp);
                    else
                        queArray.get(3).add(temp);
                }
            }
            System.err.printf("\n");

            scanner.close();
        } 

  
    }

    /**
     * Checks the deleteMin method of priorityQueue for A and B
     * Integer - A
     * String - B
     * Character - A
     * Float - B
     * için denendi.
     */
    public static void testDeleteMınMethod(){
            System.err.println("Queue of Integer");

        PriorityQueueA<Integer> p = new PriorityQueueA();
        p.add(32);
        p.add(432);
        p.add(2);
        p.add(434332);
        p.add(32455);
        p.add(-56);
        p.add(-57);
        p.add(432);
        p.deleteMin();
        System.err.println(p);
        p.deleteMin();
        System.err.println(p);        p.deleteMin();
        System.err.println(p);        p.deleteMin();
        System.err.println(p);        p.deleteMin();
        System.err.println(p);        p.deleteMin();
        System.err.println(p);        p.deleteMin();
        System.err.println(p);        p.deleteMin();
        System.err.println(p);        

///////////////////////////////////////////////////

        
        System.err.println("Queue of String");
        
        PriorityQueueB<String> s = new PriorityQueueB();
        s.add("ali");
        s.add("zeli");
        s.add("abi");
        s.add("celi");
        s.add("kali");
        s.add("deli");
        s.add("yıldız");
        s.add("furkan");
        System.err.println(s);
        s.deleteMin();
        System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();System.err.println(s);
        s.deleteMin();
        
        ///////////////////////////////////////////////////////////////
        System.err.println("Queue of Character");

        PriorityQueueA<Character> c = new PriorityQueueA();
        c.add('c');
        c.add('z');
        c.add('a');
        c.add('e');
        c.add('h');
        c.add('m');
        c.add('y');
        c.add('z');
        c.add('d');
        System.err.println(c);
        c.deleteMin();
        System.err.println(c);
        c.deleteMin();
        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        System.err.println(c);
        c.deleteMin();        

    /////////////////////////////////////////////////////////////////

        System.err.println("Queue of Float");

        PriorityQueueB<Float> f = new PriorityQueueB();
        f.add(45.7f);
        f.add(4.7f);
        f.add(345.7f);
        f.add(-45.7f);
        f.add(435.7f);
        f.add(15.7f);
        f.add(3.7f);
        System.err.println(f);
        f.deleteMin();System.err.println(f);
        f.remove(15.7f);
        f.deleteMin();System.err.println(f);
        f.deleteMin();System.err.println(f);
        f.deleteMin();System.err.println(f);
        f.deleteMin();System.err.println(f);
        f.deleteMin();System.err.println(f);
        f.deleteMin();

    }
    
}















