package LibrarySystem;

import java.io.IOException;
/**
 * The main class of the Library Management System.
 *
 */
public class mainTester {
    public static void main(String[] args) {

        try {
            Login login = new Login();
        } catch (IOException ex) {
            System.err.println("File error!");
        }


    }
}