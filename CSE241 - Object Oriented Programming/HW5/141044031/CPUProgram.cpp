/* 
 * File:   CPUProgram.cpp
 * Author: furkan
 * 
 * Created on November 10, 2016, 9:52 PM
 */
#include "CPUProgram.h"
#include <iostream>
#include <fstream>

CPUProgram::CPUProgram(int optionValue) {
    setOption(optionValue);
}
CPUProgram::CPUProgram() {
    CPUProgram(0);
}
/* CPUProgram, CPUProgram class'ının constracture idir. CPUProgram'ın bir 
   objesi olustugunda bu constracture ReadFile fonksiyonunu cagiracak.
 * ReadFile fonksiyonundan yanliş bir deger gelirse exit 1 ile çıkıyoruz.
 return ile çıkamayız Constracture'dan çünkü Constracturenin return degeri
 yok ve suana kadar baska bir yolla Constracture dan cikmayi ogrenmedik ileride
 ogrenecegimizden, simdilik öğrendiklerimize göre exit(1) ile çıkmak zorundayız.
 */

CPUProgram :: CPUProgram(const string& fileName){
    
    ReadFile(fileName);
}


/* ReadFile fonksiyonu parametre olarak acilmak istenen dosyanin adini alacak,
 * dosyayi acma islemi basarili olursa, instruction string vectorune
 * dosyadaki tum bilgileri sirasiyla kaydedecek.
 * Fonksiyon islemler basari ile gerceklesirse 0, gerceklesemezse -1 return
 * edecek.
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
/* Operator+= that takes an instruction line as a string and appends the 
instruction to the end of the program.
*/
void CPUProgram::operator+=(const string& order){ 
	addInstruction(order);
}
/* Operator+ that takes a CPUProgram and an instruction line as a string. 
It returns a new CPUProgram that has the original CPUProgram with appended 
last line from the parameter string.
*/
const CPUProgram CPUProgram::operator+(const string& order)const{
    
    CPUProgram newCPU = *this;//There is no pointer or etc so default assg is OK
    newCPU.addInstruction(order);
    return newCPU;

}

/*
Operator[] that takes an integer and works like the getLine function. 
It returns the program line as a string.

return degeri olarak normalde referans donderilir ama hatali durumlarda exit 
degilde temp yollanmasi istendiginden referans uygulanamaz.

*/
const string CPUProgram::operator[](int index)const{

    if(index>size() || index<0 || size()<=index){
        
        cout << "Illegal index in CPUProgram, I'll return empty string";
        return "";
    }

    return instruction[index];

}
/* Operator[] that takes an integer and works like the getLine function. 
It returns the program line as a string. And you can use for assignment the fuc.  

return degeri olarak normalde referans donderilir ama hatali durumlarda exit 
degilde temp yollanmasi istendiginden referans uygulanamaz.
*/
string CPUProgram::operator[](int index){
    
    if(index>size() || index<0 || size()<=index){
        
        cout << "Illegal index in CPUProgram, I'll return empty string";
        return "";
    }
    
    return instruction[index];
    
}
/*Function call operator() that takes two integers and returns a new program 
that contains the instructions between the given integers.
*/
CPUProgram  CPUProgram::operator()(int num1,int num2)const{

    if(num1 < 0 || num2<0 || num1>size() || num2>size() || num1>num2){
        cerr<<"'()' parametres should be bigger than 0 and smaller than"; 
        cerr<<" size of instruction I'll return empty object";
        CPUProgram empty;
        return empty;
    }
    
    CPUProgram newProg;
    
    int k = 0;
    for(int i=num1;  i<=num2; ++i , ++k)
        newProg.addInstruction(getLine(i));

    return newProg;

}
/* It prints the program */
ostream& operator<<(ostream& outputStream,const CPUProgram& cpu){
    
    if(cpu.size()==0){ // Dosya okunmadı ise
        cerr<< "First you have to read File"<<endl;
        exit(1);
    }
    for(int i=0; i<cpu.size(); ++i)
        outputStream << cpu[i]<<endl;
  
    return outputStream;
}
/*
Operator+ that takes two programs and returns a new program that appends the 
second programs to the first one
*/
const CPUProgram operator+(const CPUProgram& other){
        
    int size1=size();
    int size2=other.size();
    
    if(size1==0 || size2== 0){
        cerr<<"You have to read file first!"<<endl;
        exit(1);
    }
    
    CPUProgram newCPU;
    for(int i = 0; i<size1; ++i)
        newCPU.addInstruction(getLine(i));
    for(int i = 0; i<size2; ++i)
        newCPU.addInstruction(other[i]);
    return newCPU;
}
/* Pre decrement operators --that delete the last line of the program. 
return degeri olarak normalde referans donderilir ama hatali durumlarda exit 
degilde temp yollanmasi istendiginden referans uygulanamaz.*/
const CPUProgram CPUProgram :: operator--(){
    if(size()<=0){
    	cerr<<"CPUProgram is empty, I'll return empty object"<<endl;
    	CPUProgram empty;
    	return empty;
    }
    dellInstruction();
    return *this;
}
/* Post decrement operators --that delete the last line of the program. */
const CPUProgram CPUProgram :: operator--(int ignorMe){
    if(size()<=0){
    	cerr<<"CPUProgram is empty, I'll return empty object"<<endl;
    	CPUProgram empty;
    	return empty;
    }
    CPUProgram newCPU = *this;
    dellInstruction();
    return newCPU;
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