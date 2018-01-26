/* 
 * File:   Memory.cpp
 * Author: furkan
 * 
 * Created on October 28, 2016, 8:16 PM
 */
#include <iostream>
#include "Memory.h"

using namespace std;

/* Default constructure, optiona ve adress degerlerine 0 atiyacak */
Memory::Memory(): Memory(0) {}
/* Memory objesi eger 1 integer vererek olusturulursa verilen integer,
optiona atanacak ve tum adress degerlerine sifir atanacak. */
Memory::Memory(int optionVal){
	isOptionValid(optionVal);
    setOption(optionVal);
    for (int i = 0 ; i < 50; ++i)
        setMem(i,0);
}
/* Tum adress degerleri ekrana basilacak*/
void Memory::printAll()const{
    cout << "Memory Values:"<<endl;
    for (int i = 0 ; i < 50 ; ++i)
        cout <<'#'<<i<<':'<< getMem(i)<<' ';
    cout <<"\n";
}
/*isOptionValid fonksiyonu aldigi optionun gecerli olup olmadigini kontrol
 *edecek. Option 1 2 veya 0 degilse program sonlanacak.
*/
void Memory::isOptionValid(int progOption)const{
    if(progOption!=0 && progOption!=1 && progOption!=2){
        cerr << "Program option must be 0,1 or 2"<<endl;
        exit(1);
   }
}