/* 
 * File:   Bigram.cpp
 * Author: furkan
 * 
 * Created on December 14, 2016, 8:32 PM
 */

#include "Bigram.h"
namespace FurkanBigram {
	template <class T>
	ostream& operator<< (ostream& outputStream, const Bigram<T>& o){
		return o.print(outputStream);
    }
}