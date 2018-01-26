import java.io.*;
import java.util.LinkedList;

public class mainTester {
    public static void main(String[] args) throws FileNotFoundException {

        myStringBuilder msb = new myStringBuilder();

        try {
            msb = readToFile("numbers.txt");
            String result1 = msb.toString();
            String result2 = msb.toString2();
            String result3 = msb.toString3();
            writeToFile("result1.txt",result1);
            writeToFile("result2.txt",result2);
            writeToFile("result3.txt",result3);
        } catch (IOException e) {
            System.err.println("Exception handled!");

        }

    }

    /**
     * To write a file given strings
     * @param filename filename
     * @param str string which will be writing to file.
     * @throws IOException if file is not found.
     */
    public static void writeToFile(String filename,String str) throws IOException {

        try {
            FileWriter writer = new FileWriter(filename, true);
            writer.write(str);
            writer.close();

        } catch (IOException e) {
            throw e;
        }

    }

    /**
     * To read a file
     * @param filename file name
     * @return myStringBuilder object with appended values from file.
     * @throws IOException if file is not found.
     */
    public static myStringBuilder readToFile(String filename) throws IOException {
        InputStream in = new FileInputStream(new File(filename));
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        myStringBuilder out = new myStringBuilder();
        String line;
        int i =0;
        try {
            while ((line = reader.readLine()) != null) {
                out.append(line);
                System.out.println(i++);
            }
            reader.close();

        }
        catch (IOException e){
            throw  e;
        }
        return out;
    }

}
