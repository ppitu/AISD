#include <iostream>
#include <string>

#include "Map.hpp"

using namespace std;

template <typename Iter>
void printDebugInfo(const std::pair<bool, Iter> &insert_info)
{
	cout << (insert_info.first ? "Dodano " + !*insert_info.second : "Nie dodano ;/") << endl;	
}

template <typename Iter>
void printDebugInfo(const Iter &find_info)
{
	cout << (find_info ? "Znaleziono " + !*find_info : "Nie znaleziono ;/") << endl;

}

template <typename K, typename V>
void printSetSizeAndElems(Map<K, V> &m)
{
	cout << "Size " << m.size() << endl;
	for(auto &e : m)
		cout << e << ", ";
	cout << endl;
}

template <typename K, typename V>
void printSetSizeAndElems(const Map<K, V> &m)
{
	cout << "Size " << m.size() << endl;
	for(const auto &e : m)
		cout << e << ", ";
	cout << endl;
}



int main()
{
	Map<int, string> map_t;

	printDebugInfo(map_t.insert({8, "eight"}));
	printDebugInfo(map_t.insert({4, "four"}));
	printDebugInfo(map_t.insert({10, "ten"}));
	printDebugInfo(map_t.insert({10, "ten"}));
	printDebugInfo(map_t.insert({2, "two"}));
	printDebugInfo(map_t.insert({5, "five"}));
	printDebugInfo(map_t.insert({9, "nine"}));
	printDebugInfo(map_t.insert({12, "twelve"}));
	printDebugInfo(map_t.insert({12, "twelve"}));
	printDebugInfo(map_t.insert({1, "one"}));
	printDebugInfo(map_t.insert({14, "fourteen"}));
	printDebugInfo(map_t.insert({7, "seven"}));

	{
		auto m2 = map_t;
		printSetSizeAndElems(m2);
	}

	auto it = map_t.find(10);
	*it = "10 (poprawione)";

	printDebugInfo(map_t.find(5));	
	map_t.remove(4);
	printDebugInfo(map_t.find(5));
map_t.remove(12);
map_t.remove(14);
printDebugInfo(map_t.insert( { 0, "zero" } ));
printDebugInfo(map_t.insert( { 16, "sixteen" } ));
{
Map<int, std::string> m3;
m3 = map_t;
printSetSizeAndElems(m3);
}
map_t.remove(8);
printSetSizeAndElems(map_t);
const auto m4 = map_t;
printSetSizeAndElems(m4);
auto it2 = m4.find(10);
// *it2 = "nie powinno sie skompilowac";
// m4[2] = "nie powinno sie skompilowac";
map_t[2] = "two (poprawione)";
map_t[20] = "twenty";
printSetSizeAndElems(map_t);

return 0;
}
