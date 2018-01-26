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
 * This class created to manage the login system.
 */
public class Login {
    /**
     * The name of the person who logged in
     */
    private final  String NAME;
    /**
     * The password of persons
     */
    private final String PASSWORD;
    /**
     * If staff is logined the system informations of it else null
     */
    private Staffs staff = null;
    /**
     * If user is logined the system informations of it else null
     */
    private Users user = null;
    /**
     * This methods, creates users and library database if there are no, then
     * the user is prompted for e-mail and password and the correctness is 
     * checked.
     */
    Login() throws IOException{
        String [] temp = askMailPassword();
        NAME = temp[0];
        PASSWORD = temp[1];
        /**
         * If there are no files to create files.
         */
        FileWriter writer = new FileWriter("users.csv",true);
        writer = new FileWriter("library.csv",true);

        LibraryUsers loginedInfo =  LoginCheck("staff.csv",NAME,PASSWORD);


        if(loginedInfo == null)
            loginedInfo = LoginCheck("users.csv",NAME, PASSWORD);

        if(loginedInfo == null){
            System.err.println("Invalid login!");
            System.exit(1);
        }
        choiceOptions(loginedInfo);
    }

    /**
     * This method checks given mail and password is in given csvFile or not.
     *
     * @param csvFile to check users and staffs csv file one by one
     * @param mail the mail of person who want to login library system
     * @param password the password of person who want to login library system
     * @return match person to its class if it is user, returns its user class,
     * if it is staff returns its staff class, if its not match returns null.
     */
    private LibraryUsers LoginCheck(String csvFile,String mail, String password)
    {
        ArrayList<LibraryUsers> libraryPeople = null;
        libraryPeople = (ArrayList<LibraryUsers>) read(csvFile);
        for(int i=0; i<libraryPeople.size(); ++i){
            if (libraryPeople.get(i).getEMail().equalsIgnoreCase(mail)){
                if(libraryPeople.get(i).getPassword().equals(password))
                    return libraryPeople.get(i);
                else{
                    System.err.println("Wrong password!");
                    return null;
                }
            }
        }
        return null;
    }
    /**
     * This function checks csvFile parameter, if the file is users database,
     * creates users objects and returns it otherwise creates staffs objects and
     * returns it.
     * @param csvFile the database file which as for being reed.
     * @return according to databese returns Users objects list or Staffs 
     * objects list.
     */
    private List read(String csvFile){
        /**
         * The object created to store all books in library system.
         */
        ArrayList<LibraryUsers> libraryPeople =  new ArrayList();

        try (BufferedReader br = new BufferedReader(new FileReader(csvFile))) {
            /**
             * A line of database.
             */
            String line;
            while ((line = br.readLine()) != null) {
                if (!line.equals("")) {
                    String[] parts = line.split(",");
                    if (csvFile.equals("staff.csv")) {
                        staff = new Staffs(parts[0], parts[1], parts[2], parts[3]);
                        libraryPeople.add(staff);
                    } else if (csvFile.equals("users.csv")) {
                        user = new Users(parts[0], parts[1], parts[2], parts[3]);
                        libraryPeople.add(user);
                    }
                }
            }
            br.close();
        } catch (FileNotFoundException ex) {
            System.err.println("File can not be found");
            System.exit(0);
        } catch (IOException ex) {
            System.err.println("File open error");
            System.exit(0);
        }

        return libraryPeople;

    }
    /**
     * This method asks to user e-mail and password
     * @return a string which contains person's e-mail and password.
     */
    private String[] askMailPassword(){
        /**
         * to take users mail as a input.
         */
        String mail_ ;
        /**
         * to take users password as a input.
         */
        String password_ ;
        /**
         * to return users mail and password we should create String array.
         */
        String[] configs = new String[2];
        System.out.println("**** LİBRARY MANAGEMENT SYSTEM ****");
        System.out.println("Welcome the library management system.");
        System.out.printf("For login to system please write your e-mail: ");
        Scanner scanner = new Scanner(System.in);
        mail_ = scanner.nextLine();
        System.out.printf("Please write your password: ");
        password_ = scanner.nextLine(); // gizle şifreyi

        configs[0] = mail_;
        configs[1] = password_;

        return configs;
    }
    /**
     * This method is a polimorfic method, it checks the incoming parameter
     * and calls interface according to this
     * @param libraryPeople the person's information class who want to login 
     * the library system 
     */
    private void choiceOptions(LibraryUsers libraryPeople){
        if (libraryPeople instanceof Users ){
            Users libraryUsers = (Users)libraryPeople;
            choiceUser(libraryUsers);
        }
        else if (libraryPeople instanceof Staffs){
            Staffs libraryStaffs = (Staffs)libraryPeople;
            choiceStaff(libraryStaffs);
        }

    }
    /**
     * This method has Users interface, its operations.Then waits to
     * take input to do operations.
     * @param libraryUsers the users information who want to login the
     * library system 
     */
    private void choiceUser(Users libraryUsers){
        /**
         * The option provides select a operation
         */
        int option = 0;
        Scanner scanner = new Scanner(System.in);
        while ( option != 3){
            System.out.println("You can do those operations.");
            System.out.println("1) Borrow a book.");
            System.out.println("2) Return a book.");
            System.out.println("3) Exit.");
            System.out.printf("Please select an operation :");
            option = scanner.nextInt();
            switch (option) {
                case 1:
                    libraryUsers.borrowBook();
                    break;
                case 2:
                    libraryUsers.returnBook();
                    break;
                case 3:
                    System.out.println("Good bye!");
                    System.exit(0);
                default:
                    System.err.println("Invalid option please try again!");
                    break;
            }

        }
    }
    /**
     * This method shows Staffs interface and its operations.Then waits to
     * take input to do the operations.
     * @param libraryStaffs the staffs information who want to login the
     * library system 
     */
    private void choiceStaff(Staffs libraryStaffs){
        /**
         * The option provides select a operation
         */
        int option = 0;
        Scanner scanner = new Scanner(System.in);
        while ( option != 4){
            System.out.println("You can do those operations.");
            System.out.println("1) Add a new book.");
            System.out.println("2) Remove a book from library.");
            System.out.println("3) Register a new library user.");
            System.out.println("4) Exit.");
            System.out.printf("Please select an operation :");
            option = scanner.nextInt();
            switch (option) {
                case 1:
                    libraryStaffs.addBook();
                    break;
                case 2:
                    libraryStaffs.removeBook();
                    break;
                case 3:
                    libraryStaffs.addUser();
                    break;
                case 4:
                    System.out.println("Good bye!");
                    System.exit(0);

                default:
                    System.err.println("Invalid option please try again!");
                    break;
            }
        }
    }

    /**
     * To access private member of class
     * @return name of user who loginned the system.
     */
    public String getName() {
        return NAME;
    }
    /**
     * This method writes who is loginned the system.
     */
    public String toString(){

        return "NAME: " + this.getName();
    }

}
