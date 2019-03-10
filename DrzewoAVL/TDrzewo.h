#ifndef TDrzewo_H_
#define TDrzewo_H_

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

#endif //TDrzewo_H_