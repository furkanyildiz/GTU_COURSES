package numeric_hw2;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author yldzf
 */

public final class GESP {
    /**
     * The matrix array
     */
    private final ArrayList<ArrayList<Double>> matrix;
    /**
     * The dimension of matrix
     */
    private int dimension = 0 ;
    /**
     * The size of a line of augmentedMatrix
     */
    private int augmentedMatrixSize = 0 ;
    
    /**
     * The constructure read file and creates 2 dimentional matrix (with using 
     * ArrayList) then it fills it with reading file and solves the matrix
     * according to Gaussian elimination with scaled partial pivoting method.
     * @param filename the file name of the matrix
     * @throws FileNotFoundException if file is not found
     * @throws ArithmeticException if there is a calculating problem
     * @throws Exception if there is a solving problem
     */
    public GESP(String filename) throws FileNotFoundException, ArithmeticException,Exception {
        Read(filename);
        matrix = new ArrayList<>();
        for(int i=0; i<dimension; ++i)
            matrix.add(new ArrayList<>());
        
        
        ReadAndAdd(filename);
        augmentedMatrixSize = dimension +1 ;
        ScaledPartialPivoting();
        
        try {
            SolveEquation();
        } catch (Exception ex) {
            System.err.println("The equation can not solve!");
            System.exit(0);
        }

    }
    /**
     * The method creates Scale vector for Matrix
     */
    private ArrayList<Double> defineScale(ArrayList<Double> scale)throws ArithmeticException{
        
        for(int i=0; i<dimension; ++i){
            double max = 0.0;
            for(int j=0; j<augmentedMatrixSize-1; ++j){
                if( max < Math.abs(matrix.get(i).get(j)))
                    max =  Math.abs(matrix.get(i).get(j));
            }
            scale.add(max);
        }
        if(scale.contains(0.0))
            throw new ArithmeticException("Scaler vector can not be has zero!");
        return scale;
    }
    /**
     * The method calculates multipler
     * @param a1
     * @param a2
     * @return 
     */
    private Double calculateMultipler(int a1 ,int a2 ){
        return (matrix.get(a1).get(a2)/matrix.get(a2).get(a2));
    }
    /**
     * The method changes given rows
     * @param r1 first row to change
     * @param r2 second row to change
     */
    private void changeRows(int r1,int r2){
        
        ArrayList<Double> temp = new ArrayList();
        
        temp = matrix.get(r1);
        matrix.set(r1, matrix.get(r2));
        matrix.set(r2, temp);
        
    }
    /**
     * The method calculates that which index has maximum number in given list.
     * @param list the list for search max index
     * @return maximum index of list
     */
    private int indexOfMax(List<Double> list){
        Double max = list.get(0);
        int indexOfMax = 0;
        for(int i=1; i<list.size(); ++i)
            if(max < list.get(i)){
                max = list.get(i);
                indexOfMax = i;
            }
        return indexOfMax;
    }
    /**
     * The method checks the given matrixes is upper triangular or not.         
     * @return 
     */
    private boolean isItUpperTriangular(){
        
        boolean isUpperTriangle = true; // be optimistic!
        for (int i = 1; i < dimension && isUpperTriangle; ++i) // rows
            for (int j = 0; j < i && isUpperTriangle; ++j) // columns - see example
                if (matrix.get(i).get(j) != 0) 
                    isUpperTriangle = false;
        return isUpperTriangle;
    }
    /**
     * The method calculates the scalled Partial Pivoting of given metricex
     * @throws Exception 
     */
    private void ScaledPartialPivoting() throws Exception{
        ArrayList<Double> scale = new ArrayList<>();
        ArrayList temp = new ArrayList();
        int maxRow = 0;
        Double multiplier = 1.0;
        for(int i=0; i<dimension; ++i){
            scale = defineScale(scale); 

            for(int j=0; j<augmentedMatrixSize-1; ++j){
                
                temp.add(Math.abs(matrix.get(j).get(i))/scale.get(j));
                
            }

            maxRow = indexOfMax(temp);


            if(maxRow != i)
                changeRows(i,maxRow);
 
            for(int j=i+1; j<matrix.size(); ++j){
                multiplier = calculateMultipler(j, i);
                for(int k=0; k<matrix.get(i).size(); ++k)
                    matrix.get(j).set(k,matrix.get(j).get(k) - multiplier * matrix.get(i).get(k));
                
            }
            if(isItUpperTriangular())
                break;
            
            temp.removeAll(temp);

        }
        if(!isItUpperTriangular()){
            throw new Exception("The system has no unique solition!");
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
        
        for(int i=0; i<xArray.size();++i)
            if( i != index)
                result.add(aVectorOfMatrix.get(i)*xArray.get(i));
        
        for(int i=0; i<result.size(); ++i)
            resultSum +=result.get(i);
        
        return resultSum;
    }
    /**
     * The method find the matrixes root (After the has done matricex Gaussian 
     * elimination with scaled partial pivoting)
     * @throws Exception when there is a error in finding roots
     */
    private void SolveEquation() throws Exception{
        ArrayList<Double> x = new ArrayList();
        for(int i=0; i<dimension; ++i)
            x.add(1.0);
        
        for(int i=dimension-1; i>=0; --i){
            double b = multipleArrays(matrix.get(i),x,i);
            double a = matrix.get(i).get(i);
            double c = matrix.get(i).get(dimension);
            double d = (c-b)/a;

            x.set(i, d);
            
        }
        for(int i=0; i<x.size(); ++i)
            System.out.printf(" x%d: %s",i,x.get(i));
        System.out.println();
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
    /**
     * The method returns String represantation of the object
     * @return  String represantation of the object
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
//        System.err.printf("denk:%d\n",augmentedMatrixSize);
//        System.err.printf("denksss:%d\n",dimension);
        for(int i=0; i<matrix.size(); ++i){
            for(int j=0; j<matrix.get(i).size(); ++j){
                sb.append(matrix.get(i).get(j)).append(" ");
            }
            sb.append('\n');

        }
        return sb.toString(); 
    }
}
