#ifndef TDrzewoAVL_HPP_
#define TDrzewoAVL_HPP_

#include <iostream>
#include <stack>

using namespace std;

template <class T>
class Iterator;

template <class T>
class TDrzewoAVL
{
	public:

		stack<T> x3;

		TDrzewoAVL();
		TDrzewoAVL(const TDrzewoAVL &);
		TDrzewoAVL& operator= (const TDrzewoAVL &kopiuj)
		{
			if(&kopiuj != this)
			{
				makeEmpty(root);
				root = nullptr;
				root = copyNode(kopiuj.root);
				treesize = kopiuj.treesize;
			}
		}

		~TDrzewoAVL();
		void display();
		std::pair<bool, typename TDrzewoAVL<T>::Iterator> insert(T );
		void remove(T );
		int treeSize();
		int treeSize() const;
		
		struct Node
		{
			T data;
			Node* left;
			Node* right;
			Node* currentNode;
			int height;
		};

		Node* findElement(T ); //zwraca wskaznik do szukanego elementu
		Node* root = nullptr;

		stack<Node*> pomstack;

		class Iterator
		{
			public:

				typename TDrzewoAVL<T>::Node* aktualny = nullptr;
				stack<typename TDrzewoAVL<T>::Node*> rodzic;

				void setAktualny()
				{
					while(aktualny->left != nullptr)
					{
						rodzic.push(aktualny);
						aktualny = aktualny->left;
					}
				}

				Iterator()
				{
					aktualny = nullptr;
				}

				Iterator(typename TDrzewoAVL<T>::Node* node)
				{
					aktualny = node;
				}

				Iterator(typename TDrzewoAVL<T>::Node* node, std::stack<typename TDrzewoAVL<T>::Node*> pomstack)
				{
					aktualny = node;
					rodzic = pomstack;
				}

				std::size_t size() const { return treeSize();}

				bool operator!=( Iterator &it ) 
				{
					return !((*this) == it);
				}

				bool operator!=( Iterator &it ) const
				{
					return !((*this) == it);
				}

				bool operator==( Iterator &it ) 
				{
					return (this->aktualny == it.aktualny);
				}

				bool operator==( Iterator &it ) const
				{
					return (this->aktualny == it.aktualny);
				}

				const T& operator*() const
				{
					return (this->aktualny->data);
				}

				Iterator& operator++()
				{
					if(aktualny->right != nullptr)
					{
						aktualny = aktualny->right;
						rodzic.push(aktualny);

						while(aktualny->left != nullptr)
						{
							aktualny = aktualny->left;
							rodzic.push(aktualny);
						}
					}

					if(!rodzic.empty())
					{
						aktualny = rodzic.top();
						rodzic.pop();
					}else
					{
						aktualny = nullptr;
					}

					return *this;
				}

				Iterator operator++(int)
				{
					Iterator old = *this;
					++(*this);
					return old;
				}

				operator bool() const 
				{
					return true;
				}
		};	

		Iterator begin()
		{
			if(treeSize() == 0)
			{
				Iterator it;
				return it;
			}

			Iterator it(root);
			it.setAktualny();
			return it;
		}

		Iterator begin() const
		{
			if(treeSize() == 0)
			{
				Iterator it;
				return it;
			}

			Iterator it(root);
			it.setAktualny();
			return it;
		}

		Iterator end()
		{
			Iterator it;
			return it;
		}

		Iterator end() const
		{
			Iterator it;
			return it;
		}

		operator bool() { return true; }

		typename TDrzewoAVL<T>::Iterator findEle(T );

	private:

		int treesize = 0;

		Node* singleRightRotate(Node* &);
		Node* singleLeftRotate(Node* &);
		Node* doubleLeftRotate(Node* &);
		Node* doubleRightRotate(Node* &);
		Node* findMin(Node* );
		Node* findMax(Node* );
		int height(Node* );
		int getBalance(Node* );
		Node* insert(T, Node* );	
		void inorder(Node* );
		Node* remove(T, Node* );
		Node* find(T, Node* );
		Node* copyNode(Node* );
		void makeEmpty(Node *);
};


//////////////////////////////////////////////////////////////////

template <typename T>
TDrzewoAVL<T>::TDrzewoAVL()
{
	root = nullptr;
}

template <typename T>
TDrzewoAVL<T>::TDrzewoAVL(const TDrzewoAVL &kopiuj)
{
	root = copyNode(kopiuj.root);
	treesize = kopiuj.treesize;
}

template <typename T>
TDrzewoAVL<T>::~TDrzewoAVL()
{
	makeEmpty(root);
}

template <typename T>
void TDrzewoAVL<T>::display()
{
	inorder(root);
	cout << endl;
}

template <typename T>
std::pair<bool, typename TDrzewoAVL<T>::Iterator> TDrzewoAVL<T>::insert(T x)
{
	treesize++;

	bool pombool = false;

	if(findElement(x) == nullptr)
	{
		root = insert(x, root);
		pombool = true;

		auto z = findElement(x);

		return std::make_pair(pombool, typename TDrzewoAVL<T>::Iterator (z, pomstack));
	}
	treesize--;
	return std::make_pair(pombool, typename TDrzewoAVL<T>::Iterator (root, pomstack));
}

