/* 
 * File:   BigramDyn.h
 * Author: furkan
 *
 * Created on December 15, 2016, 2:37 PM
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H
#include "Bigram.h"
#include "Fmap.h"
#include "exception.h"
using FurkanSTL::Fmap;
using namespace std;
namespace FurkanBigram {

    template <class T>
    class BigramDyn:public Bigram<T>{
    public:
        typedef Fmap<pair<T,T>> value_type;
        BigramDyn();
        BigramDyn(int);
        BigramDyn(const BigramDyn& orig)=default;
        BigramDyn& operator=(const BigramDyn<T>& rightSide) = default;
        virtual void readFile(const string &filename) 
    							 throw (READFILEERROR,FILEIOERROR) override ;
        virtual int numGrams()const override;
        virtual int numOfGrams(const T& one,const T& two)const override;
        virtual const pair<T, T> maxGrams()const override;
        virtual ostream& print(ostream& outputStream)const override;
        template <class U>
        friend ostream& operator<< (ostream& outputStream, 
        												const BigramDyn<U>& o);
        virtual ~BigramDyn()=default;


    private:
        value_type mymap;
        void calculateBigram(ifstream& file)throw (READFILEERROR);
    };

} //END OF namespace FurkanBigram

#endif /* BIGRAMDYN_H */