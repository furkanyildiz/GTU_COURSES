package LibrarySystem;

import java.util.LinkedList;

/**
 * This class base abstract class of Staffs and Users.
 *
 */
public abstract class LibraryUsers implements Library{
    /**
     * The name of person(User/Staff).
     */
    protected String name;
    /**
     * The password of person (User/Staff).
     */
    protected String password;
    /**
     * The e-mail of person (User/Staff).
     */
    protected String eMail;
    /**
     * The id of person (User/Staff).
     */
    protected String id;
    /**
     * The books of list which are in library system.
     */
    protected LinkedList<Book> booksArray;
    /**
     * The library database name.
     */
    private final String LIBRARYDATABASE = "library.csv";
    /**
     * This function reads database then fills booksArray field.
     */
    final protected void updateBooks(){
        booksArray = (LinkedList<Book>) Book.read(LIBRARYDATABASE);
    }
    /**
     * To access the name of the library person's
     * @return the name of the person.
     */
    @Override
    public String getName() {
        return name;
    }
    /**
     * To access the id of the library person's
     * @return the id of the person.
     */
    @Override
    public String getID() {
        return id;
    }
    /**
     * To access the mail of the library person's
     * @return the mail of the person.
     */
    @Override
    public String getEMail() {
        return eMail;
    }
    /**
     * To access the password of library person's.
     * @return the password of the person.
     */
    protected String getPassword(){
        return password;
    }

    /**
     * This method writes informations to csv file .
     */
    abstract protected void writeCSV();

}