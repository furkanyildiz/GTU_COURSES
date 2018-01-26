package cse222_hw4_p2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Queue;
import java.util.Scanner;

/**
 *
 * @author yldzf
 */
public class _mainTester<E> {

    public static void main(String[] args) {
        
        
        String inputFile = "test.csv";
        String outputFile = "testResult_2.csv";
        
        myQueue<Integer> qi =  new myQueue<>();
        myQueue<Float> qf =  new myQueue<>();
        myQueue<Character> qc =  new myQueue<>();
        myQueue<String> qs =  new myQueue<>();
        ArrayList<myQueue> queArray = new ArrayList();
        
        queArray.add(qi);
        queArray.add(qf);
        queArray.add(qc);
        queArray.add(qs);
        try{
            Read(inputFile,queArray);
        }
        catch(FileNotFoundException e){
            System.err.println("File not found!");
            System.exit(1);
        }
        WriteResults(outputFile,queArray);
        
        System.err.println("2.2 Testing:");
        Queue<String> javaQ = new LinkedList<>();
        javaQ.add("GTU");
        javaQ.add("FuRKaN");
        javaQ.add("YıLdıZ");
        javaQ.add("141044031");
        javaQ.add("Computer");
        
        
        _mainTester test_2 = new _mainTester();
        System.out.println("The queue:");
        System.out.println(javaQ);
        test_2.reverseQueue(javaQ);
        System.out.println("After reverse operation:");
        System.out.println(javaQ);

        
        
        

    }    
    public void reverseQueue(Queue<E> que) {
        if(que.isEmpty())
            return;
        E temp = que.poll();
        if(!que.isEmpty()) 
            reverseQueue(que);
        que.add(temp);
    }
    /**
     * The methods reverses the queues and reverses the queue's columns(it's lines)
     * @param filename the filename to write
     * @param queArr the array of queue's
     */
    public static void WriteResults(String filename, ArrayList<myQueue> queArr){

        try{
        
            FileWriter writer = new FileWriter(filename,true);
            for(int i=queArr.size()-1; i>=0; --i){
                int sizeOfObject = queArr.get(i).getSize();
                if(sizeOfObject != 0){
                    queArr.get(i).reverse();
                    writer.write(Integer.toString(queArr.get(i).getSize()));
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
    public static void Read(String filename,ArrayList<myQueue> queArray) throws FileNotFoundException{
                    
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

}
