#include <iostream>
#include <string>

#include "Set.hpp"

using namespace std;

template <typename Iter>
void printDebugInfo(const std::pair<bool, Iter> &insert_info)
{
	cout << (insert_info.first ? "Dodano " + std::to_string(*insert_info.second) : "Nie dodano ;/") << endl;
}

template <typename Iter>
void printDebugInfo(const Iter &find_info)
{
	cout << (find_info ? "Znaleziono " +std::to_string(*find_info) : "Nie znaleziono ;/") << endl;
}

template <typename T>
void printSetSizeAndElems(Set<T> &s)
{
	cout << "Size: " << s.size() << endl;
	for(auto &e : s)
		cout << e << ", ";
	cout << endl;
}

template <typename T>
void printSetSizeAndElems(const Set<T> &s)
{
	cout << "Size " << s.size() << endl;
	for(const auto &e : s) 
		cout << e << ", ";
	cout << endl;
}

int main()
{
	Set<int> s;

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

	printDebugInfo(s.find(8));

	auto it = s.find(10);

	s.remove(4);
	s.remove(12);
	s.remove(14);


	const auto s4 = s;
	printSetSizeAndElems(s4);

	printSetSizeAndElems(s);

	return 0;
}
