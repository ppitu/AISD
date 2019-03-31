#ifndef TSet_hpp_
#define TSet_hpp_

#include <iostream>

#include "TDrzewoAVL.hpp"

using namespace std;

template <typename T>
class TSet
{
    public:
        TDrzewoAVL<T> x1;

        void insert(T );
        void display();
        void findElement(T );
        void remove(T );
        int sizeElement();

};

template <typename T>
void TSet<T>::insert(T x)
{
    if(x1.findElement(x) == nullptr)
        x1.insert(x);
    else 
        return;
}

template <typename T>
void TSet<T>::display()
{
    x1.display();
}

template <typename T>
void TSet<T>::findElement(T x)
{
    auto pom = x1.findElement(x);
}

template <typename T>
void TSet<T>::remove(T x)
{
    if(x1.findElement(x) == nullptr)
        return;
    else 
        x1.remove(x);
}

template <typename T>
int TSet<T>::sizeElement()
{
    return x1.treeSize();
}

#endif //Tset_hpp_