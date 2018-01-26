/* 
 * File:   CPU.cpp
 * Author: FURKAN YILDIZ
 * 
 * Created on October 21, 2016, 9:20 PM
 */

#include "CPU.h"
#include <iostream>

using namespace std;

/* Bu constructure obje olusturulurken herhangibir ilk atama yapilmak istenmeden
 olusturulmussa calisacak ve registerlere sifir, PC ye 1 atiyacak.*/
CPU :: CPU(){
    setR1(0);
    setR2(0);
    setR3(0);
    setR4(0);
    setR5(0);
    setPC(1);
}
/* Bu constructure objeyi olustururken eger ilk degerler atanmak isteyerek 
 olusturulursa cagırılacak ve eger registerlere sifirdan, PC ye 1 den
 farklı deger atanmissa uyari verip registelere sifir, PC ye 1 atiyacak.*/
CPU :: CPU(int Reg1,int Reg2,int Reg3,int Reg4,int Reg5, int ProgC)
{
    if(Reg1 != 0 && Reg2!= 0 && Reg3!=0 && Reg4!=0 && Reg5!=0 && ProgC!=1)
        cerr << "All registers must be 0 and Program Counter must be 1, So"
                "I done it"<<endl;
    
    CPU();
}
void CPU :: print()const{
    
    cout << "R1:" << getR1() <<" R2:" << getR2()
         <<" R3:" << getR3() <<" R4:" << getR4()
         <<" R5:" << getR5() <<" PC:" << getPC() << endl;
    return;
    
}
/* execute fonksiyonu komut satirinin icerdigi bir string alir, aldigi bu
 * stringdeki komutlari calistirir ve program counteri update eder.
 */
int  CPU :: execute(string& instructionLine){
    string command, string1,string2;
    int returnValueOfCommands = 0 ;
    divideInst(instructionLine,command, string1,string2);
    ToMyUpper(command);
    if(command == "MOV")
        returnValueOfCommands = MOV(string1,string2);
    else if(command == "ADD")
        returnValueOfCommands = ADD(string1,string2);
    else if(command == "SUB")
        returnValueOfCommands = SUB(string1,string2);
    else if(command == "PRN")
        returnValueOfCommands = PRN(string1);
    else if(command == "JMP")
        returnValueOfCommands = JMP(string1,string2);
    else if(command == "HLT")
        setHlt(true);
    
    int updatePC = getPC() +1 ; // her satir okunduktan sonra PC 1 arttirilir
    setPC(updatePC);
    
    if(returnValueOfCommands == -1)
        return -1;
    return 0;
}
/*divideInst fonksiyonu dort adet string alir, 1. stringi dolu, digerlerini
 * bos olarak alır. Amaci, 1. parametre olarak aldigi komut satirini 3 e bolmek 
 * ve boylece order , firstString , secondString parametrelerini doldurmaktır.
 * Ornegin CurrentLine "MOV R1,R2" ise order a "MOV", firstString e "R1",
 * secondString e "R2" yazacaktir.
 * Fonksiyon islerini basari ile bitirirse 0, bitiremezse -1 return eder.
 */
void CPU :: divideInst(const string& currentLine, string& order, 
                         string& firstString, string& secondString)const{
    //Bastaki ve orderdan sonraki bosluklar siliniyor 1 bosluk bırakiliyor
    //orderdan sonra, dolayısıyla ilk okunacak index order'ın size'ı +1 (bosluk)
    //yani 4 oluyor.
    int firstStrIndex = 4;
    int sizeOfStr1 = 0;
    int sizeOfLine = currentLine.size();
    
    order = currentLine.substr(0,3);
    if(order != "HLT"){

        int loopCounter = firstStrIndex ;
        while(currentLine[loopCounter] != ' ' && currentLine[loopCounter]!= ','
          &&currentLine[loopCounter] != ';' && currentLine[loopCounter]!= '\0'){
            sizeOfStr1++;
            loopCounter++;
        }
        firstString = currentLine.substr(firstStrIndex,sizeOfStr1) ;
    }
    if(order == "PRN" || (order == "JMP"  && (currentLine[firstStrIndex]!='r' 
                                          &&  currentLine[firstStrIndex]!='R')))
        secondString="";
    else if(order == "HLT"){
        firstString="";
        secondString="";
    }
    else{
        int indexComma = currentLine.find_first_of(',');

        secondString = currentLine.substr(indexComma + 1, sizeOfLine - 
                                                               (indexComma +1));
    }
    return;
}
/*MOV fonksiyonu parametre olarak 2 string alacak
 *1. parametre register, 2. parametre const ise const degeri registere atiyacak
 *1. ve 2. parametre register ise 1. registerdeki degeri 2. registere atiyacak
 *islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek 
 */
