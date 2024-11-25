#ifndef _SRC_BANK_H_
#define _SRC_BANK_H_

#include "BST.h"
#include "Account.h"
#include "Funds.h"

#include <list>
#include <iostream>
#include <vector>

using namespace std;

class Bank
{
public:
    Bank();

    void RunTransaction(vector<string> transaction_order);

    void CreateAccount(int uid, string first_name, string last_name);
    void DeleteAccount(int uid, string first_name, string last_name);

    bool DepositFunds(int uid, int fund_id, long amount);
    bool WithdrawFunds(int uid, int fund_id, long amount);

    bool TransferFunds(int uid_from, int fund_id_from, int uid_to, int fund_id_to, long amount);

    vector<string> GetAccountTransactionHistory(int uid);
    vector<string> GetFundTransactionHistory(int uid, int fund_id);

    friend ostream &operator<<(ostream &os, const Bank &obj);

private:
    BST<Account> accounts_;
    bool DoesAccountExist(int uid);
    Account &GetAccount(int uid);
    bool TransferFundsBetweenMoneyMarketToCover(Account *account, int amount, int fund_id);
};

Bank::Bank()
{
    accounts_ = BST<Account>();
}

inline void Bank::RunTransaction(vector<string> transaction_order)
{
    if (transaction_order[0] == "O")
    {
        if (transaction_order.size() != 4)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        CreateAccount(stoi(transaction_order[1]), transaction_order[2], transaction_order[3]);
    }
    else if (transaction_order[0] == "D")
    {
        if (transaction_order.size() != 4)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        DepositFunds(stoi(transaction_order[1]), stoi(transaction_order[2]), stoi(transaction_order[3]));
    }
    else if (transaction_order[0] == "W")
    {
        if (transaction_order.size() != 4)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        WithdrawFunds(stoi(transaction_order[1]), stoi(transaction_order[2]), stoi(transaction_order[3]));
    }
    else if (transaction_order[0] == "T")
    {
        if (transaction_order.size() != 6)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        TransferFunds(stoi(transaction_order[1]), stoi(transaction_order[2]), stoi(transaction_order[3]), stoi(transaction_order[4]), stoi(transaction_order[5]));
    }
    else if (transaction_order[0] == "A")
    {
        if (transaction_order.size() != 2)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        // TODO implement
        cerr << "NEED TO IMPLEMENT THIS" << endl;
    }
    else if (transaction_order[0] == "F")
    {
        if (transaction_order.size() != 3)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        // TODO implement
        cerr << "NEED TO IMPLEMENT THIS" << endl;
    }
    else
    {
        cerr << "INVALID TRANSACTION COMMAND" << endl;
    }
}

void Bank::CreateAccount(int uid, string first_name, string last_name)
{
    if (DoesAccountExist(uid))
    {
        cerr << "Account With ID: " << uid << " Already Exists" << endl;
        return;
    }
    map<int, long> funds = map<int, long>();

    for (int fund_id : GetAllFundIDs())
    {
        funds[fund_id] = 0;
    }
    Account new_account(first_name, last_name, uid, funds);

    accounts_.Insert(new_account);
}

bool Bank::DepositFunds(int uid, int fund_id, long amount)
{
    if (!DoesAccountExist(uid))
    {
        cerr << "Account With ID: " << uid << " Does Not Exists" << endl;
        return false;
    }
    else if (!DoesFundExist(fund_id))
    {
        cerr << "Fund With ID: " << fund_id << " Does Not Exists" << endl;
    }
    Account *account = &GetAccount(uid);
    account->DepositAssets(fund_id, amount);
    return true;
}

