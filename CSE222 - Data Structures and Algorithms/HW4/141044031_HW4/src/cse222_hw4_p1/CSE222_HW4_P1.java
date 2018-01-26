package cse222_hw4_p1;

/**
 *
 * @author yldzf
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Locale;


public class CSE222_HW4_P1<E> {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException {
     
        String inputFile = "5bin.csv";
        String outputFile = "testResult_1.csv";
        ArrayList<StackInterface> StackInterfaceArrayA = new ArrayList();
        ArrayList<StackInterface> StackInterfaceArrayB = new ArrayList();
        ArrayList<StackInterface> StackInterfaceArrayC = new ArrayList();
        ArrayList<StackInterface> StackInterfaceArrayD = new ArrayList();

        StackInterface<Integer> a1 = new StackA<>();
        StackInterface<Float> a2 = new StackA<>();
        StackInterface<Character> a3 = new StackA<>();
        StackInterface<String> a4 = new StackA<>();

        StackInterface<Integer> b1 = new StackB<>();
        StackInterface<Float> b2 = new StackB<>();
        StackInterface<Character> b3 = new StackB<>();
        StackInterface<String> b4 = new StackB<>();

        StackInterface<Integer> c1 = new StackC<>();
        StackInterface<Float> c2 = new StackC<>();
        StackInterface<Character> c3 = new StackC<>();
        StackInterface<String> c4 = new StackC<>();

        StackInterface<Integer> d1 = new StackD<>();
        StackInterface<Float> d2 = new StackD<>();
        StackInterface<Character> d3 = new StackD<>();
        StackInterface<String> d4 = new StackD<>();

        StackInterfaceArrayA.add(a1);
        StackInterfaceArrayA.add(a2);
        StackInterfaceArrayA.add(a3);
        StackInterfaceArrayA.add(a4);

        StackInterfaceArrayB.add(b1);
        StackInterfaceArrayB.add(b2);
        StackInterfaceArrayB.add(b3);
        StackInterfaceArrayB.add(b4);

        StackInterfaceArrayC.add(c1);
        StackInterfaceArrayC.add(c2);
        StackInterfaceArrayC.add(c3);
        StackInterfaceArrayC.add(c4);

        StackInterfaceArrayD.add(d1);
        StackInterfaceArrayD.add(d2);
        StackInterfaceArrayD.add(d3);
        StackInterfaceArrayD.add(d4);


        
        long startTime = System.currentTimeMillis();

        /**
         * Read from file and push items for Stack A and then write it to file
         */
        Read(inputFile,StackInterfaceArrayA);
        WriteResults(outputFile,StackInterfaceArrayA);
        
        long endTime = System.currentTimeMillis();

        System.out.println("Stack A operations took " + (endTime - startTime) + " milliseconds");
        
        startTime = System.currentTimeMillis();
        /**
         * Read from file and push items for Stack B and then write it to file
         */
        Read(inputFile,StackInterfaceArrayB);
        WriteResults(outputFile,StackInterfaceArrayB);

        endTime = System.currentTimeMillis();
        System.out.println("Stack B operations took " + (endTime - startTime) + " milliseconds");

        startTime = System.currentTimeMillis();
        
        /**
         * Read from file and push items for Stack C and then write it to file
         */
        Read(inputFile,StackInterfaceArrayC);
        WriteResults(outputFile,StackInterfaceArrayC);
        
        
        endTime = System.currentTimeMillis();
        System.out.println("Stack C operations took " + (endTime - startTime) + " milliseconds");

        startTime = System.currentTimeMillis();
        /**
         * Read from file and push items for Stack D and then write it to file
         */
        Read(inputFile,StackInterfaceArrayD);
        WriteResults(outputFile,StackInterfaceArrayD);
        
        endTime = System.currentTimeMillis();
        System.out.println("Stack D operations took " + (endTime - startTime) + " milliseconds");
        
    }
    
 
    /**
     * Writes given stack array's objects  to given file.
     * @param filename the name of the output file
     * @param stackArr the array of stack's
     */
    public static void WriteResults(String filename, ArrayList<StackInterface> stackArr){

        try{
        
            FileWriter writer = new FileWriter(filename,true);
            for(int i=0;  i<stackArr.size(); ++i){
                int sizeOfObject = stackArr.get(i).getSize();
                if(sizeOfObject != 0){
                    writer.write(Integer.toString(sizeOfObject));
                    writer.write(',');
                    writer.write(stackArr.get(i).toString());
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
    public static void Read(String filename,ArrayList<StackInterface> stackArr) throws FileNotFoundException{
                    
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
                    stackArr.get(0).push(a);
                }
                else if(scanner.hasNextFloat()){
                    f = scanner.nextFloat();
                    stackArr.get(1).push(f);
                }
                else {
                    temp = scanner.next();
                    if(temp.length() == 1)
                        stackArr.get(2).push(temp);
                    else
                        stackArr.get(3).push(temp);
                }
            }
            System.err.printf("\n");

            scanner.close();
        } 

  
    }
}
