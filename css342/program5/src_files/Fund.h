
#ifndef _SRC_FILES_FUND_H_
#define _SRC_FILES_FUND_H_

#include <map>
#include <string>

using namespace std;

class Fund
{
public:

    Fund();
    Fund(int fund_id, string fund_name);

    void RegisterAccount(int uid);

    void Deposit(int uid, long amount);
    void Withdraw(int uid, long amount);
    long GetAccountFunds(int uid);


    int fund_id() const;
    string fund_name() const;
    map<int, long> fund_accounts() const;

private:
    int fund_id_ = 0;
    string fund_name_ = "";
    map<int, long> fund_accounts_ = map<int, long>(); //key: user id
};

#endif //_SRC_FILES_FUND_H_