/* 
 * File:   CPUProgramDyn.cpp
 * Author: furkan
 * 
 * Created on November 26, 2016, 8:59 AM
 */
using namespace std;
#include "CPUProgramDyn.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
namespace{
	/* upperString fonksiyonu 1 string alıyor ve aldıgı stringin butun  
	 * harflerini buyuk harfe ceviriyor */
	void upperString(string& word){
	    int wordSize= word.size();
	    for(int i=0; i< wordSize; i++)
	        if(word[i]>='a' && word[i]<='z')
	            word[i]-='a'-'A';
	    return;
	}
	/*checkOrders fonksiyonu 1 string alir ve aldigi bu stringin assembly 
	 * komutu olup olmadigini kontrol eder, assembly komutu ise true degilse 
	 * false return eder.
	 */
	bool checkOrders(string& order){
	    upperString(order);
	    return (order == "MOV" || order == "ADD" || order == "SUB" ||
	    		order == "JMP" || order == "PRN" || order == "JPN" || 
	    		order == "HLT" );
	}
	/* checkCommends fonksiyonu belirtilen index den (line da siradaki islem
	* yapilmasi gereken index) sonraki degerlerin gecerli olup olamayacagini
	* kontrol eder. Ornegin "MOV R1,R2 r1 to r2" satiri gecersiz bir komuttur 
	* cunku eger komut satiri yorum iceriyorsa basinda ';' yer almalidir.
	* Verilen string gecerli ise true, gecerli degilse false return eder.
	*/
	bool checkCommends(const string& line, int index ){
	    
	    int lineOfSize = line.size();
	    if(lineOfSize != index){
	        while(line[index] == ' ')
	            index++;
	        
	        if(lineOfSize != index && line[index] != ';'){
	            cerr << "The file has syntax error"<< endl;
	            return false;
	        }
	    }
	    return true;
	}
	/*canFileOpen fonksiyonu acilmak istenilen dosyanin streamini alir ve 
	dosyanin acilip acilamayacagini kontrol eder, aciliyorsa true, acilamiyorsa 
	false return eder.*/
	bool canFileOpen(const ifstream& fileStream){
		// DOSYA SORUNSUZ SEKİLDE ACILIP ACILMADIGI KONTROLU
	    if (fileStream.fail()){ 
	        cerr << "File open failed." <<endl;
	        return false;
	    }
	    return true;
	}

