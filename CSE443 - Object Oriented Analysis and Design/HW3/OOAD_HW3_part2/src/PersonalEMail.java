import java.util.Iterator;

public class PersonalEMail extends EMailComponent {

    /**
     * Name of owner of the email.
     */
    private String nameOfOwner;
    /**
     * Email address.
     */
    private String emailAdress;

    /**
     * Creates an email with its owner.
     * @param name owner of email.
     * @param adress email address.
     */
    public PersonalEMail(String name,String adress) {
        this.nameOfOwner = name;
        this.emailAdress = adress;
    }

    /**
     * Returns owner of email.
     * @return owner of email.
     */
    public String getNameOfOwner(){
        return this.nameOfOwner;
    }

    /**
     * Returns email address.
     * @return email address.
     */
    public String getEmailAdress(){
        return this.emailAdress;
    }


    /**
     * Print group's information with it's all emails.
     */
    @Override
    public void print(){
        System.out.println(getInfo());
    }

    /**
     * Creates an iterator for the group.
     * @return an iterator for the group.
     */
    @Override
    public Iterator<EMailComponent> createIterator() {
        return new NullIterator();
    }
    /**
     * Returns an information about the group.
     * @return an information about the group.
     */
    @Override
    public String getInfo() {
        return getEmailAdress() +" " + getNameOfOwner();
    }
}
