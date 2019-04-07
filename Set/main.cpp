#include <iostream>
#include <string>
#include "TSet.hpp"

using namespace std;

template <typename Iter>
void printDebugInfo(const std::pair<bool, Iter> &insert_info) { std::cout << (insert_info.first ? "Dodano " + std::to_string(*insert_info.second) : "Nie dodano ;/") << std::endl; }

template <typename Iter>
void printDebugInfo(const Iter &find_info) { std::cout << (find_info ? "Znaleziono " + std::to_string(*find_info) : "Nie znaleziono ;/") << std::endl; }

template <typename T>
void printSetSizeAndElems(TSet<T> &s)
{
std::cout << "Size: " << s.sizeElement() << std::endl;
for(auto &e : s) std::cout << e << ", ";
std::cout << std::endl;
}

template <typename T>
void printSetSizeAndElems(const TSet<T> &s)
{
std::cout << "Size: " << s.sizeElement() << std::endl;
for(const auto &e : s) std::cout << e << ", ";
std::cout << std::endl;
}

int main()
{
TSet<int> s;
printDebugInfo(s.insert(8));
printDebugInfo(s.insert(4));
printDebugInfo(s.insert(10));
printDebugInfo(s.insert(10));
printDebugInfo(s.insert(2));
printDebugInfo(s.insert(5));
printDebugInfo(s.insert(9));
printDebugInfo(s.insert(12));
printDebugInfo(s.insert(12));
printDebugInfo(s.insert(1));
printDebugInfo(s.insert(14));
printDebugInfo(s.insert(7));
{
auto s2 = s;
printSetSizeAndElems(s2);
}
auto it = s.findElement(10);
//*it = 2;
printDebugInfo(s.findElement(5));
s.remove(4);
printDebugInfo(s.findElement(5));
s.remove(12);
s.remove(14);
printDebugInfo(s.insert(0));
printDebugInfo(s.insert(16));
{
TSet<int> s3;
s3 = s;
printSetSizeAndElems(s3);
}
s.remove(8);
printSetSizeAndElems(s);
const auto s4 = s;
printSetSizeAndElems(s4);

return 0;
}


