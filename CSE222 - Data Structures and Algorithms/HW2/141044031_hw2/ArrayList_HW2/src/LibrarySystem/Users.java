package LibrarySystem;

import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.Calendar;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Users class of library management system.
 *
 */
public class Users extends LibraryUsers {
    /**
     * CSV file of users database.
     */
    private final String LIBRARYDATABASE = "users.csv";
    /**
     * The constructer fills the fields.
     * @param id_num Users id number.
     * @param name_ Users name.
     * @param pass Users password
     * @param mail Users mail.
     */
    Users(String id_num, String name_, String pass, String mail) {
        id = id_num;
        name = name_;
        password = pass;
        eMail = mail;
        if(LIBRARYDATABASE.isEmpty())
            booksArray = null;
        else
            updateBooks();
    }
    /**
     * This method asks the user to borrow books from the library. If book is
     * available, the system borrows books for two months.
     */
    public void borrowBook(){
        if (booksArray == null){

            System.out.println("There is no book to borrow!");
            return;
        }
        System.out.printf("Please write the id of the book you want to borrow:");
        Scanner scanner = new Scanner(System.in);
        /**
         * The id of book which is wantting borrow.
         */
        String b_id = scanner.nextLine();
        /**
         * To store that wanting book is avaible or not.
         */
        boolean found = false;
        updateBooks();
        for (Book aBook : booksArray){
            if (aBook.getID().equals(b_id)){
                found = true;
                if(aBook.getAvailability().equals("NULL")){
                    aBook.setAvailability("FALSE");
                    aBook.setBorrowed(getID());
                    aBook.setAvaibleDate(setDate());
                    System.out.printf("%s is borrowed by you\n",aBook.getName());
                    System.out.printf("You must return the book within two ");
                    System.out.printf("months. (%s)\n",aBook.getAvaibleDate());
                }
                else{
                    System.out.println("This book was borrowed by someone else.");
                    System.out.printf("The availability date of this book is:");
                    System.out.printf(" %s\n",aBook.getAvaibleDate());
                }
            }
        }
        if( found == true)
            for (int i =0; i<booksArray.size(); ++i)
                if (i == 0)
                    booksArray.get(i).writeCSV(false);
                else
                    booksArray.get(i).writeCSV(true);

        else
            System.out.println("This book was not found on the system.");
    }
    /**
     * This method returns a book which is borrowed by a user.
     */
    public void returnBook(){
        System.out.printf("Please write the id of the book you want to return:");
        Scanner scanner = new Scanner(System.in);
        /**
         * The id of book which is wantting return back.
         */
        String b_id = scanner.nextLine();
        /**
         * To store that wanting book is avaible or not.
         */
        int found = 0;
        updateBooks();
        for (Book aBook : booksArray){
            if (aBook.getID().equals(b_id)){
                //Kitap benim tarafımdan mı alınmış, kontrolu
                if(aBook.getBorrowed().equals(getID())){
                    found = 1;
                    aBook.setAvailability("NULL");
                    aBook.setBorrowed("NULL");
                    aBook.setAvaibleDate("NULL");
                    System.out.printf("You returned the %s\n",aBook.getName());
                }
                else{
                    System.out.printf("You have not this book!\n");
                    found = 2;
                }

            }
        }
        if( found != 0)
            for (int i =0; i<booksArray.size(); ++i)
                if (i == 0)
                    booksArray.get(i).writeCSV(false);
                else
                    booksArray.get(i).writeCSV(true);
        else
            System.out.println("This book was not found on the system.");
    }
    /**
     * This method writes user information to users database.
     */
    @Override
    protected void writeCSV(){
        try {
            /**
             * To writes users information using this object.
             */
            FileWriter writer = new FileWriter(LIBRARYDATABASE,true);
            writer.write(getID());
            writer.write(',');
            writer.write(getName());
            writer.write(',');
            writer.write(getPassword());
            writer.write(',');
            writer.write(getEMail());
            writer.write('\n');
            writer.flush();
            writer.close();
        } catch (IOException ex) {
            System.err.println("File error!");
            System.exit(1);
        }
    }
    /**
     * This method sets the users return dates to two months after the date
     * they borrow the book.
     * @return  two mounts after the borrowed date.
     */
    private String setDate(){
        /**
         * Todays date
         */
        LocalDate todayDate = LocalDate.now();
        /**
         * Todays date as a String type
         */
        String today = todayDate.toString();
        /**
         * The setting format of date.
         */
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        /**
         * Gets a calendar using the default time zone and locale.
         */
        Calendar c = Calendar.getInstance();
        try {
            c.setTime(format.parse(today));
        } catch (ParseException ex) {
            Logger.getLogger(Users.class.getName()).log(Level.SEVERE, null, ex);
        }
        c.add(Calendar.MONTH, 2);
        /**
         * After 2 years.
         */
        String twoMonthLater = format.format(c.getTime());
        return twoMonthLater;
    }
    /**
     * This method writes users informations (id-name and e-mail)
     *
     */
    public String toString(){

        return "ID: "+this.getID() + " NAME: " + this.getName() + " E-MAIL: "  +this.getEMail();
    }

}