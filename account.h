// Mohammad Zahid
// Hw5 Banking

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <queue>
#include <iostream>

using namespace std;

class Account {
    public:
        explicit Account(string &accName, const int &accID);
        //getter function for Account Name
        string getAccName() const;
        // getter function for account Id
        int getAccID() const;
        // deposits funds
        bool deposit(const int &amount, const int &fund);
        // withdraws funds
        bool withdraw(const int &amount, const int &fund);
        //getter function for the Name of the fund
        string getFundName(int i) const;
        //getter function for fund balance
        int getFundBal(int i) const;
        //Transfers between account
        bool transfer(const int &fundFrom, const int &amount, const int &fundTo);
        queue<string> fundsHistArray[10];
        

    private:
        // if the acount does not have enough money this method runs
        string noM(const int &amount, const string &accountName, const int &fund);
        string accountName;
        int accountID;
        int fundsArray[10] = {0};
        // all of the fund names into an array
        string fundsNameArray[10] = 
    {
        "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
         "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund",
          "Value Fund", "Value Stock Index"
    };


};





#endif //ACCOUNT_H