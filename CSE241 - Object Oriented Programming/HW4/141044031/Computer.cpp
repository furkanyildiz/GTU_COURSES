/* 
 * File:   Computer.cpp
 * Author: furkan
 * 
 * Created on October 29, 2016, 10:38 PM
 */
#include "Computer.h"
using namespace std;


Computer::Computer() {
    setOption(0);
    CPU pc_CPU;
    CPUProgram pc_CPUProgram;
    Memory pc_Memory;
    setCPU(pc_CPU);
    setCPUProgram(pc_CPUProgram);
    setMemory(pc_Memory);
    
}

/* Obje integer deger verilerek olusturulursa bu constructure cagirilacak ve
 * constructure, parametresiz contructure yi cagirip, cpu, cpuprogram ve 
 * memory classlarinin jump olmasini engelleyecek, daha sonra
 * optionun gecerli olup olmadigini kontrol edecek eger gecerli ise
 * optionu computerin cpu nun cpuprogramıin ve memorynin optionuna set 
 * edecek.  */
Computer::Computer(int option) :Computer() {
    isOptionValid(option);
    setOption(option);
    pcCPU.setOption(option);
    pcCPUProgram.setOption(option);
    pcMemory.setOption(option);
}
/* Obje olusturulurken cpu,cpuprogram,memory ve integer verilirse bu constucture
 * cagirilacak. Verilen classlari computer'in classlarina atiyacak,o
 * optionu kontrol edip, gecerli ise classlara set edecek 
*/
Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory, 
                                                                int option)
{
    isOptionValid(option);
    setCPU(myCPU);
    setCPUProgram(myCPUProgram);
    setMemory(myMemory);
    setOption(option);
    pcCPU.setOption(option);
    pcCPUProgram.setOption(option);
    pcMemory.setOption(option);
}
/*isOptionValid fonksiyonu aldigi optionun gecerli olup olmadigini kontrol
 *edecek. Option 1 2 veya 0 degilse program sonlanacak.
*/
void Computer::isOptionValid(int progOption)const{
    if(progOption!=0 && progOption!=1 && progOption!=2){
        cerr << "Program option must be 0,1 or 2"<<endl;
        exit(1);
   }
   return;
}
/* execute fonksiyonu herhangibir parametre almayacak ve herhangibir return 
 * degeri olmayacak,bu fonksiyonu kullanmak icin daha onceden dosyanin 
 * okunmus ve kaydedilmis olmasi gerekmektedir. getLine fonksiyonu ile o 
 * kayitlara tek tek ulasip, execute ile komutlari calistiracagiz */
void Computer:: execute(){
    //Eger dosya okunup instructionlara kaydedilmeden, program run
    //edilmeye calisilirse, program hata verip cikmali.
    if(pcCPUProgram.size()<1){
        cerr<<"Program can not run, you have to read file first!"<<endl;
        exit(1);
    }
    while(!pcCPU.halted()){
        string instruction = pcCPUProgram.getLine(pcCPU.getPC());
        pcCPU.execute(instruction, pcMemory);
    }
    return;
}
/* Computer class'inin tek basina calisabilmesi icin overload edilmistir. Eger
 * tek basina calistirilmak istenirse execute fonksiyonuna filename parametresi
 * verilmelidir. Fonksiyon ReadFile'ı cagirip dosyayi okuyup instructin 
 * vektorune kaydedecek, getLine fonksiyonu ile o kayitlara tek tek ulasip,
 * execute ile komutlari calistiracagiz */
void Computer:: execute(const string& filename){
    pcCPUProgram.ReadFile(filename);
    while(!pcCPU.halted()){
        string instruction = pcCPUProgram.getLine(pcCPU.getPC());
        pcCPU.execute(instruction, pcMemory);
    }
    return;
}