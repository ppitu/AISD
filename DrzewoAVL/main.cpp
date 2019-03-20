#include <iostream>

#include "TDrzewoAVL.hpp"

using namespace std;

int main()
{
    TDrzewoAVL<int> x1;

    x1.insert(3);
    x1.insert(2);
    x1.insert(2);
    x1.insert(4);
    x1.insert(6);

    x1.display();

    x1.remove(3);

    x1.display();

    auto element = x1.findElement(2);
    element = x1.findElement(10);

    auto z = x1.treeSize();

    TDrzewoAVL<int> x2(x1);

    x2.display();

    x2.insert(8);

    x1.display();
    x2.display();
    z = x1.treeSize();
    z = x2.treeSize();

    auto x3 = x2;
    x2.display();
    x3.display();

    x3.insert(15);

    x2.display();
    x3.display();
    z = x2.treeSize();
    z = x3.treeSize();

}