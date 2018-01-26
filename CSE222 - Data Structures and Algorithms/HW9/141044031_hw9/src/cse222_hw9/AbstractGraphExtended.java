package cse222_hw9;


import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

/**
 *
 * @author yldzf
 */
public abstract class AbstractGraphExtended extends AbstractGraph {

    // Data Fields
    /** The number of vertices */
    private int numV;
    /** Flag to indicate whether this is a directed graph */
    private boolean directed;

    /**
     * Contructure
     * @param numV number of vertex.
     * @param directed true if graph is directer otherwise false.
     */
    public AbstractGraphExtended(int numV, boolean directed) {
        super(numV, directed);
    }
    /**
     * This method selects a random number between 0 and edgeLimit then adds
     * that much edges to calling graph. The source and destination vertices
     * of edges will be random again.
     * @param edgeLimit the number for adding edge to graph
     * @return number of added vertex to graph.
     * @throws IllegalArgumentException if vertex number is zero or the creating
     * random number is bigger than number of Vertex or zero after 100 iteration
     */
    public int addRandomEdgesToGraph (int edgeLimit) throws IllegalArgumentException{

        if(getNumV() == 0)
            throw new IllegalArgumentException("There is no vertex in the graph");
        Random r = new Random();
        int Low = 0;
        int High = edgeLimit;
        int randomNum = r.nextInt(High-Low) + Low ;
        int count = 0 ;

        while(randomNum >= getNumV() || randomNum == 0 ){
            randomNum = r.nextInt(High-Low) + Low;
            ++count;
            if(count == 100)
                throw new IllegalArgumentException("edgeLimit fail");

        }
        int inserted = 0;
        for(int i=0; i<randomNum; ++i){
            r = new Random();
            int source = r.nextInt(High-Low) + Low;
            int dest = r.nextInt(High-Low) + Low;
            count = 0 ;

            while(source >= getNumV() || dest >= getNumV()){
                source = r.nextInt(High-Low) + Low;
                dest = r.nextInt(High-Low) + Low;
                ++count;
                if(count == 100)
                    throw new IllegalArgumentException("edgeLimit fail");
            }

            count = 0 ;
            while(dest == source){
                dest = r.nextInt(High-Low) + Low;
                // yeni dest vertex sayisindan büyük ise tekrar while ye girmesi için
                //sourceyle desti esitliyoruz
                if(dest >= getNumV())
                    dest = source;
                ++count;
                if(count == 100)
                    throw new IllegalArgumentException("edgeLimit fail");
            }

            Edge e = new Edge(source, dest,1.0);

            //eğer random olusturulan edge daha önceden graph'ta varsa eklenmemeli
            if(!isDirected()){
                if (getEdge(e.getSource(), e.getDest()).getWeight() == Double.POSITIVE_INFINITY &&
                    getEdge(e.getDest(), e.getSource()).getWeight() == Double.POSITIVE_INFINITY    ) {
                    inserted++;
                    insert(e);
                }

            }
            else {
                if (getEdge(e.getSource(), e.getDest()).getWeight() == Double.POSITIVE_INFINITY) {
                    insert(e);
                    inserted++;
                }

            }
        }

        return inserted;
    }
    /**
     * Traverses the graph with breadth First Search algorithm.
     * @param start start vertex to traverse graph
     * @return the parent array of vertexs.
     */
    public int [] breadthFirstSearch (int start){
        Queue<Integer> theQueue = new LinkedList<>();
        int[] parent = new int[getNumV()];
        for (int i = 0; i < getNumV(); i++)
            parent[i] = -1;

        boolean[] identified = new boolean[getNumV()];
        identified[start] = true;
        theQueue.offer(start);
        while (!theQueue.isEmpty()) {
            int current = theQueue.remove();
            Iterator<Edge> itr = edgeIterator(current);
            while (itr.hasNext()) {
                Edge edge = itr.next();
                int neighbor = edge.getDest();
                if (!identified[neighbor]) {
                    identified[neighbor] = true;
                    theQueue.offer(neighbor);
                    parent[neighbor] = current;
                }
            }
        }
        return parent;
    }
    /**
     * Returns a connected companend graph array
     * @return a connected companend graph array
     * @throws UnsupportedOperationException if the graph is directed
     */
    public Graph [] getConnectedComponentUndirectedGraph () throws UnsupportedOperationException{

        if(isDirected())
            throw new UnsupportedOperationException("The "
                    + "getConnectedComponentUndirectedGraph method works "
                    + "only on undirected graphs");

        ArrayList<Edge> all = fillAllEdgesToArray();
        ArrayList<ArrayList<Edge>> graphArr = new ArrayList<>();
        ArrayList<ArrayList<Edge>> newGraphArr = new ArrayList<>();

        for(int i=0; i<getNumV(); ++i){

            Queue<Edge> queue = new LinkedList();

            for(int j=0; j<all.size(); ++j){
                if(all.get(j).getSource() == i){
                    queue.add(all.remove(j));
                    j--;
                }
            }
            while(!queue.isEmpty()){
                boolean added = false;

                Edge first = queue.poll();

                for(int j=0; j<all.size(); ++j)
                    if(all.get(j).getSource() == first.getDest()){
                        queue.add(all.remove(j));
                        j--;
                    }

                for(int k=0; (k<graphArr.size() && !added); ++k){

                    for(int m=0; (m<graphArr.get(k).size() && !added); ++m){
                        if(graphArr.get(k).get(m).getSource()== first.getSource() ||
                                graphArr.get(k).get(m).getDest()== first.getSource() ||
                                graphArr.get(k).get(m).getSource()== first.getDest() ||
                                graphArr.get(k).get(m).getDest()== first.getDest()){
                            graphArr.get(k).add(first);
                            added = true;
                        }

                    }
                }
                if(!added){
                    graphArr.add(new ArrayList());
                    graphArr.get(graphArr.size()-1).add(first);
                }
            }
        }

        for(int i=0; i<graphArr.size(); ++i){
            int minArrForAGraph[] = findMinArr(graphArr.get(i));
            newGraphArr.add(new ArrayList() );
            for(int j=0; j< graphArr.get(i).size(); ++j){
                newGraphArr.get(i).add(new Edge(findIndex(minArrForAGraph , graphArr.get(i).get(j).getSource()),
                        findIndex(minArrForAGraph , graphArr.get(i).get(j).getDest()),
                        graphArr.get(i).get(j).getWeight()));
            }
        }

        if(this instanceof ListGraph){

            Graph[] ListGraphArr = new ListGraph[newGraphArr.size()];

            for(int i=0; i<newGraphArr.size(); ++i){
                ListGraphArr[i] = new ListGraph( findVertexNum(newGraphArr.get(i)), directed);
                for(int j=0; j< newGraphArr.get(i).size(); ++j){
                    Edge e = newGraphArr.get(i).get(j);
                    ListGraphArr[i].insert(e);
                }
            }

            return ListGraphArr;
        }
        else if(this instanceof MatrixGraph){

            Graph[] MatrixGraphArr = new MatrixGraph[newGraphArr.size()];

            for(int i=0; i<newGraphArr.size(); ++i){
                MatrixGraphArr[i] = new MatrixGraph( findVertexNum(newGraphArr.get(i)), directed);
                for(int j=0; j< newGraphArr.get(i).size(); ++j){
                    Edge e = newGraphArr.get(i).get(j);
                    MatrixGraphArr[i].insert(e);
                }
            }
            return MatrixGraphArr;
        }
        return null;
    }

