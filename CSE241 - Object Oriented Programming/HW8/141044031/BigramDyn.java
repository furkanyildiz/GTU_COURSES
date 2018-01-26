
import FurkanTemplateLib.FMap;
import FurkanTemplateLib.FPair;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
@SuppressWarnings({"rawtypes", "unchecked"})

/**
 *
 * @author yldzf
 * @param <T>
 */
public class BigramDyn<T> implements Bigram<T> {
    private FMap<FPair<?,?>,Integer> map;
    private int DataType=2;
    //No param constructure calls int param constructure.
    public BigramDyn(){
        this(2);
    }
    //int param(int value is datatype) constucture creates a map object.
    public BigramDyn(int op){
        DataType= op;
        map = new FMap<FPair<?,?>,Integer>();
    }
    //Copy constructure
	public BigramDyn(BigramDyn other)throws Exception{
    	if(other == null){
    		FException fatalError = new FException("Fatal Error");
    		throw fatalError;
    	}
    	this.map= new FMap(other.map);
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
        for(int i=0; i<map.getUsed(); ++i)
            sum += map.getVal(i);
        return sum;
    }
    //This method takes two elements as Bigrams and returns the number of that 
    //so far
    public int numOfGrams(T val1, T val2) {
        FPair<T,T> temp = new FPair<T,T>(val1,val2);
        for(int i=0; i<map.getUsed(); ++i)
            if(map.getKey(i).equals(temp))
                return map.getVal(i);
        return 0;
    }
    //This method prints all Bigrams occurences decreasing occurency order.
    public String toString(){
        StringBuilder sb = new StringBuilder();

        for(int i=0; i<map.getUsed(); ++i){
           	sb.append(map.getKey(i)).append(" - ").append(map.getVal(i));
       		sb.append("\n");
       	}
        //Mapin son elemanındaki "\n" karakterini siliyoruz, güzel bir çıktı 
        //elde edebilmek için
        sb.deleteCharAt(sb.length()-1);
        return sb.toString();
    }
    //This method calculates Bigrams for integers
    private void CalculateBigramINT(Scanner inputStream)throws FException{
        int a = 0,b = 0;
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
                int found = 0;
                if(map.search(temp)!=null)
                    found = map.search(temp).getSecond();
                if(found == 0)
                    map.put(temp, 1);
                else
                    map.search(temp).setSecond(++found);
            }
            else{
                FException badData = new FException("Bad Data");
                throw badData;
            }
            a=b;
        }
        
    }
    //This method calculates Bigrams for strings
    private void CalculateBigramSTR(Scanner inputStream)throws FException{
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
                int found = 0;
                if(map.search(temp)!=null)
                    found = map.search(temp).getSecond();
                if(found == 0)
                    map.put(temp, 1);
                else
                    map.search(temp).setSecond(++found);
                
            }
            else{
                FException badData = new FException("Bad Data");
                throw badData;
            }
           a=b;
        }
    }
    //This method calculates Bigrams for doubles
    private void CalculateBigramDOB(Scanner inputStream)throws FException{
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
                int found = 0;
                if(map.search(temp)!=null)
                    found = map.search(temp).getSecond();
                if(found == 0)
                    map.put(temp, 1);
                else
                    map.search(temp).setSecond(++found);
                
            }
            else{
                FException badData = new FException("Bad Data");
                throw badData;
            }
          	 a=b;
        }
    }
}