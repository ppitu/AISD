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
        typename TDrzewoAVL<T>::Iterator findElement(T );
        void remove(T );
        int sizeElement();
        int sizeElement() const;

        typename TDrzewoAVL<T>::Iterator begin()
        {
            return x1.begin();
        }

        typename TDrzewoAVL<T>::Iterator begin() const
        {
            return x1.begin();
        }

        typename TDrzewoAVL<T>::Iterator end()
        {
            return x1.end();
        }

        typename TDrzewoAVL<T>::Iterator end() const
        {
            return x1.end();
        }

        typename TDrzewoAVL<T>::Iterator findEle(T x)
        {
            return x1.findEle(x);
        }

        std::size_t size() const { return x1.treeSize();}

};

template <typename T>
std::pair<bool, typename TDrzewoAVL<T>::Iterator> TSet<T>::insert(T x)
{
    return x1.insert(x);
}

template <typename T>
void TSet<T>::display()
{
    x1.display();
}

template <typename T>
typename TDrzewoAVL<T>::Iterator TSet<T>::findElement(T x)
{
    return x1.findEle(x);
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

template <typename T>
int TSet<T>::sizeElement() const
{
    return x1.treeSize();
}

#endif //Tset_hpp_