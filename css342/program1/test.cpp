
#include <iostream>
#include <sstream>
#include "time_span.h"
using namespace std;
bool CheckValues(TimeSpan time, int hours, int minutes, int seconds)
{
    if ((time.hours() != hours) || (time.minutes() != minutes) || (time.seconds() != seconds))
    {
        return false;
    }
    return true;
}
bool TestZeros()
{
    TimeSpan ts(0, 0, 0);
    return CheckValues(ts, 0, 0, 0);
}

bool TestNegSet()
{
    TimeSpan ts(0, -90, -90);
    return CheckValues(ts, -1, -31, -30);
}
bool TestFloatSeconds()
{
    TimeSpan ts(127.86);
    // cout << "TestFloatSeconds:" << ts << endl;
    return CheckValues(ts, 0, 2, 8);
}
bool TestNegativeMinute()
{
    TimeSpan ts(8, -23, 0);
    return CheckValues(ts, 7, 37, 0);
}
bool TestNegativeHour()
{
    TimeSpan ts(-3, 73, 2);
    return CheckValues(ts, -1, -46, -58);
}
bool TestAdd()
{
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 + ts2 + ts3 + ts4;
    return CheckValues(add_it_up, 4, 7, 5);
}
bool TestAddInPlace()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, 6, 7, 8)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}
bool TestRemoveInPlace()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, 4, 5, 6)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}

bool TestAddBetter()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    TimeSpan ts3 = ts1 + ts2;
    if ((!CheckValues(ts3, 6, 7, 8)) || (!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}
bool TestRemoveBetter()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    TimeSpan ts3 = ts1 - ts2;
    if ((!CheckValues(ts3, 4, 5, 6)) || (!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1)))
    {
        return false;
    }
    return true;
}

bool TestEquals()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(5, 6, 7);
    return (ts1 == ts2);
}

bool TestNotEquals()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(5, 6, 7);
    return (ts1 != ts2);
}

bool TestGreaterThan()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    return (ts1 > ts2);
}

bool TestGreaterThan2()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    return !(ts2 > ts1);
}

bool TestLessThan()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    return !(ts1 < ts1);
}

bool TestLessThan2()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    return (ts2 < ts1);
}

bool TestCompareEquals()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(5, 6, 7);
    if (!(ts1 <= ts2))
    {
        return false;
    }
    if (!(ts1 >= ts2))
    {
        return false;
    }
    ts1.set_time(4, 5, 6);
    if (!(ts1 <= ts2))
    {
        return false;
    }
    if (!(ts2 >= ts1))
    {
        return false;
    }

    return true;
}

bool Testistream()
{
    TimeSpan ts1(0, 0, 0);
    cout << "Enter 3 ints seperated by spaces:";
    cin >> ts1;
    cout << ts1 << endl;
    return false;
}

bool TestNegation()
{
    TimeSpan ts1(5, 6, 7);
    // cout << ts1 << endl;
    ts1 = -ts1;
    // cout << ts1 << endl;
    return CheckValues(ts1, -5, -6, -7);
}

bool TestAddPlusPlus()
{
    TimeSpan ts1(5, 6, 7);
    // cout << ts1 << endl;
    ts1++;
    // cout << ts1 << endl;
    return CheckValues(ts1, 5, 6, 8);
}

bool TestRemovePlusPlus()
{
    TimeSpan ts1(5, 6, 7);
    // cout << ts1 << endl;
    ts1--;
    // cout << ts1 << endl;
    return CheckValues(ts1, 5, 6, 6);
}

// Testing For Negative Values
bool TestAddInPlaceNegative()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, 4, 5, 6)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}
bool TestRemoveInPlaceNegative()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, 6, 7, 8)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}

