// Mohammad Zahid
// Hw5 Banking

#include "account.h"
#include <queue>
#include <iostream>
#include <string>
using namespace std;
Account::Account(string &accName, const int &accID) {
    accountName = accName;
    accountID = accID;
}
//getter function for the Name of the fund
string Account::getFundName(int i) const {
    return fundsNameArray[i];
}
//getter function for fund balance
int Account::getFundBal(int i) const {
    return fundsArray[i];
}
//getter function for Account Name
string Account::getAccName() const {
    return accountName;
}
// if the acount does not have enough money this method runs
string Account::noM(const int &amount, const string &accountName, const int &fund) {
    string output = "ERROR: Not enough funds to withdraw ";
    output.append(to_string(amount));
    output.append(" from ");
    output.append(accountName);
    output.append(" ");
    output.append(this->fundsNameArray[fund]);
    return output;
}
// getter function for account Id
int Account::getAccID() const {
    return accountID;
}
// deposits funds
bool Account::deposit(const int &amount, const int &fund) {
    if (fund < 0 || fund > 9) return false;
    fundsArray[fund] += amount;
    return true;
}
//transfers between accounts
bool Account::transfer(const int &fundFrom, const int &amount, const int &fundTo)
{
    //check to make sure that the accounts are within bounds
    if (fundFrom < 0 || fundFrom > 9)
    {
        string  problem = "Tranfer terminated. Account: ";
        problem.append(to_string(fundFrom));
        problem.append(" doesn't exist.");
        cout << problem << endl;
        return false;
    };

    if (fundTo < 0 || fundTo > 9)
    {
        string  problem = "Tranfer terminated. Account: ";
        problem.append(to_string(fundTo));
        problem.append(" doesn't exist.");
        cout << problem << endl;
        return false;
    };

    //check to make sure that funds aren't transfered to itself
    if (fundFrom == fundTo)
    {
        string  problem = "Tranfer terminated. Funds from Account:";
        problem.append(to_string(fundFrom));
        problem.append(" can't be transferred to same Account");
        cout << problem << endl;
        return false;
    };
    
    //check to see account is able to be withdrawn from
    if (withdraw(amount, fundFrom) == true)
    {
        deposit(amount, fundFrom);
        return true;
    };
    
    return false;
};
// withdraws funds
bool Account::withdraw(const int &a, const int &fund) {
    if (fund < 0 || fund > 9) return false;
    int amount = a;
    if ((fundsArray[fund] - amount) < 0) {
        switch (fund) {
            case 0: {
                if (((fundsArray[0] + fundsArray[1]) - amount) < 0) {
                    cout << noM(amount, accountName, fund) << endl;
                    return false;
                }
                else {
                    amount -= fundsArray[0];
                    fundsArray[0] = 0;
                    fundsArray[1] -= amount;
                    return true;
                }
                break;
            }

            case 1: {
                if (((fundsArray[0] + fundsArray[1]) - amount) < 0) {
                    cout << noM(amount, accountName, fund) << endl;
                    return false;
                } 
                else {
                    amount -= fundsArray[1];
                    fundsArray[1] = 0;
                    fundsArray[0] -= amount;
                    return true;
                }
                break;
            }
            
            case 2: {
                if (((fundsArray[2] + fundsArray[3]) - amount) < 0) {
                    cout << noM(amount, accountName, fund) << endl;
                    return false;
                }
                else {
                    amount -= fundsArray[2];
                    fundsArray[2] = 0;
                    fundsArray[3] -= amount;
                    return true;
                }
                break;
            }

            case 3: {
                if (((fundsArray[2] + fundsArray[3]) - amount) < 0) {
                    cout << noM(amount, accountName, fund) << endl;
                    return false;
                }
                else {
                    amount -= fundsArray[3];
                    fundsArray[3] = 0;
                    fundsArray[2] -= amount;
                    return true;
                }
                break;
            }
            default: {
                    cout << noM(amount, accountName, fund) << endl;
                return false;
                break;
            }
        }
    } else {
        fundsArray[fund] -= amount;
        return true;
    }
        
}
