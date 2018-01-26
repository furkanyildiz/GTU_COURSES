/*
 * File:   Fmap.cpp
 * Author: furkan
 *
 * Created on December 15, 2016, 2:37 PM
 */

#include "Fmap.h"
#include <utility>
#include <iostream>
using namespace std;
namespace FurkanSTL{
	// No param constructure calls, int param constructure 
    template <class T,class U >
    Fmap<T,U>::Fmap():Fmap(23){}
    //int param constucture is allocates memory according to given number
    template <class T,class U >
    Fmap<T,U>::Fmap(int cap):capacity(cap),used(0){
        data= new value_type[cap];
    }
    // Copy constructure, creates(with copy) a new obje according to given obje 
    template <class T,class U >
    Fmap<T,U>::Fmap(const Fmap& orig) 
    :capacity( orig.getCap() ) , used(0) {

    	data= new value_type[getCap()];
    	
        for(int i=0; i<orig.getUsed(); ++i)
            this->insert(orig.data[i].first,orig.data[i].second);
    }
    // chechs that datas capacity is full or not.
    template <class T,class U >
    bool Fmap<T,U>::full()const{
        return capacity==used;
    }
    // if datas capacity is full, the function be called and extends capacity
    template <class T,class U >
    void Fmap<T,U>::extendCap(){
        setCap(getCap()*2+1);
       	value_type_ptr temp=new value_type[getCap()];
       	for(int i=0; i<getUsed(); ++i)
            temp[i]=data[i];
        delete [] data;
        data=temp;
    }
    //Insert a value to map.
    template <class T,class U >
    void Fmap<T,U>::insert ( T val,  U val2){
        if(full()) //if capacity is full we need to extend it.
            extendCap();
        int index=getUsed();
    	data[index].first  = val;
        data[index].second = val2;
    	setUsed(++index);
    	sort();
    }
    //Convert to empty the map
    template <class T,class U >
    void Fmap<T,U>::empty(){
        setUsed(0);
    }
    //Assingmen operator
    template <class T,class U >
    Fmap<T,U>& Fmap<T,U>::operator=(const Fmap<T,U>& rightSide){
        
        if(getCap()!=rightSide.getCap()){
            delete [] data;
            setCap(rightSide.getCap());
            setUsed(0);
            data = new  value_type[getCap()];
        }
        setUsed(rightSide.getUsed());
        for(int i=0; i<getUsed(); ++i)
             data[i]=rightSide[i];

        return *this;
    }
    //Search template value in Fmap, return number of serached value
    template <class T,class U>
    int Fmap<T,U>::search(T value)const{
        int count = 0;
        for(int i=0; i<getUsed(); ++i)
            if(data[i].first == value)
                return data[i].second;
        return count;
        
    }
    //Search template value in Fmap, return index of serached value
    template <class T,class U>
    int Fmap<T,U>::found(const T& value)const{
        int index = -1;
        for(int i=0; i<getUsed(); ++i)
            if(data[i].first == value)
                return i;
        return index;
        
    }
    template <class T,class U >
    pair< T, U> & Fmap<T,U>:: operator[](const T& pairVal){
    	if(getUsed()!=0)
    		sort();
        int index = found(pairVal);
        if(index==-1){//Not found
        	cerr<<"//Not found, I'll return last indexs referance"<<endl;
        	return data[getUsed()-1];
        }
        return data[index];
    }
    
    template <class T,class U >
    const pair< T, U> & Fmap<T,U>:: operator[](const T& pairVal)const{
        int index = found(pairVal);
        if(index==-1){//Not found
        	cerr<<"//Not found, I'll return last indexs referance"<<endl;
        	return data[getUsed()-1];
        }
        return data[index];
    }
    template <class T,class U >
    pair< T, U> & Fmap<T,U>:: operator[](int index){
        if(index>=getUsed()){
            cerr<<"Index can not be equal or greater than used";
            cerr<<" so I'll return at least string of my object."<<endl;            
            return data[getUsed()-1];  
        }
    	if(getUsed()!=0)
    		sort();
        return data[index];
    }
    template <class T,class U >
    const pair<T, U>& Fmap<T,U>:: operator[](int index)const{
        if(index>=getUsed()){
            cerr<<"Index can not be equal or greater than used";
            cerr<<" so I'll return at least string of my object."<<endl;            
            return data[getUsed()-1];  
        }
        return data[index];

    }
    template <class V,class Y=int >
    ostream& operator<<(ostream& outputStream,const Fmap<V,Y>& other){

    	for(int i=0; i<other.getUsed(); ++i){
            outputStream<<"("<<other.data[i].first.first<<"-";
			outputStream<<other.data[i].first.second<<")"<<endl;
		}
    	return outputStream;
    }
    template <class T,class U>
    ostream& Fmap<T,U>::print(ostream& outputStream)const{


    	for(int i=0; i<getUsed(); ++i){
            outputStream<<"("<<data[i].first.first<<"-";
			outputStream<<data[i].first.second<<") num: "<<data[i].second;

			if(i!=getUsed()-1)
				outputStream<<endl;

		}
    	return outputStream;
    }
    // Sorts data decreasing occurent order.
    template <class T,class U >
    void  Fmap<T,U>::sort(){

    	int size=getUsed();

	    for(int i=0; i<size-1; ++i){
	    	for(int j=0; j<size-i-1; ++j){
	    		if(data[j].second < data[j+1].second){

	    			auto temp=data[j];
	    			data[j]=data[j+1];
	    			data[j+1]=temp;
	    		}
	    	}
	    }

    }
    // Destructure deletes all allocated data.
    template <class T,class U >
    Fmap<T,U>::~Fmap(){

    	delete [] data;
        data = nullptr;
    }
}