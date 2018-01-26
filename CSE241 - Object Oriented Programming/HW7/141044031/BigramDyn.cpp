#include "BigramDyn.h"
#include <fstream>
#include "exception.h"

namespace FurkanBigram {

	/* No param constructure */
    template <class T>
    BigramDyn<T>::BigramDyn():Bigram<T>(){
    }
    /* int param contructure*/
    template <class T>
    BigramDyn<T>::BigramDyn(int val):Bigram<T>(){

    }
    /*takes a filename as a string parameter, reads the file, calculates all 
    the bigrams.*/
    template <class T>
    void BigramDyn<T>::readFile(const string &filename)
                                            throw (READFILEERROR,FILEIOERROR){
        ifstream file;
        file.open(filename);
        if (file.fail()) 
            throw FILEIOERROR();
        calculateBigram(file);
        file.close();

    }
    /* calculates all bigrams and stores the bigrams to std::map, if there is
    	a problem with calculating bigrams throw exception */
    template <class T>
    void BigramDyn<T>::calculateBigram(ifstream& file)throw (READFILEERROR){
        T a,b;
        file >> a;
        if(file.eof())
        	throw READFILEERROR();
        while(!file.eof()){
            
            if(file.bad( ))
                throw READFILEERROR();
            
            if(!(file>>b))
            	throw READFILEERROR();
            pair<T,T> temp;
            temp = make_pair(a,b);
            int found = mymap.search(temp);
            if(found == 0)
               mymap.insert(temp,1);
            else{
                ++found;
                mymap[temp].second=found;
            }
            a=b;
                            
        }

    }
    /* returns the total number of bigrams calculated so far. */
	template <class T>
    int BigramDyn<T>::numGrams()const{
        int sum = 0;
        for(int i=0; i<mymap.getUsed(); ++i)
            sum+=mymap.getCount(i);
        return sum;
    }
    /* takes two elements as bigrams and returns the number of that bigram 
	read so far*/
    template <class T>
    int BigramDyn<T>::numOfGrams(const T& one, const T& two)const{
        pair<T,T> temp;
        temp = make_pair(one,two);
        return mymap.search(temp);
    }
    /* returns the bigram that has occurred most frequently.  */
    template <class T>
    const pair<T, T> BigramDyn<T>::maxGrams()const{
        int max = mymap.getCount(0);
        int index = 0;
        for(int i=1; i<mymap.getUsed(); ++i)
            if(max<mymap.getCount(i)){
                max=mymap.getCount(i);
                index = i;
            }
        return mymap[index].first;
        
    }
    /*  prints all the bigrams and their occurences in decreasing occurent 
	order. When we want to print object of BigramDyn, Base class << 
	operators calling the function and the function is calling to Fmap's
	print function and returning ostream object. */
    template <class T>
    ostream&  BigramDyn<T>::print(ostream& outputStream)const{
        return mymap.print(outputStream);
    }
    /*  prints all the bigrams and their occurences in decreasing occurent 
	order. When we want to print object of BigramDyn, Base class << 
	operators calling the function and the function is calling to Fmap's
	print function and returning ostream object. */
	template <class T>
	ostream& operator<< (ostream& outputStream, const BigramDyn<T>& o){
		return o.print(outputStream);
    }
    
}//END OF namespace FurkanBigram