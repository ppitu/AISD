#ifndef BST_HPP_
#define BST_HPP_

#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class BST
{
	public:
		BST();
		BST(const BST &);
		BST& operator=(const BST& );
		std::pair<bool, typename BST<T>::Iterator> insert(T, bool );
		void remove(T );
		void display();
		void search(T );
		int size();
		int size() const;

		class Iterator
		{
			public:
				typename BST<T>::Node* current = nullptr;
				stack<typename BST<T>::Node* > parent;

				Iterator();
				Iterator(typename BST<T>::Node* );
				Iterator(typename BST<T>::Node*, stack<typename BST<T>::Node* > );
				
				void setCurrent();
				
				T& operator*();
				Iterator& operator++();
				Iterator operator++(int);
				bool operator!=(Iterator& );
				bool operator==(Iterator& );

				T& operator*() const;
				bool operator!=(Iterator& ) const;
				bool operator==(Iterator& ) const;
		};

		Iterator begin();
		Iterator end();

		Iterator begin() const;
		Iterator end() const;

	private:

		struct Node
		{
			T data;
			Node* left;
			Node* right;
		};

		Node* root;
		stack<typename BST<T>::Node*> helpstack;
	
	public:
		Node* find(T );
		typename BST<T>::Iterator findElem(T );

	private:

		void inorder(Node* );
		Node* makeEmpty(Node* );
		Node* insert(T, Node*);
		Node* findMin(Node* );
		Node* findMax(Node* );
		Node* remove(T, Node* );
		Node* find(T, Node* );
		Node* copyNode(Node *);

		int treesize = 0;
};

/*Funkcje publiczne*********************************************************/

template <typename T>
BST<T>::BST()
{
	root = nullptr;
}

template <typename T>
BST<T>::BST(const BST &copy)
{
	root = copyNode(copy.root);
	treesize = copy.treesize;
}

template <typename T>
typename BST<T>::BST& BST<T>::operator=(const BST<T> &copy)
{
	if(&copy != this)
	{		
		makeEmpty(root);
		root = nullptr;	
		root = copyNode(copy.root);		
		treesize = copy.treesize;
		
	}		
}

template <typename T>
std::pair<bool, typename BST<T>::Iterator> BST<T>::insert(T x, bool helpbool)
{
	if(helpbool)
	{
		treesize++;
		root = insert(x, root);

		return std::make_pair(helpbool, typename BST<T>::Iterator (find(x, root), helpstack));
	}

	return std::make_pair(helpbool, typename BST<T>::Iterator (root, helpstack));
}

template <typename T>
void BST<T>::remove(T x)
{
	treesize--;
	root = remove(x, root);
}

template <typename T>
void BST<T>::display()
{
	inorder(root);
	cout << endl;
}

template <typename T>
void BST<T>::search(T x)
{
	auto z = find(x, root);

	if(z == nullptr)
		cout << "Nie znaleziono elementu" << endl;
	else
		cout << "Znaleziono element" << endl;
}

template <typename T>
int BST<T>::size()
{
	return treesize;
}

template <typename T>
int BST<T>::size() const
{
	return treesize;
}

template <typename T>
typename BST<T>::Iterator BST<T>::begin()
{
	if(size() == 0)
	{
		Iterator it;
		return it;
	}

	Iterator it(root);
	it.setCurrent();
	return it;
}

template <typename T>
typename BST<T>::Iterator BST<T>::end()
{
	Iterator it;
	return it;
}

template <typename T>
typename BST<T>::Iterator BST<T>::begin() const
{
	if(size() == 0)
	{
		Iterator it;
		return it;
	}

	Iterator it(root);
	it.setCurrent();
	return it;
}

template <typename T>
typename BST<T>::Iterator BST<T>::end() const
{
	Iterator it;
	return it;
}

template <typename T>
typename BST<T>::Node* BST<T>::find(T x)
{
	return find(x, root);
}

template <typename T>
typename BST<T>::Iterator BST<T>::findElem(T x)
{
	auto z = find(x);

	if(z == nullptr)
		return typename BST<T>::Iterator (z, helpstack);

	return typename BST<T>::Iterator (z, helpstack);
}

/*Funkcje klasy iterator publiczne*********************************************/

template <typename T>
BST<T>::Iterator::Iterator()
{
	current = nullptr;
}

template <typename T>
BST<T>::Iterator::Iterator(typename BST<T>::Node* node)
{
	current = node;
}

