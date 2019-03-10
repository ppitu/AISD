#ifndef TDrzewo_HPP
#define TDrzewo_HPP

#include <iostream>

using namespace std;

template <typename T>
class TDrzewoAVL 
{
    public:

    TDrzewoAVL();
    void insert(T );
    void remove(T );
    void display();

    private:

    struct Node
    {
    T data;
    Node* left;
    Node* right;
    int height;
    };

    Node* root;

    void makeEmpty(Node* );
    Node* insert(T, Node*);
    Node* singleRightRotate(Node* &);
    Node* singleLeftRotate(Node* &);
    Node* doubleLeftRotate(Node* &);
    Node* doubleRightRotate(Node* &);
    Node* findMin(Node* );
    Node* findMax(Node* );
    Node* remove(T, Node*);
    int height(Node* );
    int getBalance(Node* );
    void inorder(Node* );

};

/************************************************************************************************/

template <typename T>
TDrzewoAVL<T>::TDrzewoAVL()
{
    root = nullptr;
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

typename
TDrzewoAVL<T>::Node* TDrzewoAVL<T>::insert(T x, Node* t)
{
    if(t == nullptr)
    {
        t = new Node;
        t->data = x;
        t->height = 0;
        t->left = t->right = nullptr;
    } else if (x < t->data)
    {
        t->left = insert(x, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(x < t->left->data)
                t = singleRightRotate(t);
            else 
                t = doubleRightRotate(t);
        }
    } else if (x > t->data) 
    {
        t->right = insert(x, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(x > t->right->data)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    } else {
        cout << "blad" << endl;
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

TDrzewoAVL<T>::Node* TDrzewoAVL::singleRightRotate(Node* &t)
{
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

TDrzewoAVL<T>::Node* TDrzewoAVL::singleLeftRotate(Node* &t)
{
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(t->right), t->height) + 1;
    return u;
}

TDrzewoAVL<T>::Node* TDrzewoAVL::doubleRightRotate(Node* &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

TDrzewoAVL<T>::Node* TDrzewoAVL::doubleLeftRotate(Node* &t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

TDrzewoAVL<T>::Node* TDrzewoAVL::findMin(Node* t)
{
    if(t == nullptr)
        return nullptr;
    else if(t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

TDrzewoAVL<T>::Node* TDrzewoAVL::findMax(Node* t)
{
    if( t == nullptr)
        return nullptr;
    else if(t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

TDrzewoAVL<T>::Node* TDrzewoAVL::remove(int x, Node* t)
{
    Node* tmp;

    //Element nie znaleziony
    if( t == nullptr)
        return t;
    //Szukanie elementu
    else if(x < t->data)
        t->left = remove(x, t->left);
    else if(x > t->data)
        t->right = remove(x, t->right);
    //Znaleziono element z dwojka dzieci 
    else if(t->left && t->right)
    {
        tmp = findMin(t->right);
        t->data = tmp->data;
        t->right = remove(t->data, t->right);
    } else //Bez dzieci
    {
        tmp = t;
        if(t->left == nullptr)
            t = t->right;
        else if(t->right == nullptr)
            t= t->left;

        delete tmp;
    }

    if(t == nullptr)
        return t;

    t->height = max(height(t->left), height(t->right)) + 1;

    //Jesli drzewo nie zbalansowane
        if(height(t->left) - height(t->right) == -2)
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

int TDrzewoAVL<T>::height(Node* t)
{
    return (t == nullptr ? -1 : t->height);
}

int TDrzewoAVL<T>::getBalance(Node* t)
{
    if(t == nullptr)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void TDrzewoAVL<T>::inorder(Node* t)
{
    if(t == nullptr)
        return;
    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}

void TDrzewoAVL<T>::insert(int x)
{
    root = insert(x, root);
}

void TDrzewoAVL<T>::remove(int x)
{
    root = remove(x, root);
}

void TDrzewoAVL<T>::display()
{
    inorder(root);
    cout << endl;
}

//////////////////////////////////////////////

#endif //TDrzewo_HPP