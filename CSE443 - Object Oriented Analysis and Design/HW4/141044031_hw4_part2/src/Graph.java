import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class Graph implements IGraph {

    private Map<Double,List<Map<Object,Object>>> graph;

    /**
     * Constructure of the class. Creates graph.
     */
    public Graph(){
        super();
        this.graph = new TreeMap<>();
    }
    /**
     * Returns graph informations.
     * @return graph informations
     */
    public Map<Double,List<Map<Object,Object>>> getGraphInfo(){
        return this.graph;
    }
    /**
     * Add an edge to the graph.
     * @param fromVertex source vertex.
     * @param toVertex destination vertex.
     * @param weight weight of the edge.
     */
    @Override
    public void addItem(Object fromVertex, Object toVertex, Double weight) {

        Map<Object,Object> edge = new TreeMap<>();
        edge.put(fromVertex,toVertex);
        if (graph.get(weight) == null){
            List l = new ArrayList<>();
            l.add(edge);
            graph.put(weight,l);
        }else
            graph.get(weight).add(edge);
    }
    /**
     * Remove an edge from the graph.
     * @param fromVertex source vertex.
     * @param toVertex destination vertex.
     * @param weight weight of the edge.
     * @return true if the edge is removed else false.
     */
    @Override
    public boolean removeItem(Object fromVertex, Object toVertex, Double weight) {
        if(graph.get(weight) == null)
            return false;
        Map<Object,Object> edge = new TreeMap<>();
        edge.put(fromVertex,toVertex);

        return graph.get(weight).remove(edge);
    }
    /**
     * String information of the graph.
     * @return String information of the graph.
     */
    public String print(){
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyy HH:mm:ss:nn");
        LocalDateTime now = LocalDateTime.now();
        System.out.println("print method called at " + dtf.format(now));
        long startTime = System.nanoTime();

        StringBuilder s = new StringBuilder();
        Iterator<Map.Entry<Double, List<Map<Object, Object>>>> it = this.graph.entrySet().iterator();

        while (it.hasNext()){
            Map.Entry<Double, List<Map<Object, Object>>> map = it.next();
            Double weight = map.getKey();
            List<Map<Object, Object>> edges = map.getValue();
            for(Map<Object, Object> edge : edges){
                Object vertex1 = edge.keySet().iterator().next();
                Object vertex2 = edge.values().iterator().next();

                s.append("V1:"+vertex1.toString()+" V2:" + vertex2.toString() + " W:"+weight + "\n");
            }

        }
        long endTime = System.nanoTime();
        System.out.println("print method took " + (endTime - startTime) + " nanoseconds");
        return s.toString();
    }

}
