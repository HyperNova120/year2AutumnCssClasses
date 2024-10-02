#ifndef PROGRAM1_TIME_SPAN_H
#define PROGRAM1_TIME_SPAN_H

#include <iostream>
#include "math.h"
using namespace std;

class TimeSpan
{
public:
    TimeSpan();
    TimeSpan(double secondsin);
    TimeSpan(double minutesin, double secondsin);
    TimeSpan(double hoursin, double minutesin, double secondsin);

    void set_time(int hoursin, int minutesin, int secondsin);

    friend ostream &operator<<(ostream &os, const TimeSpan &obj);
    friend istream &operator>>(istream &is, TimeSpan &obj);

    TimeSpan operator+(const TimeSpan &obj);
    TimeSpan operator++(const int second_add);
    TimeSpan operator--(const int second_remove);
    TimeSpan operator-(const TimeSpan &obj);
    TimeSpan operator-=(const TimeSpan &obj);
    TimeSpan operator+=(const TimeSpan &obj);
    bool operator==(const TimeSpan &obj);
    bool operator!=(const TimeSpan &obj);
    bool operator<=(const TimeSpan &obj);
    bool operator>=(const TimeSpan &obj);
    bool operator<(const TimeSpan &obj);
    bool operator>(const TimeSpan &obj);

    int hours() const;
    int minutes() const;
    int seconds() const;

    int TotalSeconds() const;
    void SetFromTotalSeconds(double total_seconds);

private:
    int m_hours_;
    int m_seconds_;
    int m_minutes_;
};
#endif