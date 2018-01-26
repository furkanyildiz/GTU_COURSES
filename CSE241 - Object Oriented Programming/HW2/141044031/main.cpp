/*
 * HW2_141044031_FURKAN_YILDIZ
 * Source File
 *
 * Created on October 10, 2016  by FURKAN YILDIZ
 */

/*
 * Program 2 parametre ile calistirilacak 1. parametre okunacak dosyanin adi
   2. parametre ise programin calisma optionudur. 
 * Eger 0 girilirse islemler yapilarak registerlerin ve adreslerin 
   son hali ekrana basilacak
 * Eger 1 girilirse once ne islem yapilacagi ekrana basilacak sonra islem
   yapilacak ve islem yapildiktan sonrada registerlerin durumu her adımda
   ekrana basilacaktir. (Eger islem "PRN" ise komutu ekrana bastip 1 alt
   satira gecilecek ve islem yapildiktan sonra 1 alt satirda registerlerin 
   durumu yazilacaktir)
 * Eger option 2 ise, her instruction option 1 gibi calisacak ve option 1 e 
   ek olarak her instruction dan sonra adreslerin anlik durumu ekrana basilacak.
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*openFile fonksiyonu stream degiskeni ve acilacak dosyanin adini alacak
 dosyayi acmaya calisacak eger basarili bir sekilde acilirsa 0 return edecek ve
 * program devam edecek. Eger acilamazsa -1 return edecek ve program sonlanacak 
 */
int openFile(fstream& file, const char* nameOfFile);
/* doCommands fonksiyonu dosyadan komutlari okuyacak ve okudugu komutlari
 gerceklestirecek, Ornegin "MOV" okursa MOV fonksiyonunu cagiracak */
