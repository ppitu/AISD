#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>

#include "BST.hpp"

template <typename K, typename V>
class Map
{
	public:	

		void insert(std::pair<K, V> );
		int size();

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

				friend ostream& operator<<(ostream&, MapElem &);

		};
	
	public:
		BST<MapElem> bst_t;
		typename BST<MapElem>::Iterator begin();
		typename BST<MapElem>::Iterator end();	
};

/*funkcje publiczne klasy Map*************************************************/

template <typename K, typename V>
void Map<K, V>::insert(std::pair<K, V> key_value)
{
	bst_t.insert(key_value);
}

template <typename K, typename V>
int Map<K, V>::size()
{
	return bst_t.size();
}

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::begin()
{
	return bst_t.begin();
}

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::end()
{
	return bst_t.end();
}

/*funkcje publiczne klasy MapElem********************************************/

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

template <typename K, typename V>
ostream& operator<<(ostream& out, typename Map<K, V>::MapElem &elem)
{
	out << "(" << elem.key_value.first << "," << elem.key_value.second << ")";
	return out;
}

#endif //MAP_HPP
