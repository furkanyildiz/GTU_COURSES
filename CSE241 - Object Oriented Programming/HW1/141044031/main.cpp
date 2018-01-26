/*
 * HW1_141044031_FURKAN_YILDIZ
 * Source File
 *
 * Created on October 5, 2016  by FURKAN YILDIZ
 */

/*
 * Program 2 parametre ile calistirilacak 1. parametre okunacak dosyanin adi
 * 2. parametre ise programin calisma optionudur. 
 * Eger 0 girilirse islemler yapilarak registerlerin son hali ekrana basilacak
 * Eger 1 girilirse once ne islem yapilacagi ekrana basilacak sonra islem
 * yapilacak ve islem yapildiktan sonrada registerlerin durumu her adımda
 * ekrana basilacaktir. (Eger islem "PRN" ise komutu ekrana bastip 1 alt
 * satira gecilecek ve islem yapildiktan sonra 1 alt satirda registerlerin 
 * durumu yazilacaktir)
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/* MOV fonksiyonu 2 tane string ve 1 tane array alacak, aldigi stringleri
 registerler ile eslestirecek ve 2. registerdeki degeri 1. registere
 atayacak, eger 2. register constant ise constant degeri 1. registere atacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int MOV(const string& registerA, const string& registerB,int registers[]);
/* ADD fonksiyonu 2 tane string ve 1 tane array alacak, aldigi stringleri
 registerler veya constant ile eslestirecek ve 2 registeri yada 1 register,
 1 constant toplayip sonucu 1. registere yazacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int ADD(const string& registerA, const string& registerB,int registers[]);
/* SUB fonksiyonu 2 tane string ve 1 tane array alacak, aldigi stringleri
 registerler veya constant ile eslestirecek ve 1.registeri, 2. registerden
 yada constanttan cikartip sonucu 1. registere yazacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int SUB(const string& registerA, const string& registerB,int registers[]);
/*PRN fonksiyonu 1 string ve 1 array aliyor. Aldigi stringi registerle
 yada bir constant deger ile eslestiriyor ve o registeri yada constant degeri
 ekrana basıyor
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int PRN(const string& registerA, const int registers[]);
/*JMP fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini
 * ve programin hangi option ile calistirilacagini alacak 
 * register const veya sadece const alabilir eger register alırsa bu registerin
 * sifir oldugu durumda const. satira atlicak, eger sadece const olursa direk
 * o const. satira atliyacak 
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int JMP(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption);
/*ToMyUpper fonksiyonu 1 string alıyor ve aldıgı stringin butun harflerini buyuk
 * harfe ceviriyor */
void ToMyUpper(string& word);
/*strToInt fonksiyonu bir string i integera ceviriyor ornegin "123" u 123 e
 * ayni zamanda bu fonksiyon registeri anlamayada kullaniliyor ornegin
 * "R3" yazan bir stringe bu fonksiyonu uygularsak bize 3 dondurecek. Bu degeri
 * ise arr[2] olarak kullanacagiz ve o registere erisecegiz.
 * bu fonksiyon islem basariyla gerceklesirse stringin integere cevirilmis 
 * halini, gerceklesemezse -1 return edecek*/
int strToInt(const string strOfInt);
/* power fonksiyonu stringi integere cevirirken kullanilmak icin yazilmis 
 * yardimci bir fonksiyondur. Bu cevirme isleminde sadece 10 ussu x tarzi
 * islemler yapilacagindan sadece bu islemlere gore duzenlenmistir. Genis,
 * bundan baska bir kulllanim icin degildir.*/
int power(const int num1, const int num2);
/*fillString fonksiyonu islem yapılacak dosyanın referansini, islemler sonucu
 * doldurulacak 2 stringin referansini ve neye gore doldurulacagina dair
 * command i alacak
 * dosyadaki her satiri tek tek okuyacak ve stringleri ayiracak stringlerden
 * sonra eger o satirda bir seyler yaziyorsada hic yokmus gibi davranilacak */
void fillString(fstream& FILE, string& string1 , string& string2, 
                const string command);
/*isItRegister fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 register olup olmadigina bakiyor eger register ise true, degilse false 
 * donduruyor */
