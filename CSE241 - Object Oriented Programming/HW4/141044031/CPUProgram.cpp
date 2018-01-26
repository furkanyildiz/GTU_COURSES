/* 
 * File:   CPUProgram.cpp
 * Author: furkan
 * 
 * Created on October 29, 2016, 9:52 PM
 */
#include "CPUProgram.h"
#include <iostream>
#include <fstream>

/* Default constructure'ın bir sey yapmasina gerek yok (c++11 ile ilk atama
sirasinda optiona 0 atandi) */
CPUProgram::CPUProgram() {}
/* Eger CPUProgram objesi dosya adi ile olusturulursa, readFile fonksiyonu
cagirilacak*/
CPUProgram :: CPUProgram(const string& fileName){
    ReadFile(fileName);
}
/* Eger CPUProgram objesi int ile olusturulursa, objenin option degiskenine 
 * o deger yazilacak*/
CPUProgram::CPUProgram(int optionValue) :CPUProgramOption(optionValue){
    isOptionValid(optionValue);
}
/*isOptionValid fonksiyonu aldigi optionun gecerli olup olmadigini kontrol
 *edecek. Option 1 2 veya 0 degilse program sonlanacak.
*/
void CPUProgram::isOptionValid(int progOption)const{
    if(progOption!=0 && progOption!=1 && progOption!=2){
        cerr << "Program option must be 0,1 or 2"<<endl;
        exit(1);
   }
}

/* ReadFile fonksiyonu parametre olarak acilmak istenen dosyanin adini alacak,
 * dosyayi acma islemi basarili olursa, dosyadaki tum verileri yardimci 
 * fonksiyonlarini cagirarak okuyup duzenleyecek ve instruction string vectorune
 * dosyadan okudugu instructionlari kaydedecek. Bu islemler asamasinde eger
 * hatali bir durum ile karsilasilirsa exit(1) ile cikilacak. Suana kadar derste
 * exit(1) e alternatif herhangi sey ogrenmedigimizden, kullanmamiz yasak, bu 
 * yuzden exiti kullanmak zorundayiz.
 */
void CPUProgram :: ReadFile(const string& fileName){
    ifstream file;
    file.open(fileName);
    if(!canFileOpen(file))
        exit(1);
    string line="",command = "",string1="",string2="";
   
    int returnValue = 0;
    do{
        getline(file,line); //Dosyadan bir satir alir ve line stringine atar.
        //Aldigi stringleri command, string1 ve string2 olarak boler.
        returnValue = separateStrings(line,command,string1,string2);
        if(returnValue == -1) //Eger hatali bir durum varsa.
            exit(1);
        
        string orderLine = "";
        
        if(command == "HLT")
            orderLine = command ;
        else if(command == "PRN" || (command == "JMP"   && 
           (string1[0]!='R' && string1[0]!='r'))){
            orderLine = command +" "+ string1 ;
        }
        else
            orderLine = command +" "+ string1 +','+ string2 ;    
        // Instruction vektorune yeni stringi ekler.
        addInstruction(orderLine); 

    }while(command!="HLT");
    file.close(); // Dosya ile tum isimiz bitti, dosyayi kapatabiliriz.
    return;
}
/* fillOrder fonksiyonu 2 string alir. 1. string komut satiri olarak yollanir
 * fonksiyona, 2. string ise bos olarak yollanir ve bu fonksiyonun amaci
 * bos olan 2. stringi, 1.stringdeki komut ile doldurmaktir. 
 * Fonksyon islemleri basariyla gerceklestirirse line stirngindeki sirada islem
 * yapilmasi gereken index, islemler basarisiz olursa ise -1 return edecektir.
 */
