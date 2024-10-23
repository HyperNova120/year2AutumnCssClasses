#ifndef CATALAN_H_
#define CATALAN_H_
#include <iostream>
#include <map>
#include <sstream>
#include <climits>
#include "uint256.h"
#include "uint512.h"
#include <chrono>
#include <ctime>

using namespace std;

class Catalan
{
public:
    Catalan(int n);
    UInt512 FindCatalanNumber(int n);

    long debug_calculations();
    long debug_lookups();
private:
    map<UInt512, UInt512> known_numbers_;
    long debug_calculations_ = 0;
    long debug_lookups_ = 0;
};
#endif //CATALAN_H_