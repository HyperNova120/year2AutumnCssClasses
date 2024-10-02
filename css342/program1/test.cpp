#include <iostream>
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
    ts1.set_time(4,5,6);
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

void test(bool result, string title)
{
    (result) ? cout << "[PASS]:" << title << endl : cout << "[FAIL]:" << title << endl;
}

int main()
{
    cout << "Testing TimeSpan Class" << endl;
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
    test(TestCompareEquals(),"TestCompareEquals");
    cout << "[PASS]:<<:" << TimeSpan(15, 36, 24) << endl;
    cout << "[PASS]:<<:" << TimeSpan(0, 59, 59) << endl;
    cout << "[PASS]:<<:" << TimeSpan(0, 59, 60) << endl;
    cout << "[PASS]:<<:" << TimeSpan(0, 59, 61) << endl;
    cout << "[PASS]:<<:" << TimeSpan(0, 60, 60) << endl;
    cout << "[PASS]:<<:" << TimeSpan(0, 61, 61) << endl;
    Testistream();
    cout << "Testing Complete" << endl;
}