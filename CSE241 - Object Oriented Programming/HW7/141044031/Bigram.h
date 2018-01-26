/* 
 * File:   Bigram.h
 * Author: furkan
 *
 * Created on December 14, 2016, 8:32 PM
 */

#ifndef BIGRAM_H
#define BIGRAM_H
#include <iostream>
using namespace std;

namespace FurkanBigram {
    template <class T>
    class Bigram
    {
    public:
        Bigram()=default;
        Bigram(const Bigram& other)=default;
        Bigram& operator=(const Bigram& other)=default;
        virtual void readFile(const string &filename)=0;
        virtual int numGrams()const=0;
        virtual int numOfGrams(const T& one,const T& two)const=0;
        virtual const pair<T, T> maxGrams()const=0;
        virtual ostream& print(ostream& outputStream) const = 0;
        template <class U>
        friend ostream& operator<< (ostream& outputStream, const Bigram<U>& o);
        virtual ~Bigram()=default;
    };
}
#endif /* BIGRAM_H */