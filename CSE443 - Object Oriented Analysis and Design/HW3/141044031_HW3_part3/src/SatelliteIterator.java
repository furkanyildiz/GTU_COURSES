import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class SatelliteIterator implements Iterator {
    /**
     * Iterator of class.
     */
    private Iterator iter;
    /**
     * List to handle items of matrix with iterator traversal
     */
    private List<Integer> list;
    /**
     * Integer array to store matrix.
     */
    private Integer matrix[][];

    /**
     * Constructure. Iterates given matrix spirally clockwise.
     * @param matrix accepts array of 2D matrix.
     */
    public SatelliteIterator(Integer[][] matrix){
        this.matrix = matrix;
        list = new ArrayList<Integer>();

        iterateMatrix(0,0,matrix.length,matrix[0].length);
        iter = list.iterator();
    }

    /**
     * Iterates matrix spirally clockwise and add thems to list.
     * @param X index of row
     * @param Y index of column
     * @param lenX row number of matrix
     * @param lenY column number of matrix
     */
    private void iterateMatrix(int X,int Y, int lenX, int lenY) {

        Boolean isHorizontal = false; //yatay matris
        Boolean isVertical = false; //dusey matris

        if (lenX <= 0 || lenY <= 0)
            return;
        else if (lenX == 1 && lenY == 1){
            list.add(matrix[X][Y]);
            return;
        }
        else if (lenX == 1)
            isHorizontal = true;
        else if(lenY == 1)
            isVertical = true;


        //top left to top right
        for(int i=0; i<lenY-1; ++i)
            list.add(matrix[X][Y++]);
        //top right to bottom right
        for(int i=0; i<lenX-1; ++i)
            list.add(matrix[X++][Y]);
        if ( !isHorizontal && !isVertical) {
            //bottom right to bottom left
            for (int i = 0; i < lenY - 1; ++i)
                list.add(matrix[X][Y--]);
            //bottom left to top left
            for (int i = 0; i < lenX - 1; ++i)
                list.add(matrix[X--][Y]);
        }
        else
            list.add(matrix[X][Y]);

        iterateMatrix(++X,++Y, lenX-2, lenY-2);
    }

    /**
     * Check there is an item in next of the iterator.
     * @return true if there is an item next.
     */
    @Override
    public boolean hasNext() {
        return iter.hasNext();
    }

    /**
     * Returns next item of iterator.
     * @return next item of iterator.
     */
    @Override
    public Object next() {
        return iter.next();
    }
}
