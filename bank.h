// Mohammad Zahid
// Hw5 Banking


#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <string>
#include <queue>
#include "account.h"
#include "BSTree.h"
using namespace std;
class Bank {
    public:
        Bank();
        ~Bank();
        //prints all of the transactions 
        void printTransactions();
        // goes through all of the transactions
        bool processTransactions();
        //creates the queue using the file
        bool queueTransactions(string &fileName);
       

    private:
        queue<string> tempQ;
        BSTree bankAccounts;
        
};


#endif //BANK_H