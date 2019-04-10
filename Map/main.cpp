#include <iostream>
#include <string>

#include "Map.hpp"

using namespace std;

template <typename K, typename V>
void printSetSizeAndElems(Map<K, V> &m)
{
	cout << "Size " << m.size() << endl;
	for(auto &e : m)
		std::cout << e ;
	cout << endl;
}



int main()
{
	Map<int, string> map_t;

	map_t.insert({1, "first"});

	printSetSizeAndElems(map_t);

	return 0;
}
