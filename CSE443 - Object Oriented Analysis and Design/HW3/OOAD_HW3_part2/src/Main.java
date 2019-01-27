import java.util.Iterator;

public class Main {

    public static void main(String[] args){
        EMailComponent EMailAdressBook = new GroupEmail("EMail Adress Book");
        EMailComponent arkadaslar = new GroupEmail("Arkadaşlar");
        EMailComponent cocuklukArkadaslari = new GroupEmail("Çocukluk Arkaadşları");
        EMailComponent ilkOkulArkadaslari = new GroupEmail("İlk Okul Arkadaşları");

        EMailComponent Universite = new GroupEmail("Üniversite");
        EMailComponent OgretimGorevlileri = new GroupEmail("Ogretim Gorevlileri");
        EMailComponent Asistanlar = new GroupEmail("Asistanlar");

        EMailComponent Aile = new GroupEmail("Aile");



        EMailComponent email1 = new PersonalEMail("Sami YALCIN","sami@das.com");
        EMailComponent email2 = new PersonalEMail("Mehmet DURAN","mehmet@qwe.com");

        EMailComponent email3 = new PersonalEMail("Ahmet Kamil DURSUN","ahmetkamil@dsa.com");
        EMailComponent email4 = new PersonalEMail("Sude AKSU","sude@das.com");
        EMailComponent email5 = new PersonalEMail("Hamza CELEBI","hamza@qweq.com");

        EMailComponent email6 = new PersonalEMail("Yusuf Sinan AKGUL","ysa@gtu.edu.tr");
        EMailComponent email7 = new PersonalEMail("Yakup GENC","ygenc@gtu.edu.tr");
        EMailComponent email8 = new PersonalEMail("Seyma TEKTAS","seyma@gtu.edu.tr");

        EMailComponent email9 = new PersonalEMail("Fulya YILDIZ","fulya@hotmail.com");
        EMailComponent email10 = new PersonalEMail("Kenan YILDIZ","kenan@hotmail.com");


        ilkOkulArkadaslari.add(email4);
        ilkOkulArkadaslari.add(email5);
        cocuklukArkadaslari.add(ilkOkulArkadaslari);
        cocuklukArkadaslari.add(email3);

        arkadaslar.add(cocuklukArkadaslari);
        arkadaslar.add(email1);
        arkadaslar.add(email2);

        OgretimGorevlileri.add(email6);
        OgretimGorevlileri.add(email7);

        Asistanlar.add(email8);

        Universite.add(OgretimGorevlileri);
        Universite.add(Asistanlar);

        Aile.add(email9);
        Aile.add(email10);


        EMailAdressBook.add(arkadaslar);
        EMailAdressBook.add(Universite);
        EMailAdressBook.add(Aile);

        EMailAdressBook.print();

//        Iterator<EMailComponent> iter = group1.createIterator();
//
//        while (iter.hasNext()){
//            EMailComponent mail = iter.next();
//            System.out.println(mail.getInfo());
//        }



//        Iterator it =  email1.createIterator();
//
//        while (it.hasNext()){
//            EMailComponent mail = (EMailComponent)it.next();
//            mail.print();
//        }


    }

}
