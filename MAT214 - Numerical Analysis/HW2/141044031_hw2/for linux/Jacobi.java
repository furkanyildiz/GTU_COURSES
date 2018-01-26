import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

/**
 *
 * @author yldzf
 */
public final class Jacobi {
    /**
     * Matrix which is readed from file.
     */
    private final ArrayList<ArrayList<Double>> matrix;
    /**
     * The dimension of matrix
     */
    private int dimension = 0 ;

    /**
     * The constructure read file and creates 2 dimentional matrix (with using 
     * ArrayList) then it fills it with reading file and solves the matrix
     * according to Jacobi method.
     * @param filename the file name of the matrix
     * @throws FileNotFoundException if file is not found
     * @throws Exception if there is a problem when calculating.
     */
    Jacobi(String filename) throws FileNotFoundException,Exception{
        Read(filename);
        matrix = new ArrayList<>();
        for(int i=0; i<dimension; ++i)
            matrix.add(new ArrayList());
        
        ReadAndAdd(filename);
        
        try {
            Jacobi();
        } catch (Exception ex) {
            throw ex;
        }
        
        
    }
    /**
     * The method calculates roots of matrix, according to Jacobi, max 100 iterations
     * @throws Exception if iteration number is equal to 100
     */
    private void Jacobi() throws Exception{
        
        
        ArrayList<Double> m1 = new ArrayList<>();
        ArrayList<Double> m2 = new ArrayList<>();
        double epsilon = 0.001;
        
        for(int i=0; i<dimension; ++i)
            m1.add(0.0);
        int iteartionNumber = 0;
        boolean found = false;
        while(!found){
            
            for(int i=0; i<dimension & !found; ++i){
                
                double a = multipleArrays(matrix.get(i),m1,i);
                double b = matrix.get(i).get(dimension);
                double c = matrix.get(i).get(i);
                double d = (b-a)/c;

                m2.add(d);
                
                if( epsilon > ( (Math.abs(Collections.max(m2)- Collections.max(m1)))/(Math.abs(Collections.max(m2)))  ) ) 
                    found = true;
                
            }
            if(found)
                for(int k=0; k<m1.size(); ++k)
                    System.out.printf("x%d:%s\n",k,m1.get(k));
            
            m1 = (ArrayList<Double>) m2.clone();
            m2.removeAll(m2);
            iteartionNumber++;
            
            if(iteartionNumber == 100){
                throw new Exception("It can not be calculated!");
            }
        }
    }
    /**
     * The method multiples given vectors except given index of vector
     * @param aVectorOfMatrix given matrix of main Matrix
     * @param xArray solition of X vector
     * @param index the index which will be not calculate
     * @return sum of the result vectors entiries
     * @throws Exception When size are not equal for multipication
     * 
     */
    private double multipleArrays(ArrayList<Double> aVectorOfMatrix, ArrayList<Double> xArray, int index) throws Exception{
        if(aVectorOfMatrix.size()-1 != xArray.size())
            throw new Exception("Size are not equal for multipication");
        ArrayList<Double> result = new ArrayList<>();
        double resultSum = 0.0;
        
        for(int i=0; i<xArray.size(); ++i)
            if( i != index)
                result.add(aVectorOfMatrix.get(i)*xArray.get(i));
        
        for(int i=0; i<result.size(); ++i)
            resultSum +=result.get(i);
        
        return resultSum;
    }
    /**
     * The function read files and fills the matrix
     * @param filename the name of file to read
     * @throws FileNotFoundException if there is no file
     */
    public void ReadAndAdd(String filename)throws FileNotFoundException{
                    
        File file = new File(filename);
        Scanner scanner1 = new Scanner(file);
        String line ;
        Scanner scanner;
        int index = 0;

        while(scanner1.hasNextLine()){
            line = scanner1.nextLine();
            String[] str_array = line.split(",");
            for(String s: str_array)
                matrix.get(index).add(Double.parseDouble(s));

            ++index;
        }
    }
    /**
     * The method read's file and calcualtes the metrix of dimension
     * @param filename the name of the file
     * @throws FileNotFoundException if file is not found
     */
    public void Read(String filename) throws FileNotFoundException{
                    
        File file = new File(filename);
        Scanner scanner1 = new Scanner(file);
        String line ;
        Scanner scanner;

        while(scanner1.hasNextLine()){
            line = scanner1.nextLine();
            ++dimension;
        }
    }
 
}
