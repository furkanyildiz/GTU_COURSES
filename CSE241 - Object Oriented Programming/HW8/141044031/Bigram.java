import java.io.FileNotFoundException;

/**
 *
 * @author yldzf
 */
interface Bigram<T> {
    public void readFile(String filename)throws FileNotFoundException,Exception;
    public int numGrams();
    public int numOfGrams(T val1, T val2);
    public String toString();
}
