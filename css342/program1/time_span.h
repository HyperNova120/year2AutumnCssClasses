#ifndef PROGRAM1_TIME_SPAN_H
#define PROGRAM1_TIME_SPAN_H

#include <iostream>
using namespace std;

class TimeSpan
{   
    public:
    TimeSpan();
    TimeSpan(double secondsin);
    TimeSpan(double minutesin, double secondsin);
    TimeSpan(double hoursin, double minutesin, double secondsin);


    void set_time(int hoursin, int minutesin, int secondsin);

    friend ostream& operator<<(ostream& os, const TimeSpan& obj);
    
    int hours() const;
    int minutes() const;
    int seconds() const;

    private:
        int m_hours;
        int m_seconds;
        int m_minutes;
};
#endif