template <typename T>
typename TDrzewoAVL<T>::Iterator TDrzewoAVL<T>::findEle(T x)
{
	auto z = findElement(x);
	if(z != nullptr)
	{
		return typename TDrzewoAVL<T>::Iterator (z, pomstack);
	}
	else 
		return typename TDrzewoAVL<T>::Iterator (z, pomstack);

}

template <typename T>
void TDrzewoAVL<T>::remove(T x)
{
	treesize--;
	root = remove(x, root);
}

template <typename T>
int TDrzewoAVL<T>::treeSize()
{
	//cout << treesize << endl;
	return treesize;
}

template <typename T>
int TDrzewoAVL<T>::treeSize() const
{
	//cout << treesize << endl;
	return treesize;
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::findElement(T x)
{
	auto element = find(x, root);
	return element;
}


template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::singleRightRotate(Node* &t)
{
	Node* u = t->right;
	t->right = u->left;
	u->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	u->height = max(height(t->right), t->height) + 1;
	return u;	
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::singleLeftRotate(Node* &t)
{
	Node* u = t->right;
	t->right = u->left;
	u->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	u->height = max(height(t->right), t->height) + 1;
	return u;
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::doubleLeftRotate(Node* &t)
{
	t->right = singleRightRotate(t->right);
	return singleLeftRotate(t);
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::doubleRightRotate(Node* &t)
{
	t->left = singleLeftRotate(t->left);
	return singleRightRotate(t);
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::findMin(Node* t)
{
	if(t == nullptr)
		return nullptr;
	else if(t->left == nullptr)
		return t;
	else 
		return findMin(t->left);
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::findMax(Node* t)
{
	if(t == nullptr)
		return nullptr;
	else if(t->right == nullptr)
		return t;
	else
		return findMax(t->right);
}

template <typename T>
int TDrzewoAVL<T>::height(Node* t)
{
	if(t == nullptr)
		return 0;
	else
		return height(t->left) - height(t->right);
}

template <typename T>
int TDrzewoAVL<T>::getBalance(Node* t)
{
	if(t == nullptr)
		return 0;
	else
		return height(t->left) - height(t->right);
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::insert(T x, Node* t)
{
	if(t == nullptr)
	{
		t = new Node;
		t->data = x;
		t->height = 0;
		t->left = t->right = nullptr;
	} else if(x < t->data)
	{
		pomstack.push(t->left);
		t->left = insert(x, t->left);
		if(height(t->left) - height(t->right) == 2)
		{
			if(x < t->left->data)
				t = singleRightRotate(t);
			else
				t = doubleRightRotate(t);
		}
	} else if(x > t->data)
	{
		pomstack.push(t->right);
		t->right = insert(x, t->right);
		if(height(t->right) - height(t->left) == 2)
		{
			if(x > t->right->data)
				t = singleLeftRotate(t);
			else
				t = doubleLeftRotate(t);
		}
	} else
	{
		treesize--;
	}

	t->height = max(height(t->left), height(t->right)) + 1;
	return t;
}

template <typename T>
void TDrzewoAVL<T>::inorder(Node* t)
{
	if(t == nullptr)
		return;
	inorder(t->left);
	cout << t->data << " ";
	inorder(t->right);
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::remove(T x, Node* t)
{
	Node* tmp;

	//Element nie znaleziony
	if(t == nullptr)
	{
		treesize++;
		return t;
	} else if(x < t->data) //Szukanie elementu
		t->left = remove(x, t->left);
	else if(x > t->data)
		t->right = remove(x, t->right);
	else if(t->left && t->right) //Znaleziono element z dwojka dzieci
	{
		tmp = findMin(t->right);
		t->data = tmp->data;
		t->right = remove(t->data, t->right);
	}else //Bez dzieci
	{
		tmp = t;
		if(t->left == nullptr)
			t = t->right;
		else if(t->right == nullptr)
			t = t->left;

		delete tmp;
	}

	if(t == nullptr)
		return t;

	t->height = max(height(t->left), height(t->right)) + 1;

	//Jesli drzewno nie zbalansowane
	if(height(t->left) - height(t->right) == -1)
	{
        if(height(t->right->right) - height(t->right->left) == 1)
            return singleLeftRotate(t);
        else
               return doubleLeftRotate(t);
    }
    else if(height(t->right) - height(t->left) == 2)
    {
        if(height(t->left->left) - height(t->left->right) == 1)
            return singleRightRotate(t);
        else
            return doubleRightRotate(t);
    }
	
	return t;
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::find(T x, Node* t)
{
	if(t == nullptr)
		return nullptr;

	if(t->data == x)
		return t;
	else if(x < t->data)
		return find(x, t->left);
	else
		return find(x, t->right);
}

template <typename T>
typename TDrzewoAVL<T>::Node* TDrzewoAVL<T>::copyNode(Node* t)
{
	if(t == nullptr)
		return nullptr;

	Node* copynode = new Node;
	copynode->data= t->data;
	copynode->height = t->height;
	copynode->left = copyNode(t->left);
	copynode->right = copyNode(t->right);
	return copynode;
}

template <typename T>
void TDrzewoAVL<T>::makeEmpty(Node* t)
{
	if(t == nullptr)
		return;
	
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
}

#endif //TDrzewo 
