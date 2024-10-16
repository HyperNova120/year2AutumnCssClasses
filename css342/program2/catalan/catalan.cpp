#include <iostream>
#include <map>
#include <sstream>
#include <climits>
#include "uint256.h"
#include "uint512.h"
#include <chrono>
#include <ctime>

using namespace std;

map<UInt512, UInt512> known_numbers_;
long calculations = 0;
long lookups = 0;

UInt512 FindCatalanNumber(int n)
{
    if (n == 0)
    {
        return 1;
    }
    if (known_numbers_.find(n) != known_numbers_.end())
    {
        // cout << "known number" << endl;
        lookups++;
        return known_numbers_[n];
    }
    calculations++;
    UInt512 sum_ = 0;
    for (int i = 0; i < n; i++)
    {
        sum_ += FindCatalanNumber(i) * FindCatalanNumber((n - 1) - i);
    }
    known_numbers_[n] = sum_;
    return sum_;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Catalan: Malformed Input; Missing/Too-Many Input Parameter(s)" << endl;
        return -1;
    }

    stringstream ss;
    ss << argv[1];
    int n;
    ss >> n;

    if (n < 0)
    {
        cout << "Catalan: Malformed Input; Cannot Be Negative" << endl;
        return -1;
    }
    else if (n > 262 && !KDEBUG) // yes this has been tested, 512bit is big enough to be correct until n=262
    {
        cout << "Catalan: Input Too Large, Will Cause Overflow" << endl;
        return -1;
    }

    chrono::system_clock::time_point start = chrono::system_clock::now();
    UInt512 result = FindCatalanNumber(n);

    if (KDEBUG)
    {
        cout << "lookups to Calculations:" << lookups << "/" << calculations << " Ratio:" << ((double)lookups / (double)calculations) << ":1" << endl;
        cout << "Calculation Time:" << (chrono::system_clock::now() - start).count() / 1000000 << "ms" << endl;
    }

    cout << result << endl;
}