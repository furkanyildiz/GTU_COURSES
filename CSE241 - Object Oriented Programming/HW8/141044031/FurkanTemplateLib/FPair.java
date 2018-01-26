package FurkanTemplateLib;
import java.util.*; 
@SuppressWarnings({"rawtypes", "unchecked"})

/**
 *
 * @author yldzf
 * @param <A>
 * @param <B>
 */
public class FPair<A,B> {
    private A first;
    private B second;
    //This constructure assigns given values as a parameters to datas
    public FPair(A first, B second) {
        super();
        this.first = first;
        this.second = second;
    }
    //No param constructure assigns null to datas
    public FPair() {
        this(null,null);
    }
    //Copy constructure
    public FPair( FPair<A,B> other)throws Exception{
        System.out.println("Pair const");
        if(other == null)
            throw new NullPointerException();

        this.first=other.first;
        this.second=other.second;
    }
    //HashCode
    public int hashCode() {
        int hashFirst = first != null ? first.hashCode() : 0;
        int hashSecond = second != null ? second.hashCode() : 0;

        return (hashFirst + hashSecond) * hashSecond + hashFirst;
    }
    //This methods check given 2 Pair are same or not.
    public boolean equals(Object other) {
        if (other instanceof FPair) {
            @SuppressWarnings("unchecked")
            FPair<A,B> otherPair = (FPair<A,B>) other;
            return 
            ((  this.first == otherPair.first ||
                ( this.first != null && otherPair.first != null &&
                  this.first.equals(otherPair.first))) &&
             (  this.second == otherPair.second ||
                ( this.second != null && otherPair.second != null &&
                  this.second.equals(otherPair.second))) );
        }

        return false;
    }
    //toString returns a string which have data values as a string
    public String toString(){ 
       return "(" + first + ", " + second + ")"; 
    }
    //This method returns first value of pair
    public A getFirst() {
        return first;
    }
    //This method sets first value of pair
    public void setFirst(A first) {
        this.first = first;
    }
    //This method returns second value of pair
    public B getSecond() {
        return second;
    }
    //This method sets second value of pair
    public void setSecond(B second) {
        this.second = second;
    }

}