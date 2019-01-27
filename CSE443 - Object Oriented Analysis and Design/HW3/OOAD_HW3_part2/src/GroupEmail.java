import javax.swing.border.EmptyBorder;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class GroupEmail extends EMailComponent {

    /**
     * Iterator to iterate group mails.
     */
    private Iterator<EMailComponent> iterator;
    /**
     * List to store group's mails.
     */
    private List<EMailComponent> emails;
    /**
     * Name of the group.
     */
    private String  nameOfOwner;

    /**
     * Creates a group with group name.
     * @param owner
     */
    public GroupEmail(String owner){
        this.emails = new ArrayList();
        this.nameOfOwner = owner;
        this.iterator = null;
    }

    /**
     * Returns name of the group.
     * @return name of the group.
     */
    public String getNameOfOwner(){
        return this.nameOfOwner;
    }

    /**
     * Add  new EmailComponent
     * @param e EmailComponent
     */
    @Override
    public void add(EMailComponent e){
        emails.add(e);
    }
    /**
     * Remove an EmailComponent
     * @param e EmailComponent
     */
    @Override
    public void remove(EMailComponent e){
        emails.remove(e);
    }
    /**
     * Returns a child of i th for the component.
     * @param i child number as index
     * @return  a child of i th for the component.
     */
    @Override
    public EMailComponent getChild(int i){
        return emails.get(i);
    }

    /**
     * Print group's information with it's all emails.
     */
    @Override
    public void print(){
        System.out.println(getInfo() );

        Iterator<EMailComponent> iter = emails.iterator();
        while (iter.hasNext()){
            EMailComponent mail = (EMailComponent)iter.next();
            mail.print();
        }
        System.out.println("-----------"+ getNameOfOwner());



    }

    /**
     * Creates an iterator for the group.
     * @return an iterator for the group.
     */
    @Override
    public Iterator<EMailComponent> createIterator() {
        if (iterator == null)
            iterator =  new CompositeIterator(emails.iterator());

        return iterator;
    }

    /**
     * Returns an information about the group.
     * @return an information about the group.
     */
    @Override
    public String getInfo() {
        return "\nGroup Name is:" + getNameOfOwner() ;
    }
}
