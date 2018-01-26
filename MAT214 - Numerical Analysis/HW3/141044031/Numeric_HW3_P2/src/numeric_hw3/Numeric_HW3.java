package numeric_hw3;

import java.util.ArrayList;
import java.util.Map;

/**
 *
 * @author yldzf
 */
public class Numeric_HW3 {

    public static class MyEntry<K, V> implements Map.Entry<K, V> {
        private final K x;
        private V y;

        public MyEntry(K key, V value) {
            this.x = key;
            this.y = value;
        }

        @Override
        public K getKey() {
            return x;
        }

        @Override
        public V getValue() {
            return y;
        }

        @Override
        public V setValue(V value) {
            V old = this.y;
            this.y = value;
            return old;
        }
    }
    
    
    public static void main(String[] args) {


        MyEntry<Double,Double> m1 = new MyEntry(1.0,0.7651977);
        MyEntry<Double,Double> m2 = new MyEntry(1.3,0.6200860);
        MyEntry<Double,Double> m3 = new MyEntry(1.6,0.4554022);
        MyEntry<Double,Double> m4 = new MyEntry(1.9,0.2818186);
        MyEntry<Double,Double> m5 = new MyEntry(2.2,0.1103623);
        
        
        ArrayList<MyEntry<Double,Double>> arr = new ArrayList<>();
        
        arr.add(m1);
        arr.add(m2);
        arr.add(m3);
        arr.add(m4);
        arr.add(m5);

        
        String result = DividedDifference(arr);
        
        System.out.println(result);
        
        
    }
        
        

    public static String DividedDifference(ArrayList<MyEntry<Double,Double>> coordinates){
        Double[] x = new Double[coordinates.size()]; 
        Double[] y = new Double[coordinates.size()];
        int i = 0;
        for(MyEntry<Double,Double> aCortdinate  : coordinates){
            
            x[i] = aCortdinate.getKey();
            y[i] = aCortdinate.getValue();
            i++;
        }
        
        
        return dividedDifferences(x,y);
        
    }
    
    public static String dividedDifferences (Double[] x, Double[] y) {
        int n = x.length;
        Double[] dividedDifferencesArr = y.clone();
        for(int i=1; i<n; i++) {
            for(int j=n-1; j>0; j--) {
                if(j-i>=0)
                  dividedDifferencesArr[j] = (dividedDifferencesArr[j]-dividedDifferencesArr[j-1])/(x[j]-x[j-i]);

            }
        }
        
        StringBuilder sum = new StringBuilder(dividedDifferencesArr[0].toString());
        sum.append(" ");
        StringBuilder mult;
        for(int i=1; i<dividedDifferencesArr.length; ++i){
            mult = new StringBuilder();
            for(int j=0; j<=i-1; ++j){
                mult.append("(x - ").append(x[j]).append(") ");
            }
            sum.append(dividedDifferencesArr[i].toString()).append("(").append(mult).append(") + ");
        }
        sum.deleteCharAt(sum.length()-2);
        return sum.toString();
        
    }
}
