/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



import java.util.NavigableMap;
import java.util.TreeMap;


public class Main
{
    public static void main(String args[]){

        System.out.println("Q1--------------------------------------------------------------------------- " );

        final Boolean q1 = Q1Test();
        System.out.println("Q2--------------------------------------------------------------------------- " );

        final Boolean q2 = Q2Test();
        if (q1 == q2 == Boolean.TRUE) {
            System.out.println("Your tests is done. Make sure that you test all methods of class!! " );
            return;
        }
    }
    public static Boolean Q1Test(){

        NavigableMap<String,String> turkey = new BinaryNavMap<>();
        turkey.put("uskudar","istanbul");
        turkey.put("kadıkoy","istanbul");
        turkey.put("cekirge","bursa");
        turkey.put("gebze","kocaeli");
        turkey.put("niksar","tokat");
        turkey.put("kecıoren","ankara");
        turkey.put("aksaray","istanbul");
        turkey.put("foca","izmir");
        turkey.put("manavgat","antalya");
        turkey.put("kahta","adıyaman");
        System.out.println("biga eklendi: "+turkey.put("biga","canakkale"));

        System.out.println("The original set odds is " + turkey);
        System.out.println("The original size is " + turkey.size());
        System.out.println(turkey.entrySet());
        System.out.println("lowerEnrty of kadikoy: " + turkey.lowerEntry("kadıkoy"));
        System.out.println("lowerKey of kadikoy: " + turkey.lowerKey("kadıkoy"));

        System.out.println("floorEntry of kadikoy: " + turkey.floorEntry("kadıkoy"));
        System.out.println("floorKey of kadikoy: " + turkey.floorKey("kadıkoy"));

        System.out.println("ceilingEntry of kadikoy: " + turkey.ceilingEntry("kadıkoy"));
        System.out.println("ceilingKey of kadikoy: " + turkey.ceilingKey("kadıkoy"));

        System.out.println("higherEntry of kadikoy: " + turkey.higherEntry("kadıkoy"));
        System.out.println("higherKey of kadikoy: " + turkey.higherKey("kadıkoy"));

        System.out.println("The first entry is " +turkey.firstEntry());
        System.out.println("The first key is " +turkey.firstKey());

        System.out.println("The last entry is " +turkey.lastEntry());
        System.out.println("The last key is " +turkey.lastKey());
        turkey.descendingMap();
        System.out.println("The Descending Map is " +turkey.descendingMap());

        System.out.println("The Navigable Key Set is " +turkey.navigableKeySet());

        System.out.println("The Descending Key Set is " +turkey.descendingKeySet());

        System.out.println("The Head Map is " +turkey.headMap("gebze"));

        System.out.println("The Tail Map is " +turkey.tailMap("gebze"));

        turkey.descendingMap();
        NavigableMap<String,String> m = null ;
        try{
            m = turkey.subMap("uskudar",true,"gebze",false);
            System.out.println("The ordered set m is " + m);
            m = turkey.subMap("cekirge",true,"foca",false);
            System.out.println("The ordered set m is " + m);
        }catch(IllegalArgumentException e){
            System.out.println("IllegalArgumentException handled for subMap opearation.");
        }

        System.out.println("Poll first entry " +turkey.pollFirstEntry());
        System.out.println("After poll first entry " +turkey);

        System.out.println("Poll last entry " +turkey.pollLastEntry());
        System.out.println("After last first entry " +turkey);

        System.out.println("kecıoren'in value'sini değişirsek: " +turkey.put("kecıoren", "newCity"));
        System.out.println("kecıoren'in value'sini değişirdikten sonra: " +turkey);


        return Boolean.TRUE;

    }
    public static Boolean Q2Test(){
        HashMap<String,String> turkey=new HashTableChaining<>();
        turkey.put("edremit","balikesir");
        turkey.put("edremit","van");
        turkey.put("kemalpasa","bursa");
        turkey.put("kemalpasa","izmir");
        turkey.put("ortakoy","istanbul");//we assume a district
        turkey.put("ortakoy","aksaray");
        turkey.put("ortakoy","corum");
        turkey.put("kecıoren","ankara");
        turkey.put("pinarbasi","kastamonu");
        turkey.put("pinarbasi","kayseri");
        turkey.put("eregli","konya");
        turkey.put("eregli","tekirdag");
        turkey.put("eregli","zonguldak");
        turkey.put("golbasi","adıyaman");
        turkey.put("golbasi","ankara");
        //put method test
        System.out.println("Biga eklendi, return value: " +turkey.put("biga","canakkale"));

        //toString method test
        System.out.println(turkey);

        // size method test
        System.out.println("Size: " + turkey.size());
        turkey.get("ortakoy");
        //get method test
        System.out.println("Biga icin girilen ilk value: " +turkey.get("biga"));
        System.out.println("Eregli icin girilen ilk value: " + turkey.get("eregli"));
        System.out.println("Ortakoy icin girilen ilk value: "  + turkey.get("ortakoy"));
        System.out.println("Edremit icin girilen ilk value: "  +turkey.get("edremit"));


        //remove method tests - size method tests
        System.out.println("Edremit' in key olduğu ilk ikili siliniyor: : "  +turkey.remove("edremit"));
        System.out.println("Edremit' in key olduğu ilk ikili silindikten sonra: : "  +turkey);
        System.out.println("After deleted size: " + turkey.size());

        System.out.println("pinarbasi' in key olduğu ilk ikili siliniyor: : "  +turkey.remove("pinarbasi"));
        System.out.println("pinarbasi' in key olduğu ilk ikili silindikten sonra: : "  +turkey);
        System.out.println("After deleted size: " + turkey.size());

        System.out.println("Edremit' in key olduğu ilk ikili(ikinci kez) siliniyor: : "  +turkey.remove("edremit"));
        System.out.println("Edremit' in key olduğu ilk ikili(ikinci kez) silindikten sonra: : "  +turkey);
        System.out.println("After deleted size: " + turkey.size());

        System.out.println("Edremit' in key olduğu ilk ikili(ucuncu kez (Mapta yer almıyor)) siliniyor: : "  +turkey.remove("edremit"));
        System.out.println("Edremit' in key olduğu ilk ikili(ucuncu kez (Mapta yer almıyor)) silindikten sonra: : "  +turkey);
        System.out.println("After deleted size: " + turkey.size());


        return Boolean.TRUE;
    }
    public static void deneme()  {
        NavigableMap<String, String> turkey = new TreeMap<>();
        turkey.put("uskudar","istanbul");
        turkey.put("kadıkoy","istanbul");
        turkey.put("cekirge","bursa");
        turkey.put("gebze","kocaeli");
        turkey.put("niksar","tokat");
        turkey.put("kecıoren","ankara");
        turkey.put("aksaray","istanbul");
        turkey.put("foca","izmir");
        turkey.put("manavgat","antalya");
        turkey.put("kahta","adıyaman");
        turkey.put("biga","canakkale");


        System.out.println("The original set odds is " + turkey);
        System.out.println(turkey.entrySet());
        System.out.println("lowerEnrty of kadikoy: " + turkey.lowerEntry("kadıkoy"));
        System.out.println("lowerKey of kadikoy: " + turkey.lowerKey("kadıkoy"));

        System.out.println("floorEntry of kadikoy: " + turkey.floorEntry("kadıkoy"));
        System.out.println("floorKey of kadikoy: " + turkey.floorKey("kadıkoy"));

        System.out.println("ceilingEntry of kadikoy: " + turkey.ceilingEntry("kadıkoy"));
        System.out.println("ceilingKey of kadikoy: " + turkey.ceilingKey("kadıkoy"));

        System.out.println("higherEntry of kadikoy: " + turkey.higherEntry("kadıkoy"));
        System.out.println("higherKey of kadikoy: " + turkey.higherKey("kadıkoy"));

        System.out.println("The first entry is " +turkey.firstEntry());
        System.out.println("The first key is " +turkey.firstKey());

        System.out.println("The last entry is " +turkey.lastEntry());
        System.out.println("The last key is " +turkey.lastKey());

        System.out.println("The Descending Map is " +turkey.descendingMap());

        System.out.println("The Navigable Key Set is " +turkey.navigableKeySet());

        System.out.println("The Descending Key Set is " +turkey.descendingKeySet());

        System.out.println("The Head Map is " +turkey.headMap("gebze"));

        System.out.println("The Tail Map is " +turkey.tailMap("gebze"));


        NavigableMap<String,String> m = null ;
        try{
            m = turkey.subMap("uskudar",true,"gebze",false);
            System.out.println("The ordered set m is " + m);
            m = turkey.subMap("cekirge",true,"foca",false);
            System.out.println("The ordered set m is " + m);
        }catch(IllegalArgumentException e){
            System.out.println("IllegalArgumentException handled for subMap opearation.");
        }
        System.out.println("Poll first entry " +turkey.pollFirstEntry());
        System.out.println("After poll first entry " +turkey);

        System.out.println("Poll last entry " +turkey.pollLastEntry());
        System.out.println("After last first entry " +turkey);

    }


}

