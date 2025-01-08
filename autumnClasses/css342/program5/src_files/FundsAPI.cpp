#include "FundsAPI.h"
#include "Fund.h"
#include <map>
using namespace std;

map<int, Fund> global_funds::funds_;

map<int, Fund> global_funds::funds()
{
    return map<int, Fund>(funds_);
}


