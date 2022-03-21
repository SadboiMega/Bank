// Mohammad Zahid
// Hw5 Banking

#include "bank.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstring>
#include "BSTree.h"

using namespace std;
Bank::Bank() = default;
Bank::~Bank() { 
};
//creates the queue using the file
bool Bank::queueTransactions(string &fileName) {
    ifstream myfile (fileName);
    string line;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            tempQ.push(line);
        }
        
    }
    return true;
}
// goes through all of the transactions
bool Bank::processTransactions() {
    string transactionLine;
    
    while (!tempQ.empty()) {
        transactionLine = tempQ.front(); // take in first transaction
        char char_line_array[transactionLine.length() + 1];
        strcpy(char_line_array, transactionLine.c_str());
        switch (char_line_array[0]) {
            case 'O': {
                //get the name of the account
                unsigned long int i{2};
                string name = "";
                while (!isdigit(transactionLine.at(i))) {
                    name.push_back(transactionLine.at(i));
                    i++;
                }
                //get the account id
                string id = "";
                while ((i < transactionLine.length()) && isdigit(transactionLine.at(i))) {
                    id.push_back(transactionLine.at(i));
                    i++;
                }
                string first = "";
                unsigned long int k{0};
                while (isalpha(name.at(k))) {
                    first.push_back(name.at(k));
                    k++;
                }
                k++;
                string last = "";
                while ((k < name.length()) && isalpha(name.at(k))) {
                    last.push_back(name.at(k));
                    k++;
                }
                string space = " ";
                name = last + space + first;
                
                
                auto *newAcc = new Account(name, stoi(id));
                if (!bankAccounts.insert(newAcc)) {
                    delete newAcc;
                }
                
                break;
            }
            
            case 'D': {
                int i{2};
                string almostID = "";
                while (isdigit(transactionLine.at(i))) {
                    almostID.push_back(transactionLine.at(i));
                    i++;
                }
                

                string id = "";
                string fundID = "";
                for (unsigned long int j{0}; j < almostID.length(); j++) {
                    if (j < almostID.length() - 1) {
                        id.push_back(almostID.at(j)); 
                    }
                    if (j == almostID.length() - 1) {
                        fundID.push_back(almostID.at(j));
                    }
                }

                i++;
                string amount = "";
                while (isdigit(transactionLine.at(i))) {
                    amount.push_back(transactionLine.at(i));
                    i++;
                }

                Account *pAcc;
                bankAccounts.retrieve(stoi(id), pAcc);
                pAcc->deposit(stoi(amount), stoi(fundID));
                pAcc->fundsHistArray[stoi(fundID)].push(transactionLine);
                break;
            }
            
            case 'W': {
                int i{2};
                string almostID = "";
                while (isdigit(transactionLine.at(i))) {
                    almostID.push_back(transactionLine.at(i));
                    i++;
                }
                

                string id = "";
                string fundID = "";
                for (unsigned long int j{0}; j < almostID.length(); j++) {
                    if (j < almostID.length() - 1) {
                        id.push_back(almostID.at(j)); 
                    }
                    if (j == almostID.length() - 1) {
                        fundID.push_back(almostID.at(j));
                    }
                }

                i++;
                string amount = "";
                while (isdigit(transactionLine.at(i))) {
                    amount.push_back(transactionLine.at(i));
                    i++;
                }

                Account *pAcc;
                bankAccounts.retrieve(stoi(id), pAcc);
                bool success = pAcc->withdraw(stoi(amount), stoi(fundID));
                if (success == false) {
                    string fail = "W " + id + fundID + " " + amount + " (failed)";
                    transactionLine.append(fail);
                    pAcc->fundsHistArray[stoi(fundID)].push(transactionLine);
                } else {
                    pAcc->fundsHistArray[stoi(fundID)].push(transactionLine);
                }
                
                break;
            }
            
            case 'T': {
                string accFrom = "";
                for (int i{2}; i < 6; i++) {
                    accFrom.push_back(transactionLine.at(i));
                }

                string accFromFund = "";
                accFromFund.push_back(transactionLine.at(5));

                int i{8};
                string amount = "";
                while (isdigit(transactionLine.at(i))) {
                    amount.push_back(transactionLine.at(i));
                    i++;
                }
                i++;
                int x = i;
                string accTo = "";
                while ((i < (x+4)) && isdigit(transactionLine.at(i))) {
                    accTo.push_back(transactionLine.at(i));
                    i++;
                }
                string accToFund = "";
                accToFund.push_back(transactionLine.at(i));

                Account *from;
                Account *to;
                bankAccounts.retrieve(stoi(accFrom), from);
                bankAccounts.retrieve(stoi(accTo), to);
                if (to == nullptr) {
                    cout << "Transfer stopped. Account: "<< accTo << " does not exist" << endl;
                }
                else if (from == nullptr) {
                    cout << "Transfer stopped. Account: "<< accFrom << " does not exist" << endl;
            
                    
                } else {
                    int iamount = stoi(amount);
                    int iaccFromFund = stoi(accFromFund);
                    int iaccToFund = stoi(accToFund);
                    bool withdrawSuccess;
                    if (from->getFundBal(iaccFromFund) >= iamount) {
                        withdrawSuccess = from->withdraw(iamount, iaccFromFund);
                    } else {
                        withdrawSuccess = false;
                    }
                    
                    if (withdrawSuccess == false) {
                        string fail = "T " + accFrom + accFromFund + " " + amount + " " + accTo + accToFund + " (failed)";
                        transactionLine.append(fail);
                        from->fundsHistArray[iaccFromFund].push(transactionLine);
                    } else {
                        from->fundsHistArray[iaccFromFund].push(transactionLine);
                    }
                    
                    if (withdrawSuccess) {
                        to->deposit(iamount, iaccToFund);
                    }
                    from->fundsHistArray[iaccToFund].push(transactionLine);
                }
                
                break;
            }
            
            case 'H': {
                queue<string> temp;
                int i{2};
                string acc = "";
                while (isdigit(transactionLine.at(i))) {
                    acc.push_back(transactionLine.at(i));
                    i++;
                }
                int accid = stoi(acc);
                if (accid > 9999) {
                    int fund = (accid % 10);
                    accid -= fund;
                    accid = accid / 10;
                    Account *pAcc;
                    bankAccounts.retrieve(accid, pAcc);
                    if (pAcc != nullptr) {
                        cout << endl;
                        cout << "Transaction History for " << pAcc->getAccName() << " "
                        << pAcc->getFundName(fund) << ": $" << pAcc->getFundBal(fund) << endl;
                        while (!pAcc->fundsHistArray[fund].empty()) {
                            cout << pAcc->fundsHistArray[fund].front() << endl;
                            temp.push(pAcc->fundsHistArray[fund].front());
                            pAcc->fundsHistArray[fund].pop();
                        }

                        while (!temp.empty()) {
                            pAcc->fundsHistArray[fund].push(temp.front());
                            temp.pop();
                        }
                    }
                }
                else {
                    Account *pAcc;
                    bankAccounts.retrieve(accid, pAcc);
                    if (pAcc != nullptr) {
                        cout << endl;
                        cout << "Transaction History for " << pAcc->getAccName() << " by fund." << endl;
                        for (int i{0}; i < 10; i++) {
                            cout << pAcc->getFundName(i) << ": $" << pAcc->getFundBal(i) << endl;
                            while (!pAcc->fundsHistArray[i].empty()) {
                                cout << pAcc->fundsHistArray[i].front() << endl;
                                temp.push(pAcc->fundsHistArray[i].front());
                                pAcc->fundsHistArray[i].pop();
                            }

                            while (!temp.empty()) {
                                pAcc->fundsHistArray[i].push(temp.front());
                                temp.pop();
                            }
                        }
                    }
                }
                break;
            }
            
            default: {
                break;
            }
            
        }

        tempQ.pop(); //remove transaction
        
    }
    
    return true;
}
//prints all of the transactions
void Bank::printTransactions() {
    queue<string> temp;
    while (!tempQ.empty()) {
        cout << tempQ.front() << endl;
        temp.push(tempQ.front());
        tempQ.pop();
    }
    while (!temp.empty()) {
        tempQ.push(temp.front());
        temp.pop();
    }
    
}