	/* findIndexComma fonksiyonu bir string ve bu stringin size 'ını parametre
	 olarak alir ve bu stringde virgul arar, eger varsa virgulun indexini, yoksa
	 -1 return eder. */
	int  findIndexComma(const string str, int size){
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

	/* fillOrder fonksiyonu 2 string alir. 1. string komut satiri olarak yollanir
	 * fonksiyona, 2. string ise bos olarak yollanir ve bu fonksiyonun amaci
	 * bos olan 2. stringi, 1.stringdeki komut ile doldurmaktir. 
	 * Fonksyon islemleri basariyla gerceklestirirse line stirngindeki sirada 
	 * islemyapilmasi gereken index, islemler basarisiz olursa ise -1 return 
	 * edecektir.
	 */
	int  fillOrder(const string& line, string& cmd){
	    int spaceBeforeOrder = 0, loopCounter = 0, spaceAfterOrder = 0;
	    
	    while(line[loopCounter++] == ' ')
	        spaceBeforeOrder++;
	    
	    loopCounter = spaceBeforeOrder ;
	    int ordersize = 3 ; // Elimizdeki tum order'lerin size'ı 3 "MOV" etc
	    
	    cmd=line.substr(spaceBeforeOrder,ordersize);
	    
	    if(!checkOrders(cmd)){
	        cerr <<"The file has syntax error"<<endl;
	        return -1;
	    }
	    
	    loopCounter = spaceBeforeOrder + ordersize ;
	    while(line[loopCounter++]== ' ')
	        spaceAfterOrder++;
	    
	    return spaceBeforeOrder + ordersize + spaceAfterOrder  ;
	    
	}
	/* fillSecondString fonksiyonu parametre olarak 2 string alacak. 1. string
	 * komut satiri olan line stringi, 2. string ise bos olarak gonderilecek ve
	 * bu fonksiyon tarafindan secondString olarak doldurulacak.
	 * Ornegin line:"MOV R1,R2" ise secondString "R2" olarak doldurulacak.
	 */
	bool fillSecondString(const string& line,string &secondString){
	    int loopCounter = 0;
	    int strSize = line.size();
	    int indexComma = findIndexComma(line,strSize);
	    
	    if(indexComma == -1){
	        cerr <<"The file has syntax error"<<endl;
	        return false;
	    }
	    int spaceAfterComma = 0;
	    
	    for ( loopCounter = 0; loopCounter<indexComma; ++loopCounter){
	        if(line[loopCounter]==';'){
	            cerr << "The file has syntax error"<<endl;
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
	        cerr <<"The file has syntax error"<<endl;
	        return false;
	    }
	    secondString = line.substr(beginSecond,stringSize);
	    return checkCommends(line,beginSecond + stringSize);
	}
	/*fillStrings fonksiyonu 4 tane string alacak aldigi stringlerden 2 si
	 * line ve command stringleri dolu gelecek ve bu fonksiyon bu stringler
	 * yardimi ile bos olan firstString ve secondString'leri dolduracak.
	 * Ornegın line "R1,  R2  ; R1 to R2" ise firstString: "R1",
	 * secondString: "R2" olacak.
	 * Fonksiyon islemleri basari ile tamamlayabilirse true, tamamlayamazsa 
	 * false return edecek.
	 */
	bool fillStrings(string& line,const string& command, 
	                               string& firstString,string& secondString){
	    unsigned int loopCounter = 0 , stringSize = 0;
	    int returnValue = 0;
	    while(line[loopCounter]!=' ' && line[loopCounter]!=','
	        &&line[loopCounter]!=';' && line[loopCounter]!= '\0'){
	        stringSize++; // firstString in size'ı
	        loopCounter++;
	    }
	    // 1. string bu fonksiyona gonderilen line'in 0. indexinden stringin 
	    //sizeina kadar olacaktır.
	    firstString=line.substr(0,stringSize);
	    if(stringSize == 0){
	        cerr <<"The file has syntax error"<<endl;
	        return false;
	    }
	    if(command=="PRN" || (command=="JMP"&& (line[0]!='R' && line[0]!='r')))

	        returnValue = checkCommends(line,stringSize);
	    
	    else{
	        //virgulden once sacma sapan seyler var mi dosyada kontrolu
	        for(loopCounter=stringSize; loopCounter<line.find_first_of(','); 
	                                                             ++loopCounter)
	            if(line[loopCounter]!=' '){
                    cerr <<"The file has syntax error"<<endl;
                    return false;
	            } //2. stringi doldurmak icin fonksiyon cagiriyoruz.
	        returnValue = fillSecondString(line,secondString);
	    }
	       
	    if(!returnValue)
	        return false;
	    return true;
	}
	
	/* separateStrings fonksiyonu 4 adet string alacak, sadece 1. parametresi 
	 * olan komut satirinin stringi dolu olarak gonderilecek fonksiyona diger 
	 * stringleri olan order, firstString ve secondString i gerekli fonksiyon 
	 * cagirmalari ile dolduracak. Ornegin lineOfFile="MOV R1,R2 ; R1 to R2" 
	 * ise order="MOV",firstString="R1" ve secondString = "R2" olacak.
	 * Fonksiyon, islemler basari ile gerceklesirse 0, gerceklesemezse -1
	 * return edecek.
	 */
	int separateStrings(const string& lineOfFile, string& order, 
	                         string& firstString, string& secondString){
	    
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

}//END OF UNNAMEDNAMESPACE

namespace FurkanCPUProgDyn{
	/*No param constructure, 100lik capacity almak icin diger constructureyi 
	cagiracak */
    CPUProgramDyn::CPUProgramDyn():CPUProgramDyn(100) {}
    /* 1 param constructure, aldigi integer kadar kapasiteye sahip dinamic
    array oluşturacak. */
    CPUProgramDyn::CPUProgramDyn(int cap):capacity(cap),used(0) {
        order = new string[capacity];
    }
    /* Copy constructure, parametre olarak aldigi dinamic classi aynen 
    kopyalayacak. */
    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& orig)
    :capacity( orig.getCap() ) , used(0) ,dynOption( orig.getOption() ) 
    {
        order = new string[capacity];
        setUsed(orig.getUsed());
        for(int i=0; i<orig.size(); ++i)
        	order[i]=orig[i];
    }
	/* ReadFile fonksiyonu parametre olarak acilmak istenen dosyanin adini 
	 * alacak, dosyayi acma islemi basarili olursa, instruction dinamic arrayine
	 * dosyadaki tum bilgileri sirasiyla kaydedecek.*/
	void CPUProgramDyn :: ReadFile(const string& fileName){
	    ifstream file;
	    // Stringi c stringe ceviriyoruz.
	    char * cfileName = new char [fileName.length()+1];
  		strcpy (cfileName, fileName.c_str());
	    if(cfileName=='\0'){
	    	cerr<<"You have to write, filename."<<endl;
	    	exit(1);
	    }
	    file.open(cfileName);
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
      	delete[] cfileName;
	    return;
	}
	/* The overload will compare 2 CPUProgramDyn' size. if they are equal
    operator will be return true, else false.*/
    bool CPUProgramDyn::operator==(const CPUProgramDyn& other)const{
        return(size()==other.size());
    }
    /* The overload will compare 2 CPUProgramDyn' size. if they are not equal
    operator will be return true, else false. */
    bool CPUProgramDyn::operator!=(const CPUProgramDyn&other)const{ 
        return(size()!=other.size());
    }
    /* The overload will compare 2 CPUProgramDyn' size.if first dinamic class 
    equal or smallar than operator will be return true, else false. */
    bool CPUProgramDyn::operator<=(const CPUProgramDyn&other)const{ 
        return(size()<=other.size());
    }
    /* The overload will compare 2 CPUProgramDyn' size. if first dinamic class 
    smallar than operator will be return true, else false. */
    bool CPUProgramDyn::operator<(const CPUProgramDyn&other)const{ 
        return(size()<other.size());
    }
    /* The overload will compare 2 CPUProgramDyn' size. if first dinamic class 
    equal or greather than operator will be return true, else false.*/
    bool CPUProgramDyn::operator>=(const CPUProgramDyn&other)const{ 
        return(size()>=other.size());
    }
    /* The overload will compare 2 CPUProgramDyn' size.if first dinamic class 
    greather than operator will be return true, else false. */
    bool CPUProgramDyn::operator>(const CPUProgramDyn&other)const{ 
        return(size()>other.size());
    }
  	/* The operator= will assignment the second class to the first class and
  	return first class's adress */
	CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& rightSide){
		if(getCap()!=rightSide.getCap()){
			delete [] order;
			setCap(rightSide.getCap());
			order = new string[getCap()];
		}
		setOption(rightSide.getOption());
		setUsed(rightSide.getUsed());
		for(int i=0; i<getUsed(); ++i)
			order[i]=rightSide[i];

		return *this;
	}
    /* The function check capacity is full or not */
    bool CPUProgramDyn::full()const{
        return capacity==used;
    }
    /* When the capacity is full, the function will be call and capacity will
    extend.*/
    void CPUProgramDyn::extendCap(){
        setCap(getCap()*2+1);
       	string *temp=new string[getCap()];
       	for(int i=0; i<getUsed(); ++i)
        	temp[i]=order[i];
        delete [] order;
        order=temp;
    }
    /* The fuction size, will return dinamic array's size. */
    int CPUProgramDyn::size()const{
        return getUsed();
    }
    /* The fuction getLine will return the given number of line. */
    const string CPUProgramDyn::getLine(int lineNumber)const{
    	if(lineNumber<0){
    		cerr<<"index can not be smaller than 0, I'll return empty string\n";
    		return "";
    	}
    	else if(lineNumber>getUsed()){
    		cerr<<"index can not be greathen than used, I'll return empty"; 
    		cerr<<"string"<<endl;
    		return "";
    	}
    	return (*this)[lineNumber];
    }
    /* The fuction addInstruction, will add a new string to dinamic array*/
    void CPUProgramDyn::addInstruction(const string& direction){
        if(full()) //eger capacity full ise buyutmeliyiz.
            extendCap();
        order[getUsed()]=direction;
        ++used;
    }
    /* The fuction dellInstruction, will delete the last string of dinamic 
    array*/
    void CPUProgramDyn::dellInstruction(){

    	order[getUsed()-1]="";
    	--used;

    }
    /* The operator--, will delete last string of dinamic array and return 
    itself */
    const CPUProgramDyn& CPUProgramDyn::operator--(){//--a

    	if(getUsed()==0){
    		cerr<<"There is nothing to delete,I'll return myself"<<endl;
    		return *this;
    	}

    	dellInstruction();
    	return *this;

    }
    /* The operator--, will delete last string of dinamic array and return
    temp object which object has still the deleted data. */
    const CPUProgramDyn CPUProgramDyn::operator--(int ignorMe){//a--
    	if(getUsed()==0){
    		cerr<<"There is nothing to delete,I'll return myself"<<endl;
    		return (*this);
    	}
    	CPUProgramDyn temp= *this; 
    	dellInstruction();
    	return temp;

    }
    /*Objenin istenilen indexinin stringini dondurur.Const objeler uzerinde 
    calisabilir ve return ettigi deger degistirilemez. Normalde adress return 
   	etmesi gerekiyor fakat hatali durumlarda exit degilde bos string return 
    etmemiz istendiginden bunu uygulayamadık.
    */
    const string& CPUProgramDyn::operator[](int index)const{
       // cout<<"in:"<<index<<"used:"<<getUsed()<<endl;
        if(index>=getUsed()){
            cerr<<"Index can not be equal or greater than used";
            cerr<<" so I'll return at least string of my object."<<endl;            
            return order[getUsed()-1];  
        }
        return order[index];
    }
    /*Objenin istenilen indexinin stringini dondurur.Eger objenin arrayine bir
    seyler atamak istersek bize bu  operator lazim olacagi icin eklendi. 
    Normalde adress return etmesi gerekiyor fakat hatali durumlarda exit 
    degilde bos string return etmemiz istendiginden bunu uygulayamadık.
    */
    string& CPUProgramDyn::operator[](int index){
        
        if(index>=getUsed()){
            cerr<<"Index can not be equal or greater than used";
            cerr<<" so I'll return at least string of my object."<<endl;            
            return order[getUsed()-1]; 
        }
        return order[index];
    }
    /*Operator+= that takes an instruction line as a string and appends the 
    instruction to the end of the program. */
    void CPUProgramDyn::operator+=(const string& order){ 
		addInstruction(order);
	}
	/*Function call operator() that takes two integers and returns a new 
	program that contains the instructions between the given integers. */
	const CPUProgramDyn CPUProgramDyn::operator()(int num1,int num2)const{

	    if(num1 < 0 || num2<0 || num1>size() || num2>size() || num1>num2){
	        cerr<<"'()' parametres should be bigger than 0 and smaller than"; 
	        cerr<<" size of instruction I'll return empty object";
	        CPUProgramDyn empty;
	        return empty;
	    }
	    
	    CPUProgramDyn newProg;
	    
	    for(int i=num1;  i<=num2; ++i)
	        newProg.addInstruction(getLine(i));

	    return newProg;

	}
	/* Operator+ that takes a CPUProgramDyn and an instruction line as a string. 
	It returns a new CPUProgramDyn that has the original CPUProgramDyn 
	with appended last line from the parameter string. */
	const CPUProgramDyn CPUProgramDyn::operator+(const string& order)const{

		CPUProgramDyn newCPU = *this;
		newCPU.addInstruction(order);
		return newCPU;
	}
	/*
	Operator+ that takes two programs and returns a new program that appends the 
	second programs to the first one */
   	const CPUProgramDyn CPUProgramDyn::operator+(const CPUProgramDyn& other)
   	const
   	{
   		int totalUsed= getUsed()+other.getUsed();
   		CPUProgramDyn newCPU(totalUsed+1);
   		int i=0;
   		for(; i<getUsed(); ++i)
   			newCPU.addInstruction(order[i]);
   		
   		for(int j=0; j<other.getUsed(); ++j)
   			newCPU.addInstruction(other.order[j]);

   		return newCPU;
   	}
   	/*Operator>> that prints the program */
    ostream& operator<<(ostream& outputStream,const CPUProgramDyn& cpu){

        if(cpu.size()==0){ // Dosya okunmadı ise
            cerr<< "First you have to read File, I will return ostream"<<endl;
            return outputStream;
        }

        for(int i=0; i<cpu.size(); ++i){
            outputStream << cpu[i];
            if(i!=cpu.size()-1)
            	cout<<endl;
        }

        return outputStream;
    }
    /* Concructure will delete array */
    CPUProgramDyn::~CPUProgramDyn() {
    	delete [] order;
    	order=nullptr;
    }

}//END OF FurkanCPUProgDyn