template <typename T>
BST<T>::Iterator::Iterator(typename BST<T>::Node* node, stack<typename BST<T>::Node*> helpstack)
{
	current = node;
	parent = helpstack;
}

template <typename T>
void BST<T>::Iterator::setCurrent()
{
	while(current->left != nullptr)
	{
		parent.push(current);
		current = current->left;
	}
}

template <typename T>
T& BST<T>::Iterator::operator*()
{
	return (this->current->data);
}

template <typename T>
typename BST<T>::Iterator& BST<T>::Iterator::operator++()
{
	if(current->right != nullptr)
	{
		current = current->right;
		parent.push(current);

		while(current->left != nullptr)
		{
			current = current->left;
			parent.push(current);
		}
	}

	if(!parent.empty())
	{
		current = parent.top();
		parent.pop();
	} else
	{
		current = nullptr;
	}

	return *this;
}

template <typename T>
typename BST<T>::Iterator BST<T>::Iterator::operator++(int)
{
	Iterator old = *this;
	++(*this);
	return old;
}

template <typename T>
bool BST<T>::Iterator::operator!=(Iterator &it )
{
	return !((*this) == it);
}

template <typename T>
bool BST<T>::Iterator::operator==(Iterator &it)
{
	return (this->current == it.current);
}

template <typename T>
T& BST<T>::Iterator::operator*() const
{
	return (this->current->data);
}

template <typename T>
bool BST<T>::Iterator::operator!=(Iterator &it ) const
{
	return !((*this) == it);
}

template <typename T>
bool BST<T>::Iterator::operator==(Iterator &it) const
{
	return (this->current == it.current);
}

/*Funkcje prywatne BST*********************************************************/

template <typename T>
void BST<T>::inorder(Node* t)
{
	if(t == nullptr)
		return;

	inorder(t->left);
	cout << t->data << " ";
	inorder(t->right);
}

template <typename T>
typename BST<T>::Node* BST<T>::makeEmpty(Node* t)
{
	if(t == nullptr)
		return nullptr;

	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;

	return nullptr;
}

template <typename T>
typename BST<T>::Node* BST<T>::insert(T x, Node* t)
{
	if(t == nullptr)
	{
		t = new Node;
		t->data = x;
		t->left = t->right = nullptr;
	} else if(x < t->data)
	{
		helpstack.push(t->left);
		t->left = insert(x, t->left);
	}
	else if(x > t->data)
	{
		helpstack.push(t->right);
		t->right = insert(x, t->right);
	}
	else
	{
		//helpstack.push(t->data);
		if(x < t->data)
			t->left = insert(x, t->left);
		else
			t->right = insert(x, t->right);
	}
	
	return t;
}

template <typename T>
typename BST<T>::Node* BST<T>::findMin(Node* t)
{
	if(t == nullptr)
		return nullptr;
	else if(t->left == nullptr)
		return t;
	else
		return findMin(t->left);
}

template <typename T>
typename BST<T>::Node* BST<T>::findMax(Node* t)
{
	if(t == nullptr)
		return nullptr;
	else if(t->right == nullptr)
		return t;
	else
		return findMax(t->right);
}

template <typename T>
typename BST<T>::Node* BST<T>::remove(T x, Node* t)
{
	Node* tmp;

	if(t == nullptr)
	{
		treesize++;
		return nullptr;
	}

	else if(x < t->data)
		t->left = remove(x, t->left);
	else if(x > t->data)
		t->right = remove(x, t->right);
	else if(t->left && t->right)
	{
		tmp = findMin(t->right);
		t->data = tmp->data;
		t->right = remove(t->data, t->right);
	} else
	{
		tmp = t;
		if(t->left == nullptr)
			t = t->right;
		else if(t->right == nullptr)
			t = t->left;
		delete tmp;
	}

	return t;
}

template <typename T>
typename BST<T>::Node* BST<T>::find(T x, Node* t)
{
	if(t == nullptr)
		return nullptr;
	else if(x < t->data)
		return find(x, t->left);
	else if(x > t->data)
		return find(x, t->right);
	else
		return t;
}


template <typename T>
typename BST<T>::Node* BST<T>::copyNode(Node* t)
{
		if(t == nullptr)
			return nullptr;

		Node* copynode = new Node;
		copynode->data= t->data;
		copynode->left = copyNode(t->left);
		copynode->right = copyNode(t->right);
		return copynode;
}

#endif //BST_HPP_
