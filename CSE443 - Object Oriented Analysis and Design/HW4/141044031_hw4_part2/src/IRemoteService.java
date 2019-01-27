import javax.naming.NoPermissionException;
import java.io.Serializable;
import java.util.Map;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IRemoteService extends Remote   {


    /**
     * Creates Minimum spanning Tree as Graph, according to Kruscal Algorithm
     * @param graph graph to calculate spanning tree
     * @param clientID the client ID who called the service.
     * @return minimum spanning tree as a graph
     * @throws RemoteException
     * @throws NoPermissionException if client has not enough credit.
     */
    public IGraph minimumSpanningTree(IGraph graph, Integer clientID) throws RemoteException, NoPermissionException;


    /**
     * The incidence matrix corresponding to the given graph
     * @param graph graph to calculate incidence matrix
     * @param clientID the client ID who called the service.
     * @return incidence matrix as mapped vertex to list fo edges.
     * @throws RemoteException
     * @throws NoPermissionException if client has not enough credit.
     */
    public Map<Object, int[]> IncidenceMatrix(IGraph graph, Integer clientID)throws RemoteException,NoPermissionException;

    /**
     * The service only gives information to server print information like "xxx ID client is connecto to server"
     * @param clientID the client ID who connected to server.
     * @throws RemoteException
     */
    public void login(Integer clientID) throws RemoteException;

}
