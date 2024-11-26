#include "Account.h"
#include <iostream>
Account::Account(int uid)
{
    uid_ = uid;
}

Account::Account(string first_name, string last_name, int uid)
{
    uid_ = uid;
    first_name_ = first_name;
    last_name_ = last_name;
}

Account::Account(const Account &other)
{
    *this = other;
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
    uid_ = other.uid_;
    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    return *this;
}

ostream &operator<<(ostream &os, const Account &obj)
{
    map<int, Fund> tmp = global_funds::funds();
    os << obj.first_name_ << " " << obj.last_name_ << " Account ID: " << to_string(obj.uid_) << endl;
    for (int fund_id : GetAllFundIDs())
    {
        os << "    " << GetFundName(fund_id) << ": $" << tmp[fund_id].GetAccountFunds(obj.uid_) << endl;
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
