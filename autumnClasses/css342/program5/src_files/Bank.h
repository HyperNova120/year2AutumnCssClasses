
#ifndef _SRC_FILES_BANK_H_
#define _SRC_FILES_BANK_H_

#include <string>
#include <queue>
#include <list>
#include <vector>
#include <map>

#include "Transaction.h"
#include "Account.h"
#include "Fund.h"
#include "BST.h"

using namespace std;
class Bank
{
public:
    Bank();
    void ReadTransactions(string file_name);
    void ExecuteTranactions();

private:
    vector<string> split(string s, char delim);

    bool CreateAccount(Transaction &transaction);
    bool DepositFunds(Transaction &transaction);
    bool WithdrawFunds(Transaction &transaction);
    bool TransferFunds(Transaction &transaction);

    bool DoesAccountExist(int uid) const;
    Account &GetAccount(int uid) const;
    bool TransferFundsBetweenElligibleFundsToCover(Transaction &transaction);

    void PrintAccountTransactionHistory(Transaction &transaction);
    void PrintFundTransactionHistoryForAccount(Transaction &transaction);

    void AddToTransactionHistory(Transaction &transaction);

    bool isValidTransaction(Transaction &transaction);

    queue<Transaction> transactions_ = queue<Transaction>();
    BST<Account> accounts_ = BST<Account>();
    map<int, list<Transaction>> account_transaction_history_ = map<int, list<Transaction>>(); // key: account id
    map<int, list<Transaction>> fund_transaction_history_ = map<int, list<Transaction>>();    // key fund id
    
};

#endif //_SRC_FILES_BANK_H_