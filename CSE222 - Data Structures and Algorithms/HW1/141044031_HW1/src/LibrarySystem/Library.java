package LibrarySystem;

/**
 * Interface of Staffs and Users.
 *
 */

public interface Library {
    /**
     * To access name of person
     * @return name of person 
     */
    public String getName();
    /**
     * To access id of person
     * @return id of person. 
     */
    public String getID();
    /**
     * To access e-mail of person
     * @return e-mail of person. 
     */
    public String getEMail();
}