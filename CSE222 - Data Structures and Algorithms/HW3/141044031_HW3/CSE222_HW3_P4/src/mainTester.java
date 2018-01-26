
public class mainTester{

    public static void main(String[] args) {
        SingleLinkedList<Integer> s = new SingleLinkedList();
        System.out.println(s.deletedToString());
        System.out.println(s);

        for(int i =0; i<100; ++i)
            s.add(i*25+1);
        System.out.println("100 integer eklendikten sonra:");

        System.out.println(s);
        System.out.printf("Single Linked list size:%s\n",s.getSize());

        System.out.println(s.deletedToString());
        System.out.printf("Deleted Nodes size:%s\n",s.deletedSize());
        try {
            for(int i=0; i<50; ++i)
                s.remove(i*25+1);
        }catch (Exception e){
            System.out.println("Exception!!");
            System.exit(0);
        }
        System.out.println("50 integer silindikten sonra:");

        System.out.println(s);
        System.out.printf("Single Linked list size:%s\n",s.getSize());

        System.out.println(s.deletedToString());
        System.out.printf("Deleted Nodes size:%s\n",s.deletedSize());
        for(int i=0; i< 100; ++i)
            s.add(i*23+5);
        System.out.println("Tekrar 100 integer eklendikten sonra:");

        System.out.println(s);
        System.out.printf("Single Linked list size:%s\n",s.getSize());

        System.out.println(s.deletedToString());
        System.out.printf("Deleted Nodes size:%s\n",s.deletedSize());


    }
}