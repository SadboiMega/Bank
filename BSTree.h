// Mohammad Zahid
// Hw5 Banking

#ifndef BSTREE_H
#define BSTREE_H

#include "account.h"
#include <iostream>

class BSTree {
    public: 
    //constructor
        BSTree();
    //deconstructor
        ~BSTree();
        bool insert(Account *pAccount);
        bool retrieve(const int &rAccountID, Account *&pAccount) const;
        //Displays tree
        void display() const;
        //checks if acount is root is empty
        bool isEmpty() const;      
    private: 
    class Node {
        public:
        Node(Account *inAccount) {
            pAccount = inAccount;
            Right = nullptr;
            Left = nullptr;
        }
        ~Node() {
            delete pAccount;
        }

        Account *pAccount;
        Node *Right;
        Node *Left;
    };
    Node *Root;
    // Recursive helper function for retrieve
    Account* recRetrieve(Node *pRoot, int AccntID) const;
    // Recursive helper function for insert
    bool recInsert(Account *pAccID, Node *&pRoot);
    // Recursive helper function for Display
    void recDisplay(Node *pRoot) const;
    void empty(Node *pNode);
};

#endif //BSTREE_H