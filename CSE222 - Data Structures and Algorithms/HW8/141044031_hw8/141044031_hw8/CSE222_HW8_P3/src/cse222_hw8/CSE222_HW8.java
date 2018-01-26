package cse222_hw8;

/**
 *
 * @author yldzf
 */
public class CSE222_HW8 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        AVLTree avl = new AVLTree();
        avl.add(10);
        avl.add(11);
        avl.add(12);
        avl.add(13);
        avl.add(14);
        avl.add(15);
        avl.add(16);
        avl.add(17);
        avl.add(18);
        avl.add(19);
        avl.add(20);

        //System.out.println(avl);
        avl.delete(15);
        //System.out.println(avl);
        avl.delete(13);
        System.out.println(avl);

    }

}
