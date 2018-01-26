/* 
 * File:   CPU.cpp
 * Author: furkan
 * 
 * Created on October 28, 2016, 8:40 PM
 */
#include "Memory.h"
#include "CPU.h"
#include <iostream>

#include <string>
using namespace std;
CPU::CPU(int optionVal){
    isOptionValid(optionVal);
    setOption(optionVal);
    setter(1,0);
    setter(2,0);
    setter(3,0);
    setter(4,0);
    setter(5,0);
}
CPU::CPU() :CPU(0){}
/*isOptionValid fonksiyonu aldigi optionun gecerli olup olmadigini kontrol
 *edecek. Option 1 2 veya 0 degilse program sonlanacak.
*/
void CPU::isOptionValid(int progOption)const{

    if(progOption!=0 && progOption!=1 && progOption!=2){
        cerr << "Program option must be 0,1 or 2"<<endl;
        exit(1);
   }
}
int CPU :: execute(string instruction, Memory &cMemory){
    string command, string1,string2;
    string temp = instruction;
    int returnValueOfCommands = 0 ;
    delSpaces(instruction);
    editInst(instruction);
    if(instruction  == ""){
        cerr <<temp<<"Syntax Error"<<endl;
        exit(1);
    }
    divideInst(instruction,command, string1,string2);
    ToMyUpper(command);
    if(option == 1 || option == 2)
        cout << command<<" "<<string1<<" "<<string2<<endl;
        
    if(command == "MOV")
        returnValueOfCommands = MOV(string1,string2,cMemory);
    else if(command == "ADD")
        returnValueOfCommands = ADD(string1,string2,cMemory);
    else if(command == "SUB")
        returnValueOfCommands = SUB(string1,string2,cMemory);
    else if(command == "PRN")
        returnValueOfCommands = PRN(string1,cMemory);
    else if(command == "JMP")
        returnValueOfCommands = JMP(string1,string2);
    else if(command == "JPN")
        returnValueOfCommands = JPN(string1,string2);
    else if(command == "HLT"){
        setHlt(true);
        print();
        cMemory.printAll();
    }
    else{
        cerr <<"Syntax Error, Invalid command!"<<endl;
        exit(1);
    }
    if((option == 1 || option == 2) && command != "HLT"){
        print();
        if(option == 2)
            cMemory.printAll();
    }
    int updatePC = getPC() +1 ; // her satir okunduktan sonra PC 1 arttirilir
    setPC(updatePC);
    if(returnValueOfCommands == -1)
        exit(1);
    return 0;
}
/* print fonksiyonu registerlerin degerlerini ekrana basacak.*/
void CPU :: print(){
    cout <<"CPU Register Values:"<<endl;
    for(int i = 1; i<=5; ++i)
        cout <<'R'<<i<<':'<<getter(i)<<' ';
    cout <<"\n";
}
string CPU :: editInst(string &str)const{
    if(str == "HLT")
        return str;
    string order = str.substr(0,3);
    ToMyUpper(order);

    if(str[3]!=' ') //komuttan sonra bosluk yoksa
        str = order + ' ' + &str[3];
    while(str[4] == ' ') //komutttan sonra 1 bosluk olması icin
        str = str.substr(0,4)+&str[5];
    int stringSize = 0;
    int loopCounter = 4;
    while(str[loopCounter]!=' ' && str[loopCounter]!=',' 
                                                && str[loopCounter]!= '\0'){
        stringSize++; // firstString in size'ı
        loopCounter++;
    }
    if(order=="PRN" ||  (order=="JMP"   && (str[4]!='R' && str[4]!='r'))){
        //tek string okunacak
        int  strsize= str.size();
        if(strsize!= 4+stringSize)
            str= "";
        return str;
    }
    else{
        int stringSize2=0;
        int indexComma = str.find_first_of(',');
        if(indexComma == -1) //virgul yoksa
            return "";
        if(4+stringSize != indexComma)
            while(str[4+stringSize] == ' ')
                str = str.substr(0,4+stringSize) + &str[5+stringSize];

        indexComma = str.find_first_of(',');
        if(4+stringSize != indexComma)
            return "";
        while(str[indexComma+1] == ' ')
            str = str.substr(0,indexComma+1) + &str[indexComma+2];
        loopCounter = 7;
        while(str[loopCounter]!=' ' && str[loopCounter]!= '\0'){
            stringSize2++; // secondString in size'ı
            loopCounter++;
        }
        int  strsize= str.size();
        if(strsize!= 5+stringSize +stringSize2)
            return "";
        else
            return str;
    }
}
void CPU :: divideInst(const string& currentLine, string& order,
                             string& firstString, string& secondString)const{
    //Bastaki ve orderdan sonraki bosluklar siliniyor 1 bosluk bırakiliyor
    //orderdan sonra, dolayısıyla ilk okunacak index order'ın size'ı +1 (bosluk)
    //yani 4 oluyor.
    int firstStrIndex = 4;
    int sizeOfStr1 = 0;
    int sizeOfLine = currentLine.size();
    order = currentLine.substr(0,3);
    ToMyUpper(order);
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
/* delSpaces fonksiyonu instruction olarak girilen stringin basindan ve sonundan
 * eger bosluk varsa bosluklari silecektir. Ornegin "   prn r5  " i "prn r5"
 * formatina cevirecek.
*/
void CPU :: delSpaces(string& str)const{
    if(str[0]==' '){
        str=&str[1];
        delSpaces(str);
    }
    int lastIndex = str.size() - 1;
    if(str[lastIndex] == ' '){
        str = str.substr(0,lastIndex);
        delSpaces(str);
    }
    return;
}

/*MOV fonksiyonu 2 adet string ve 1 memory classi alacak. Aldigi stringlerin
 *register,adres yada const olma durumlarini kontrol edip,
 *1. parm register, 2. parametre adres ise, registerdeki degeri adresse atiyacak
 *1. parm adres, 2. parametre register ise, adres deki degeri registere atiyacak
 *1. parametre adres, 2. parametre const ise, const degeri adresse atiyacak.
 *1. register 2. parametre const ise const degeri registere atiyacak
 *1. ve 2. parametre registerse 1. registerdeki degeri 2. registere atiyacak
 * islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek 
*/
int CPU :: MOV(const string& stringA,const string& stringB, Memory& cMemory){
    int error = 0;
    // stringA R5 ise idA 5 olacak.
    int idA = turnIndex(stringA);// "#x"ya da"Rx" gonderince idA ya x atar.
    int idB = turnIndex(stringB);

    if(isItRegister(stringA)){
        if(isItRegister(stringB))
            //RegisterA'daki degeri idB ye atiyoruz.
            setter(idB,getter(idA));
        
        else if(isItConst(stringB))
            //idB stringinde yazan const value yi idA ya atiyoruz.
            setter(idA,strToInt(stringB));
        else if(isItAdress(stringB))
            cMemory.setMem(idB,getter(idA));
        
        else
            error = 1;
    }
    else if(isItAdress(stringA)){
        if(isItRegister(stringB))
            setter(idB,cMemory.getMem(idA));
            
        else if(isItConst(stringB))
            cMemory.setMem(idA,strToInt(stringB));
        else
            error = 1;
    }
    else
        error = 1;
    if(error == 1){
        cerr <<"MOV "+stringA+','+stringB<< endl;
        cerr << "Syntax error / invalid MOV" << endl;
        return -1;
    }
    return 0; 
}
/*ADD fonksiyonu 2 adet string ve 1 memory classi alacak. Aldigi stringlerin
* register,adres yada const olma durumlarini kontrol edip,
* 1. ve 2. parametre registerse 1.ve 2. registerlerdeki degerleri toplayip 1. 
  registere atiyacak
* 1. register 2. parametre const ise const deger ile registerdeki degeri 
  toplayip registere atiyacak
* 1. parametre register, 2. parametre adres ise, registerdeki deger ile 
  adressdeki degeri toplayip registere atiyacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek
*/

int CPU :: ADD(const string& stringA,const string& stringB, Memory& cMemory){
    int idA = turnIndex(stringA);// "Rx" gonderince idA ya x atar.
    int idB = turnIndex(stringB);
    int error = 0 ;
    if(isItRegister(stringA)){
        
        if(isItRegister(stringB))
            setter(idA, getter(idA) + getter(idB));
        else if(isItConst(stringB))
            setter(idA, getter(idA) + strToInt(stringB));
        else if(isItAdress(stringB))
            setter(idA, getter(idA) + cMemory.getMem(idB));
        else
            error = 1;
    }
    else
        error = 1 ;
    if(error == 1){
        cerr <<"ADD "+stringA+','+stringB<< endl;
        cerr << "Syntax error / invalid ADD" << endl;
        return -1;
    }
    return 0;
}
/*SUB fonksiyonu 2 adet string ve 1 memory classi alacak. Aldigi stringlerin
 *register,adres yada const olma durumlarini kontrol edip,
 * 1. parametre register, 2. parametre adres ise, adresdeki degeri registerdeki 
  degerden cikarip registere atiyacak
 * 1. register 2. parametre const ise const deger ile registerdeki degerden 
  const degeri cikartip registere atiyacak
 * 1. ve 2. parametre registerse 1. registerlerden 2. registerdeki degerleri 
  cikartip 1. registere atiyacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek
*/
int CPU :: SUB(const string& stringA,const string& stringB, Memory& cMemory){
    int idA = turnIndex(stringA);// "Rx" gonderince idA ya x atar.
    int idB = turnIndex(stringB);
    int error = 0 ;
    if(isItRegister(stringA)){
        
        if(isItRegister(stringB))
            setter(idA, getter(idA) - getter(idB));
        else if(isItConst(stringB))
            setter(idA, getter(idA) - strToInt(stringB));
        else if(isItAdress(stringB))
            setter(idA, getter(idA) - cMemory.getMem(idB));
        else
            error = 1;
    }
    else
        error = 1 ;
    if(error == 1){
        cerr <<"SUB "+stringA+','+stringB<< endl;
        cerr <<"Syntax error / invalid SUB" <<endl;
        return -1;
    }
	return 0;
}
/*PRN fonksiyonu 2 adet string ve 1 memory classi alacak. Aldigi stringlerin
 *register,adres yada const olma durumlarini kontrol edip,
 *parametre adress ise adressdeki degeri,register ise registerdeki degeri
 const ise constu ekrana basacak
*bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek
*/
int CPU:: PRN(const string& stringA,const Memory& cMemory)const{
    int id = turnIndex(stringA);
    if(isItRegister(stringA))
        cout <<"=>"<<getter(id)<<"<="<<endl;
    else if(isItConst(stringA))
        cout <<"=>"<< stringA <<"<="<<endl;
    else if(isItAdress(stringA))
        cout <<"=>"<< cMemory.getMem(id)<<"<="<<endl;
    else{
        cerr <<"PRN "+stringA<< endl;
        cerr << "This is not a register,constant or address!" << endl;
        return -1;
    }
    return 0;
}
/*JMP fonksiyonu 2 adet string ve 1 memory classi alacak. Aldigi stringlerin
 *register yada const olma durumlarini koptrol edecek. Stringler,
 * register-const veya const alabilir eger register alırsa bu registerin
 * sifir oldugu durumda constuncu satira atlicak, eger sadece const olursa direk
 * o constuncu satira atliyacak bu fonksiyon islem basariyla gerceklesirse 0, 
 * gerceklesemezse -1 return edecek
*/
int CPU :: JMP(const string& stringA,const string& stringB){
    
    int error = 0 ;
    int id = turnIndex(stringA);
    if(isItRegister(stringA)){
        if(!isItConst(stringB))
            error = 1 ;
        if(getter(id) == 0)
            setPC(strToInt(stringB)-1);
    }
    else if(isItConst(stringA))
        setPC(strToInt(stringA)-1);
    
    else
        error = 1;
    if(error == 1){
        cerr <<"JMP "+stringA+','+stringB<< endl;
        cerr << "Syntax error / invalid JMP" << endl;
        return -1;
    }
    return 0;
}
/*JPN fonksiyonu 2 adet string ve 1 memory classi alacak. Aldigi stringlerin
 * register yada const olma durumlarini kontrol edecek. Stringler
 * register-linenumber olacak ve eger registerdeki deger sifir veya daha kucuk
 * ise linenumber inci satira atliyacak
 */
int CPU :: JPN(const string& stringA,const string& stringB){
    
    int error = 0 ;
    int id = turnIndex(stringA);
    if(isItRegister(stringA)){
        if(!isItConst(stringB))
            error = 1 ;
        if(getter(id) <= 0)
            setPC(strToInt(stringB)-1);
    }
    else if(isItConst(stringA))
         setPC(strToInt(stringA)-1);
    else
        error = 1;
    if(error == 1){
        cerr <<"JPN "+stringA+','+stringB<< endl;
        cerr << "Syntax error / invalid JPN" << endl;
        return -1;
    }
    return 0;
}
/* isItAdress fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 * adress olup olmadigina bakiyor eger adress ise true, degilse 
 * false return ediyor */
bool CPU :: isItAdress(const string& stringToCheck)const{
    // Adress olmasi icin basinde "#" olmali ve #'dan sonra gelen sayi
    // 0(dahil) ile 50(dahil degil) arasinde olmali
    if(stringToCheck[0]=='#'){
        if(strToInt(&stringToCheck[1])<0 || strToInt(&stringToCheck[1])>=50)
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
    else{ // stringin basinde - varsa (sayi negatifse)
        for(int index=1; index<strSize; ++index){
            if(StrRegister[index]-'0'>9 || StrRegister[index]-'0'<0)
                return false;      
        }
    }
    return true;
}
/*isItRegister fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 register olup olmadigina bakiyor eger register ise true, degilse false 
 donduruyor */
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
int  CPU :: strToInt(const string& strOfInt)const{
    int sum=0;
    int index=0;
    int strOfSize=strOfInt.size();
    if(strOfInt[0]=='-' ){
        index=1;
        --strOfSize;
    }
    for(int k=strOfSize-1; k>=0; --k,++index)
        sum+=(strOfInt[index]-'0') * power(10,k);

    if(strOfInt[0]=='-')
        sum*=-1;
    return sum;
}
/*turnIndex fonksiyonu 1 string aliyor ve aldigi string eger register veya 
 *adress ise 1. indexinden itibaren geri donduruyor. Ornegin "#49" u
 *49 olarak geri donderiyor. 
*/
int CPU :: turnIndex(const string& str)const{
    if(str[0] =='r'|| str[0] =='R'|| str[0] =='#')
        return strToInt(&str[1]);
    return -1;
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