#ifndef _SRC_FUNDS_H_
#define _SRC_FUNDS_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

vector<int> GetAllFundIDs()
{
    vector<int> tmp = vector<int>();
    for (int i = 0; i <= 7; i++)
    {
        tmp.push_back(i);
    }
    return tmp;
};

string GetFundName(int fund_id)
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

bool DoesFundExist(int fund_id)
{
    return fund_id >= 0 && fund_id <= 7;
};

vector<int> GetMoneyMarketFundIDs()
{
    vector<int> tmp = vector<int>();
    tmp.push_back(0);
    tmp.push_back(1);
    return tmp;
};
bool IsMoneyMarketFund(int fund_id)
{
    return fund_id == 0 || fund_id == 1;
};

#endif _SRC_FUNDS_H_;