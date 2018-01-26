/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package numeric_hw3_p3;


import java.util.ArrayList;
import java.util.Map;

/**
 *
 * @author yldzf
 */
public class LeastSquares {



  
    /**
     * 
     * @param coordinates
     * @param n at most degree
     */
    public Double[][] leastSquare(ArrayList<MyEntry<Double,Double>> coordinates, int n ){
        
        int m = coordinates.size();
        
        Double[][] Matrix = new Double[n+1][n+2];
        
        for(int i=0; i<n+1; ++i){
            for(int j=0; j<n+2; ++j){
                Matrix[i][j] = 0.0;
            }
            
        }
        
        for(int i =0; i<=n; ++i){
            
            Matrix[i] = fillARow(i, n+i, Matrix[i], m, coordinates);
            Matrix[i][n+1] = sumOfY(i,m,coordinates);
            
        }
        return Matrix;
        
    } 
    private Double[] fillARow(int start, int end, Double[] arr, int m, ArrayList<MyEntry<Double,Double>> coordinates) {
        int index = 0;
        for(int j=start; j<=end; ++j){
            
            for(int i=1; i<=m; ++i){
                
                arr[index] += Math.pow( coordinates.get(i-1).getKey(), j);
                
            }
            ++index;
        }
        return arr;
    }
    private Double sumOfY(int start,int m, ArrayList<MyEntry<Double,Double>> coordinates) {
        
        Double sum = 0.0;
        
        for(int i=1; i<=m; ++i){
            
            sum+= coordinates.get(i-1).getValue() * Math.pow(coordinates.get(i-1).getKey(), start);
        }
        return sum;
    }

    
}
