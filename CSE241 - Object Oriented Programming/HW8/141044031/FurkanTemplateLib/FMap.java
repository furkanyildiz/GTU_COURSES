package FurkanTemplateLib;
import java.util.*;
@SuppressWarnings({"rawtypes", "unchecked"})

/**
 *
 * @author yldzf
 * @param <K>
 * @param <V>
 */
public class FMap<K  ,V> {
    private FPair<K,V>[] data;
    int capacity=23;
    int used=0;
    //No param constrcutre calls int param constrcutre
    public FMap(){
        this(23);
    }
    //int param constucture allocates memory for pair arrays.
    public FMap(int cap){
        super();
        capacity=cap;
        used =0;
        data = new FPair[ capacity];
        for(int i=0; i< capacity; ++i)
            data[i] = new FPair<K,V>();
    }
    //Copy constructure
    public FMap(FMap other)throws Exception{
        if(other == null)
            throw new NullPointerException();
        this.data = new FPair[other.getCap()];
        for(int i=0; i<other.getUsed(); ++i)
            this.data[i] = new FPair(other.data[i]);
        this.setUsed(other.getUsed());
    }
    //This methods add pair into data
    public void put(K key, V value){
        if(used>=capacity)
            extendCap();
        data[used].setFirst(key);
        data[used].setSecond(value);
        ++used;
    }
    //This method returns used value of data.
    public int getUsed(){
        return used;
    }
    //This method returns capacity of data.
    public int getCap(){
        return capacity;
    }
    //This method returns a key according to data's index.
    public K getKey(int i){
        return data[i].getFirst();
    }
    //This method returns a value according to data's index.
    public V getVal(int i){
        return data[i].getSecond();
    }
    //This method sets capacity value
    private void setCap(int cap){
        capacity = cap;
    }
    //This method sets used value
    private void setUsed(int size){
        used=size;
    }
    //This method extends capacity. if capacity is full, the method should call.
    private void extendCap(){
        setCap(getCap()*2+1);
        data = Arrays.copyOf(data, getCap());
        for(int i=getUsed(); i<getCap(); ++i)
            data[i] = new FPair<K,V>();
    }
    //This method set capacity to zero.
    public void empty(){
        setCap(0);
    }
    //This method search a value into Pair arrays.
    public FPair<K, V> search(K value){
        
        for(int i=0; i<getUsed(); ++i)
            if(data[i].getFirst().equals(value))//equals override edilecek
                return data[i];
        return null;
    }
}