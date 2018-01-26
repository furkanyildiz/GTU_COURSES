package numaric_hw3_p1;

import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

/**
 *
 * @author yldzf
 */
public class Numaric_HW3_P1 {

    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Random rand = new Random();
        
        Integer[][] arr = new Integer[10][10];
        
        
        for(int i=0; i<10; ++i)
            for(int j=0; j<10; ++j)
                arr[i][j] = rand.nextInt(30) + 1 ;
        /* Random olusturulan matrix */
        for(int im=0; im<10; ++im){
            for(int j=0; j<10; ++j)
                System.out.printf("%5d  ",arr[im][j]);
            System.out.println();
        }
        System.out.println("----------------------------");
        System.out.println();

        /* Random olusturulan matrix'in zoomlayalım */
        Zoom z = new Zoom();

        Integer[][] zz = z.zoom(arr, 3, 1);
        
        int size =10*3;
        
        for(int im=0; im<size; ++im){
            for(int j=0; j<size; ++j)
                System.out.printf("%d\t",zz[im][j]);
            System.out.println();
        }
        
        
    }

}
            
       
