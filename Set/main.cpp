#include <iostream>

#include "TDrzewo.hpp"
#include "TSet.hpp"

using namespace std;

int main()
{
    TSet<int> x1;

    x1.insert(4);
    x1.insert(4);
    x1.insert(3);

    x1.display();
}