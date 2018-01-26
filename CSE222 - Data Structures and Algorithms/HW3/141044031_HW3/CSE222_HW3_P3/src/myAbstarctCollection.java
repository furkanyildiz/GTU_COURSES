import java.util.AbstractCollection;
import java.util.Iterator;

/**
 * The abstract class extends from Java's AbstractCollection
 * @param <E> Instance type
 */
public abstract class myAbstarctCollection<E> extends AbstractCollection<E> {
    /**
     * The method appends any myAbstarctCollection object to any
     * other myAbstarctCollection object by concatenating them.
     * @param other myAbstarctCollection instance object
     * @return the appended Collection.
     */
    public myAbstarctCollection<E> appendAnything(myAbstarctCollection<E> other){

        Iterator iter = other.iterator();
        while(iter.hasNext()){
            this.add((E) iter.next());
        }
        return this;

    }
}
