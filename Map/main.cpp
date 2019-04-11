#include <iostream>
#include <string>

#include "Map.hpp"

using namespace std;

template <typename Iter>
void printDebugInfo(const std::pair<bool, Iter> &insert_info)
{
	//cout << (insert_info.first ? "Dodano " + *insert_info.second : "Nie dodano ;/") << endl;
	
	if(insert_info.first)
		cout << "Dodano " << *insert_info.second;
	else
		cout << "Nie dodano ;/";

	cout << endl;
	
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





	return 0;
}
