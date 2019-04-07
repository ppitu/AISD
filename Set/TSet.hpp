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

        std::pair<bool, typename TDrzewoAVL<T>::Iterator> insert(T );
        void display();
        std::pair<bool, typename TDrzewoAVL<T>::Iterator> findElement(T );
        void remove(T );
        int sizeElement();

        typename TDrzewoAVL<T>::Iterator begin()
        {
            return x1.begin();
        }

        typename TDrzewoAVL<T>::Iterator end()
        {
            return x1.end();
        }

};

template <typename T>
std::pair<bool, typename TDrzewoAVL<T>::Iterator>  TSet<T>::insert(T x)
{
    bool pombool = false;
    typename TDrzewoAVL<T>::Iterator iter;

    if(x1.findElement(x) == nullptr)
    {
        pombool = true;
        x1.insert(x); 
        
        return std::make_pair(pombool, typename TDrzewoAVL<T>::Iterator (iter));
    }
    return make_pair(pombool, typename TDrzewoAVL<T>::Iterator (iter));
        
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
    /*if(pom == nullptr)
        return nullptr;
    else
    {
        ;
    }*/
    
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