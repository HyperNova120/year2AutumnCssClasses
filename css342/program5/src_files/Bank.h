#ifndef _SRC_BANK_H_
#define _SRC_BANK_H_

#include "BST.h"
#include "Account.h"
#include "FundsAPI.h"

#include <list>
#include <iostream>
#include <vector>

using namespace std;

class Bank
{
public:
    Bank();

    void RunTransaction(vector<string> transaction_order);

    friend ostream &operator<<(ostream &os, const Bank &obj);

private:
    void CreateAccount(int uid, string first_name, string last_name);
    void DeleteAccount(int uid, string first_name, string last_name);

    bool DepositFunds(int uid, int fund_id, long amount);
    bool WithdrawFunds(int uid, int fund_id, long amount);

    bool TransferFunds(int uid_from, int fund_id_from, int uid_to, int fund_id_to, long amount);

    vector<string> GetAccountTransactionHistory(int uid);
    vector<string> GetFundTransactionHistory(int uid, int fund_id);

    bool DoesAccountExist(int uid) const;
    Account &GetAccount(int uid) const;
    bool TransferFundsBetweenElligibleFundsToCover(Account *account, int amount, int fund_id, vector<int> FundIDs);
    void PrintAccountTransactionHistory(int uid) const;
    void PrintAccountTransactionHistory(int uid, int fund_id) const;

    BST<Account> accounts_;
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
        // cerr << "NEED TO IMPLEMENT THIS" << endl;
        PrintAccountTransactionHistory(stoi(transaction_order[1]));
    }
    else if (transaction_order[0] == "F")
    {
        if (transaction_order.size() != 3)
        {
            cerr << "INVALID TRANSACTION COMMAND" << endl;
            return;
        }
        // TODO implement
        //cerr << "NEED TO IMPLEMENT THIS" << endl;
        PrintAccountTransactionHistory(stoi(transaction_order[1]), stoi(transaction_order[2]));
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
    account->AddTransaction(fund_id, "D " + to_string(account->uid()) + " " + to_string(fund_id) + " " + to_string(amount));
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

    string transaction_string = "D " + to_string(uid) + " " + to_string(fund_id) + " " + to_string(amount);
    Account *account = &GetAccount(uid);
    if (account->GetFundAssets(fund_id) < amount)
    {
        // withdraw past account funds

        if (IsMoneyMarketFund(fund_id))
        {
            if (!TransferFundsBetweenElligibleFundsToCover(account, amount, fund_id, GetMoneyMarketFundIDs()))
            {
                cerr << "Account With ID: " << uid << " Has Insufficient Funds Within Money Market Funds To Cover" << endl;
                account->AddTransaction(fund_id, transaction_string + " (FAILED)");
                return false;
            }
        }
        else if (IsBondFund(fund_id))
        {
            if (!TransferFundsBetweenElligibleFundsToCover(account, amount, fund_id, GetBondFundIDs()))
            {
                cerr << "Account With ID: " << uid << " Has Insufficient Funds Within Bond Funds To Cover" << endl;
                account->AddTransaction(fund_id, transaction_string + " (FAILED)");
                return false;
            }
        }
        else
        {
            cerr << "Account With ID: " << uid << " Has Insufficient Funds Within Fund With ID: " << fund_id << endl;
            account->AddTransaction(fund_id, transaction_string + " (FAILED)");
            return false;
        }
    }

    account->WithdrawAssets(fund_id, amount);
    account->AddTransaction(fund_id, transaction_string);

    return true;
}