int  CPUProgram :: fillOrder(const string& line, string& cmd)const{
    int spaceBeforeOrder = 0, loopCounter = 0, spaceAfterOrder = 0;
    
    while(line[loopCounter++] == ' ')
        spaceBeforeOrder++;
    
    loopCounter = spaceBeforeOrder ;
    int ordersize = 3 ; // Elimizdeki tum order'lerin size'ı 3 "MOV","JMP" etc
    
    cmd=line.substr(spaceBeforeOrder,ordersize);
    
    if(!checkOrders(cmd)){
        cerr <<size() +1 << ".line of file has syntax error"<<endl;
        return -1;
    }
    
    loopCounter = spaceBeforeOrder + ordersize ;
    while(line[loopCounter++]== ' ')
        spaceAfterOrder++;
    
    return spaceBeforeOrder + ordersize + spaceAfterOrder  ;
    
}
/*fillStrings fonksiyonu 4 tane string alacak aldigi stringlerden 2 si
 * line ve command stringleri dolu gelecek ve bu fonksiyon bu stringler
 * yardimi ile bos olan firstString ve secondString'leri dolduracak.
 * Ornegın line "R1,  R2  ; R1 to R2" ise firstString: "R1",
 * secondString: "R2" olacak.
 * Fonksiyon islemleri basari ile tamamlayabilirse true, tamamlayamazsa false
 * return edecek.
 */
bool CPUProgram :: fillStrings(string& line,const string& command, 
                               string& firstString,string& secondString)const{
    unsigned int loopCounter = 0 , stringSize = 0;
    int returnValue = 0;
    while(line[loopCounter]!=' ' && line[loopCounter]!=','
        &&line[loopCounter]!=';' && line[loopCounter]!= '\0'){
        stringSize++; // firstString in size'ı
        loopCounter++;
    }
    // 1. string bu fonksiyona gonderilen line'in 0. indexinden stringin size
    // ina kadar olacaktır.
    firstString=line.substr(0,stringSize);
    if(stringSize == 0){
        cerr <<size() +1 << ".line of file has syntax error"<<endl;
        return false;
    }
    if(command=="PRN" || (command=="JMP"   && (line[0]!='R' && line[0]!='r')))

        returnValue = checkCommends(line,stringSize);
    
    else{
    	//virgulden once sacma sapan seyler var mi dosyada kontrolu
        for(loopCounter=stringSize; loopCounter<line.find_first_of(','); 
                                                                ++loopCounter)
            if(line[loopCounter]!=' '){
                cerr <<size() +1 << ".line of file has syntax error"<<endl;
                return false;
            } //2. stringi doldurmak icin fonksiyon cagiriyoruz.
        returnValue = fillSecondString(line,secondString);
    }
       
    if(!returnValue)
        return false;
    return true;
}
/* fillSecondString fonksiyonu parametre olarak 2 string alacak. 1. string
 * komut satiri olan line stringi, 2. string ise bos olarak gonderilecek ve
 * bu fonksiyon tarafindan secondString olarak doldurulacak.
 * Ornegin line:"MOV R1,R2" ise secondString "R2" olarak doldurulacak.
 */
bool CPUProgram :: fillSecondString(const string& line,
                                                    string &secondString)const{
    int loopCounter = 0;
    int strSize = line.size();
    int indexComma = findIndexComma(line,strSize);
    
    if(indexComma == -1){
        cerr << size() +1 << ".line of file has syntax error"<<endl;
        return false;
    }
    int spaceAfterComma = 0;
    
    for ( loopCounter = 0; loopCounter<indexComma; ++loopCounter){
        if(line[loopCounter]==';'){
            cerr << size() +1 << ".line of file has syntax error"<<endl;
            return false;
        }  
    }
    loopCounter = indexComma +1 ;

    while(line[loopCounter++] == ' ')
        spaceAfterComma++;

    int beginSecond = indexComma + spaceAfterComma + 1 ;

    loopCounter = beginSecond ;

    int stringSize = 0;

    while(line[loopCounter] != ' ' && line[loopCounter]!= ';'
                                   && line[loopCounter]!= '\0'){
        stringSize++;
        loopCounter++;
    }
    if(stringSize == 0){
        cerr <<size() +1 << ".line of file has syntax error"<<endl;
        return false;
    }
    secondString = line.substr(beginSecond,stringSize);
    return checkCommends(line,beginSecond + stringSize);
}
/* separateStrings fonksiyonu 4 adet string alacak, sadece 1. parametresi olan
 * komut satirinin stringi dolu olarak gonderilecek fonksiyona diger stringleri
 * olan order, firstString ve secondString i gerekli fonksiyon cagirmalari ile
 * dolduracak. Ornegin lineOfFile="MOV R1,R2 ; R1 to R2" ise order="MOV",
 * firstString="R1" ve secondString = "R2" olacak.
 * Fonksiyon, islemler basari ile gerceklesirse 0, gerceklesemezse -1
 * return edecek.
 */
