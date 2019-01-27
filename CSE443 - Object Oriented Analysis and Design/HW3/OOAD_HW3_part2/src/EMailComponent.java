import java.util.Iterator;

public abstract class EMailComponent {

    /**
     * Add  new EmailComponent
     * @param e EmailComponent
     */
    public void add(EMailComponent e){
        throw new UnsupportedOperationException();
    }
    /**
     * Remove an EmailComponent
     * @param e EmailComponent
     */
    public void remove(EMailComponent e){
        throw new UnsupportedOperationException();
    }

    /**
     * Print EmailComponent information.
     */
    public void print(){
        throw new UnsupportedOperationException();
    }

    /**
     * Returns a child of i th for the component.
     * @param i child number as index
     * @return  a child of i th for the component.
     */
    public EMailComponent getChild(int i){
        throw new UnsupportedOperationException();
    }

    /**
     * Returns an information about EMailComponent
     * @return string as information component.
     */
    public String getInfo(){
        throw new UnsupportedOperationException();
    }

    /**
     * Create an iterator for EMailComponent.
     * @return iterator for EMailComponent
     */
    public abstract Iterator<EMailComponent> createIterator();
}
