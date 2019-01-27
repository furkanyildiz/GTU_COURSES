import java.util.Iterator;

public class NullIterator implements Iterator {
    /**
     * Returns always false.
     * @return false.
     */
    @Override
    public boolean hasNext() {
        return false;
    }

    /**
     * Returns null.
     * @return null.
     */
    @Override
    public Object next() {
        return null;
    }
}
