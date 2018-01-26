/* 
 * File:   BigramMap.h
 * Author: furkan
 *
 * Created on December 14, 2016, 8:34 PM
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include "Bigram.h"
#include "exception.h"
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;
namespace FurkanBigram 
{
    template <class T, class U=int>
    class BigramMap :public Bigram<T>
    {
    public:
        BigramMap();
        BigramMap(int);
        BigramMap(const BigramMap& orig)=default;
        BigramMap& operator=(const BigramMap<T,U>& rightSide) = default;
        virtual void readFile(const string &filename)
        							throw (READFILEERROR,FILEIOERROR) override ;
        virtual int numGrams()const override;
        virtual int numOfGrams(const T& one,const T& two)const override;
        virtual const pair<T, T> maxGrams()const override;
		virtual ostream& print(ostream& outputStream) const override;
        template <class W, class X>
        friend ostream& operator<< (ostream& outputStream, 
        											const BigramMap<W,int>& o);
        virtual ~BigramMap()=default;
    private:
        map<pair<T,T>, int> mymap;
        void calculateBigram(ifstream& file)throw (READFILEERROR);

    };
}
#endif /* BIGRAMMAP_H */