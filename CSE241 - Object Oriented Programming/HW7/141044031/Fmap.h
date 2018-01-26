/*
 * File:   Fmap.h
 * Author: furkan
 *
 * Created on December 15, 2016, 2:37 PM
 */

#ifndef FMAP_H
#define FMAP_H
#include <iostream>
#include <utility>
#include <iterator>

using namespace std;
namespace FurkanSTL{
        
    template <typename T,typename U=int>
    class Fmap
    {
    public:
        typedef pair<T, U> value_type;
        typedef pair<T, U>* value_type_ptr;
        typedef int size_t;
        Fmap();
        Fmap(int);
        Fmap(const Fmap& orig);
        pair< T, U> & operator[](const T& pairVal);
        const pair< T, U> & operator[](const T& pairVal)const;
        pair< T, U> & operator[](int index);
        const pair<T, U> & operator[](int index)const;
        int getUsed()const{return used;}
        int getCap()const{return capacity;}
        int getCount(int i)const{ return data[i].second;}
        void empty();
        template <class V,class Y>
        friend ostream& operator<<(ostream& outputStream,
        											const Fmap<V,Y>& other);
        ostream& print(ostream& outputStream)const;
        Fmap<T,U>& operator=(const Fmap<T,U>& rightSide);
        int search(T value)const;
        void insert ( T val,  U val2);
        virtual ~Fmap();
        void sort();


    private:
        value_type_ptr data;
        size_t capacity;
        size_t used;
        void extendCap();
        void setCap(int val){capacity=val;}
        void setUsed(int val){used= val;}
        bool full()const;
        int found(const T& value)const;


    };
} //END OF NAMESPACES

#endif /*FMAP_H */