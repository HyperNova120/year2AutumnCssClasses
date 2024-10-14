#include <iostream>
#include <map>
#include <sstream>
#include <climits>
#include "uint256.h"
#include "uint512.h"

using namespace std;

map<UInt512, UInt512> knownNumbers_;

UInt512 FindCatalanNumber(unsigned long long n)
{
    if (n == 0)
    {
        return 1;
    }

    if (knownNumbers_.find(n) != knownNumbers_.end())
    {
        // cout << "known number" << endl;
        return knownNumbers_[n];
    }

    UInt512 sum_ = 0;
    for (unsigned long long i = 0; i < n; i++)
    {
        sum_ += FindCatalanNumber(i) * FindCatalanNumber((n - 1) - i);
    }
    knownNumbers_[n] = sum_;
    return sum_;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Catalan: Malformed Input; Missing Input Parameter" << endl;
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
    else if (n > 133)
    {
        //cout << "Catalan: Input Too Large, Will Cause Overflow" << endl;
        //return -1;
    }
    UInt512 result = FindCatalanNumber(n);
    cout << result << endl;

    /* UInt256 shiftTest(0, ULLONG_MAX);
    cout << shiftTest << endl;
    cout << "after Shift" << endl;
    shiftTest = shiftTest << 128;
    cout << shiftTest << endl;
    cout << "after Shift" << endl;
    shiftTest = shiftTest >> 128;
    cout << shiftTest << endl;
    UInt256 andTest = shiftTest << 1;
    cout << "andTest" << endl;
    cout << andTest << endl;
    andTest = andTest & shiftTest;
    cout << "after andTest" << endl;
    cout << andTest << endl; */
/* 
    UInt512 test(5);
    UInt512 test2(5);
    test = test * test2;
    cout << test << endl; */
}