int CPU :: MOV(const string& registerA,const string& registerB){
    if(isItRegister(registerA)){

        if(isItRegister(registerB))
            //RegisterA'daki degeri registerB ye atiyoruz.
            setter(getter(registerA),registerB);
   
        else if(isItConst(registerB))
            //registerB stringinde yazan const value yi registerA ya atiyoruz.
            setter(strToInt(registerB),registerA);
               
        else{
            cerr << "Syntax error / Invalid MOV" << endl;
            return -1;
        }    
    }
    else{
        cerr << "Syntax error /Invalid MOV" << endl;
        return -1;
    }
    return 0; 
}
/*ADD fonksiyonu paramatre olarak 2 string alacak
 * 1. ve 2. parametre register ise 1.ve 2. registerlerdeki degerleri toplayip 1. 
  registere atiyacak
 * 1. register 2. parametre const ise const deger ile registerdeki degeri 
  toplayip registere atiyacak
 * islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek 
 */
int CPU :: ADD(const string& registerA,const string& registerB){
    if(isItRegister(registerA)){
        
        if(isItRegister(registerB))
            //Register A ile register B yi toplayip registerA ya atiyoruz.
            setter(getter(registerB)+getter(registerA),registerA);
      
        else if(isItConst(registerB)){
            //RegisterB stirnginde yazan value ile registerA daki degeri
            // toplayip RegisterA ya yaziyoruz.
            setter(strToInt(registerB),registerA);
        }
        else{
            cerr << "Syntax error /Invalid ADD" << endl;
            return -1;
        }
    }
    else{
        cerr << "Syntax error /Invalid ADD" << endl;
            return -1;
        }
    return 0;
}
/*SUB fonksiyonu paramatre olarak 2 string alacak
 * 1. register 2. parametre const ise const deger ile registerdeki degerden 
  const degeri cikartip registere atiyacak
 * 1. ve 2. parametre registerse 1. registerlerden 2. registerdeki degerleri 
  cikartip 1. registere atiyacak
 *Islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek 
 */
int CPU :: SUB(const string& registerA,const string& registerB){
    if(isItRegister(registerA)){
        
        if(isItRegister(registerB))
            setter(getter(registerA)-getter(registerB),registerA);
        
        else if(isItConst(registerB))
            setter(getter(registerA)-strToInt(registerB),registerA);
        else{
            cerr << "Syntax error / Invalid SUB" << endl;
            return -1; 
        }
    }
    else{
        cerr << "Syntax error / Invalid SUB" << endl;
        return -1;
    }
    return 0;
}
/*PRN fonksiyonu paramatre olarak 2 string alacak
 * parametre adress ise adressdeki degeri,register ise registerdeki degeri
   const ise constu ekrana basacak
 *Islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek 
 */
int CPU :: PRN(const string& registerA)const{
    if(isItRegister(registerA))
        cout <<"=>"<<getter(registerA)<<"<="<<endl;
    else if(isItConst(registerA))
        cout <<"=>"<< registerA<<"<="<<endl;
    else{
        cerr <<registerA<< "\nThis is not a register or constant!" << endl;
        return -1;
    }
    return 0;
}
/*JMP fonksiyonu paramatre olarak 2 string alacak
 * Bu stringler (Parametreleri), register-const veya const olabilir 
 * eger 1. parametre register ise bu registerin sifir oldugu durumda 
   constuncu satira atlicak.
 * eger 1. parametre const olursa, constuncu satira atliyacak.
 * Islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek 
 */
int CPU :: JMP(const string& registerA,const string& registerB) {

    if(isItRegister(registerA)){
        if(!isItConst(registerB)){ 
            cerr << "Syntax error / Invalid JMP"<< endl;
            return -1;
        }
        if(getter(registerA)==0)
            setPC(strToInt(registerB)-1);
    }
    else if(isItConst(registerA))
        setPC(strToInt(registerA)-1) ;
    
    else{
        cerr << "Syntax error / Invalid JMP"<< endl;
        return -1;
    }   /*Jumpu yapabilmesi için ya registerB nin değeri sıfır olacak yada
         registerB constant bir değer olacak (jumpuda olunca yazacagından..)*/
    return 0;
}
/*isItRegister fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 register olup olmadigina bakiyor eger register ise true, degilse false 
 * donduruyor */
bool CPU :: isItRegister(const string& strRegister)const{
    int strSize = strRegister.size();
    int strSizeShould = 2;// we have only 5 cpu and "R5" size is 2
    if(strRegister[0]=='r' || strRegister[0]=='R'){
        if(strSizeShould!=strSize)
            return false;
        for(int index=1; strSizeShould>index; ++index)
            if(strRegister[index]-'0'>5 || strRegister[index]-'0'<0)
                return false;      
    }
    else
        return false;
    return true;
}
/* isItConst fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 * constant(tamsayi) olup olmadigina bakiyor eger constant ise true, degilse 
 * false return ediyor */
