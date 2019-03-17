#include <iostream>

#include "TDrzewo.hpp"

using namespace std;

int main()
{
    TDrzewoAVL<int> x1;
    

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
    x1.treeSize();
    x1.insert(2);
    x1.treeSize();
    x1.display();
    x1.remove(4);
    x1.treeSize();
    x1.display();
    x1.remove(4);
    x1.treeSize();
    x1.display();

    TDrzewoAVL<int> x2 {x1};

    x2.display();
    x2.remove(1);
    x1.display();
    x2.display();  

    x1.findElement(7);
    x1.findElement(34);
}