    /**
     * Verilen graph arrayindeki vertex sayisini return eder.
     * @param grapArr graph arrayi
     * @return graph arrayindeki vertex sayisi
     */
    private int findVertexNum(ArrayList<Edge> grapArr){
        return findMinArr(grapArr).length;
    }

    /**
     * Graph arrayindeki vertexleri sirali bir sekilde içeren array return eder.
     * Or:(1,4) (1,5) returns 1,4,5
     * @param grapArr graph arrayi
     * @return vertexleri sirali bir sekilde içeren array
     */
    private int[] findMinArr(ArrayList<Edge> grapArr){

        ArrayList<Integer> allArr = new ArrayList();

        for(int m = 0; m< grapArr.size(); ++m){

            if(!allArr.contains(grapArr.get(m).getSource()))
                allArr.add(grapArr.get(m).getSource());
            if(!allArr.contains(grapArr.get(m).getDest()))
                allArr.add(grapArr.get(m).getDest());

        }
        int[] arr = new int[allArr.size()];
        for(int j =0 ; j<allArr.size(); ++j){
            arr[j] = allArr.get(j);
        }
        Arrays.sort( arr );
        return arr;
    }

    /**
     * Aranilan elemanin indexini return eder
     * @param arr içinde aranilan array
     * @param target aranilan eleman
     * @return aranilan elemanin indexi
     */
    private int findIndex(int[] arr, int target){
        for(int i=0; i<arr.length; ++i){
            if(arr[i] == target)
                return i;
        }
        return -1;
    }

