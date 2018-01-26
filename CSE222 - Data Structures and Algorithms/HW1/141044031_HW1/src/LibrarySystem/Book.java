package LibrarySystem;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
/**
 * The book class created to store all book's information in a class.
 *
 */
public class Book {

    /**
     * The books database file.
     */
    final private String CSVFILE = "library.csv";
    /**
     * Books id.
     */
    final private String ID;
    /**
     * Books name
     */
    final private String NAME;
    /**
     * Books author.
     */
    final private String AUTHOR;
    /**
     * Books availability, if NULL book is free else not.
     */
    private String availability;
    /**
     * The user who borrowed the book. If NULL, book is free.
     */
    private String borrowed;
    /**
     * The date when book will be free. If NULL, book is free.
     */
    private String avaibleDate;
    /**
     * The constructere calls another constructure and fills the fields
     * @param id_ book id
     * @param name_ book name
     * @param author_ books author
     */
    Book(String id_,String name_, String author_){
        this(id_,name_,author_,"NULL","NULL","NULL");
    }
    /**
     * The constructer fills the fields.
     * @param id_ book id
     * @param name_ book name
     * @param author_ books author
     * @param availability_ books availability
     * @param borrowed_ the user who borrowed the book.
     * @param date the date when book will be free.
     */
    Book(String id_,String name_, String author_, String availability_,
         String borrowed_, String date){
        ID = id_;
        NAME = name_;
        AUTHOR = author_;
        availability = availability_;
        borrowed = borrowed_;
        avaibleDate = date;

    }
    /**
     * This method writes book's information to "library.csv" database
     * @param append if true the information appends the database otherwise
     * information written on last data.
     */
    protected void writeCSV(boolean append) {
        try {
            /**
             * The object to write file.
             */
            FileWriter writer = new FileWriter(CSVFILE,append);
            writer.write(getID());
            writer.write(',');
            writer.write(getName());
            writer.write(',');
            writer.write(getAuthor());
            writer.write(',');
            writer.write(getAvailability());
            writer.write(',');
            writer.write(getBorrowed());
            writer.write(',');
            writer.write(getAvaibleDate());
            writer.write('\n');
            writer.flush();
            writer.close();
        } catch (FileNotFoundException ex) {
            System.err.println("File can not be found");
            System.exit(0);
        } catch (IOException ex) {
            System.err.println("File open error");
            System.exit(0);
        }
    }
    /**
     * To access person's id number.
     * @return the id of book.
     */
    public String getID(){
        return ID;
    }
    /**
     * To access book's name.
     * @return the name of book.
     */
    public String getName() {
        return NAME;
    }
    /**
     * To access book's author.
     * @return the author of book.
     */
    public String getAuthor() {
        return AUTHOR;
    }
    /**
     * To check the availability of book. (Someone can borrow or not)
     * @return if "NULL" can borrow anyone, else not.
     */
    public String getAvailability() {
        return availability;
    }
    /**
     * To change the availability of book. (Someone can borrow or not)
     * @param availability_ the setting value. If "NULL" anyone can borrow,
     * else not.
     */
    protected void setAvailability(String availability_){
        availability = availability_;
    }
    /**
     * Who is borrowed the book.
     * @return if "NULL" its free, else someone has it.
     */
    public String getBorrowed() {
        return borrowed;
    }
    /**
     * To set borrow status,if "NULL" its free, anyone can borrow it, else
     * the id of user (given with parameter) have it.
     * @param borrowStatus the id of user who has it.
     */
    protected void setBorrowed(String borrowStatus){
        borrowed = borrowStatus;
    }
    /**
     * To chech the book's avaible date.
     * @return Book's avaible date.
     */
    public String getAvaibleDate() {
        return avaibleDate;
    }
    /**
     * To set the book's avaible date.
     * @param date Book's avaible date.
     */
    protected void setAvaibleDate(String date) {
        avaibleDate = date;
    }
    /**
     * This function read's the given csv file and creates books objects list
     * according the reading.
     * @param csvFile csv file database to read.
     * @return books objects list
     */
    public static List read(String csvFile){
        /**
         * The object created to store all books in library system.
         */
        ArrayList<Book> booksList =  new ArrayList();

        try (BufferedReader br = new BufferedReader(new FileReader(csvFile))) {
            /**
             * A line of database.
             */
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                Book book = new Book(parts[0],parts[1],parts[2],parts[3],
                        parts[4],parts[5]);
                booksList.add(book);

            }
            br.close();
        } catch (FileNotFoundException ex) {
            System.err.println("File can not be found");
            System.exit(0);
        } catch (IOException ex) {
            System.err.println("File open error");
            System.exit(0);
        }

        return booksList;

    }
    public String toString(){
        return "ID:" + this.getID() +" Name :" + this.getName() + " Author :" +this.getAuthor()
                + " Availability: "+ this.getAvailability()  +" AvaibleDate: " +this.getAvaibleDate()
                + " Borrowed from: "+this.getBorrowed();
    }


}