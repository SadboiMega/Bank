// Mohammad Zahid
// Hw5 Banking

#include "BSTree.h"
using namespace std;
        //constructor
        BSTree::BSTree() {
            Root = nullptr;
        };
        //deconstructor
        BSTree::~BSTree() {
            empty(Root);
        };
        // Displays tree
        void BSTree::display() const {
            recDisplay(Root);
        }
        // Recursive helper function for Display
        void BSTree::recDisplay(BSTree::Node *pRoot) const {
            if (pRoot != nullptr) {
                recDisplay(pRoot->Left);
                cout << pRoot->pAccount->getAccName() << " " 
                << " Account ID: " <<
                pRoot->pAccount->getAccID() << endl;

                for (int i = 0; i < 10; i++) {
                    cout << "       " << pRoot->pAccount->getFundName(i) << ": $" <<
                 pRoot->pAccount->getFundBal(i) << endl;
                }
            cout << endl;
            recDisplay(pRoot->Right);
            }
        }

        bool BSTree::retrieve(const int &accNumber, Account *&Account) const {
            Account = recRetrieve(Root, accNumber);
            return Account != nullptr;
        }
        // Recursive helper function for retrieve
        Account* BSTree::recRetrieve(BSTree::Node* pRoot, int AccID) const {
            if (pRoot == nullptr) {
                return nullptr;
            }
            else if (pRoot->pAccount->getAccID() == AccID) {
                return pRoot->pAccount;
            }
            else if (AccID < pRoot->pAccount->getAccID()) {
                return recRetrieve(pRoot->Left, AccID);
            }
            else {
                return recRetrieve(pRoot->Right, AccID);
            }
        }

    bool BSTree::insert(Account *pAccount) {
        return recInsert(pAccount, Root);
    }
    // Recursive helper function for insert
    bool BSTree::recInsert(Account *acc, BSTree::Node *&pRoot) {
        if (pRoot == nullptr) {
            pRoot = new Node(acc);
            pRoot->pAccount = acc;
            pRoot->Left = pRoot->Right = nullptr;
            return true;
        } 
        else {
            if (pRoot->pAccount->getAccID() > acc->getAccID()) {
                if (pRoot->Left == nullptr) {
                    Node *Temp = new Node(acc);
                    Temp->pAccount = acc;
                    Temp->Left = Temp->Right = nullptr;
                    pRoot->Left = Temp;
                    return true;
                } else {
                    return recInsert(acc, pRoot->Left);
                }   
            } else if (pRoot->pAccount->getAccID() < acc->getAccID()) {
                if (pRoot->Right == nullptr) {
                    Node *Temp = new Node(acc);
                    Temp->pAccount = acc;
                    Temp->Left = Temp->Right = nullptr;
                    pRoot->Right = Temp;
                    return true;
                } else {
                    return recInsert(acc, pRoot->Right);
                }
            } else {
                cout << endl;
                cout << "Error: Account for " << acc->getAccName() << " was not created." << endl;
                cout << "Account with ID: " << acc->getAccID() << " already exists." << endl;
                return false;
            }
        }
    };
    //clears out tree
    void BSTree::empty(BSTree::Node *Node) {
        if (Node) {
            empty(Node->Left);
            empty(Node->Right);
            delete Node;
        }
    };
    //checks if tree is empty
    bool BSTree::isEmpty() const {
        return Root == nullptr;
    };