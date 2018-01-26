/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package numeric_hw3_p3;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author yldzf
 */
public class Numeric_HW3_P3 {
    
    public static void main(String[] args) {

        MyEntry<Double,Double> m1 = new MyEntry(0.0,1.0000);
        MyEntry<Double,Double> m2 = new MyEntry(0.25,1.2840);
        MyEntry<Double,Double> m3 = new MyEntry(0.50,1.6487);
        MyEntry<Double,Double> m4 = new MyEntry(0.75,2.1170);
        MyEntry<Double,Double> m5 = new MyEntry(1.0,2.7183);
        
        
        ArrayList<MyEntry<Double,Double>> arr = new ArrayList<>();
        
        arr.add(m1);
        arr.add(m2);
        arr.add(m3);
        arr.add(m4);
        arr.add(m5);
        
        LeastSquares l = new LeastSquares();
        
        Double[][] m = l.leastSquare(arr, 2);
        for(int i=0; i<m.length; ++i){
            for(int j=0; j<m[0].length; ++j){
                System.out.printf("%f   ",m[i][j]);
            }
            System.out.println();

        }
        GESP g = new GESP();
        ArrayList<Double> s = null; 
        try {
            s = g.gaus(m);
        } catch (ArithmeticException ex) {
            Logger.getLogger(Numeric_HW3_P3.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(Numeric_HW3_P3.class.getName()).log(Level.SEVERE, null, ex);
        }
        System.out.println(s);
    }
}

