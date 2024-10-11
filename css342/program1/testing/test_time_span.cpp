#include <iostream>
#include <sstream>
#include "time_span.h"
using namespace std;

bool CheckValues(TimeSpan time, int hours, int minutes, int seconds) {
    if ((time.hours() != hours) || (time.minutes() != minutes) || (time.seconds()
                                                                   != seconds)) {
        return false;
    }
    return true;
}

bool TestZeros() {
    TimeSpan ts(0, 0, 0);
    return CheckValues(ts, 0, 0, 0);
}

bool TestFloatAndDouble() {
    TimeSpan ts;

    ts = TimeSpan(127.86);
    if (!CheckValues(ts, 0, 2, 8)) return false;

    ts = TimeSpan(127.86f);
    if (!CheckValues(ts, 0, 2, 8)) return false;

    ts = TimeSpan(1.0, 127.86);
    if (!CheckValues(ts, 0, 3, 8)) return false;

    ts = TimeSpan(1.0f, 127.86f);
    if (!CheckValues(ts, 0, 3, 8)) return false;

    ts = TimeSpan(10.0, -2.0, 127.86);
    if (!CheckValues(ts, 10.0, 0, 8)) return false;

    ts = TimeSpan(10.0f, -2.0f, 127.86f);
    if (!CheckValues(ts, 10, 0, 8)) return false;

    return true;
}

bool TestNegativeMinute() {
    TimeSpan ts(8, -23, 0);
    return CheckValues(ts, 7, 37, 0);
}

bool TestNegativeHour() {
    TimeSpan ts(-3, 73, 2);
    return CheckValues(ts, -1, -46, -58);
}

bool TestAdd() {
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 + ts2 + ts3 + ts4;
    return CheckValues(add_it_up, 4, 7, 5);
}

bool TestSub() {
    TimeSpan ts1, ts2(-5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts4 - ts3 - ts2 - ts1;
    return CheckValues(add_it_up, 3, 53, 5);
}

bool TestNeg() {
    TimeSpan ts(6, 9, 47);
    if (!CheckValues(ts, 6, 9, 47)) return false;
    if (!CheckValues(-ts, -6, -9, -47)) return false;

    return true;
}

bool TestAddInPlace() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, -1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 0, 59))) {
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, 6, 7, 6)) || (!CheckValues(ts2, 1, 0, 59))) {
        return false;
    }
    return true;
}

bool TestSubInPlace() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(-1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 0, -58, -59))) {
        return false;
    }
    ts1 -= ts2;
    if ((!CheckValues(ts1, 6, 5, 6)) || (!CheckValues(ts2, 0, -58, -59))) {
        return false;
    }
    return true;
}

bool TestEquals() {
    TimeSpan ts1(1, 5, 4);
    TimeSpan ts2(2, -54, -56);
    TimeSpan ts3(5, 1, 6);

    return ts1 == ts2 && !(ts1 != ts2) && ts1 == ts1 && !(ts1 != ts1) && ts1 != ts3 && !(ts1 == ts3);
}

bool TestLessThan() {
    TimeSpan ts1(1, 5, 4);
    TimeSpan ts2(2, -54, -56);
    TimeSpan ts3(5, 1, 6);
    TimeSpan ts4(1, 5, 5);
    TimeSpan ts5(1, 5, 3);

    bool comp = ts1 < ts3 && ts2 < ts3 && ts1 < ts4 && ts2 < ts4 && ts5 < ts1 && ts5 < ts2;
    bool compEquals = ts1 <= ts3 && ts2 <= ts3 && ts1 <= ts4 && ts2 <= ts4 && ts5 <= ts1 && ts5 <= ts2;
    bool equals = ts1 <= ts2 && ts1 <= ts1 && ts2 <= ts2 && ts3 <= ts3 && ts4 <= ts4 && ts5 <= ts5;
    bool notCompSelf = !(ts1 < ts1) && !(ts2 < ts2) && !(ts3 < ts3) && !(ts4 < ts4) && !(ts5 < ts5);
    bool notComp = !(ts3 < ts1) && !(ts3 < ts2) && !(ts4 < ts1) && !(ts4 < ts2) && !(ts1 < ts5) && !(
                       ts2 < ts5);
    bool notCompEquals = !(ts3 <= ts1) && !(ts3 <= ts2) && !(ts4 <= ts1) && !(ts4 <= ts2) && !(ts1 <= ts5) && !(
                             ts2 <= ts5);

    return comp && compEquals && equals && notCompSelf && notComp && notCompEquals;
}

