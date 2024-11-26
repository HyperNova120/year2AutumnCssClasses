#include "Fund.h"

Fund::Fund()
{
}

Fund::Fund(int fund_id, string fund_name)
{
    fund_id_ = fund_id;
    fund_name_ = fund_name;
}

void Fund::RegisterAccount(int uid)
{
    fund_accounts_[uid] = 0;
}

void Fund::Deposit(int uid, long amount)
{
    fund_accounts_[uid] += amount;
}

void Fund::Withdraw(int uid, long amount)
{
    fund_accounts_[uid] -= amount;
}

long Fund::GetAccountFunds(int uid) const
{
    return fund_accounts_.at(uid);//[uid];
}

int Fund::fund_id() const
{
    return fund_id_;
}

string Fund::fund_name() const
{
    return fund_name_;
}

map<int, long> Fund::fund_accounts() const
{
    return fund_accounts_;
}
