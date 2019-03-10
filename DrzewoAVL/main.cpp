#include <iostream>

#include "TDrzewo.h"

using namespace std;

int main()
{
    TDrzewoAVL x1;

    x1.insert(3);
    x1.insert(6);
    x1.insert(4);

    x1.display();
}