import java.util.Iterator;
import java.util.Stack;

public class CompositeIterator implements Iterator {

    /**
     * iterator.
     */
    Iterator<EMailComponent> iterator;
    /**
     * Stack, to store iterators.
     */
    Stack<Iterator<EMailComponent>> stack;

    /**
     * Creates an iterator.
     * @param iter iterator.
     */
    public CompositeIterator(Iterator iter){
        iterator = iter;
        stack = new Stack<Iterator<EMailComponent>>();
        stack.push(iterator);
    }

    /**
     * Check there is an item in next of the iterator.
     * @return true if there is an item next.
     */
    @Override
    public boolean hasNext() {

        if (stack.empty())
            return false;
        else{
            Iterator<EMailComponent> mailIter = stack.peek();
            if (mailIter.hasNext())
                return true;
            else{
                stack.pop();
                return hasNext();
            }
        }
    }

    /**
     * Returns next item of iterator.
     * @return next item of iterator.
     */
    @Override
    public Object next() {

        if (hasNext()){
            Iterator<EMailComponent> iter = stack.peek();
            EMailComponent com = iter.next();
            if (com instanceof GroupEmail)
                stack.push(com.createIterator());
            return com;
        }
        else
            return null;

    }
}
