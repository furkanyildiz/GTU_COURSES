package numaric_hw3_p1;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author yldzf
 */
public class Zoom {
    private Integer[][] zoomed;
    public Zoom(){
        
    }
    
    public Integer[][] zoom(Integer matrix[][], int z, int s){
        
        if(s != 1 && s!= 2 && s!=3)
            return null;
        
        switch (s) {
            case 1://Neıgbour
                return zoomS1(matrix,z);
            case 2://linear
                return null;
            default://cubic
                return null;
        }
            
    }
    
    
    private Integer[][] zoomS1(Integer matrix[][], int z){
    
        if(matrix.length != 10 || matrix[0].length != 10)
            return null;
        
        int zoom = 10 * z;
        
        zoomed = new Integer[zoom][zoom];
        
        Integer[] oneD = convert1D(matrix);
        
        int size = zoom * zoom ;
        int len = 10;
        int index = 0;
        for(int x =0; x<zoom; x+=z){
            
            for(int y=0; y<zoom; y+=z){
                replaceAElemnet(oneD[index++], x,y,z,zoom);
            }
            
        }
        return zoomed;
    }
    private void replaceAElemnet(Integer elem, int startx, int starty, int len, int size){
        
        int count = 0;
        int m = 0, n =0;
        for(int i =startx; n< len; i++){
            m = 0;
            for(int j=starty; m<len; ++j){
                
                zoomed[i][j] = elem;
                m++;
            }
            n++;
        }
    }
        
    /**
     * http://stackoverflow.com/questions/8935367/convert-a-2d-array-into-a-1d-array
     * @param arr
     * @return 
     */
    private Integer[] convert1D(Integer[][] arr) {
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[i].length; j++) { 
                list.add(arr[i][j]); 
            }
        }
        Integer[] vector = new Integer[list.size()];
        for (int i = 0; i < vector.length; i++) {
            vector[i] = list.get(i);
        }
        return vector;
    }
    
    
    
}
/*




package numaric_hw3_p1;

import java.util.ArrayList;
import java.util.List;


public class Zoom {
    private Integer[][] zoomed;

    public Integer[][] zoomS1(Integer matrix[][], int z, int s){
    
        if(matrix.length != 10 || matrix[0].length != 10)
            return null;
        
        int zoom = 10 * z;
        
        zoomed = new Integer[zoom][zoom];
        
        Integer[] oneD = convert1D(matrix);
        
        int size = zoom * zoom ;
        int len = 10;
        int index = 0;
        for(int x =0; x<zoom; x+=len){
            
            for(int y=0; y<zoom; y+=len){
                replaceAElemnet(oneD[index++], x,y,len,zoom);
            }
            
        }
        return zoomed;
    }
    private void replaceAElemnet(Integer elem, int startx, int starty, int len, int size){
        
        int count = 0;
        int m = 0, n =0;
        for(int i =startx; n< len; i++){
            m = 0;
            for(int j=starty; m<len; ++j){
                
                zoomed[i][j] = elem;
                m++;
            }
            n++;
        }
    }
        

    private Integer[] convert1D(Integer[][] arr) {
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[i].length; j++) { 
                list.add(arr[i][j]); 
            }
        }
        Integer[] vector = new Integer[list.size()];
        for (int i = 0; i < vector.length; i++) {
            vector[i] = list.get(i);
        }
        return vector;
    }
    
    
    
}






*/