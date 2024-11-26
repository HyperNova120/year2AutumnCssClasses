#ifndef _SRC_FUNDSAPI_H_
#define _SRC_FUNDSAPI_H_

#include <vector>
#include <string>
#include <map>
#include "Fund.h"

using namespace std;

class global_funds //allows anybody to look at the funds but only Bank to edit them
{
public:
    friend class Bank;

    static map<int, Fund> funds();

private:
    static map<int, Fund> funds_;
};

inline vector<int> GetAllFundIDs()
{
    vector<int> tmp = vector<int>();
    for (int i = 0; i <= 7; i++)
    {
        tmp.push_back(i);
    }
    return tmp;
};

inline string GetFundName(int fund_id)
{
    map<int, string> funds = map<int, string>();
    funds[0] = "Money Market";
    funds[1] = "Prime Money Market";
    funds[2] = "Long-Term Bond";
    funds[3] = "Short-Term Bond";
    funds[4] = "500 Index Fund";
    funds[5] = "Capital Value Fund";
    funds[6] = "Growth Equity Fund";
    funds[7] = "Growth Index Fund";
    return funds[fund_id];
};

inline bool DoesFundExist(int fund_id)
{
    return fund_id >= 0 && fund_id <= 7;
};

inline vector<int> GetMoneyMarketFundIDs()
{
    vector<int> tmp = vector<int>();
    tmp.push_back(0);
    tmp.push_back(1);
    return tmp;
};

inline vector<int> GetBondFundIDs()
{
    vector<int> tmp = vector<int>();
    tmp.push_back(2);
    tmp.push_back(3);
    return tmp;
};

inline bool IsMoneyMarketFund(int fund_id)
{
    return fund_id == 0 || fund_id == 1;
};

inline bool IsBondFund(int fund_id)
{
    return fund_id == 2 || fund_id == 3;
};

#endif //_SRC_FUNDSAPI_H_;