    /**
     * Checks the given graph bipartite or not
     * @return true if graph is bipartite, otherwise false
     * @throws UnsupportedOperationException if the graph is directed
     */
    public boolean isBipartiteUndirectedGraph () throws UnsupportedOperationException{
        if(isDirected())
            throw new UnsupportedOperationException("The "
                    + "isBipartiteUndirectedGraph method works only on "
                    + "undirected graphs");
        Graph [] graphsArr;
        graphsArr = getConnectedComponentUndirectedGraph();
        boolean isItBipartite = true;

        for(int i=0; (i<graphsArr.length && isItBipartite) ; ++i){
            int colorArr[] = null;
            int size = 0;
            if(isDirected())
                size = graphsArr[i].getNumV();
            else
                size = graphsArr[i].getNumV() * 2 ;

            colorArr = new int[getNumV()];
            for (int j=0; j<getNumV(); ++j)
                colorArr[j] = -1;

            Queue <Integer> queue = new LinkedList<>();
            int firstVertexForColor = 0;
            colorArr[firstVertexForColor] = 1;
            queue.add(firstVertexForColor);

            while (!queue.isEmpty() && isItBipartite)
            {
                int current = queue.remove();
                Iterator <Edge> itr = edgeIterator(current);

                while(itr.hasNext()){
                    Edge next = itr.next();
                    int neighbour = next.getDest();
                    if(colorArr[neighbour] == -1)
                    {
                        colorArr[neighbour] = 1-colorArr[current];
                        queue.add(neighbour);
                    }
                    if(colorArr[neighbour]==colorArr[current])
                        isItBipartite =  false;
                }

            }
        }
        return isItBipartite;
    }

    /**
     *
     * @param fileName
     * @throws java.io.FileNotFoundException
     */
    public void writeGraphToFile (String fileName) throws FileNotFoundException{

        ArrayList<Edge> all = fillAllEdgesToArray();
        int vertexNum = findVertexNum(all);

        PrintWriter writer = new PrintWriter(fileName);
        writer.print(vertexNum);
        for( Edge e:all ){

            writer.write("\n" + e.getSource() + " " + e.getDest());

        }
        writer.close();
    }

    /**
     * Bu method grapth'daki tum edgeleri bir arraylist'e ekler, graph yönsüz
     * olsa dahi tersi varsa eklemez, yani (0,1) ekli iken (1,0) eklenmez.
     * @return tum edgeleri iceren bir list
     */
    private ArrayList fillAllEdgesToArray(){

        ArrayList<Edge> all = new ArrayList<>();

        for(int i=0; i<getNumV(); ++i){

            Iterator<Edge> itr = edgeIterator(i);
            while(itr.hasNext()){
                Edge current =  itr.next();
                Edge inverse = new Edge(current.getDest(),current.getSource(),current.getWeight());

                if( !all.contains(current) && !all.contains(inverse))
                    all.add(current);
            }
        }
        return all;
    }

}