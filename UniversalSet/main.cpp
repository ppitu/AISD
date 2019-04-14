#include <iostream>
#include <string>

#include "UniversalSet.hpp"

using namespace std;

template <typename T, std::size_t N>
void printSizeAndElems(const typename UniversalSet<T, N>::Vector &v)
{
	cout << "Size: " << v.count() << endl;
	/*for(auto &e : v) 
		cout << e << ", ";*/
	cout << endl;
}

int main()
{
	constexpr std::size_t N = 10u;

	UniversalSet<std::string, N> us({"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"});

	auto v1 = us.makeVector();
	auto v2 = us.makeVector();

	cout << us.elem(0) << endl;
	cout << us[0] << endl;
	cout << us.universeSize() << endl;
	cout << v1.count() << endl;
	cout << v2.count() << endl;
	v1.lol();
	v2.lol();
	
	for(std::size_t i = 0; i < us.universeSize(); i++)
	{
		if(i == 2)
		{ v1.insert(i);
		}
		else v2.insert(i);
	}

	cout << v1.count() << endl;
	cout << v2.count() << endl;	
	v1.lol();
	v2.lol();

	auto v3 = v2;
	cout << (v1.isMember(1u) ? "Znaleziono" : "Nie znaleziono") << endl;
	cout << (v1.isMember(2u) ? "Znaleziono" : "Nie znaleziono") << endl;
	cout << (v2.remove(8u) ? "Usunieto" : "Nie usunieto") << endl;
	cout << (v2.remove(9u) ? "Usunieto" : "Nie usunieto") << endl;

	v2.lol();

	auto v4 = v1 + v3;

	cout << v1.count() << endl;
	cout << v3.count() << endl;
	cout << v4.count() << endl;	
	v1.lol();
	v3.lol();
	v4.lol();

	const auto v5 = v3 - v2;

	cout << v3.count() << endl;
	cout << v2.count() << endl;
	cout << v5.count() << endl;	
	v3.lol();
	v2.lol();
	v5.lol();

	auto v6 = v3 * v5;

	cout << v3.count() << endl;
	cout << v5.count() << endl;
	cout << v6.count() << endl;	
	v3.lol();
	v5.lol();
	v6.lol();

	const auto v7 = v5 / v3;

	cout << v5.count() << endl;
	cout << v3.count() << endl;
	cout << v7.count() << endl;	
	v5.lol();
	v3.lol();
	v7.lol();
}
