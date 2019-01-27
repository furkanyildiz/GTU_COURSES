import java.util.Iterator;

public class part3Main {

    /**
     * Demo main
     * @param args
     */
    public static void main(String[] args){

        Integer arr[][] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
        //Integer arr[][] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
        //Integer arr[][] = {{1,2,3,4, 5,6,7,8, 9,10},{11,12,13,14, 15,16,17,18, 19,20},{21,22,23,24, 25,26,27,28, 29,30}};

        Iterator p3 = new SatelliteIterator(arr);
        while (p3.hasNext()){
            System.out.print(p3.next() + " ");
        }

    }

}