bool Bank::TransferFunds(int uid_from, int fund_id_from, int uid_to, int fund_id_to, long amount)
{
    string transaction_string = "T " + to_string(uid_from) + " " + to_string(fund_id_from) + " " + to_string(uid_to) + " " + to_string(fund_id_to) + " " + to_string(amount);
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
        if (IsMoneyMarketFund(fund_id_from))
        {
            if (!TransferFundsBetweenElligibleFundsToCover(account_from, amount, fund_id_from, GetMoneyMarketFundIDs()))
            {
                cerr << "Account With ID: " << fund_id_from << " Has Insufficient Funds Within Money Market Funds To Cover" << endl;
                account_from->AddTransaction(fund_id_from, transaction_string + " (Failed)");
                account_to->AddTransaction(fund_id_to, transaction_string + " (Failed)");
                return false;
            }
        }
        else if (IsBondFund(fund_id_from))
        {
            if (!TransferFundsBetweenElligibleFundsToCover(account_from, amount, fund_id_from, GetBondFundIDs()))
            {
                cerr << "Account With ID: " << fund_id_from << " Has Insufficient Funds Within Bond Funds To Cover" << endl;
                account_from->AddTransaction(fund_id_from, transaction_string + " (Failed)");
                account_to->AddTransaction(fund_id_to, transaction_string + " (Failed)");
                return false;
            }
        }
        else
        {
            cerr << "Account With ID: " << fund_id_from << " Has Insufficient Funds Within Fund With ID: " << fund_id_from << endl;
            account_from->AddTransaction(fund_id_from, transaction_string + " (Failed)");
            account_to->AddTransaction(fund_id_to, transaction_string + " (Failed)");
            return false;
        }
    }
    account_from->WithdrawAssets(fund_id_from, amount);
    account_to->DepositAssets(fund_id_to, amount);

    account_from->AddTransaction(fund_id_from, transaction_string);
    account_to->AddTransaction(fund_id_to, transaction_string);

    return true;
}

bool Bank::DoesAccountExist(int uid) const
{
    return accounts_.Contains(Account(uid));
}

Account &Bank::GetAccount(int uid) const
{
    return accounts_.Get(Account(uid));
}

bool Bank::TransferFundsBetweenElligibleFundsToCover(Account *account, int amount, int fund_id, vector<int> FundIDs)
{
    int overDrawnBy = amount - account->GetFundAssets(fund_id);

    int totalBondFunds = 0;
    for (int i = 0; i < FundIDs.size(); i++)
    {
        if (FundIDs[i] != fund_id)
        {
            totalBondFunds += account->GetFundAssets(FundIDs[i]);
        }
    }

    if (totalBondFunds < overDrawnBy)
    {
        // total money market funds is insufficient
        return false;
    }

    // transfer needed funds
    for (int i = 0; i < FundIDs.size() && overDrawnBy > 0; i++)
    {
        if (FundIDs[i] == fund_id)
        {
            continue;
        }

        if (account->GetFundAssets(FundIDs[i]) < overDrawnBy)
        {
            int transferAmount = account->GetFundAssets(FundIDs[i]);
            account->DepositAssets(fund_id, transferAmount);
            account->WithdrawAssets(FundIDs[i], transferAmount);
            overDrawnBy -= transferAmount;
        }
        else
        {
            account->DepositAssets(fund_id, overDrawnBy);
            account->WithdrawAssets(FundIDs[i], overDrawnBy);
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

void Bank::PrintAccountTransactionHistory(int uid) const
{
    if (!DoesAccountExist(uid))
    {
        cerr << "Account With ID: " << to_string(uid) << " Does Not Exist" << endl;
        return;
    }

    Account *account = &GetAccount(uid);
    map<int, std::vector<std::__cxx11::string>> history = account->transaction_history();
    cout << "Transaction History For " << account->first_name() << " " << account->last_name() << endl;
    for (int i : GetAllFundIDs())
    {
        cout << GetFundName(i) << ": $" << account->GetFundAssets(i) << endl;
        for (string s : history[i])
        {
            cout << "   " << s << endl;
        }
    }
    cout << endl;
}

void Bank::PrintAccountTransactionHistory(int uid, int fund_id) const
{
    if (!DoesAccountExist(uid))
    {
        cerr << "Account With ID: " << to_string(uid) << " Does Not Exist" << endl;
        return;
    }
    else if (!DoesFundExist(fund_id))
    {
        cerr << "Fund With ID: " << fund_id << " Does Not Exists" << endl;
    }

    Account *account = &GetAccount(uid);
    map<int, std::vector<std::__cxx11::string>> history = account->transaction_history();
    cout << "Transaction History For " << account->first_name() << " " << account->last_name() << " " << GetFundName(fund_id) << " Fund: $" << account->GetFundAssets(fund_id) << endl;

    for (string s : history[fund_id])
    {
        cout << "   " << s << endl;
    }
    cout << endl;
}

#endif //_SRC_BANK_H_