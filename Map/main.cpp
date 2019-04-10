#include <iostream>
#include <string>

#include "Map.hpp"

using namespace std;

int main()
{
	Map<int, string> map_t;

	map_t.insert({1, "first"});

	return 0;
}
