import java.io.Serializable;
import java.util.List;
import java.util.Map;

/**
 * Graph interface
 */
public interface IGraph extends Serializable {

    /**
     * Add an edge to the graph.
     * @param fromVertex source vertex.
     * @param toVertex destination vertex.
     * @param weight weight of the edge.
     */
    public void addItem(Object fromVertex, Object toVertex, Double weight);

    /**
     * Remove an edge from the graph.
     * @param fromVertex source vertex.
     * @param toVertex destination vertex.
     * @param weight weight of the edge.
     * @return true if the edge is removed else false.
     */
    public boolean removeItem(Object fromVertex, Object toVertex, Double weight);

    /**
     * String information of the graph.
     * @return String information of the graph.
     */
    public String print();

    /**
     * Returns graph informations.
     * @return graph informations
     */
    public Map<Double, List<Map<Object,Object>>> getGraphInfo();

}
