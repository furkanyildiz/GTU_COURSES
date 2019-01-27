package equations_solver;
/**
 * Solve's the equation of the system.
 * @author yldzf
 *
 */
public interface MethodsOfSolvingLinearEquations {
    /**
     * Abstract method. Solves the linear equation.
     * @return target values x0,x1,...,xn
     * @throws Exception if there is no solution.
     */
    public Double[] solve() throws Exception;


}
