
#ifndef _SRC_FILES_ACCOUNT_H_
#define _SRC_FILES_ACCOUNT_H_

#include <string>
#include <map>
#include "FundsAPI.h"
using namespace std;
class Account
{
public:
    Account(int uid);
    Account(string first_name, string last_name, int uid);
    Account(const Account &other);

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
    int uid_;
    string first_name_;
    string last_name_;
};

#endif //_SRC_FILES_ACCOUNT_H_