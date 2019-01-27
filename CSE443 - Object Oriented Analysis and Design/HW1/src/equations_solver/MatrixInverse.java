package equations_solver;
import java.util.Arrays;


/**
 * The class solves linear equations with Matrix Inverse method.
 */
class MatrixInverse implements MethodsOfSolvingLinearEquations {
    /**
     * The matrix array
     */
    private final Double[][] matrix;
    /**
     * Equations of array.
     */
    private final Double[][] equation;
    /**
     * The results of linear equations.
     */
    private final Double[][] result ;
    /**
     * The equations readed from GUI.
     */
    private String[] equations;
    /**
     * The dimension of matrix
     */
    private int dimension = 0 ;

    /**
     * Read String array, call to fill matrix function and parses it equation and result matrixes.
     * @param equations Each string is a one equation. Equation contains result.
     */
    public MatrixInverse(String[] equations) {
        this.equations = equations;
        dimension = equations.length;

        equation = new Double[dimension][dimension];
        result = new Double[dimension][1];

        matrix = new Double[dimension][dimension+1];

        fill_matrix();


        parse_equation_and_result();


    }

    /**
     * According to readed string fills the matrix.
     */
    private void fill_matrix() {
        String sequation;
        int f = 0;
        for(int i = 0; i< dimension; ++i) {
            sequation = equations[i];
            String[] equ = sequation.split(",");
            f = 0;
            for(String s: equ) {

                matrix[i][f] = Double.parseDouble(s);
                ++f;
            }

        }

    }
    /**
     * Parses the matrix as equations and results.
     */
    private void parse_equation_and_result() {
        //Parse Equation Matrix and Results.
        for(int i=0; i< matrix.length; ++i) {
            for(int j =0; j< matrix.length; ++j) {
                equation[i][j] = matrix[i][j];
            }

            result[i][0] = matrix[i][matrix.length];

        }
    }


    /**
     * Solves the linear equations.
     * @param equation linear equation matrix
     * @param result results of linear equations
     * @return Solution of the equation.
     * @throws ArithmeticException if the determinant is zero
     */
    private  Double[][] inverse_method(Double[][] equation,Double[][] result)throws ArithmeticException {
        double det = determinant();
        if (det == 0.0)
            throw new ArithmeticException("No Inverse!");

        Double[][] inv = inverse_(equation);
	    /*
	    System.out.println("inv:");
	    for (Double[] row : inv) System.out.println(java.util.Arrays.toString(row));
	    System.out.println("res:");
	    for (Double[] row : result) System.out.println(java.util.Arrays.toString(row));
        */

        return matrixMult(inv,result);


    }

    /**
     * Mult two matrices.
     * @param A first matrix
     * @param B second matrix
     * @return multiplication of two matrices.
     */
    private Double[][] matrixMult(Double[][] A, Double[][] B) {

        if (A[0].length != B.length)
            throw new ArithmeticException("A's row not match B's colums!");


        Double[][] C = new Double[dimension][1];
        //initialize C because we will sum its items.
        for (int i = 0; i < dimension; i++)
            Arrays.fill( C[i], 0.0);



        // Each A's row should mult with each B row than plus them.
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                C[i][0] += A[i][j] * B[j][0];


        return C;
    }




    /**
     * The method changes given rows
     * @param r1 first row to change
     * @param r2 second row to change
     */
    private void changeRows(int r1,int r2){

        Double[] temp = new Double[matrix[0].length];

        temp = matrix[r1];
        matrix[r1] = matrix[r2];
        matrix[r2] = temp;

    }




    /**
     * Calculates inverse of matrix with Gauss Jordan technique
     * @param A matrix
     * @return inverse of matrix.
     */
    private Double[][] inverse_(Double[][] A){

        double diag,temp;

        Double[][] B = new Double[dimension][dimension];

        for(int i=0; i<dimension; ++i)
            for(int j=0; j<dimension; ++j)
                B[i][j] = (i == j ? 1.0 : 0.0);


        for(int i=0; i<dimension; ++i) {
            diag=A[i][i];
            for (int j = 0; j<dimension; ++j) {
                A[i][j] = A[i][j] / diag;
                B[i][j] = B[i][j] / diag;
            }
            for(int m=0; m<dimension; ++m) {
                if(m!=i) {
                    temp = A[m][i];
                    for(int j=0; j<dimension; ++j) {
                        A[m][j] = A[m][j] - (A[i][j] * temp);
                        B[m][j] = B[m][j] - (B[i][j] * temp);
                    }

                }

            }


        }

        return B;

    }
    //Some helped from https://www.sanfoundry.com/java-program-compute-determinant-matrix/
    /**
     * Calculates detarminant of given Matrix.
     * @return determinant value of the matrix.
     */
    // Some helped from http://easy-learn-c-language.blogspot.com.tr/2013/02/numerical-methods-determinant-of-nxn.html
    private double determinant(){
        Double[][] matrixCopy = new Double[dimension][dimension];
        double determinantOfMatrix = 1.0;

        for(int i =0; i<dimension; ++i)
            for(int j=0; j<dimension; ++j)
                matrixCopy[i][j] = matrix[i][j];

        for(int i = 0; i<dimension; ++i)
            for(int j = 0; j<dimension; ++j)
                if(j>i){

                    double r = matrixCopy[j][i]/matrixCopy[i][i];
                    for(int k = 0; k < dimension; k++)
                        matrixCopy[j][k] -= r * matrixCopy[i][k];

                }


        for(int i = 0; i < dimension; i++)
            determinantOfMatrix *= matrixCopy[i][i];

        return determinantOfMatrix ;

    }



    /**
     * Abstract method. Solves the linear equation.
     * @return target values x0,x1,...,xn
     * @throws Exception if there is no solution.
     */
    @Override
    public Double[] solve()throws Exception {

        Double[][] solution = inverse_method(matrix,result);
        Double[] res = new Double[solution.length];
        for(int i=0; i<solution.length; ++i)
            res[i] = solution[i][0];

        return res;
    }

}