bool TestGreaterThan() {
    TimeSpan ts1(1, 5, 4);
    TimeSpan ts2(2, -54, -56);
    TimeSpan ts3(5, 1, 6);
    TimeSpan ts4(1, 5, 5);
    TimeSpan ts5(1, 5, 3);

    bool comp = ts3 > ts1 && ts3 > ts2 && ts4 > ts1 && ts4 > ts2 && ts1 > ts5 && ts2 > ts5;
    bool compEquals = ts3 >= ts1 && ts3 >= ts2 && ts4 >= ts1 && ts4 >= ts2 && ts1 >= ts5 && ts2 >= ts5;
    bool equals = ts1 >= ts2 && ts1 >= ts1 && ts2 >= ts2 && ts3 >= ts3 && ts4 >= ts4 && ts5 >= ts5;
    bool notCompSelf = !(ts1 > ts1) && !(ts2 > ts2) && !(ts3 > ts3) && !(ts4 > ts4) && !(ts5 > ts5);
    bool notComp = !(ts1 > ts3) && !(ts2 > ts3) && !(ts1 > ts4) && !(ts2 > ts4) && !(ts5 > ts1) && !(
                       ts5 > ts2);
    bool notCompEquals = !(ts1 >= ts3) && !(ts2 >= ts3) && !(ts1 >= ts4) && !(ts2 >= ts4) && !(ts5 >= ts1) && !(
                             ts5 >= ts2);

    return comp && compEquals && equals && notCompSelf && notComp && notCompEquals;
}

bool TestOutput() {
    TimeSpan ts1(5, -6, 7);
    TimeSpan ts2(-1, -1, 1);

    stringstream out{};

    out << ts1 << endl << ts2 << endl;

    return out.str() == "Hours: 4, Minutes: 54, Seconds: 7\nHours: -1, Minutes: 0, Seconds: -59\n";
}

bool TestInput() {
    stringstream out{};

    out << "10";
    out << "-5";
    out << "-2";

    TimeSpan ts1;
    out >> ts1;

    return CheckValues(ts1, 9, 54, 58);
}

bool TestSetTime() {
    TimeSpan ts1(6, 28, 3);
    if (!CheckValues(ts1, 6, 28, 3)) {
        return false;
    }

    ts1.set_time(1, 7, 3);
    if (!CheckValues(ts1, 1, 7, 3)) {
        return false;
    }

    ts1.set_time(-1, 7, 3);
    if (!CheckValues(ts1, 0, -52, -57)) {
        return false;
    }

    return true;
}

int main() {
    cout << "Testing TimeSpan Class" << endl;
    if (!TestZeros()) cout << "Failed: TestZeros" << endl;
    if (!TestFloatAndDouble()) cout << "Failed: TestFloatAndDouble" << endl;
    if (!TestNegativeMinute()) cout << "Failed: TestNegativeMinute" << endl;

    if (!TestNegativeHour()) cout << "Failed: TestNegativeHour" << endl;
    if (!TestAdd()) cout << "Failed: TestAdd" << endl;
    if (!TestSub()) cout << "Failed: TestSub" << endl;
    if (!TestNeg()) cout << "Failed: TestNeg" << endl;
    if (!TestAddInPlace()) cout << "Failed: TestAddInPlace" << endl;
    if (!TestSubInPlace()) cout << "Failed: TestSubInPlace" << endl;

    if (!TestEquals()) cout << "Failed: TestEquals" << endl;
    if (!TestLessThan()) cout << "Failed: TestLessThan" << endl;
    if (!TestGreaterThan()) cout << "Failed: TestGreaterThan" << endl;

    if (!TestOutput()) cout << "Failed: TestOutput" << endl;
    if (!TestInput()) cout << "Failed: TestInput" << endl;

    if (!TestSetTime()) cout << "Failed: TestSetTime" << endl;
    cout << "Testing Complete" << endl;
}
