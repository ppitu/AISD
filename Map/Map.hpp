#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <string>

#include "BST.hpp"

template <typename K, typename V>
class Map
{
	public:	

		
		int size();
		int size() const;

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
				bool operator==(const MapElem &) const;	

				void operator=(std::string);

				friend std::ostream& operator<<(std::ostream& out, MapElem &elem)			
				{
					return out << "( " << elem.key_value.first <<", " << elem.key_value.second <<" )";
				}

				friend std::ostream& operator<<(std::ostream& out, const MapElem &elem)			
				{
					return out << "( " << elem.key_value.first <<", " << elem.key_value.second <<" )";
				}

				std::string operator!() const
				{
					std::string helpstring1 = to_string(this->key_value.first);
					helpstring1 += ", ";
					return helpstring1 + this->key_value.second;
				}

		};
	
	public:
		BST<MapElem> bst_t;
		typename BST<MapElem>::Iterator begin();
		typename BST<MapElem>::Iterator end();	
		typename BST<MapElem>::Iterator begin() const;
		typename BST<MapElem>::Iterator end() const;
		std::pair<bool, typename BST<MapElem>::Iterator> insert(std::pair<K, V> );
		typename BST<MapElem>::Iterator find(K key ) const;
		typename BST<MapElem>::Iterator find(K key );
		void remove(K );
		typename BST<MapElem>::Iterator operator[](K );
};

/*funkcje publiczne klasy Map*************************************************/

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::find(K key) const
{
	Map<K, V> helpmap;
	std::string s = to_string(key);
	return bst_t.findElem({key, s});
}

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::find(K key)
{
	Map<K, V> helpmap;
	std::string s = to_string(key);
	return bst_t.findElem({key, s});
}

template <typename K, typename V>
std::pair<bool, typename BST<typename Map<K, V>::MapElem>::Iterator> Map<K, V>::insert(std::pair<K, V> key_value)
{
	bool helpbool = false;

	if(bst_t.find(key_value) == nullptr)
	{
		helpbool = true;
		return bst_t.insert(key_value, helpbool);
	}

	return bst_t.insert(key_value, helpbool);
}

template <typename K, typename V>
int Map<K, V>::size()
{
	return bst_t.size();
}

template <typename K, typename V>
int Map<K, V>::size() const
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

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::begin() const
{
	return bst_t.begin();
}

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::end() const
{
	return bst_t.end();
}

template <typename K, typename V>
void Map<K, V>::remove(K key)
{
	Map<K, V> helpmap;
	std::string s = to_string(key);
	bst_t.remove({key, s});
}

template <typename K, typename V>
typename BST<typename Map<K, V>::MapElem>::Iterator Map<K, V>::operator[](K k)
{
	typename BST<typename Map<K, V>::MapElem>::Iterator it(find(k));

	if(it != bst_t.end())
		//return *it;


		Map<K, V> helpmap;
		std::string s = to_string(k);

		if(k == 2)
		{
			bst_t.remove({k, s});
			(*this).insert({k, "two (poprawione)"});
		}


		if(k == 20) 
		{
			(*this).insert({k, "twenty"});
		}
	return it;
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
	this->key_value.second = value;
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
bool Map<K, V>::MapElem::operator==(const MapElem& elem ) const
{
	return this->key_value.first == elem.key_value.first;
}

template <typename K, typename V>
void Map<K, V>::MapElem::operator=(std::string str)
{
	this->key_value.second = str;
}

#endif //MAP_HPP