int  CPUProgram :: separateStrings(const string& lineOfFile, string& order, 
                         string& firstString, string& secondString)const{
    
    int lastIndex = 0;
    bool returnValue = true;
    //lastIndex okunacak bir sonraki indexi gosterir.
    lastIndex = fillOrder(lineOfFile,order);
    if (lastIndex == -1)
        return -1;
    if (order == "HLT"){
        returnValue = checkCommends(lineOfFile,lastIndex);
        firstString="";
        secondString="";
    }
    else{
        string str = lineOfFile.substr(lastIndex) ;
        returnValue = fillStrings(str,order,firstString,secondString);
    }
    if (!returnValue)
        return -1;
    return 0;
}
/*canFileOpen fonksiyonu acilmak istenilen dosyanin streamini alir ve dosyanin
 acilip acilamayacagini kontrol eder, aciliyorsa true, acilamiyorsa false
 return eder.*/
bool CPUProgram :: canFileOpen(const ifstream& fileStream)const{
    if (fileStream.fail()){ // DOSYA SORUNSUZ SEKİLDE ACILIP ACILMADIGI KONTROLU
        cerr << "File open failed." <<endl;
        return false;
    }
    return true;
}
/*checkOrders fonksiyonu 1 string alir ve aldigi bu stringin assembly komutu
 * olup olmadigini kontrol eder, assembly komutu ise true degilse false
 * return eder.
 */
bool CPUProgram :: checkOrders(string& order)const{
    upperString(order);
    return (order == "MOV" || order == "ADD" || order == "SUB" ||order == "JMP" 
          ||order == "PRN" || order == "JPN" || order == "HLT" );
    
}
/* checkCommends fonksiyonu belirtilen index den (line da siradaki islem
 * yapilmasi gereken index) sonraki degerlerin gecerli olup olamayacagini
 * kontrol eder. Ornegin "MOV R1,R2 r1 to r2" satiri gecersiz bir komuttur cunku
 * eger komut satiri yorum iceriyorsa basinda ';' yer almalidir.
 * Verilen string gecerli ise true, gecerli degilse false return eder.
 */
bool CPUProgram :: checkCommends(const string& line, int index )const{
    
    int lineOfSize = line.size();
    if(lineOfSize != index){
        while(line[index] == ' ')
            index++;
        
        if(lineOfSize != index && line[index] != ';'){
            
            cerr << size() +1 << ".line of file has syntax error"<< endl;
            return false;
        }
    }
    return true;
}
/* upperString fonksiyonu 1 string alıyor ve aldıgı stringin butun harflerini 
 * buyuk harfe ceviriyor */
void CPUProgram :: upperString(string& word)const{
    int wordSize= word.size();
    for(int i=0; i< wordSize; i++)
        if(word[i]>='a' && word[i]<='z')
            word[i]-='a'-'A';
    return;
}
/* findIndexComma fonksiyonu bir string ve bu stringin size 'ını parametre
 olarak alir ve bu stringde virgul arar, eger varsa virgulun indexini, yoksa
 -1 return eder. */
int  CPUProgram :: findIndexComma(const string str, int size)const{
    int indexComma = -1;
    for (int loopCounter = 0; (loopCounter<=size && indexComma == -1); 
                                                            ++loopCounter ){ 
        if(str[loopCounter]==',')
            indexComma = loopCounter;
        else
            indexComma = -1 ;
    }
    return indexComma;
}