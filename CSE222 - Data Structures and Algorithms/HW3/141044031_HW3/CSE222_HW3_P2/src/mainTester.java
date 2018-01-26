import java.io.FileNotFoundException;


public class mainTester {

    public static void main(String[] args) throws FileNotFoundException {

        myLinkedList<String > LL = new myLinkedList();

        LL.add("Merhaba");
        LL.add("ben");
        LL.add("Furkan");
        LL.add("YILDIZ");
        LL.add("141044031");
        LL.add("GTU");

        System.out.printf("LL: %s\n",LL);
        System.out.printf("Reversed LL: %s\n",LL.reverseToString());
        System.out.printf("After reversed it shouldn't be change LL: %s\n",LL);




    }

}
