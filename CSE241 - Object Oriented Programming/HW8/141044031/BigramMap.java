import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;
import FurkanTemplateLib.FPair;
import java.io.*;
/**
 *
 * @author yldzf
 * @param <T>
 */
public class BigramMap<T> implements Bigram<T> {

    private int DataType=2;
    private Map<FPair<?,?>,Integer> map;
    //No param constructure creates a HashMap object.
    public BigramMap() {
        this.map = new HashMap<>(23);
    }
    //int param constructure creates a HashMap object.
    public BigramMap(int _Datatype) {
        this.map = new HashMap<>(23);
        DataType=_Datatype;
    }
    //This method takes a filename as a String param and read the file, 
    //calculates all the bigrams. Throws exception if there are problems with 
    //opening and reading file
    public void readFile(String filename)throws FileNotFoundException,Exception{
        Scanner inputStream = null;
        try{
            inputStream = new Scanner(new FileInputStream(filename));
            switch (DataType) {
                case 1:
                    CalculateBigramINT(inputStream);
                    break;
                case 2:
                    CalculateBigramSTR(inputStream);
                    break;
                case 3:
                    CalculateBigramDOB(inputStream);
                    break;
                default:
                    break;
            }
            sortByValue();
        }
        catch(FileNotFoundException e){
            throw e;
        }
        catch(FException e){
            throw e;
        }
        finally{
            if(inputStream != null)
                inputStream.close();
        }
    }
    //This method returns the total number of Bigrams
    public int numGrams() {
        int sum = 0;
        for (Map.Entry<FPair<?, ?>, Integer> entry : map.entrySet())
            sum+=entry.getValue();

        return sum;
        
    }
    //This method takes two elements as Bigrams and returns the number of that 
    //so far
    public int numOfGrams(T val1, T val2) {
        FPair<T,T> temp = new FPair<>(val1,val2);
        return map.get(temp) != null ? map.get(temp) : 0;
    }
    //This method prints all Bigrams occurences decreasing occurency order.
    public String toString(){
        StringBuilder sb = new StringBuilder();

        for (Map.Entry<FPair<?, ?>, Integer> entry : map.entrySet()){
            sb.append(entry.getKey()).append(" - ").append(entry.getValue());
            sb.append("\n");
        }
        //Mapin son elemanındaki "\n" karakterini siliyoruz, güzel bir çıktı 
        //elde edebilmek için
        sb.deleteCharAt(sb.length()-1);
        return sb.toString();
    }
    //This method sortes map occurences decreasing occurency order.
    private void sortByValue() {
        // Convert Map to List of Map
        List<Map.Entry<FPair<?,?>,Integer>> list =
                new LinkedList<>(map.entrySet());

        // Sort list with a custom comparator
        Collections.sort(list, new Comparator<Map.Entry<FPair<?, ?>,Integer>>(){
        public int compare(Map.Entry<FPair<?, ?>,Integer> o1,
                           Map.Entry<FPair<?, ?>,Integer> o2) {
            return (o2.getValue()).compareTo(o1.getValue());
        }
        });
        //put it into a new datas Map LinkedHashMap
        Map<FPair<?,?>,Integer> sortedMap = new LinkedHashMap<>();
        for (Iterator<Map.Entry<FPair<?, ?>,Integer>> it = list.iterator(); 
                                                            it.hasNext(); ) {
            Map.Entry<FPair<?, ?>,Integer> entry = it.next();
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        map=sortedMap;
    }
    //This method calculates Bigrams for integers
    private void CalculateBigramINT(Scanner inputStream) throws FException{
        Integer a = 0,b = 0;
        if (inputStream.hasNextInt())
           a=inputStream.nextInt();
        
        else{
            FException errorFile = new FException("Reading file error.");
            throw errorFile;
        }

        while (inputStream.hasNext()) {
            if (inputStream.hasNextInt()){
                b=inputStream.nextInt();
                FPair<Integer,Integer> temp = new FPair<Integer,Integer>(a,b);
                if(map.get(temp)==null)
                    map.put(temp,1);
                else{
                    int value = map.get(temp);
                    ++value;
                    map.put(temp,value);
                }
            }
            else{
                FException badData = new FException("Bad Data");
                throw badData;
            }
            a=b;
        }
    }
    //This method calculates Bigrams for strings
    private void CalculateBigramSTR(Scanner inputStream) throws FException{
        String a = null,b = null;
        if (inputStream.hasNext())
            a=inputStream.next();
        
        else{
            FException errorFile = new FException("Reading file error.");
            throw errorFile;
        }
        while (inputStream.hasNext()) {
            if (inputStream.hasNext()){
                b=inputStream.next();
                FPair<String,String> temp = new FPair<String,String>(a,b);
                if(map.get(temp)==null)
                   map.put(temp,1);
                else{
                   int value = map.get(temp);
                   ++value;
                   map.put(temp,value);
                }
            }
            else{
                FException badData = new FException("Bad Data");
                throw badData;
            }
            a=b;
        }    
    }
    //This method calculates Bigrams for doubles
    private void CalculateBigramDOB(Scanner inputStream) throws FException{
        double a = 0.0 ,b = 0.0;
        if (inputStream.hasNextDouble())
           a=inputStream.nextDouble();
        else{
            FException errorFile = new FException("Reading file error.");
            throw errorFile;
        }
        while (inputStream.hasNext()) {
            if (inputStream.hasNextDouble()){
                b=inputStream.nextDouble();
                FPair<Double,Double> temp = new FPair<Double,Double>(a,b);
                if(map.get(temp)==null)
                    map.put(temp,1);
                else{
                    int value = map.get(temp);
                    ++value;
                    map.put(temp,value);
                }
            }
            else{
                FException badData = new FException("Bad Data");
                throw badData;
            }
            a=b;
        }
    }
}