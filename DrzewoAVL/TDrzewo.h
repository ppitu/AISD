#ifndef TDrzewo_H_
#define TDrzewo_H_

class TDrzewoAVL 
{
    public:

    TDrzewoAVL();
    void insert(int );
    void remove(int );
    void display();

    private:
    
    struct Node
    {
        int data;
        Node* left;
        Node* right;
        int height;
    };

    Node* root;

    void makeEmpty(Node* );
    Node* insert(int, Node*);
    Node* singaleRightRotate(Node* &);
    Node* singleLeftRotate(Node* &);
    Node* doubleLeftRotate(Node* &);
    Node* doubleRightRotate(Node* &);
    Node* findMin(Node* );
    Node* findMax(Node* );
    Node* remove(int, Node*);
    int height(Node* );
    int getBalance(Node* );
    void inorder(Node* );

};

#endif //TDrzewo_H_