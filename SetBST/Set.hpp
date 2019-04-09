#ifndef SET_HPP_
#define SET_HPP_

#include <iostream>

#include "BST.hpp"

using namespace std;

template <typename T>
class Set
{
	public:
		BST<T> bst_t;

		std::pair<bool, typename BST<T>::Iterator> insert(T );
		void display();
		int size();
		int size() const;
		void remove(T );
		typename BST<T>::Iterator find(T );

		typename BST<T>::Iterator begin();
		typename BST<T>::Iterator end();
		typename BST<T>::Iterator begin() const;
		typename BST<T>::Iterator end() const;
};

template <typename T>
std::pair<bool, typename BST<T>::Iterator> Set<T>::insert(T x)
{
	bool helpbool = false;

	if(bst_t.find(x) == nullptr)
	{
		helpbool = true;
		return bst_t.insert(x, helpbool);
	}

	return bst_t.insert(x, helpbool);
}

template <typename T>
void Set<T>::display()
{
	bst_t.display();
}

template <typename T>
int Set<T>::size()
{
	return bst_t.size();
}

template <typename T>
int Set<T>::size() const
{
	return bst_t.size();
}

template <typename T>
void Set<T>::remove(T x)
{
	bst_t.remove(x);
}

template <typename T>
typename BST<T>::Iterator Set<T>::find(T x)
{
	return bst_t.findElem(x);
}

template <typename T>
typename BST<T>::Iterator Set<T>::begin()
{
	return bst_t.begin();
}

template <typename T>
typename BST<T>::Iterator Set<T>::end()
{
	return bst_t.end();
}

template <typename T>
typename BST<T>::Iterator Set<T>::begin() const
{
	return bst_t.begin();
}

template <typename T>
typename BST<T>::Iterator Set<T>::end() const
{
	return bst_t.end();
}
#endif //SET_HPP_