bool Bank::WithdrawFunds(int uid, int fund_id, long amount)
{
    if (!DoesAccountExist(uid))
    {
        cerr << "Account With ID: " << uid << " Does Not Exists" << endl;
        return false;
    }
    else if (!DoesFundExist(fund_id))
    {
        cerr << "Fund With ID: " << fund_id << " Does Not Exists" << endl;
    }
    Account *account = &GetAccount(uid);
    if (account->GetFundAssets(fund_id) < amount)
    {
        // withdraw past account funds
        if (!IsMoneyMarketFund(fund_id))
        {
            cerr << "Account With ID: " << uid << " Has Insufficient Funds Within Fund With ID: " << fund_id << endl;
            return false;
        }
        if (!TransferFundsBetweenMoneyMarketToCover(account, amount, fund_id))
        {
            cerr << "Account With ID: " << uid << " Has Insufficient Funds Within Money Market Funds To Cover" << endl;
            return false;
        }
    }

    account->WithdrawAssets(fund_id, amount);

    return true;
}

bool Bank::TransferFunds(int uid_from, int fund_id_from, int uid_to, int fund_id_to, long amount)
{
    if (!DoesAccountExist(uid_from) || !DoesAccountExist(uid_to))
    {
        cerr << "Account With ID: " << ((!DoesAccountExist(uid_from)) ? uid_from : uid_to) << " Does Not Exist" << endl;
        return false;
    }
    if (!DoesFundExist(fund_id_from) || !DoesFundExist(fund_id_to))
    {
        cerr << "Fund With ID: " << ((!DoesFundExist(fund_id_from)) ? fund_id_from : fund_id_to) << " Does Not Exist" << endl;
        return false;
    }

    Account *account_from = &GetAccount(uid_from);
    Account *account_to = &GetAccount(uid_to);
    if (account_from->GetFundAssets(fund_id_from) < amount)
    {
        if (!IsMoneyMarketFund(fund_id_from))
        {
            cerr << "Account With ID: " << fund_id_from << " Has Insufficient Funds Within Fund With ID: " << fund_id_from << endl;
            return false;
        }
        else if (!TransferFundsBetweenMoneyMarketToCover(account_from, amount, fund_id_from))
        {
            cerr << "Account With ID: " << fund_id_from << " Has Insufficient Funds Within Money Market Funds To Cover" << endl;
            return false;
        }
    }
    account_from->WithdrawAssets(fund_id_from, amount);
    account_to->DepositAssets(fund_id_to, amount);
    return true;
}

bool Bank::DoesAccountExist(int uid)
{
    return accounts_.Contains(Account(uid));
}

Account &Bank::GetAccount(int uid)
{
    return accounts_.Get(Account(uid));
}

bool Bank::TransferFundsBetweenMoneyMarketToCover(Account *account, int amount, int fund_id)
{
    int overDrawnBy = amount - account->GetFundAssets(fund_id);

    vector<int> moneyMarketFundIDs = GetMoneyMarketFundIDs();

    int totalMoneyMarketFunds = 0;
    for (int i = 0; i < moneyMarketFundIDs.size(); i++)
    {
        if (moneyMarketFundIDs[i] != fund_id)
        {
            totalMoneyMarketFunds += account->GetFundAssets(moneyMarketFundIDs[i]);
        }
    }

    if (totalMoneyMarketFunds < overDrawnBy)
    {
        // total money market funds is insufficient
        return false;
    }

    // transfer needed funds
    for (int i = 0; i < moneyMarketFundIDs.size() && overDrawnBy > 0; i++)
    {
        if (moneyMarketFundIDs[i] == fund_id)
        {
            continue;
        }

        if (account->GetFundAssets(moneyMarketFundIDs[i]) < overDrawnBy)
        {
            int transferAmount = account->GetFundAssets(moneyMarketFundIDs[i]);
            account->DepositAssets(fund_id, transferAmount);
            account->WithdrawAssets(moneyMarketFundIDs[i], transferAmount);
            overDrawnBy -= transferAmount;
        }
        else
        {
            account->DepositAssets(fund_id, overDrawnBy);
            account->WithdrawAssets(moneyMarketFundIDs[i], overDrawnBy);
            overDrawnBy -= overDrawnBy;
        }
    }
    return true;
}

ostream &operator<<(ostream &os, const Bank &obj)
{
    os << obj.accounts_;
    return os;
}

#endif //_SRC_BANK_H_