package cse222_hw9;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author yldzf
 */
public class CSE222_HW9 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here

        ListGraph DirectedList = new ListGraph(0, true);
        ListGraph UnDirectedList = new ListGraph(0, false);
        MatrixGraph DirectedMatrix = new MatrixGraph(0, true);
        MatrixGraph UnDirectedMatrix = new MatrixGraph(0, false);

        String testfile = "Test.txt";

        //Creating Directed List
        File f = new File(testfile);
        Scanner s = new Scanner(f);

        DirectedList = (ListGraph) ListGraph.createGraph(s, true, "list");

        //Creating Un Directed List
        f = new File(testfile);
        s = new Scanner(f);

        UnDirectedList = (ListGraph) ListGraph.createGraph(s, false, "list");

        //Creating Directed Matrix
        f = new File(testfile);
        s = new Scanner(f);

        DirectedMatrix = (MatrixGraph) MatrixGraph.createGraph(s, true, "Matrix");

        //Creating Un Directed Matrix
        f = new File(testfile);
        s = new Scanner(f);

        UnDirectedMatrix = (MatrixGraph) MatrixGraph.createGraph(s, false, "Matrix");

        // Directed ListGraph breadthFirstSearch
        int[] arr;
        arr = DirectedList.breadthFirstSearch(0);
        System.out.print("Bread First Search on directed list graph with 0. vertex: ");
        for(int i=0; i<arr.length; ++i){
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        //Undirected ListGraph breadthFirstSearch
        arr = UnDirectedList.breadthFirstSearch(0);
        System.out.print("Bread First Search on undirected list graph with 0. vertex: ");
        for(int i=0; i<arr.length; ++i){
            System.out.print(arr[i] + " ");
        }
        System.out.println();


        // Directed MatrixGraph breadthFirstSearch
        arr = DirectedMatrix.breadthFirstSearch(0);
        System.out.print("Bread First Search on directed matrix graph with 0. vertex: ");
        for(int i=0; i<arr.length; ++i){
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        // UnDirected MatrixGraph breadthFirstSearch
        arr = UnDirectedMatrix.breadthFirstSearch(0);
        System.out.print("Bread First Search on undirected matrix graph with 0. vertex: ");
        for(int i=0; i<arr.length; ++i){
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        //Directed ListGraph getConnectedComponentUndirectedGraph
        System.out.println("Test for Directed ListGraph getConnectedComponentUndirectedGraph");
        try{
            Graph[] graphArr ;
            graphArr = DirectedList.getConnectedComponentUndirectedGraph();
            //bir asagıdaki satira gelirse exception yakalanmamış demektir, test basarıyla tamamlanmis demektir
            //listgraph ve matrixgraph classlarının tostringi olmadığından onları bastıramıyorum.
            System.out.println("Number of ConnectedComponent number is: " + graphArr.length);
        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());
        }

        //Undirected ListGraph getConnectedComponentUndirectedGraph
        System.out.println("Test for Undirected ListGraph getConnectedComponentUndirectedGraph");
        try{
            Graph[] graphArr ;
            graphArr = UnDirectedList.getConnectedComponentUndirectedGraph();
            //bir asagıdaki satira gelirse exception yakalanmamış demektir, test basarıyla tamamlanmis demektir
            //listgraph ve matrixgraph classlarının tostringi olmadığından onları bastıramıyorum.
            System.out.println("Number of ConnectedComponent number is: " + graphArr.length);
        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());
        }

        //Directed MatrixGraph getConnectedComponentUndirectedGraph
        System.out.println("Test for Directed MatrixGraph getConnectedComponentUndirectedGraph");
        try{
            Graph[] graphArr ;
            graphArr = DirectedMatrix.getConnectedComponentUndirectedGraph();
            //bir asagıdaki satira gelirse exception yakalanmamış demektir, test basarıyla tamamlanmis demektir
            //listgraph ve matrixgraph classlarının tostringi olmadığından onları bastıramıyorum.
            System.out.println("Number of ConnectedComponent number is: " + graphArr.length);
        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());

        }

        //Undirected MatrixGraph getConnectedComponentUndirectedGraph
        System.out.println("Test for Undirected MatrixGraph getConnectedComponentUndirectedGraph");
        try{
            Graph[] graphArr ;
            graphArr = UnDirectedMatrix.getConnectedComponentUndirectedGraph();
            //bir asagıdaki satira gelirse exception yakalanmamış demektir, test basarıyla tamamlanmis demektir
            //listgraph ve matrixgraph classlarının tostringi olmadığından onları bastıramıyorum.
            System.out.println("Number of ConnectedComponent number is: " + graphArr.length);
        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());

        }

        //Directed ListGraph bipartite
        System.out.println("Test for Directed ListGraph bipartite");
        try{
            System.out.print("The graph is bipartite? :"+DirectedList.isBipartiteUndirectedGraph() + "\n");

        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());
        }

        //undirected List bipartite
        System.out.println("Test for Undirected ListGraph bipartite");
        try{
            System.out.print("The graph is bipartite? :"+UnDirectedList.isBipartiteUndirectedGraph() + "\n");

        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());
        }

        //Directed matrix bipartite
        System.out.println("Test for Directed MatrixGraph bipartite");
        try{
            System.out.print("The graph is bipartite? :"+DirectedMatrix.isBipartiteUndirectedGraph() + "\n");

        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());
        }

        //undirected MatrixGraph bipartite
        System.out.println("Test for Undirected MatrixGraph bipartite");
        try{
            System.out.print("The graph is bipartite? :"+UnDirectedMatrix.isBipartiteUndirectedGraph() + "\n");

        }catch(UnsupportedOperationException e){
            System.out.println(e.getMessage());
        }


        int edgenumber = 13;

        //DirectedList add random edges
        System.out.println("Test for Directed ListGraph bipartite");
        try{
            System.out.print("Created random edge number is: "+DirectedList.addRandomEdgesToGraph(edgenumber) +"\n");
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        //undirectedList add random edges
        System.out.println("Test for Undirected ListGraph bipartite");
        try{
            System.out.print("Created random edge number is: "+UnDirectedList.addRandomEdgesToGraph(edgenumber) +"\n");
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        //DirectedMatrix add random edges
        System.out.println("Test for Directed MatrixGraph bipartite");
        try{
            System.out.print("Created random edge number is: "+DirectedMatrix.addRandomEdgesToGraph(edgenumber) +"\n");
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
        //UnDirectedMatrix add random edges
        System.out.println("Test for undirected MatrixGraph bipartite");
        try{
            System.out.print("Created random edge number is: "+UnDirectedMatrix.addRandomEdgesToGraph(edgenumber) +"\n");
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        DirectedList.writeGraphToFile("DirectedList.txt");
        UnDirectedList.writeGraphToFile("UnDirectedList.txt");
        DirectedMatrix.writeGraphToFile("DirectedMatrix.txt");
        UnDirectedMatrix.writeGraphToFile("UnDirectedMatrix.txt");



    }

}
