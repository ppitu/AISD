#include "TDrzewo.hpp"

#ifndef TSet_hpp_
#define TSet_hpp_



template <typename T>
class TSet
{

    public:

    void insert(T );
    void display();
    void remove(T );

    private:

};

template <typename T>
void TSet<T>::insert(T x)
{
    TDrzewoAVL<T> s1;
    
    if(find(x, s1.root) == nullptr)
        s1.insert(x);
    else
        cout << "jest" << endl;
}

template <typename T>
void TSet<T>::display()
{
    TDrzewoAVL<T> s1;

    s1.display();
}

template <typename T>
void TSet<T>::remove(T x)
{
    TDrzewoAVL<T> s1;
    
    if(s1.find(x) == nullptr)
        return;

    s1.remove(x);
}

#endif //TSet_hpp_