int doCommands(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/* MOV fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini,
 * adress arrayini ve programin hangi option ile calistirilacagini alacak 
 *1. parm register, 2. parametre adres ise, registerdeki degeri adresse atiyacak
 *1. parm adres, 2. parametre register ise, adres deki degeri registere atiyacak
 *1. parametre adres, 2. parametre const ise, const degeri adresse atiyacak.
 *1. register 2. parametre const ise const degeri registere atiyacak
 *1. ve 2. parametre registerse 1. registerdeki degeri 2. registere atiyacak
 * islemler basariyla gerceklesirse 0, gerceklesemezse -1 return edecek */
int MOV(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/* ADD fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini,
  adress arrayini ve programin hangi option ile calistirilacagini alacak 
* 1. ve 2. parametre registerse 1.ve 2. registerlerdeki degerleri toplayip 1. 
  registere atiyacak
* 1. register 2. parametre const ise const deger ile registerdeki degeri 
  toplayip registere atiyacak
* 1. parametre register, 2. parametre adres ise, registerdeki deger ile 
  adressdeki degeri toplayip registere atiyacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int ADD(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/* SUB fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini,
  adress arrayini ve programin hangi option ile calistirilacagini alacak 
 * 1. parametre register, 2. parametre adres ise, adresdeki degeri registerdeki 
  degerden cikarip registere atiyacak
 * 1. register 2. parametre const ise const deger ile registerdeki degerden 
  const degeri cikartip registere atiyacak
 * 1. ve 2. parametre registerse 1. registerlerden 2. registerdeki degerleri 
  cikartip 1. registere atiyacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int SUB(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/* PRN fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini,
   adress arrayini ve programin hangi option ile calistirilacagini alacak 
 * parametre adress ise adressdeki degeri,register ise registerdeki degeri
   const ise constu ekrana basacak
bu fonksiyon islem basariyla gerceklesirse 0, gerceklesemezse -1 return edecek*/
int PRN(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/* JMP fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini,
 * adress arrayini ve programin hangi option ile calistirilacagini alacak 
 * register-const veya const alabilir eger register alırsa bu registerin
 * sifir oldugu durumda constuncu satira atlicak, eger sadece const olursa direk
 * o constuncu satira atliyacak bu fonksiyon islem basariyla gerceklesirse 0, 
 * gerceklesemezse -1 return edecek*/
int JMP(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/* JPN fonksiyonu islem yapılacak dosyanın referansını,adini register arrayini,
 * adress arrayini ve programin hangi option ile calistirilacagini alacak
 * register-linenumber alicak ve eger registerdeki deger sifir veya daha kucuk
 * ise linenumber inci satira atliyacak
 */
int JPN(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]);
/*HLT fonksiyonu okudugu command i string olarak, while sartini ve programin
 hangi optionla calistirilacagini alacak
 Program komut olarak "add","sub","mov","prn","jmp" veya "jpn" den baska komut 
 yakalarsa bu fonksiyonu cagiracak
 eger "HLT" diye bir komut yakalarsa programi basarili bir sekilde sonlandiracak
 eger tanimlanmayan bir komut yakalarsa programi basarisiz bir sekilde (-1)
 return ederek sonlandiracak. */
int HLT(const string& other, bool& PrograminContinue, int programOption);
/*ToMyUpper fonksiyonu 1 string alıyor ve aldıgı stringin butun harflerini buyuk
 * harfe ceviriyor */
void ToMyUpper(string& word);
/*strToInt fonksiyonu bir string i integera ceviriyor ornegin "123" u 123 e
 * ayni zamanda bu fonksiyon registeri ve adresi anlamayada kullaniliyor ornegin
 * "R3" yazan bir stringe bu fonksiyonu uygularsak bize 3 dondurecek. Bu degeri
 * ise arr[2] olarak kullanacagiz ve o registere erisecegiz.
 * Ayni sekilde "#48" yazan bir stringi bu fonksiyona gonderirsek 48 return
 * edecek.
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
/* isItConst fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 * constant(tamsayi) olup olmadigina bakiyor eger constant ise true, degilse 
 * false return ediyor */
bool isItConst(const string& StrRegister);
/* isItAdress fonksiyonu parametre olarak 1 string aliyor ve aldigi stringin
 * address olup olmadigina bakiyor gerekli sartlar cercevesinde ve eger address
 * ise true, degilse false return ediyor. */
bool isItAdress(const string& stringToCheck);
/* findLineNum fonksiyonu dosyadaki satir sayinini buluyor ve return ediyor
 * fonksiyonun kullanim amaci ise dosya 7 satirdan olusurken jump 9 gibi
 * bir degerin girilmemesini saglamak */
int findLineNum(fstream& inputfile,const char* FILENAME);
/* printContents fonksiyonu Program calistirilirken istenilen optiona gore 
 * ekrana ciktilar verir (Registerlerin ve adresslerin anlik durumlarini)*/
void printContents(const char programOption, int registers[],
                                                        unsigned int adress[]);

int main(int argc, char** argv) {
    fstream cpuFile;
    const char *FILENAME = argv[1]; // OKUNACAK DOSYANIN ISMI,CONSOLDAN GIRILIR
    const int OPTION =strToInt(argv[2]);
    if(OPTION != 0 && OPTION != 1 && OPTION != 2)
        return -1;
    const int numberOfRegister = 5;
    const int numberOfAdress = 50;
    int arrOfRegisters[numberOfRegister]={0,0,0,0,0}; //arrOfRegisters[0] == R1
    unsigned int arrOfAdress[numberOfAdress];
    for(int i=0; i<50; ++i)
        arrOfAdress[i] = 0;
    int returnValCommand = 0; // -1 return eden fonk. olursa program sonlanır.
    openFile(cpuFile,FILENAME);
    returnValCommand = 
                 doCommands(cpuFile,arrOfRegisters,FILENAME,OPTION,arrOfAdress);
    if (returnValCommand == -1)
        return -1;
    return 0;
}
int openFile(fstream& file, const char* nameOfFile){
    file.open(nameOfFile);
    if (file.fail()){ // DOSYA SORUNSUZ SEKİLDE ACILIP ACILMADIGI KONTROLU
        cerr << "File open failed." <<endl;
        return -1;
    }
    else
        return 0;
}
int doCommands(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]){
    string command = "";
    int returnValueOfFonk = 0;
    bool continueProg =true; //WHILE KONTROL SARTI
    while(continueProg){
        inputfile >> command;
        ToMyUpper(command); //Komuttaki tum harfleri buyuk harfe ceviriyor
        if(command=="MOV")
            returnValueOfFonk = MOV(inputfile,registers,FILENAME,programOption,
                                    adress);    
        else if(command=="PRN")
            returnValueOfFonk = PRN(inputfile,registers,FILENAME,programOption,
                                    adress);
        else if(command=="ADD")
            returnValueOfFonk = ADD(inputfile,registers,FILENAME,programOption,
                                    adress);
        else if(command=="SUB")
            returnValueOfFonk = SUB(inputfile,registers,FILENAME,programOption,
                                    adress);
        else if(command=="JMP")
            returnValueOfFonk = JMP(inputfile,registers,FILENAME,programOption,
                                    adress);
        else if(command=="JPN")
            returnValueOfFonk = JPN(inputfile,registers,FILENAME,programOption,
                                    adress);
        else{
            returnValueOfFonk = HLT(command,continueProg, programOption);
            printContents(-1,registers,adress);
            inputfile.close();
        }
        // Islemlerde bir hata olursa, program kendini kapatmadan once 
        // registerlerin ve adres lerin son degerlerini ekrana basacak.
        if(returnValueOfFonk == -1){
            printContents(programOption,registers,adress);
            return -1;
        }
    }
}
int MOV(fstream& inputfile,int registers[], const char* FILENAME,
         const char programOption, unsigned int adress[]){
    string registerA,registerB;
    fillString(inputfile,registerA,registerB,"MOV");
    if(programOption==1 || programOption==2)
        cout << "MOV "<< registerA <<","<< registerB;
    if(isItRegister(registerA)){

        if(isItRegister(registerB))
            
            registers[strToInt(registerB)-1]=registers[strToInt(registerA)-1];
   
        else if(isItConst(registerB))
            
            registers[strToInt(registerA)-1]=strToInt(registerB);
        
        else if(isItAdress(registerB))
            
           adress[strToInt(registerB)] =registers[strToInt(registerA)-1];
                
        else{
            cerr << "\nInvalid MOV" << endl;
            return -1;
        }              
    }
    else if(isItAdress(registerA)){
        if(isItRegister(registerB))
            registers[strToInt(registerB)-1]=adress[strToInt(registerA)];
        else if(isItConst(registerB))
            adress[strToInt(registerA)]=strToInt(registerB);
        else{
            cerr << "\nInvalid MOV" << endl;
            return -1;
        }   
    }
    else{
        cerr << "\nInvalid MOV" << endl;
        return -1;
    }
    printContents(programOption,registers,adress);
    return 0; 
}
int PRN(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]){
    string registerA,temp; //temp is only for running the fillstring function
    fillString(inputfile,registerA,temp,"PRN");
    if(programOption == 1 || programOption == 2)
        cout << "PRN "<< registerA<<endl;
    if(isItRegister(registerA))
        cout << registers[strToInt(registerA)-1]<<endl;
    else if(isItConst(registerA))
        cout << registerA<<endl;
    else if(isItAdress(registerA))
        cout << adress[strToInt(registerA)]<<endl;
    else{
        cerr << "\nThis is not a register,address or constant!" << endl;
        return -1;
    }
    return 0;
}
int ADD(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]){
    string registerA,registerB;
    fillString(inputfile,registerA,registerB,"ADD");
    if(programOption==1 || programOption==2)
        cout << "ADD "<< registerA <<","<< registerB;
    if(isItRegister(registerA)){

        if(isItRegister(registerB))
            registers[strToInt(registerA)-1]=
              registers[strToInt(registerA)-1]+registers[strToInt(registerB)-1];
      
        else if(isItConst(registerB)){
            int intValue = strToInt(registerB);
            registers[strToInt(registerA)-1]=
                                    registers[strToInt(registerA)-1]+intValue;
        }
        else if(isItAdress(registerB))
            registers[strToInt(registerA)-1]=
            registers[strToInt(registerA)-1]+adress[strToInt(registerB)];
        else{
            cerr << "\nInvalid ADD" << endl;
            return -1;
        }
    }
    else{
        cerr << "\nInvalid ADD" << endl;
            return -1;
        }
    printContents(programOption,registers,adress);
    return 0;
}
int SUB(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]){
    string registerA,registerB;
    fillString(inputfile,registerA,registerB,"SUB");
    if(programOption==1 || programOption==2)
        cout << "SUB "<< registerA <<","<< registerB;
    if(isItRegister(registerA)){
        
        if(isItRegister(registerB))
            registers[strToInt(registerA)-1]=
              registers[strToInt(registerA)-1]-registers[strToInt(registerB)-1];
        
        else if(isItConst(registerB))
            registers[strToInt(registerA)-1]=
                    registers[strToInt(registerA)-1]-strToInt(registerB);
        else if(isItAdress(registerB))
            registers[strToInt(registerA)-1]=
            registers[strToInt(registerA)-1]-adress[strToInt(registerB)];
        else{
            cerr << "\nInvalid SUB" << endl;
            return -1; 
        }
    }
    else{
        cerr << "\nInvalid SUB" << endl;
        return -1;
    }
    printContents(programOption,registers,adress);
    return 0;
}
int JMP(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]) {
    string registerA,registerB,temp;
    fillString(inputfile,registerA,registerB,"JMP");
    if(isItRegister(registerA)){
        if(registers[strToInt(registerA)-1]==0){
            if(programOption==1 || programOption==2)
                cout << "JMP "<< registerA<<"," << registerB;
            int valRegB = strToInt(registerB);
            if(valRegB>findLineNum(inputfile,FILENAME)){
                cerr << "\nInvalid JMP"<< endl;
                return -1;
            }
            inputfile.close();
            inputfile.open(FILENAME);
            for(int i=1; i<valRegB; i++)
                getline(inputfile, temp);
        }
    }
    else if(isItConst(registerA)){
        if(programOption==1  || programOption==2)
            cout << "JMP "<< registerA;
        int valRegA = strToInt(registerA);
        if(valRegA>findLineNum(inputfile,FILENAME)){
            cerr << "\nInvalid JMP"<< endl;
            return -1;
        }
        inputfile.close();
        inputfile.open(FILENAME);
        for(int i=1; i<valRegA; ++i)
            getline(inputfile, temp);
    }
    else{
        if(programOption==1 || programOption==2)
            cout << "JMP "<< registerA<<" " << registerB;
        cerr << "\nInvalid JMP"<< endl;
        return -1;
    }   /*Jumpu yapabilmesi için ya registerB nin değeri sıfır olacak yada
         registerB constant bir değer olacak (jumpuda olunca yazacagından..)*/
    if((programOption==1 || programOption==2) && 
       (registers[strToInt(registerA)-1]==0 || isItConst(registerA)))
        printContents(programOption,registers,adress);
 
    return 0;
}
int JPN(fstream& inputfile,int registers[],const char* FILENAME,
         const char programOption, unsigned int adress[]){
    string registerA,registerB,temp;
    fillString(inputfile,registerA,registerB,"JPN");
        
    if(isItRegister(registerA) && isItConst(registerB)){
        if(registers[strToInt(registerA)-1]<=0){
            if(programOption==1  || programOption==2)
                cout << "JPN "<< registerA <<","<< registerB;
            int valRegB = strToInt(registerB);
            if(valRegB>findLineNum(inputfile,FILENAME)){
                cerr << "\nInvalid JPN"<< endl;
                return -1;
            }
            inputfile.close();
            inputfile.open(FILENAME);
            for(int i=1; i<valRegB; ++i)
                getline(inputfile, temp);
        }
    }
    else{
        cerr << "\nInvalid JPN"<< endl;
        return -1;
    }
    if((programOption==1 || programOption==2) && 
                                        registers[strToInt(registerA)-1]<=0)
        printContents(programOption,registers,adress);
    return 0;
}
int HLT(const string& other, bool& PrograminContinue, int programOption){
     if(other[0]=='H' && other[1]=='L' && other[2]=='T'){
        if(programOption == 1 || programOption == 2 )
            cout << "HLT";
        PrograminContinue=false;
        return  0; 
    }
    else{
        cout << other;
        cerr<<"\nInvalid command!"<<endl;
        return -1;
    }
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
        while(temp[loopCounter--]==' ') //virgulden once olan bosluklari sayacak
            spacesBeforeComma++;

        string1=temp.substr(spacesAfterCommand,indexComma-spacesAfterCommand
                                                            -spacesBeforeComma);
        loopCounter=indexComma+1;
        while(temp[loopCounter++]==' ')
            spacesAfterComma++; //virgulden sonraki bosluk sayisi
        
        loopCounter=spacesAfterComma+indexComma+1;

        int wordSize=0;
        // MOV R2,R4; gibi ifadedelerdede hata vermeden calistirmali
        while(temp[loopCounter]!=' ' && temp[loopCounter]!=';' 
                                     && temp[loopCounter]!='\0'){
            // "\0" satirin sonuna kadar
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
bool isItAdress(const string& stringToCheck){
    
    int sizeOfString=stringToCheck.size();
    
    if(stringToCheck[0]=='#'){
    
        for(int index=1; sizeOfString > index; ++index)
            if(strToInt(stringToCheck)<0 || strToInt(stringToCheck)>=50)
                return false;
    }
    else
        return false;
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
void printContents(const char programOption, int registers[], 
                   unsigned int adress[]){
    
    if(programOption==1 || programOption==2)
        for(int i=0; i<5; ++i){
            cout << " R"<<i+1<<":"<<registers[i];
            if(i!=4)
                cout << "," ;
            else
                cout <<endl;
        }
    if(programOption == 2){
        cout << endl;
        for(int i=0; i<50; ++i){
            cout << "#" <<i<<":"<<adress[i];
            if(i!=49)
                cout<< ",";
            else
                cout<<endl<<endl;
        }
    }
    if(programOption == -1){ // Sadece "HLT" komutu icin
        int i=0;
        for(i=0; i<5; ++i){
            cout << " R"<<i+1<<":"<<registers[i];
            if(i!=4)
                cout << "," ;
            else
                cout <<endl;
        }
        cout << endl;
        for(i=0; i<50; ++i){
            cout << "#" <<i<<":"<<adress[i];
            if(i!=49)
                cout<< ",";
            else
                cout<<endl<<endl;
        }
    }
    return;
}
