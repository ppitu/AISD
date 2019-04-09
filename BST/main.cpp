#include <iostream>

#include "BST.hpp"

template <typename T>
void printSetSizeAndElems( BST<T> &s)
{
	std::cout << "Size: " << s.size() << std::endl;
	for(const auto &e : s) std::cout << e << ", ";
	std::cout << std::endl;
}

int main()
{
	BST<int> x1;

	x1.insert(1);
	x1.insert(4);
	x1.insert(5);
	x1.insert(6);
	x1.insert(2);
	x1.insert(1);
	x1.insert(10);
	x1.insert(13);
	x1.insert(16);
	x1.insert(16);
	x1.insert(14);
	x1.insert(12);
	x1.insert(11);
	x1.insert(23);

	auto x2 = x1;

	x2.remove(4);
	x2.remove(16);

	BST<int> x3(x1);

	x3.insert(54);
	x3.insert(60);

	printSetSizeAndElems(x1);
	printSetSizeAndElems(x2);
	printSetSizeAndElems(x3);
	return 0;
}