bool CPU :: isItConst(const string& StrRegister)const{
    
    int strSize=StrRegister.size();
    if(StrRegister[0] !='-') // sayi negatif degilse
        for(int index=0; index<strSize; ++index){

            if(StrRegister[index]-'0'>9 || StrRegister[index]-'0'<0)
                return false;      
        }
    else{ // sayi negatifse
        for(int index=1; index<strSize; ++index){

            if(StrRegister[index]-'0'>9 || StrRegister[index]-'0'<0)
                return false;      
        }
    }
    return true;
}
/* ToMyUpper fonksiyonu 1 string alıyor ve aldıgı stringin butun harflerini 
 * buyuk harfe ceviriyor */
void CPU :: ToMyUpper(string& word)const{
    int wordSize= word.size();
    for(int i=0; i< wordSize; i++)
        if(word[i]>='a' && word[i]<='z')
            word[i]-='a'-'A';
    return;
}
/*strToInt fonksiyonu bir string i integera ceviriyor ornegin "123" u 123 e
 * ayni zamanda bu fonksiyon registeri ve adresi anlamayada kullaniliyor ornegin
 * "R3" yazan bir stringe bu fonksiyonu uygularsak bize 3 dondurecek. Bu degeri
 * ise arr[2] olarak kullanacagiz ve o registere erisecegiz.
 * bu fonksiyon islem basariyla gerceklesirse stringin integere cevirilmis 
 * halini, gerceklesemezse -1 return edecek*/
int  CPU :: strToInt(const string strOfInt)const{
    int sum=0;
    int index=0;
    int strOfSize=strOfInt.size();
    if(strOfInt[0]=='-' || strOfInt[0]=='r'|| strOfInt[0]=='R' || 
                                               strOfInt[0]=='#'){
        index=1;
        --strOfSize;
    }
    for(int k=strOfSize-1; k>=0; --k,++index)

        sum+=(strOfInt[index]-'0') * power(10,k);

    if(strOfInt[0]=='-')

        sum*=-1;

    return sum;
 }
/* power fonksiyonu stringi integere cevirirken kullanilmak icin yazilmis 
 * yardimci bir fonksiyondur. Bu cevirme isleminde sadece 10 ussu x tarzi
 * islemler yapilacagindan sadece bu islemlere gore duzenlenmistir. Genis,
 * bundan baska bir kulllanim icin degildir.*/
int  CPU :: power(int num1, int num2)const{
    int result = 0;
    if(num2==0)
        return 1;
    else if(num2==1)
        return num1;
    else{
        result=num1*num1;

        for(int i=1; i<num2-1; ++i) 
                result*=num1;
    }
    return result;
 }
/* getter fonksiyonu parametre olarak bir string alir. Aldigi bu string 
 * register stringidir yani stringin icinde R1,R2,R3,R4 yada R5 yazar. Bu
 * fonksiyon ise stringde yazan registere gore o registerdeki degeri return
 * eder. Yani string "R3" ve R3 deki deger 5 ise return degeri 5 olaraktir.
 * Kullanim nedenimiz ise, classlarda private fonksiyonlarda dahi olsa
 * private degerleri direk kullanmak hos degildir. Getter ve Setterlarla
 * islemler yapilir. 
 */
int  CPU :: getter(const string& strRegstr)const{
    
    int returnVal = 0 ;
        
    switch(strToInt(strRegstr)){
        case 1: returnVal = getR1(); break;
        case 2: returnVal = getR2(); break;
        case 3: returnVal = getR3(); break;
        case 4: returnVal = getR4(); break;
        case 5: returnVal = getR5(); break;
        default: break;
    }
    return returnVal;
}
/* setter fonksiyonu bir integer ve bir string olmak uzere iki parametre alir
 * aldigi stringi register ile eslestirir ve integer degeri o registerin 
 * icine kaydeder. Ornegin string "R5" ve setVal 10 ise, 5. registere
 * 10 degerini kaydeder.
 * Kullanim nedenimiz ise, classlarda private fonksiyonlarda dahi olsa
 * private degerleri direk kullanmak hos degildir. Getter ve Setterlarla
 * islemler yapilir. 
 */
void CPU :: setter(int setVal,const string& strRegstr){
    switch(strToInt(strRegstr)){
        case 1: setR1(setVal); break;
        case 2: setR2(setVal); break;
        case 3: setR3(setVal); break;
        case 4: setR4(setVal); break;
        case 5: setR5(setVal); break;
    }
    return;
}
