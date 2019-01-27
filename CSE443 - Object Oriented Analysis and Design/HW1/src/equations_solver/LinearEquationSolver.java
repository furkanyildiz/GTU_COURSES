package equations_solver;

/**
 * This is the linear equation solver class. It takes a method and solves them.
 * @author yldzf
 */
public class LinearEquationSolver {

    /**
     * Solving method of linear equation.
     */
    private MethodsOfSolvingLinearEquations methods;

    /**
     * Constructor of the class. Saves the method.
     * @param m solving method.
     */
    public LinearEquationSolver(MethodsOfSolvingLinearEquations m) {

        methods = m;

    }

    /**
     * Solves the linear equation.
     * @return target values x0,x1,...,xn
     * @throws ArithmeticException if there is calculating error.
     * @throws Exception if there is no solution.
     */
    public Double[] solv() throws ArithmeticException,Exception{
        return methods.solve();
    }

}
