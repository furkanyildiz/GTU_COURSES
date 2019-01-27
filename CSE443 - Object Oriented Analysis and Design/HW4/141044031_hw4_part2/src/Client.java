import java.awt.*;

/**
 * Client
 */
public class Client {

    private Client() {}

    /**
     * Creates GUI.
     * @param args ip, default localhost.
     */
    public static void main(String[] args) {

        String host = (args.length < 1) ? "localhost" : args[0];
        Integer clientID = 2;


        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    GUI window = new GUI("rmi://"+host+"/RemoteService",clientID);
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    System.err.println("Client error!");
                }
            }
        });



    }
}
