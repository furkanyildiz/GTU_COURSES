package LibrarySystem;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
/**
 * Staffs class of library management system.
 *
 */
public class Staffs extends LibraryUsers{
    /**
     * The library database file.
     */
    final private String LIBRARYDATABASE = "library.csv";
    /**
     * The users database file.
     */
    final private String USERSDATABASE = "users.csv";
    /**
     * The Users array to do operations on them.
     */
    private ArrayList<Users> usersArray = null;
    /**
     * The constructer fills the fields.
     * @param id_num id number of staff
     * @param name_ name of staff
     * @param pass password of staff
     * @param mail mail of staff
     */
    Staffs(String id_num, String name_, String pass, String mail) {
        id = id_num;
        name = name_;
        password = pass;
        eMail = mail;

        if(USERSDATABASE.isEmpty())
            usersArray = null;
        else
            updateUsers();

        if(LIBRARYDATABASE.isEmpty())
            booksArray = null;
        else
            updateBooks();
    }
    /**
     * This method fill usersArray field according to users database file 
     */
    private void updateUsers(){
        usersArray = (ArrayList<Users>) read();
    }
    /**
     * This methos reads the users database and creates a list of users
     * according to it.
     * @return list of users in database.
     */
    private List read(){
        /**
         * The object created to store all users in library system.
         */
        ArrayList<Users> userlist =  new ArrayList();

        try (BufferedReader br = new BufferedReader
                (new FileReader(USERSDATABASE))) {

            String line;
            while ((line = br.readLine()) != null && line.equals("")) {
                String[] parts = line.split(",");
                Users user = new Users(parts[0],parts[1],parts[2],parts[3]);
                userlist.add(user);
            }
            br.close();
        } catch (FileNotFoundException ex) {
            System.err.println("File can not be found");
            System.exit(0);
        } catch (IOException ex) {
            System.err.println("File open error");
            System.exit(0);
        }
        return userlist;
    }
    /**
     * This method for sets e-mail.
     * @param newMail the e-mail of person.
     */
    private void setEMail(String newMail) {
        eMail = newMail;
    }
    /**
     * This method for sets user's id.
     * @param user_id the id of person.
     */
    private void setID(String user_id) {
        id = user_id;
    }
    /**
     * This method for sets persons password.
     * @param pass
     */
    private void setPassword(String pass) {
        password = pass;
    }
    /**
     * This method for sets persons name.
     * @param user_name the name of person.
     */
    private void setName(String user_name) {
        name = user_name;
    }
    /**
     * This method adds a new book to library system.
     */
    public void addBook(){

        System.out.printf("Please write an id for new book: ");
        Scanner scanner = new Scanner(System.in);
        /**
         * The book id the staffs wants to add to library system.
         */
        String b_id = scanner.nextLine();
        System.out.printf("Please write name of new book: ");
        /**
         * The book name the staffs wants to add to library system.
         */
        String b_name = scanner.nextLine();
        System.out.printf("Please write author of the book: ");
        /**
         * The book's author name the staffs wants to add to the library system.
         */
        String b_author = scanner.nextLine();
        /**
         * The book's informations which is wanting to add to the library system
         */
        Book newBook = new Book(b_id,b_name,b_author);
        if (booksArray == null){
            booksArray = new ArrayList();
            booksArray.add(newBook);
            writeCSV();
            return;
        }
        updateBooks();
        for (Book aBook : booksArray){
            if(newBook.getID() == null ? aBook.getID() == null :
                    newBook.getID().equals(aBook.getID())){
                System.out.printf("This id has been used!\n");
                System.out.flush();
                newBook = null;
                return;
            }
        }
        booksArray.add(newBook);
        System.out.printf("The %s is added the library system.\n",newBook.getName());
        writeCSV();

    }
    /**
     * This method removes a book from library system.
     */
    public void removeBook(){
        /**
         * The check the book is found or not
         */
        boolean found = false;
        if(booksArray == null || booksArray.size() == 0){
            System.out.println("There is no book to remove!");
            return;
        }
        System.out.printf("Please write an id of book to remove it: ");
        Scanner scanner = new Scanner(System.in);
        /**
         * The id of book which is wanting to remove.
         */
        String n_id = scanner.nextLine();
        updateBooks();
        /**
         * the count to overrite first time to writing book.
         */
        int count = 0;
        for (int i = 0 ; i<booksArray.size(); ++i){
            if (booksArray.get(i).getID().equals(n_id)){
                found = true;
                if(booksArray.get(i).getAvailability().equals("FALSE")){
                    System.out.println("The book is using from a user!");
                    return;
                }
                else{
                    System.out.printf("The %s is removed from the library system.\n",booksArray.get(i).getName());
                    booksArray.remove(i);
                }
            }
        }
        if(booksArray.size() == 0){
            try {
                FileWriter writer = new FileWriter(LIBRARYDATABASE,false);
            } catch (IOException ex) {
                System.out.println("File error!");
            }
            return;
        }
        for (int i = 0 ; i<booksArray.size(); ++i){
            if (count == 0){
                booksArray.get(i).writeCSV(false);
                ++count;
            }
            else
                booksArray.get(i).writeCSV(true);
        }
        if (found == false)
            System.out.println("The book is not in library!");

    }



    /**
     * This method adds an user to library system.
     */
    public void addUser(){
        System.out.printf("Please write an id for new user: ");
        Scanner scanner = new Scanner(System.in);
        /**
         * The id of user who wants to register the system.
         */
        String n_id = scanner.nextLine();
        System.out.printf("Please write name of new user: ");
        /**
         * The name of user who wants to register the system.
         */
        String n_name = scanner.nextLine();
        System.out.printf("Please write password of new user: ");
        /**
         * The password of user who wants to register the system.
         */
        String n_pass = scanner.nextLine();
        System.out.printf("Please write e-mail of new user: ");
        /**
         * The mail of user who wants to register the system.
         */
        String n_mail = scanner.nextLine();
        /**
         * The new users informations.
         */
        Users newUser = new Users(n_id,n_name,n_pass,n_mail);
        if (usersArray == null){
            usersArray = new ArrayList();
            usersArray.add(newUser);
            newUser.writeCSV();
            return;
        }
        updateUsers();
        for (Users user : usersArray){
            if((user.getID() == null ? newUser.getID() == null :
                    user.getID().equals(newUser.getID()))  ||
                    (user.getEMail() == null ? newUser.getEMail() == null :
                            user.getEMail().equals(newUser.getEMail()))){
                System.out.printf("This e-mail/id has been used!\n");
                System.out.flush();
                newUser = null;
                return;
            }
        }
        usersArray.add(newUser);
        System.out.printf("The %s is added the library system.\n",newUser.getEMail());
        newUser.writeCSV();
    }
    /**
     * This method writes staffs informations (id-name and e-mail)
     *
     */
    public String toString(){

        return "ID: "+this.getID() + " NAME: " + this.getName() + " E-MAIL: "  +this.getEMail();
    }
    /**
     * This methot writes to csv last element of books Array
     */
    @Override
    protected void writeCSV() {
        booksArray.get(booksArray.size()-1).writeCSV(true);
    }
}