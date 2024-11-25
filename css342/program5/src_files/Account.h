#ifndef _SRC_ACCOUNT_H_
#define _SRC_ACCOUNT_H_

#include <map>
#include <list>
#include <vector>
#include "Funds.h"
using namespace std;

class Account
{
public:
    Account(int uid);
    Account(string first_name, string last_name, int uid, map<int, long> accountFunds);
    Account(const Account &other);

    void AddTransaction(string transaction);

    long GetFundAssets(int fund_id) const;

    void DepositAssets(int fund_id, long assets_amount);
    void WithdrawAssets(int fund_id, long assets_amount);

    // operators overloaded based on uid
    bool operator<(const Account &obj) const;
    bool operator>(const Account &obj) const;
    bool operator==(const Account &obj) const;
    bool operator!=(const Account &obj) const;
    bool operator<=(const Account &obj) const;
    bool operator>=(const Account &obj) const;

    Account &operator=(const Account &other);
    friend ostream &operator<<(ostream &os, const Account &obj);

    int uid() const;
    string first_name() const;
    string last_name() const;

private:
    int uid_ = 0;
    string first_name_ = "";
    string last_name_ = "";
    map<int, long> accountFunds_;
    list<string> transaction_history_;
};

Account::Account(int uid)
{
    uid_ = uid;
}

Account::Account(string first_name, string last_name, int uid, map<int, long> accountFunds)
{
    first_name_ = first_name;
    last_name_ = last_name;
    uid_ = uid;
    accountFunds_ = accountFunds;
}

Account::Account(const Account &other)
{
    *this = other;
}

void Account::AddTransaction(string transaction)
{
    transaction_history_.push_back(transaction);
}

long Account::GetFundAssets(int fund_id) const
{
    if (!accountFunds_.count(fund_id))
    {
        return -1;
    }
    return accountFunds_.at(fund_id);
}

void Account::DepositAssets(int fund_id, long assets_amount)
{
    if (!accountFunds_.count(fund_id))
    {
        return;
    }
    accountFunds_[fund_id] += assets_amount;
}

void Account::WithdrawAssets(int fund_id, long assets_amount)
{
    if (!accountFunds_.count(fund_id))
    {
        return;
    }
    accountFunds_[fund_id] -= assets_amount;
}

bool Account::operator<(const Account &obj) const
{
    return uid_ < obj.uid_;
}

bool Account::operator>(const Account &obj) const
{
    return uid_ > obj.uid_;
}

bool Account::operator==(const Account &obj) const
{
    return uid_ == obj.uid_;
}

bool Account::operator!=(const Account &obj) const
{
    return uid_ != obj.uid_;
}

bool Account::operator<=(const Account &obj) const
{
    return uid_ <= obj.uid_;
}

bool Account::operator>=(const Account &obj) const
{
    return uid_ >= obj.uid_;
}

Account &Account::operator=(const Account &other)
{
    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    uid_ = other.uid_;
    transaction_history_ = other.transaction_history_;
    accountFunds_ = other.accountFunds_;
    return *this;
}

ostream &operator<<(ostream &os, const Account &obj)
{
    os << "======" << obj.uid_ << "======" << endl;
    os << "First Name:" << obj.first_name_ << endl;
    os << "Last Name:" << obj.last_name_ << endl;
    os << "Fund Assets:" << endl;
    vector<int> funds = GetAllFundIDs();
    for (int i = 0; i < funds.size(); i++)
    {
        os << "\t" << GetFundName(funds[i]) << "(" << funds[i] << "): $" << obj.GetFundAssets(funds[i]) << endl;
    }
    os << "============";
    for (int i = 0; i < to_string(obj.uid_).length(); i++)
    {
        os << "=";
    }
    return os;
}

int Account::uid() const
{
    return uid_;
}

string Account::first_name() const
{
    return first_name_;
}

string Account::last_name() const
{
    return last_name_;
}

#endif //_SRC_ACCOUNT_H_