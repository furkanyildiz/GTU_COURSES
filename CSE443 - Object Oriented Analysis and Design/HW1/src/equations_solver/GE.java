package equations_solver;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * The class solves linear equations with Gaussian Elimination Scaled Partial Pivoting
 * @author yldzf
 */

public final class GE implements MethodsOfSolvingLinearEquations{
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
     * The constructure reads the equation and converts it to Matrix.
     * @param equation linear equations.
     * @throws ArithmeticException if there is a calculating problem
     * @throws Exception is there is no solution
     */
    public GE(String[] equation) throws  ArithmeticException,Exception {

        String filename = "equations.txt";
        dimension = equation.length;
        //write equation to file

        write(filename,equation);


        matrix = new ArrayList<>();
        for(int i=0; i<dimension; ++i)
            matrix.add(new ArrayList());


        ReadAndAdd(filename);
        File here = new File("");
        System.out.println(here.getAbsolutePath());

        File file = new File(here.getAbsolutePath()+ "\\"+filename);
        if(file.exists())
            file.delete();
        augmentedMatrixSize = dimension +1 ;

    }

    private void write(String filename,String[] equation) throws IOException {

        FileWriter f0 = new FileWriter(filename);

        for(int i = 0 ; i<dimension; ++i) {
            f0.write(equation[i]);
            if (i!= dimension - 1)
                f0.write("\n");

        }

        f0.close();

    }


    /**
     * The method creates Scale vector for Matrix
     * @param scale Matrix total scale vector.
     * @return scale value.
     * @throws ArithmeticException if scalar is 0.
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
     * @return multipler
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
     * The method checks the given matrices is upper triangular or not.
     * @return true if the matrix is upper triangular, otherwise false.
     */
    private boolean isItUpperTriangular(){

        boolean isUpperTriangle = true;
        for (int i = 1; i < dimension && isUpperTriangle; ++i)
            for (int j = 0; j < i && isUpperTriangle; ++j)
                if (matrix.get(i).get(j) != 0)
                    isUpperTriangle = false;
        return isUpperTriangle;
    }
    /**
     * The method calculates the scalled Partial Pivoting of given metricex
     * @throws ArithmeticException if solution is no unique
     */
    private void ScaledPartialPivoting() throws ArithmeticException{
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
            //System.out.println("no uniqe");
            throw new ArithmeticException("The system has no unique solition!");
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
    private Double[]  SolveEquation() throws Exception{
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
        Double[] results = new Double[x.size()];

        int f = 0;
        for(Double sol:x)
            results[f++] = sol;



        for(int i=0; i<results.length;++i) {
            //System.out.println(results[i]);
            if (results[i] == Double.POSITIVE_INFINITY || results[i] == Double.NEGATIVE_INFINITY || results[i].isNaN() )
                throw new Exception("No solution");
        }

        return results;
    }
    /**
     * The function read files and fills the matrix
     * @param filename the name of file to read
     * @throws FileNotFoundException if there is no file
     */
    private void ReadAndAdd(String filename)throws FileNotFoundException{

        File file = new File(filename);
        Scanner scanner1 = new Scanner(file);
        String line ;
        int index = 0;

        while(scanner1.hasNextLine()){
            line = scanner1.nextLine();
            String[] str_array = line.split(",");
            for(String s: str_array)
                matrix.get(index).add(Double.parseDouble(s));

            ++index;
        }
        scanner1.close();

    }
    /**
     * The method read's file and calcualtes the metrix of dimension
     * @param filename the name of the file
     * @throws FileNotFoundException if file is not found
     */
    private void Read(String filename) throws FileNotFoundException{

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

    /**
     * This method solves the linear equation
     * @return target x0,x1,...,xn
     * @throws Exception if there is no solution.
     */
    @Override
    public Double[] solve() throws ArithmeticException,Exception {
        //System.out.println(this.toString());

        ScaledPartialPivoting();
        return SolveEquation();

    }
}
