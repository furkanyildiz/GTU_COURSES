import java.util.*;

public class BinaryNavMap<K ,V> extends AbstractMap<K,V>
        implements NavigableMap<K,V>, Cloneable, java.io.Serializable
{
    /** Binary search tree */
    private BinarySearchTree<myEntry<K,V>> bstmap;
    /** Comparator */
    Comparator < K > comparator = null;

    public BinaryNavMap() {
        this.bstmap = new BinarySearchTree<>();
    }

    public BinaryNavMap(Comparator c) {
        this.bstmap = new BinarySearchTree<>();
        comparator = c;
    }

    public BinaryNavMap(K key, V value) {
        this.bstmap = new BinarySearchTree<>(new myEntry<>(key,value));
    }

    public BinaryNavMap(K key, V value, Comparator c) {
        this.bstmap = new BinarySearchTree<>(new myEntry<>(key,value));
        comparator = c;
    }

    @Override
    public V put(K k, V v){
        myEntry<K,V> ent = new myEntry<>(k,v);
        bstmap.add(ent);
        return v;
    }
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder("{");
        Iterator itr = this.iterator();
        while(itr.hasNext())
            sb.append(itr.next()).append(", ");
        sb.deleteCharAt(sb.length()-2);
        sb.append("}");
        return sb.toString();
    }
    /**
     * To traverse In-order tree
     * @return In-order iterator
     */
    public Iterator iterator() {
        return new treeIterator(bstmap.root);
    }

    protected class treeIterator implements Iterator{
        Stack<BinaryTree.Node> stack;

        public treeIterator(BinaryTree.Node root) {
            stack = new Stack<>();
            while (root != null) {
                stack.push(root);
                root = root.left;
            }
        }

        @Override
        public boolean hasNext() {
            return !stack.isEmpty();
        }

        @Override
        public myEntry<K,V> next() {
            BinaryTree.Node node = stack.pop();
            myEntry<K,V> result = (myEntry<K,V>) node.data;
            if (node.right != null) {
                node = node.right;
                while (node != null) {
                    stack.push(node);
                    node = node.left;
                }
            }
            return result;
        }
    }

    private class myEntry < K , V > implements Comparable<myEntry<K,V>>,Map.Entry<K,V>  {
        /** The key */
        private K key;

        /** The value */
        private V value;

        /** Creates a new key-value pair.
         @param key The key
         @param value The value
         */
        public myEntry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        /** Retrieves the key.
         @return The key
         */
        @Override
        public K getKey() {
            return key;
        }

        /** Retrieves the value.
         @return The value
         */
        @Override
        public V getValue() {
            return value;
        }

        @Override
        public int compareTo(myEntry<K, V> o) {

            return compare(this.key,o.key);
        }

        @Override
        public V setValue(V val) {
            V oldValue = value;
            value = val;
            return oldValue;
        }
        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append(key).append("=").append(value);
            return sb.toString();
        }
        private int compare(K k1, K k2) {
            if (comparator != null)  // A Comparator is defined.
                return compare(k1, k2);

            else  // Use left’s compareTo method.
                return ( (Comparable < K > ) k1).compareTo(k2);

        }
    }

    @Override
    public Set<Map.Entry<K, V>> entrySet() {

        Set<Map.Entry<K, V>> set = new TreeSet<>();
        Iterator itr = iterator();
        while(itr.hasNext())
            set.add((Entry<K, V>) itr.next());

        return set;
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * strictly less than the given key, or {@code null} if there is
     * no such key.
     *
     * @param key the key
     * @return an entry with the greatest key less than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Map.Entry<K, V> lowerEntry(K key) {
        if(key == null)
            return null;
        Iterator<myEntry<K,V>> itr = this.iterator();
        myEntry<K,V> k = null;
        myEntry<K,V> prev = null;
        while(itr.hasNext()){
            k = itr.next();
            if(compare(k.key, key) >= 0)
                break;
            prev = k;

        }
        return prev;
    }


    /**
     * Returns the greatest key strictly less than the given key, or
     * {@code null} if there is no such key.
     *
     * @param key the key
     * @return the greatest key less than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K lowerKey(K key) {
        if(key == null)
            return null;
        return lowerEntry(key).getKey();
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * less than or equal to the given key, or {@code null} if there
     * is no such key.
     *
     * @param key the key
     * @return an entry with the greatest key less than or equal to
     * {@code key}, or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Map.Entry<K, V> floorEntry(K key) {
        if(key == null)
            return null;
        Iterator<myEntry<K,V>> itr = this.iterator();
        myEntry<K,V> k = null;
        myEntry<K,V> prev = null;
        while(itr.hasNext()){
            k = itr.next();
            if(compare(k.key, key) > 0)
                break;
            prev = k;

        }
        return prev;
    }

    /**
     * Returns the greatest key less than or equal to the given key,
     * or {@code null} if there is no such key.
     *
     * @param key the key
     * @return the greatest key less than or equal to {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K floorKey(K key) {
        if(key == null)
            return null;
        return floorEntry(key).getKey();
    }

    /**
     * Returns a key-value mapping associated with the least key
     * greater than or equal to the given key, or {@code null} if
     * there is no such key.
     *
     * @param key the key
     * @return an entry with the least key greater than or equal to
     * {@code key}, or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Map.Entry<K, V> ceilingEntry(K key) {
        if(key == null)
            return null;
        myEntry<K, V> returnVal = null;
        Iterator<myEntry<K,V>> itr = this.iterator();
        while(itr.hasNext()){
            returnVal = itr.next();
            if(compare(returnVal.key, key) >= 0)
                return returnVal;
        }
        return returnVal;
    }

    /**
     * Returns the least key greater than or equal to the given key,
     * or {@code null} if there is no such key.
     *
     * @param key the key
     * @return the least key greater than or equal to {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K ceilingKey(K key) {
        if(key == null)
            return null;
        return ceilingEntry(key).getKey();
    }

    /**
     * Returns a key-value mapping associated with the least key
     * strictly greater than the given key, or {@code null} if there
     * is no such key.
     *
     * @param key the key
     * @return an entry with the least key greater than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Map.Entry<K, V> higherEntry(K key) {
        if(key == null)
            return null;
        myEntry<K, V> returnVal = null;
        Iterator<myEntry<K,V>> itr = this.iterator();
        while(itr.hasNext()){
            returnVal = itr.next();
            if(compare(returnVal.key, key) > 0)
                return returnVal;
        }
        return returnVal;
    }

    /**
     * Returns the least key strictly greater than the given key, or
     * {@code null} if there is no such key.
     *
     * @param key the key
     * @return the least key greater than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K higherKey(K key) {
        if(key == null)
            return null;
        return higherEntry(key).getKey();

    }

    /**
     * Returns a key-value mapping associated with the least
     * key in this map, or {@code null} if the map is empty.
     *
     * @return an entry with the least key,
     * or {@code null} if this map is empty
     */
    @Override
    public Map.Entry<K, V> firstEntry() {
        Iterator<myEntry<K,V>> itr = this.iterator();
        if(itr.hasNext())
            return itr.next();
        else
            return null;
    }

    /**
     * Returns a key-value mapping associated with the greatest
     * key in this map, or {@code null} if the map is empty.
     *
     * @return an entry with the greatest key,
     * or {@code null} if this map is empty
     */
    @Override
    public Map.Entry<K, V> lastEntry() {
        Iterator<myEntry<K,V>> itr = this.iterator();
        myEntry retVal = null;
        if(!itr.hasNext())
            return retVal;
        else
            while(itr.hasNext())
                retVal = itr.next();
        return retVal;
    }
    /**
     * Removes and returns a key-value mapping associated with
     * the least key in this map, or {@code null} if the map is empty.
     *
     * @return the removed first entry of this map,
     * or {@code null} if this map is empty
     */
    @Override
    public Map.Entry<K, V> pollFirstEntry() {
        if(bstmap.root == null)
            return null;
        myEntry<K, V> ret = (myEntry<K, V>) firstEntry();
        if(bstmap.find(ret) == null)
            return null;
        bstmap.delete(ret);
        return ret;
    }

    /**
     * Removes and returns a key-value mapping associated with
     * the greatest key in this map, or {@code null} if the map is empty.
     *
     * @return the removed last entry of this map,
     * or {@code null} if this map is empty
     */
    @Override
    public Map.Entry<K, V> pollLastEntry() {
        if(bstmap.root == null)
            return null;
        myEntry<K, V> ret = (myEntry<K, V>) lastEntry();
        if(bstmap.find(ret) == null)
            return null;
        bstmap.delete(ret);
        return ret;
    }

    /**
     * Returns a reverse order view of the mappings contained in this map.
     * The descending map is backed by this map, so changes to the map are
     * reflected in the descending map, and vice-versa.  If either map is
     * modified while an iteration over a collection view of either map
     * is in progress (except through the iterator's own {@code remove}
     * operation), the results of the iteration are undefined.
     * <p>
     * <p>The returned map has an ordering equivalent to
     * <tt>{@link Collections#reverseOrder(Comparator) Collections.reverseOrder}(comparator())</tt>.
     * The expression {@code m.descendingMap().descendingMap()} returns a
     * view of {@code m} essentially equivalent to {@code m}.
     *
     * @return a reverse order view of this map
     */
    @Override
    public NavigableMap<K, V> descendingMap() {

        myEntry<K, V> returnVal = null;
        Stack s = new Stack();
        Iterator<myEntry<K,V>> itr = this.iterator();
        while(itr.hasNext()){
            returnVal = itr.next();
            s.add(returnVal);
        }
        NavigableMap<K, V> descendingmap = new BinaryNavMap<>();
        while(!s.isEmpty()){
            myEntry<K, V> poped = (myEntry<K, V>) s.pop();
            descendingmap.put(poped.key,poped.value);
        }

        return descendingmap;

    }

    /**
     * Returns a {@link NavigableSet} view of the keys contained in this map.
     * The set's iterator returns the keys in ascending order.
     * The set is backed by the map, so changes to the map are reflected in
     * the set, and vice-versa.  If the map is modified while an iteration
     * over the set is in progress (except through the iterator's own {@code
     * remove} operation), the results of the iteration are undefined.  The
     * set supports element removal, which removes the corresponding mapping
     * from the map, via the {@code Iterator.remove}, {@code Set.remove},
     * {@code removeAll}, {@code retainAll}, and {@code clear} operations.
     * It does not support the {@code add} or {@code addAll} operations.
     *
     * @return a navigable set view of the keys in this map
     */
    @Override
    public NavigableSet<K> navigableKeySet() {
        NavigableSet<K> set = new TreeSet<>();
        Iterator<Entry<K, V>> itr = this.iterator();
        while(itr.hasNext())
            set.add(itr.next().getKey());

        return set;
    }

    /**
     * Returns a reverse order {@link NavigableSet} view of the keys contained in this map.
     * The set's iterator returns the keys in descending order.
     * The set is backed by the map, so changes to the map are reflected in
     * the set, and vice-versa.  If the map is modified while an iteration
     * over the set is in progress (except through the iterator's own {@code
     * remove} operation), the results of the iteration are undefined.  The
     * set supports element removal, which removes the corresponding mapping
     * from the map, via the {@code Iterator.remove}, {@code Set.remove},
     * {@code removeAll}, {@code retainAll}, and {@code clear} operations.
     * It does not support the {@code add} or {@code addAll} operations.
     *
     * @return a reverse order navigable set view of the keys in this map
     */
    @Override
    public NavigableSet<K> descendingKeySet() {
        myEntry<K, V> returnVal = null;
        Stack<K> keyStack = new Stack();
        Iterator<myEntry<K,V>> itr = this.iterator();
        while(itr.hasNext()){
            returnVal = itr.next();
            keyStack.add(returnVal.key);
        }
        NavigableSet<K> navigableKeySet = new TreeSet();
        while(!keyStack.isEmpty()){
            K poped =  keyStack.pop();
            navigableKeySet.add(poped);
        }
        return  navigableKeySet;
    }

    /**
     * Returns a view of the portion of this map whose keys range from
     * {@code fromKey} to {@code toKey}.  If {@code fromKey} and
     * {@code toKey} are equal, the returned map is empty unless
     * {@code fromInclusive} and {@code toInclusive} are both true.  The
     * returned map is backed by this map, so changes in the returned map are
     * reflected in this map, and vice-versa.  The returned map supports all
     * optional map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside of its range, or to construct a
     * submap either of whose endpoints lie outside its range.
     *
     * @param fromKey       low endpoint of the keys in the returned map
     * @param fromInclusive {@code true} if the low endpoint
     *                      is to be included in the returned view
     * @param toKey         high endpoint of the keys in the returned map
     * @param toInclusive   {@code true} if the high endpoint
     *                      is to be included in the returned view
     * @return a view of the portion of this map whose keys range from
     * {@code fromKey} to {@code toKey}
     * @throws ClassCastException       if {@code fromKey} and {@code toKey}
     *                                  cannot be compared to one another using this map's comparator
     *                                  (or, if the map has no comparator, using natural ordering).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code fromKey} or {@code toKey}
     *                                  cannot be compared to keys currently in the map.
     * @throws NullPointerException     if {@code fromKey} or {@code toKey}
     *                                  is null and this map does not permit null keys
     * @throws IllegalArgumentException if {@code fromKey} is greater than
     *                                  {@code toKey}; or if this map itself has a restricted
     *                                  range, and {@code fromKey} or {@code toKey} lies
     *                                  outside the bounds of the range
     */
    @Override
    public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
        if(fromKey == null || toKey == null)
            throw new NullPointerException();

        if(compare(fromKey,toKey) > 0)
            throw new IllegalArgumentException();

        myEntry<K, V> nexItem = null;
        NavigableMap<K, V> submap = new BinaryNavMap<>();
        Iterator<myEntry<K,V>> itr = this.iterator();

        while(itr.hasNext()){
            nexItem = itr.next();
            if(compare(nexItem.key, fromKey) == 0 && fromInclusive)
                submap.put(nexItem.key, nexItem.value);
            else if(compare(nexItem.key, toKey) == 0 && toInclusive)
                submap.put(nexItem.key, nexItem.value);
            else if(compare(nexItem.key, fromKey)  >  0 && compare(nexItem.key, toKey)  <  0)
                submap.put(nexItem.key, nexItem.value);
        }
        return submap;
    }

    /**
     * Returns a view of the portion of this map whose keys are less than (or
     * equal to, if {@code inclusive} is true) {@code toKey}.  The returned
     * map is backed by this map, so changes in the returned map are reflected
     * in this map, and vice-versa.  The returned map supports all optional
     * map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside its range.
     *
     * @param toKey     high endpoint of the keys in the returned map
     * @param inclusive {@code true} if the high endpoint
     *                  is to be included in the returned view
     * @return a view of the portion of this map whose keys are less than
     * (or equal to, if {@code inclusive} is true) {@code toKey}
     * @throws ClassCastException       if {@code toKey} is not compatible
     *                                  with this map's comparator (or, if the map has no comparator,
     *                                  if {@code toKey} does not implement {@link Comparable}).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code toKey} cannot be compared to keys
     *                                  currently in the map.
     * @throws NullPointerException     if {@code toKey} is null
     *                                  and this map does not permit null keys
     * @throws IllegalArgumentException if this map itself has a
     *                                  restricted range, and {@code toKey} lies outside the
     *                                  bounds of the range
     */
    @Override
    public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
        return subMap(firstKey(), true, toKey, inclusive);
    }

    /**
     * Returns a view of the portion of this map whose keys are greater than (or
     * equal to, if {@code inclusive} is true) {@code fromKey}.  The returned
     * map is backed by this map, so changes in the returned map are reflected
     * in this map, and vice-versa.  The returned map supports all optional
     * map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside its range.
     *
     * @param fromKey   low endpoint of the keys in the returned map
     * @param inclusive {@code true} if the low endpoint
     *                  is to be included in the returned view
     * @return a view of the portion of this map whose keys are greater than
     * (or equal to, if {@code inclusive} is true) {@code fromKey}
     * @throws ClassCastException       if {@code fromKey} is not compatible
     *                                  with this map's comparator (or, if the map has no comparator,
     *                                  if {@code fromKey} does not implement {@link Comparable}).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code fromKey} cannot be compared to keys
     *                                  currently in the map.
     * @throws NullPointerException     if {@code fromKey} is null
     *                                  and this map does not permit null keys
     * @throws IllegalArgumentException if this map itself has a
     *                                  restricted range, and {@code fromKey} lies outside the
     *                                  bounds of the range
     */
    @Override
    public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
        return subMap(fromKey, inclusive, lastKey(), true);
    }

    protected int compare(K left, K right) {
        if (comparator != null) { // A Comparator is defined.
            return comparator.compare(left, right);
        }
        else { // Use left’s compareTo method.
            return ( (Comparable < K > ) left).compareTo(right);
        }
    }

    /**
     * Returns the comparator used to order the keys in this map, or
     * {@code null} if this map uses the {@linkplain Comparable
     * natural ordering} of its keys.
     *
     * @return the comparator used to order the keys in this map,
     * or {@code null} if this map uses the natural ordering
     * of its keys
     */
    @Override
    public Comparator<? super K> comparator() {
        return null;
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code subMap(fromKey, true, toKey, false)}.
     *
     * @param fromKey
     * @param toKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> subMap(K fromKey, K toKey) {
        return subMap(fromKey, true, toKey, false);
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code headMap(toKey, false)}.
     *
     * @param toKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> headMap(K toKey) {
        return headMap(toKey, false);
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code tailMap(fromKey, true)}.
     *
     * @param fromKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> tailMap(K fromKey) {
        return tailMap(fromKey, true);
    }

    /**
     * Returns the first (lowest) key currently in this map.
     *
     * @return the first (lowest) key currently in this map
     * @throws NoSuchElementException if this map is empty
     */
    @Override
    public K firstKey() {
        return firstEntry().getKey();
    }

    /**
     * Returns the last (highest) key currently in this map.
     *
     * @return the last (highest) key currently in this map
     * @throws NoSuchElementException if this map is empty
     */
    @Override
    public K lastKey() {
        return lastEntry().getKey();
    }
}