bool isItRegister(const string& StrRegister);
/*isItConst fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 constant(tamsayi) olup olmadigina bakiyor eger constant ise true, degilse false 
 * donduruyor */
bool isItConst(const string& StrRegister);
/* findLineNum fonksiyonu dosyadaki satir sayinini buluyor ve return ediyor
 * fonksiyonun kullanim amaci ise dosya 7 satirdan olusurken jump 9 gibi
 * bir degerin girilmemesini saglamak */
int findLineNum(fstream& inputfile,const char* FILENAME);
int main(int argc, char** argv) {

    fstream inputfile;
    string command,registerA,registerB;
    const char *FILENAME = argv[1]; // OKUNACAK DOSYANIN ISMI,CONSOLDAN GIRILIR
    /* OPTION PROGRAMIN CALISMA SEKLINI BELIRLER 0 GIRILIRSE SADECE ISLEMLER
    YAPILIR, 1 GIRILIRSE ISLEMLERIN TUM DETAYLARI GOSTERILIR */
    const int OPTION =strToInt(argv[2]);
    const int numberOfRegister=5;
    //REGISTER ARRAYI, 0. ELEMAN 1. REGİSTERİ, 1. ELAMAN 2. REGISTERI IFADE EDER
    int arrOfRegisters[numberOfRegister]={0,0,0,0,0}; //arrOfRegisters[0] == R1
    bool continueProg =true; //WHILE KONTROL SARTI
    // FONSIYONLARDAN GELEN DEGERLER, -1 GELIRSE PROGRAM SONLANIR
    int returnValueOfFonk; 
        
    inputfile.open(FILENAME);
    if (inputfile.fail()){ // DOSYA SORUNSUZ SEKİLDE ACILIP ACILMADIGI KONTROLU
        cerr << "File open failed." <<endl;
        return -1;
    }
    while(continueProg){
        inputfile >> command;
        ToMyUpper(command);
        if(command=="MOV"){
            fillString(inputfile,registerA,registerB,command);
            if(OPTION==1)
                cout << command << " "<< registerA <<","<< registerB;
            returnValueOfFonk = MOV(registerA,registerB,arrOfRegisters);
            if(returnValueOfFonk == -1)
                return -1;
            if(OPTION==1)
                cout <<" - R1:"<<arrOfRegisters[0]<<" R2:"<<arrOfRegisters[1] 
                     <<" R3:"<<arrOfRegisters[2]  <<" R4:"<<arrOfRegisters[3]
                     <<" R5:"<<arrOfRegisters[4]<<endl;            
        }
        else if(command=="PRN"){
            fillString(inputfile,registerA,registerB,command);
            if(OPTION==1)
                cout << command << " "<< registerA <<endl;
            returnValueOfFonk = PRN(registerA, arrOfRegisters);
            if(returnValueOfFonk == -1)
                return -1;
            if(OPTION==1)
                cout <<" - R1:"<<arrOfRegisters[0]<<" R2:"<<arrOfRegisters[1] 
                     <<" R3:"<<arrOfRegisters[2]  <<" R4:"<<arrOfRegisters[3]
                     <<" R5:"<<arrOfRegisters[4]<<endl; 
    	}
        else if(command=="ADD"){
            fillString(inputfile,registerA,registerB,command);
            if(OPTION==1)
                cout << command <<" "<< registerA<<"," << registerB;
            returnValueOfFonk = ADD(registerA,registerB,arrOfRegisters);
            if(returnValueOfFonk == -1)
                return -1;
            if(OPTION==1)
                cout <<" - R1:"<<arrOfRegisters[0]<<" R2:"<<arrOfRegisters[1] 
                     <<" R3:"<<arrOfRegisters[2]  <<" R4:"<<arrOfRegisters[3]
                     <<" R5:"<<arrOfRegisters[4]<<endl;    
        }
        else if(command=="SUB"){
            fillString(inputfile,registerA,registerB,command);
            if(OPTION==1)
                cout << command<<" "<< registerA<<"," << registerB;
            returnValueOfFonk = SUB(registerA,registerB,arrOfRegisters);
            if(returnValueOfFonk == -1)
                return -1;
            if(OPTION==1)
                cout <<" - R1:"<<arrOfRegisters[0]<<" R2:"<<arrOfRegisters[1] 
                     <<" R3:"<<arrOfRegisters[2]  <<" R4:"<<arrOfRegisters[3]
                     <<" R5:"<<arrOfRegisters[4]<<endl;    
        }
        else if(command=="JMP"){
            returnValueOfFonk = JMP(inputfile,arrOfRegisters,FILENAME,OPTION);
            if(returnValueOfFonk == -1)
                return -1;
        }
        else{
            //hlT; gibi bir ifadeninde gecerli olabilmesi icin
            if(command[0]=='H' && command[1]=='L' && command[2]=='T'){
                if(OPTION == 1)
                    cout << "HLT";
                continueProg=false;
                inputfile.close();
                cout <<" - R1:"<<arrOfRegisters[0]<<" R2:"<<arrOfRegisters[1] 
                     <<" R3:"<<arrOfRegisters[2]  <<" R4:"<<arrOfRegisters[3]
                     <<" R5:"<<arrOfRegisters[4]<<endl;    
                return  0; 
            }
            else{
                inputfile.close();
                cerr<<"Invalid command!"<<endl;
                return -1;
            }
        }
    }
    return 0;
}

