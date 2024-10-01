#include "time_span.h"

TimeSpan::TimeSpan()
{
    m_hours = 0;
    m_minutes = 0;
    m_seconds = 0;
}

TimeSpan::TimeSpan(double secondsin)
{
    TimeSpan();
    int secIn = (int)secondsin;
    int hr = secIn / 3600;
    secIn -= secIn % 3600;
    int min = secIn / 60;
    secIn -= secIn % 60;
    set_time(hr, min, secIn);
}
TimeSpan::TimeSpan(double minutesin, double secondsin)
{
    TimeSpan(secondsin + (minutesin * 60));
}
TimeSpan::TimeSpan(double hoursin, double minutesin, double secondsin)
{
    TimeSpan(minutesin + (hoursin * 60), secondsin);
}

void TimeSpan::set_time(int hoursin, int minutesin, int secondsin)
{
    m_hours = hoursin;
    m_minutes = hoursin;
    m_seconds = secondsin;
}

int TimeSpan::hours() const
{
    return m_hours;
}
int TimeSpan::minutes() const
{
    return m_minutes;
}
int TimeSpan::seconds() const
{
    return m_seconds;
}

ostream& operator<<(ostream &os, const TimeSpan &obj)
{
    os << "Hours: " << obj.hours() << ", Minutes: " << obj.minutes() << ", Seconds: " << obj.seconds();
    return os;
}
