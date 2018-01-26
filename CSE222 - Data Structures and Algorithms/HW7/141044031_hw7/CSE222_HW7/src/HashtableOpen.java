
import java.util.ArrayList;
import java.util.List;

/** Hash table implementation using open addressing.
 *  @author Koffman and Wolfgang
 * @param <K>
 * @param <V>
 */

public class HashtableOpen < K, V > implements HashMap < K, V > {
    // Data Fields
    /** The table */
    private Entry < K, V > [] table;
    private static final int START_CAPACITY = 101;
    private final double LOAD_THRESHOLD = 0.75;
    /** Count of keys in table */
    private int numKeys;
    /** Count of deleted members from table */
    private int numDeletes;
    /** To change with deleted index */
    private final Entry < K, V > DELETED = new Entry <  > (null, null);
    /** The data field keeps filed index of table for toString method */
    private final List<Integer> indexList = new ArrayList<>();



    // Constructor
    public HashtableOpen() {
        table = new Entry[START_CAPACITY];
    }

    /** Contains key-value pairs for a hash table.
     * @param <K>
     * @param <V> */
    private static class Entry < K, V > {

        /** The key */
        private K key;

        /** The value */
        private V value;

        /** Creates a new key-value pair.
         @param key The key
         @param value The value
         */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        /** Retrieves the key.
         @return The key
         */
        public K getKey() {
            return key;
        }

        /** Retrieves the value.
         @return The value
         */
        public V getValue() {
            return value;
        }

        /** Sets the value.
         @param val The new value
         @return The old value
         */
        public V setValue(V val) {
            V oldVal = value;
            value = val;
            return oldVal;
        }
    }
    /** Returns the number of entries in the map
     * @return  */
    @Override
    public int size() {
        return numKeys;
    }

    /** Returns true if empty
     * @return  true if empty */
    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }


    /** Finds either the target key or the first empty slot in the
     search chain using linear probing.
     pre: The table is not full.
     @param key The key of the target object
     @return The position of the target or the first empty slot if
     the target is not in the table.
     */
    private int findFirst(Object key) {
        // Calculate the starting index.
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length; // Make it positive.

        // Increment index until an empty slot is reached
        // or the key is found.
        while ( (table[index] != null) && (!key.equals(table[index].key))) {
            index++;
            // Check for wraparound.
            if (index >= table.length)
                index = 0; // Wrap around.
        }
        return index;
    }
    /** Finds the first empty slot in the search chain using linear probing.
     pre: The table is not full.
     @param key The key of the target object
     @return The position of the target or the first empty slot if
     the target is not in the table.
     */
    private int find(Object key) {
        // Calculate the starting index.
        int index = (key.hashCode()) % table.length;
        if (index < 0)
            index += table.length; // Make it positive.

        // Increment index until an empty slot is reached
        // or the key is found.
        while (table[index] != null) {

            index++;
            // Check for wraparound.
            if (index >= table.length)
                index = 0; // Wrap around.
        }
        return index;
    }

    /** Method get for class HashtableOpen.
     @param key The key being sought
     @return the value associated with this key if found;
     otherwise, null
     */
    @Override
    public V get(Object key) {
        // Find the first table element that is empty
        // or the table element that contains the key.
        int index = findFirst(key);

        // If the search is successful, return the value.
        if (table[index] != null)
            return table[index].value;
        else
            return null; // key not found.
    }

    /** Method put for class HashtableOpen.
     post: This key-value pair is inserted in the
     table and numKeys is incremented. If the LOAD_THRESHOLD
     is exceeded, the table is expanded.
     @param key The key of item being inserted
     @param value The value for this key
     @return Old value associated with this key if found;
     otherwise, null
     */
    @Override
    public V put(K key, V value) {

        if(value == null)
            return null;

        // Find the first table element that is empty
        int index = find(key);

        // If an empty element was found, insert new entry.
        if (table[index] == null) {
            table[index] = new Entry <  > (key, value);
            numKeys++;
            indexList.add(index);
        }

        V returnVal  = table[index].value;

        // Check whether rehash is needed.
        double loadFactor = (double) (numKeys + numDeletes) / table.length;
        if (loadFactor > LOAD_THRESHOLD)
            rehash();

        return returnVal;
    }

    /** Expands table size when loadFactor exceeds LOAD_THRESHOLD
     post: The size of table is doubled and is an odd integer.
     Each nondeleted entry from the original table is
     reinserted into the expanded table.
     The value of numKeys is reset to the number of items
     actually inserted; numDeletes is reset to 0.
     */
    private void rehash() {
        // Save a reference to oldTable.
        Entry < K, V > [] oldTable = table;
        // Double capacity of this table.
        table = new Entry[2 * oldTable.length + 1];
        indexList.clear();
        // Reinsert all items in oldTable into expanded table.
        numKeys = 0;
        numDeletes = 0;
        for (Entry<K, V> oldTable1 : oldTable) {
            if ((oldTable1 != null) && (oldTable1 != DELETED)) {
                // Insert entry in expanded table
                put(oldTable1.key, oldTable1.value);
            }
        }
    }

    /** Remove the item with a given key value
     *  @param key The key to be removed
     *  @return The value associated with this key, or null
     *  if the key is not in the table.
     */
    @Override
    public V remove(Object key) {
        int index = findFirst(key);
        if (table[index] == null)
            return null;
        V oldValue = table[index].value;
        table[index] = DELETED;
        numKeys--;
        for(int i=0; i<indexList.size(); ++i)
            if(indexList.get(i).compareTo(index) == 0)
                indexList.remove(i);
        return oldValue;
    }

    /**
     * Returns string representation of object
     * @return string representation of object
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder("{");
        for(Integer i : indexList)
            sb.append(table[i].key).append("=").append(table[i].value).append(", ");

        sb.deleteCharAt(sb.length()-2);
        sb.append("}");
        return sb.toString();
    }

}