int MOV(const string& registerA, const string& registerB, int registers[]){
    if(isItRegister(registerA)){

        if(isItRegister(registerB))
            
            registers[strToInt(registerB)-1]=registers[strToInt(registerA)-1];
   
        else if(isItConst(registerB))
            
            registers[strToInt(registerA)-1]=strToInt(registerB);
        
        else{
            cerr << "\nInvalid register/value" << endl;
            return -1;
        }              
    }
    else{
        cerr << "\nInvalid register" << endl;
        return -1;
    }
            
    return 0; 
}
int PRN(const string& registerA, const int registers[]){
    if(isItRegister(registerA))
        cout << registers[strToInt(registerA)-1]<<endl;
    else if(isItConst(registerA))
        cout << registerA<<endl;
    else{
        cerr << "\nThis is not a register or a constant!" << endl;
        return -1;
    }
    return 0;
}
int ADD(const string& registerA, const string& registerB, int registers[]){
    if(isItRegister(registerA)){

        if(isItRegister(registerB))
            registers[strToInt(registerA)-1]=
              registers[strToInt(registerA)-1]+registers[strToInt(registerB)-1];
      
        else if(isItConst(registerB)){
            int intValue = strToInt(registerB);
            registers[strToInt(registerA)-1]=
                                    registers[strToInt(registerA)-1]+intValue;
        }
        else{
            cerr << "Invalid register" << endl;
            return -1;
        }
    }
    else{
        cerr << "Invalid register" << endl;
            return -1;
        }
    return 0;
   
}
int SUB(const string& registerA, const string& registerB, int registers[]){
    if(isItRegister(registerA)){
        
        if(isItRegister(registerB))
            registers[strToInt(registerA)-1]=
              registers[strToInt(registerA)-1]-registers[strToInt(registerB)-1];
        
        else if(isItConst(registerB))
            registers[strToInt(registerA)-1]=
                    registers[strToInt(registerA)-1]-strToInt(registerB);
        else{
            cerr << "Invalid register" << endl;
            return -1; 
        }
    }
    else{
        cerr << "Invalid register" << endl;
        return -1;
    }
    return 0;
}
int JMP(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption) {
    string registerA,registerB,temp;
    fillString(inputfile,registerA,registerB,"JMP");
    if(isItRegister(registerA)){
        if(registers[strToInt(registerA)-1]==0){
            if(programOption==1)
                cout << "JMP "<< registerA<<"," << registerB;
            int valRegB = strToInt(registerB);
            if(valRegB>findLineNum(inputfile,FILENAME)){
                cerr << "\nInvalid jump"<< endl;
                return -1;
            }
            inputfile.close();
            inputfile.open(FILENAME);
            for(int i=1; i<valRegB; i++)
                getline(inputfile, temp);
        }
    }
    else if(isItConst(registerA)){
        if(programOption==1)
            cout << "JMP "<< registerA;
        int valRegA = strToInt(registerA);
        if(valRegA>findLineNum(inputfile,FILENAME)){
            cerr << "\nInvalid jump"<< endl;
            return -1;
        }
        inputfile.close();
        inputfile.open(FILENAME);
        for(int i=1; i<valRegA; ++i)
            getline(inputfile, temp);
    }
    else{
        if(programOption==1)
            cout << "JMP "<< registerA<<" " << registerB;
        cerr << "\nInvalid jump"<< endl;
            return -1;
    }
    if(programOption==1 && (registers[registerA[1]-'0'-1]==0 ||
                            (registerA[0]-'0'>=0 && registerA[0]-'0'<=9)))
        cout <<"- R1:"<<registers[0]<<" R2:"<<registers[1] <<" R3:"
             <<registers[2] <<" R4:"<<registers[3]<<" R5:"<<registers[4]<<endl;  
    return 0;
}
void ToMyUpper(string& word){
    int wordSize= word.size();
    for(int i=0; i< wordSize; i++)
        if(word[i]>='a' && word[i]<='z')
            word[i]-='a'-'A';
    return;
}
int strToInt(const string strOfInt){
	int sum=0;
	int index=0;
	int strOfSize=strOfInt.size();
	if(strOfInt[0]=='-' || strOfInt[0]=='r'|| strOfInt[0]=='R'){
            index=1;
            --strOfSize;
	}
	for(int k=strOfSize-1; k>=0; --k,++index)
	
		sum+=(strOfInt[index]-'0') * power(10,k);
		
	if(strOfInt[0]=='-')
	
		sum*=-1;
	
	return sum;
 }
