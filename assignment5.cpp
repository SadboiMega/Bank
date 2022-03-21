// Mohammad Zahid
// Hw5 Banking

#include "bank.h"
using namespace std;


void readFileTest(bool print) {
    Bank aBank;
    string inputFile;
    inputFile = "BankTransIn.txt";
    aBank.queueTransactions(inputFile);
    if (print) {
        aBank.printTransactions();
    }
    aBank.processTransactions();
}


int main() {
   readFileTest(true);
   //cout << "All Tests Ran" << std::endl; 
   return 0;
}