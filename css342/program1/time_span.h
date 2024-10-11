#ifndef PROGRAM1_TIME_SPAN_H
#define PROGRAM1_TIME_SPAN_H

#include <iostream>
#include <cmath>
using namespace std;

class TimeSpan
{
public:
    //constructors
    TimeSpan();
    TimeSpan(double secondsin);
    TimeSpan(double minutesin, double secondsin);
    TimeSpan(double hoursin, double minutesin, double secondsin);

    //formatted this way b/e required by program 1 spec
    void set_time(int hoursin, int minutesin, int secondsin);

    //i/ostream overloads
    friend ostream &operator<<(ostream &os, const TimeSpan &obj);
    friend istream &operator>>(istream &is, TimeSpan &obj);

    //operator overloads
    TimeSpan operator+(const TimeSpan &obj) const;
    TimeSpan operator-(const TimeSpan &obj) const;
    TimeSpan &operator=(const TimeSpan &obj);
    TimeSpan &operator++();
    TimeSpan &operator--();
    TimeSpan &operator++(int value);
    TimeSpan &operator--(int value);
    TimeSpan operator-() const;
    TimeSpan operator-=(const TimeSpan &obj);
    TimeSpan operator+=(const TimeSpan &obj);
    bool operator==(const TimeSpan &obj) const;
    bool operator!=(const TimeSpan &obj) const;
    bool operator<=(const TimeSpan &obj) const;
    bool operator>=(const TimeSpan &obj) const;
    bool operator<(const TimeSpan &obj) const;
    bool operator>(const TimeSpan &obj) const;

    //getters
    int hours() const;
    int minutes() const;
    int seconds() const;

private:
    int hours_;
    int seconds_;
    int minutes_;

    //easily handle settings, and comparing
    int TotalSeconds() const;
    void SetFromTotalSeconds(double total_seconds);
};
#endif