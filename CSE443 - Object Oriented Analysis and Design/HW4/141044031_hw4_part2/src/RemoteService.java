import javax.naming.NoPermissionException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class RemoteService extends UnicastRemoteObject implements IRemoteService {

    /**
     * Clients credits whichs are registered to the Server.
     */
    private Integer[] clientsCredit = {100,200,300,100,100,100,100,100,100,100};
    /**
     * The maximum client id to registered the Server. Client id's starts from zero.
     */
    private Integer maxClietID = 9;
    /**
     * Cost of Minimum spanning Tree service.
     */
    private Integer MSTCOST = 15;
    /**
     * Cost of Incidence Matrix service.
     */
    private Integer INCIDENCEMATRIXCOST = 10;

    /**
     * Constucture of Remote Service. Only calls UnicastRemoteObject's constructure.
     * @throws RemoteException
     */
    public RemoteService() throws RemoteException {
        super();
    }
    /**
     * Creates Minimum spanning Tree as Graph, according to Kruscal Algorithm
     * @param graph graph to calculate spanning tree
     * @param clientID the client ID who called the service.
     * @return minimum spanning tree as a graph.
     *      *
     * @throws RemoteException
     * @throws NoPermissionException if client has not enough credit.
     */
    @Override
    public synchronized IGraph minimumSpanningTree(IGraph graph,Integer clientID) throws RemoteException,NoPermissionException {

        if(clientsCredit[clientID] < MSTCOST)
            throw new NoPermissionException("You have not enough credit! Your credit is " + clientsCredit[clientID] + " but the service function need at least " + MSTCOST + "credits.");
        if(clientID > maxClietID )
            throw new NoPermissionException("Your client id is not registered to Server!");


        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyy HH:mm:ss:nn");
        LocalDateTime now = LocalDateTime.now();
        System.out.println("Client ID: "+ clientID.toString() + " Minimum Spanning Tree service called at " + dtf.format(now));
        long startTime = System.nanoTime();

        //Map<Double, List<Map<Object, Object>>> minimumspanningtree = new TreeMap<>();
        IGraph minimumspanningtree = new Graph();
        Set<Object> visiteds = new TreeSet<>();

        double totalWeigh = 0;

        Iterator<Map.Entry<Double, List<Map<Object, Object>>>> it = graph.getGraphInfo().entrySet().iterator();
        while (it.hasNext()){
            Map.Entry<Double, List<Map<Object, Object>>> map = it.next();
            Double weight = map.getKey();
            List<Map<Object, Object>> edges = map.getValue();
            for(Map<Object, Object> edge : edges){
                Object vertex1 = edge.keySet().iterator().next();
                Object vertex2 = edge.values().iterator().next();

                if (!visiteds.contains(vertex1) || !visiteds.contains(vertex2)){
                    totalWeigh+=weight;
                    minimumspanningtree.addItem(vertex1,vertex2,weight);
                    visiteds.add(vertex1);
                    visiteds.add(vertex2);
                }
            }
        }

        //System.out.println("Total weight:"+totalWeigh);
        long endTime = System.nanoTime();
        System.out.println("Minimum Spanning Tree service took " + (endTime - startTime) + " nanoseconds");

        clientsCredit[clientID]-=MSTCOST;
        return minimumspanningtree;
    }

    /**
     * The incidence matrix corresponding to the given graph
     * @param graph graph to calculate incidence matrix
     * @param clientID the client ID who called the service.
     * @return incidence matrix as mapped vertex to list fo edges.
     * @throws RemoteException
     * @throws NoPermissionException if client has not enough credit.
     */
    @Override
    public synchronized Map<Object, int[]> IncidenceMatrix(IGraph graph,Integer clientID) throws RemoteException,NoPermissionException {

        if(clientsCredit[clientID] < INCIDENCEMATRIXCOST)
            throw new NoPermissionException("You have not enough credit! Your credit is " + clientsCredit[clientID] + " but the service function need at least" + INCIDENCEMATRIXCOST + "credits.");
        if(clientID > maxClietID )
            throw new NoPermissionException("Your client id is not registered to Server!");

        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyy HH:mm:ss:nn");
        LocalDateTime now = LocalDateTime.now();
        System.out.println("Client ID: "+ clientID.toString() + " Incidence Matrix service called at " + dtf.format(now));
        long startTime = System.nanoTime();

        Map<Object, int[]> incidencematrix = new HashMap<>();

        Set<Object> vertexes = new HashSet<>();
        int edgeCount = 0;
        for (List<Map<Object, Object>> edges : graph.getGraphInfo().values()) {
            edgeCount += edges.size();

            for (Map<Object, Object> edge : edges) {
                vertexes.add(edge.values().iterator().next());
                vertexes.add(edge.keySet().iterator().next());
            }
        }



        for (Object vertex : vertexes) {
            int rows[] = new int[edgeCount];
            Arrays.fill(rows, 0);
            incidencematrix.put(vertex, rows);
        }

        int currentEdge = 0;
        for (List<Map<Object, Object>> edges : graph.getGraphInfo().values()) {

            for (Map<Object, Object> edge : edges) {
                Object vertex1 = edge.keySet().iterator().next();
                Object vertex2 = edge.values().iterator().next();

                incidencematrix.get(vertex1)[currentEdge] = 1;
                incidencematrix.get(vertex2)[currentEdge++] = -1;

            }
        }
        long endTime = System.nanoTime();
        System.out.println("Incidence Matrix service took " + (endTime - startTime) + " nanoseconds");

        clientsCredit[clientID]-=INCIDENCEMATRIXCOST;

        return incidencematrix;
    }
    /**
     * The service only gives information to server print information like "xxx ID client is connecto to server"
     * @param clientID the client ID who connected to server.
     * @throws RemoteException
     */
    @Override
    public void login(Integer clientID) throws RemoteException {
        System.out.println("Connected a client. The client ID is: "+clientID);
    }
}
