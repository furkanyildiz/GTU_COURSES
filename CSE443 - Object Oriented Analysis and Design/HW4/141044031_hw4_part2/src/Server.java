import java.rmi.Naming;


/**
 * Server Class
 */
public class Server {

    public Server() {}

    /**
     * Binds remote object to "rmi://localhost/RemoteService"
     * @param args ip, default localhost.
     */
    public static void main(String args[]) {
        try {
            String host = (args.length < 1) ? "localhost" : args[0];

            // Instantiating the implementation class
            IRemoteService remoteService = new RemoteService();

            Naming.rebind("rmi://"+host+"/RemoteService",remoteService);
            System.out.println("Server started");


            /*
            // Exporting the object of implementation class
            // (here we are exporting the remote object to the stub)
            IGraph stub = (IGraph) UnicastRemoteObject.exportObject(graph, 0);

            // Binding the remote object (stub) in the registry
            Registry registry = LocateRegistry.getRegistry();
            registry.bind("//localhost/Graph", stub);
            System.err.println("Server ready");
            */

        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
