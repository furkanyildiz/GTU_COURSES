/* 
 * File:   BigramMap.cpp
 * Author: furkan
 * 
 * Created on December 14, 2016, 8:34 PM
 */

#include "BigramMap.h"
#include <fstream>
#include <algorithm>
using namespace std;
namespace FurkanBigram {
    /* Template pairleri siralayabilmek icin Functor yazdık.*/
	template <typename T1, typename T2>
	struct compare {
	    typedef pair<T1, T2> type;
	    bool operator ()(type const& a, type const& b) const {
	        return a.second > b.second;
	    }
	};

	/* No param constructure */
    template <class T, class U>
    BigramMap<T,U>::BigramMap():Bigram<T>() {
    }
    /* int param contructure*/
    template <class T, class U>
    BigramMap<T,U>::BigramMap(int num):Bigram<T>() {
    }    
    /*takes a filename as a string parameter, reads the file, calculates all 
    the bigrams.*/
    template <class T, class U>
    void BigramMap<T,U>::readFile(const string &filename) 
                                        throw (READFILEERROR,FILEIOERROR)
    {
        ifstream file;
        file.open(filename);
        if (file.fail()) 
            throw FILEIOERROR();
        calculateBigram(file);
        file.close();
    }
    /* calculates all bigrams and stores the bigrams to std::map, if there is
    	a problem with calculating bigrams throw exception */
    template <class T, class U>
    void BigramMap<T,U>::calculateBigram(ifstream& file)throw (READFILEERROR){
        T a,b;
        file >> a;
        if(file.eof())
        	throw READFILEERROR();
        while(!file.eof()){
            
            if(file.bad( ))
                throw READFILEERROR();
            
            if(!(file>>b))
            	throw READFILEERROR();
            
            auto iter = mymap.find(make_pair(a,b));

            if( iter == mymap.end()) //there is no such element
                mymap.insert(make_pair(make_pair(a,b),1));

            else{
                int temp;
                temp = iter->second;
                ++temp;
                mymap[make_pair(a,b)]=temp;
            }

            a=b;
        }
    }
    /* returns the total number of bigrams calculated so far. */
    template <class T, class U>
    int BigramMap<T,U>::numGrams()const{
        int sum = 0;
        for(auto iter = mymap.begin(); iter!=mymap.end(); ++iter)
            sum+=iter->second;
        return sum;
    }
    /* takes two elements as bigrams and returns the number of that bigram 
    	read so far*/
    template <class T, class U>
    int BigramMap<T,U>::numOfGrams(const T& one, const T& two)const{
        
        auto iter = mymap.find(make_pair(one,two));
        if(iter != mymap.end())
            return iter->second;
        else
        	return 0;
    }
    /* returns the bigram that has occurred most frequently.  */
    template <class T, class U>
    const pair<T, T> BigramMap<T,U>::maxGrams()const{
        
        auto iter = mymap.begin();
        
        int max=iter->second;
        
        for(; iter!=mymap.end(); ++iter)
            if(max<iter->second)
                max=iter->second;
        
        iter = mymap.begin();
        
        while(iter->second != max)
            ++iter;
        
        return make_pair(iter->first.first,iter->first.second);
        
    }
    /*  prints all the bigrams and their occurences in decreasing occurent 
    	order. When we want to print object of BigramMap, Base class << 
    	operators calling the function. */
    template <class T, class U>
    ostream& BigramMap<T,U>::print(ostream& outputStream) const
    {

    	vector<pair<pair<T,T>,int>> mapcopy(mymap.begin(), mymap.end());
    	sort(mapcopy.begin(), mapcopy.end(), compare<pair<T,T>,int>());

        for (auto iter = mapcopy.begin(); iter!=mapcopy.end(); ++iter ){
            outputStream <<"("<<iter->first.first << "-" << iter->first.second;
        	outputStream << ") num: " << iter->second;

        	if(iter!=mapcopy.end()-1)
        		outputStream<<endl;
        }

        return outputStream;
    }
    /*  prints all the bigrams and their occurences in decreasing occurent 
	order. When we want to print object of BigramMap, Base class << 
	operators calling the function. */
	template <class T,class U>
	ostream& operator<< (ostream& outputStream, const BigramMap<T,int>& o){
		return o.print(outputStream);
    }

} //end of namespace