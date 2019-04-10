#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>

#include "BST.hpp"

template <typename K, typename V>
class Map
{
	public:	

		void insert(std::pair<K, V> );		

	private:
		class MapElem
		{
			public:
				std::pair<K, V> key_value;

				MapElem() = default;
				MapElem(const std::pair<K, V> &key_value);
				MapElem(const K &key, const V &value);

				bool operator<(const MapElem &) const;
				bool operator>(const MapElem &) const;
		};
	
	public:
		BST<MapElem> bst_t;
	
};

/*funkcjie publiczne klasy Map*************************************************/

template <typename K, typename V>
void Map<K, V>::insert(std::pair<K, V> key_value)
{
	bst_t.insert(key_value);
}

/*funkcjie publiczne klasy MapElem********************************************/

template <typename K, typename V>
Map<K, V>::MapElem::MapElem(const std::pair<K, V> &key_value)
{
	this->key_value.first = key_value.first;
	this->key_value.second = key_value.second;
}

template <typename K, typename V>
Map<K, V>::MapElem::MapElem(const K &key, const V &value)
{
	this->key_value.first = key;
	this->ke_value.second = value;
}

template <typename K, typename V>
bool Map<K, V>::MapElem::operator<(const MapElem& elem ) const
{
	 return this->key_value.first < elem.key_value.first;
}

template <typename K, typename V>
bool Map<K, V>::MapElem::operator>(const MapElem& elem ) const
{
	return this->key_value.first > elem.key_value.first;
}

#endif //MAP_HPP_