bool TestAddBetterNegative()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    TimeSpan ts3 = ts1 + ts2;
    if ((!CheckValues(ts3, 4, 5, 6)) || (!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}
bool TestRemoveBetterNegative()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    TimeSpan ts3 = ts1 - ts2;
    if ((!CheckValues(ts3, 6, 7, 8)) || (!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}

// Testing For Full Negative Values
bool FullTestAddInPlaceNegative()
{
    TimeSpan ts1(-5, -6, -7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, -5, -6, -7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, -6, -7, -8)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}
bool FullTestRemoveInPlaceNegative()
{
    TimeSpan ts1(-5, -6, -7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, -5, -6, -7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, -4, -5, -6)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}

bool FullTestAddBetterNegative()
{
    TimeSpan ts1(-5, -6, -7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, -5, -6, -7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    TimeSpan ts3 = ts1 + ts2;
    if ((!CheckValues(ts3, -6, -7, -8)) || (!CheckValues(ts1, -5, -6, -7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}
bool FullTestRemoveBetterNegative()
{
    TimeSpan ts1(-5, -6, -7);
    TimeSpan ts2(-1, -1, -1);
    if ((!CheckValues(ts1, -5, -6, -7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    TimeSpan ts3 = ts1 - ts2;
    if ((!CheckValues(ts3, -4, -5, -6)) || (!CheckValues(ts1, -5, -6, -7)) || (!CheckValues(ts2, -1, -1, -1)))
    {
        return false;
    }
    return true;
}

bool TestPosToNeg()
{
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(8, 0, 0);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 8, 0, 0)))
    {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, -2, -53, -53)) || (!CheckValues(ts2, 8, 0, 0)))
    {
        cout << ts1 << endl;
        return false;
    }
    return true;
}

void test(bool result, string title)
{
    int indentSize = 50 - title.length();
    string indent = "";
    for (int i = 0; i < indentSize; i++)
    {
        indent = indent + " ";
    }
    cout << "(" << title << ")" << indent;
    (result) ? cout << "[PASS]" << endl : cout << "[FAIL]" << endl;
}

bool testOstreamOp(TimeSpan ts, int hrs, int mins, int secs)
{
    ostringstream oss;
    oss << ts;
    ostringstream oss2;
    oss2 << "Hours: " << hrs << ", Minutes: " << mins << ", Seconds: " << secs;
    return oss.str() == oss2.str();
}

int main()
{
    cout << "=================[Testing TimeSpan Class]=================" << endl;
    test(TestZeros(), "TestZeros");
    test(TestFloatSeconds(), "TestFloatSeconds");
    test(TestNegativeMinute(), "TestNegativeMinute");
    test(TestNegativeHour(), "TestNegativeHour");
    test(TestAddInPlace(), "TestAddInPlace");
    test(TestRemoveInPlace(), "TestRemoveInPlace");
    test(TestGreaterThan(), "TestGreaterThanTrue");
    test(TestGreaterThan2(), "TestGreaterThanFalse");
    test(TestLessThan(), "TestLessThanTrue");
    test(TestLessThan2(), "TestLessThanFalse");
    test(TestAddBetter(), "TestAddBetter");
    test(TestRemoveBetter(), "TestRemoveBetter");
    test(TestCompareEquals(), "TestCompareEquals");
    test(TestNegSet(), "TestNegSet");
    test(TestNegation(), "TestNegation");
    test(TestAddPlusPlus(), "TestAddPlusPlus");
    test(TestRemovePlusPlus(), "TestRemovePlusPlus");
    test(TestAddInPlaceNegative(), "TestAddInPlaceNegative");
    test(TestRemoveInPlaceNegative(), "TestRemoveInPlaceNegative");
    test(TestAddBetterNegative(), "TestAddBetterNegative");
    test(TestRemoveBetterNegative(), "TestRemoveBetterNegative");
    test(FullTestAddInPlaceNegative(), "FullTestAddInPlaceNegative");
    test(FullTestRemoveInPlaceNegative(), "FullTestRemoveInPlaceNegative");
    test(FullTestAddBetterNegative(), "FullTestAddBetterNegative");
    test(FullTestRemoveBetterNegative(), "FullTestRemoveBetterNegative");
    test(TestPosToNeg(), "TestPosToNeg");
    test(testOstreamOp(TimeSpan(5, 2, 3), 5, 2, 3), "testOstreamOp 1");
    test(testOstreamOp(TimeSpan(1.5, 9.2, 5), 1, 39, 17), "testOstreamOp 2");
    test(testOstreamOp(TimeSpan(1.5, 4, -10), 1, 33, 50), "testOstreamOp 3");
    test(testOstreamOp(TimeSpan(7, -3), 0, 6, 57), "testOstreamOp 4");
    test(testOstreamOp(TimeSpan(-190), 0, -3, -10), "testOstreamOp 5");
    test(testOstreamOp(TimeSpan(15, 36, 24), 15, 36, 24), "testOstreamOp 6");
    test(testOstreamOp(TimeSpan(0, 59, 59), 0, 59, 59), "testOstreamOp 7");
    test(testOstreamOp(TimeSpan(0, 59, 60), 1, 0, 0), "testOstreamOp 8");
    test(testOstreamOp(TimeSpan(0, 59, 61), 1, 0, 1), "testOstreamOp 9");
    test(testOstreamOp(TimeSpan(0, 60, 60), 1, 1, 0), "testOstreamOp 10");
    test(testOstreamOp(TimeSpan(0, 61, 61), 1, 2, 1), "testOstreamOp 11");
    test(testOstreamOp(TimeSpan(-3661), -1, -1, -1), "testOstreamOp 12");
    // Testistream();
    cout << "====================[Testing Complete]====================" << endl;
}