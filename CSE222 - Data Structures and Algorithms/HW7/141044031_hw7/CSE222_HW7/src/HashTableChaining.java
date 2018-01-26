
import java.util.ArrayList;
import java.util.List;

public class HashTableChaining<K, V> implements HashMap<K, V> {

    private List<HashtableOpen<K,V>> HashTableChain;

    /** The number of keys */
    private int numKeys = 0 ;

    /** The capacity */
    private static int CAPACITY = 101;

    /** The maximum load factor */
    private static final double LOAD_THRESHOLD = 3.0;

    /** The data field keeps filled index of table for toString method */
    private List<Integer> indexList = new ArrayList<>();

    public HashTableChaining() {
        this.HashTableChain = new ArrayList<>(CAPACITY);
        for(int i=0; i<CAPACITY; ++i)
            HashTableChain.add(i, null);

    }

    /**
     * Girilen keyi, table'da arar ve eklenen ilk key-value ikilisindeki key'i
     * return eder. Yani ilk önce "edremit-X" daha sonra "edremit-Y" eklendi ise
     * get("edremit") mettodu ilk girilen value olan X'i return eder.
     * @param key target key
     * @return the first value of target key if found, otherwise null.
     */
    @Override
    public V get(Object key) {

        if(key == null)
            return null;

        int index = key.hashCode() % CAPACITY;
        if (index < 0)
            index += CAPACITY;

        if (HashTableChain.get(index) == null)
            return null; // key is not in the table.

        return HashTableChain.get(index).get(key);

    }

    @Override
    public V put(K key, V value) {
        if(key == null || value == null)
            return null;

        if(numKeys > (LOAD_THRESHOLD * HashTableChain.size()))
            rehash();

        int index = key.hashCode() % CAPACITY;
        if (index < 0)
            index += CAPACITY;
        if (HashTableChain.get(index) == null) {
            // Create a new linked list at table[index].
            HashTableChain.set(index,new HashtableOpen());
            indexList.add(index);

        }
        numKeys++;
        return HashTableChain.get(index).put(key, value);
    }

    @Override
    public V remove(Object key) {
        int index = key.hashCode() % CAPACITY;
        if (index < 0)
            index += CAPACITY;
        if (HashTableChain.get(index) == null)
            return null; // Key not in table
        numKeys--;
        V retVal =  HashTableChain.get(index).remove(key);

        if(HashTableChain.get(index).size() == 0){
            HashTableChain.set(index,null);
            //for delete from list of indexs
            for(int i=0; i<indexList.size(); ++i)
                if(indexList.get(i).compareTo(index) == 0)
                    indexList.remove(i);

        }
        return retVal;

    }
    private void rehash() {

        for(int i=0; i<CAPACITY+1; ++i)
            HashTableChain.add(null);
        CAPACITY =CAPACITY*2 +1;

    }
    @Override
    public int size() {
        return numKeys;
    }

    @Override
    public boolean isEmpty() {
        return numKeys == 0 ;
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder("{");

        for(Integer i : indexList)
            sb.append(this.HashTableChain.get(i));

        sb.append("}");
        return sb.toString();
    }
}

