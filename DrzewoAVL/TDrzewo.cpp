#include <iostream>

#include "TDrzewo.h"

using namespace std;

TDrzewoAVL::TDrzewoAVL()
{
    root = nullptr;
}

void TDrzewoAVL::makeEmpty(Node* t)
{
    if(t == nullptr)
        return;
    
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

Node* TDrzewoAVL::insert(int x, Node* t)
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
                t = singaleRightRotate(t);
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

Node* TDrzewoAVL::singleRightRotate(Node* &t)
{
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

Node* TDrzewoAVL::singleLeftRotate(Node* &t)
{
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(t->right), t->height) + 1;
    return u;
}

Node* TDrzewoAVL::doubleRightRotate(Node* &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

Node* TDrzewoAVL::doubleLeftRotate(Node* &t)
{
    t->right = singleRightRotate(t->right);
    return singleleftRotate(t);
}

Node* TDrzewoAVL::findMin(Node* t)
{
    if(t == nullptr)
        return nullptr;
    else if(t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

Node* TDrzewoAVL::findMax(Node* t)
{
    if( t == nullptr)
        return nullptr;
    else if(t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

Node* TDrzewoAVL::remove(int x, Node* t)
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
        temp = findMin(t->right);
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
        if(height(t->left) - height(t->right) == 2)
        {
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            else
                return doubleLeftRotate(t);
        }
        else if(height(t->right) - height(t->left) == 2)
        {
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            else
                return doubleRightRotate(t);
        }
        return t;

}

int TDrzewoAVL::height(Node* t)
{
    return (t == nullptr ? -1 : t->height);
}

int TDrzewoAVL::getBalance(Node* t)
{
    if(t == nullptr)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void TDrzewoAVL::inorder(Node* t)
{
    if(t == nullptr)
        return;
    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}

void TDrzewoAVL::insert(int x)
{
    root = insert(x, root);
}

void TDrzewoAVL::remove(int x)
{
    root = remove(x, root);
}

void TDrzewoAVL::display()
{
    inorder(root);
    cout << endl;
}