int power(int num1, int num2){
 	if(num2==0)
 		return 1;
 	else if(num2==1)
 		return num1;
 	else{
	 	int result=num1*num1;
	 
	 	for(int i=1; i<num2-1; ++i) 
	 		result*=num1;
 	return result;
 	}
 }
void fillString(fstream& FILE, string& string1 , string& string2, 
                const string command){
    string temp,rubbish;
    int spacesAfterCommand=0,spacesBeforeComma=0,spacesAfterComma=0;
    int indexComma, loopCounter=0;
    getline(FILE,temp);
    //komuttan sonra olan basluklari sayacak
    while(temp[loopCounter++]==' ')
        spacesAfterCommand++;
    //Eger komuttan sonra tek string varsa
    if(command=="PRN" || (command=="JMP"   && 
            (temp[spacesAfterCommand]!='R' && temp[spacesAfterCommand]!='r'))){
        int wordSize=1;
        int z=spacesAfterCommand+1;
        while(temp[z]!=' ' && temp[z]!=';'){
            ++wordSize;
            z++;
        }
        string1=temp.substr(spacesAfterCommand,wordSize);
        string2=" ";
    }
    else{
        indexComma= temp.find_first_of(','); // virgulun indexini bulacak
        int loopCounter=indexComma-1;
        while(temp[loopCounter--]==' ')  //virgulden once olan bosluklari sayacak
            spacesBeforeComma++;

        string1=temp.substr(spacesAfterCommand,indexComma-spacesAfterCommand
                                                            -spacesBeforeComma);

        loopCounter=indexComma+1;
        while(temp[loopCounter++]==' ')
            spacesAfterComma++; //virgulden sonraki bosluk sayisi
        
        loopCounter=spacesAfterComma+indexComma+1;
        int wordSize=0;
        // MOV R2,R4; gibi ifadedelerdede hata vermeden calistirmali
        while(temp[loopCounter]!=' ' && temp[loopCounter]!=';'){
            wordSize++; //virgülden sonraki boşluktan sonra kaç harf var.
            loopCounter++;
        }
        string2=temp.substr(indexComma+spacesAfterComma+1,wordSize);
    }
    return;
}
bool isItRegister(const string& strRegister){
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
bool isItConst(const string& StrRegister){
    
    int strSize=StrRegister.size();
    
    for(int index=0; index<strSize; ++index){
        
        if(StrRegister[index]-'0'>9 || StrRegister[index]-'0'<0)
            return false;      
    }
        
    return true;
}
int findLineNum(fstream& inputfile,const char* FILENAME){
    
    inputfile.close();
    inputfile.open(FILENAME);
    string temp;
    int lineNumber=0;
    while(!inputfile.eof()){
        getline(inputfile,temp);
        lineNumber++;
    }
    inputfile.close();
    inputfile.open(FILENAME);
    return lineNumber;
}