#include <iostream>

#include "TDrzewo.h"

using namespace std;

int main()
{
    TDrzewoAVL x1;

    x1.insert(1);
    x1.insert(2);
    x1.insert(3);
    x1.insert(4);
    x1.insert(5);
    x1.insert(6);
    x1.insert(7);
    x1.insert(8);
    x1.insert(9);
    x1.display();
    x1.remove(4);
    x1.display();

}