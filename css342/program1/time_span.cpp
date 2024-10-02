#include "time_span.h"

TimeSpan::TimeSpan()
{
    m_hours_ = 0;
    m_minutes_ = 0;
    m_seconds_ = 0;
}

TimeSpan::TimeSpan(double secondsin)
{
    SetFromTotalSeconds(secondsin);
}

TimeSpan::TimeSpan(double minutesin, double secondsin) : TimeSpan(secondsin + (minutesin * 60)) {}

TimeSpan::TimeSpan(double hoursin, double minutesin, double secondsin) : TimeSpan(minutesin + (hoursin * 60), secondsin) {}

void TimeSpan::set_time(int hoursin, int minutesin, int secondsin)
{
    SetFromTotalSeconds((hoursin*3600)+(minutesin*60)+secondsin);
}

void TimeSpan::SetFromTotalSeconds(double totalSeconds)
{
    int secIn = round(totalSeconds);
    int hr = secIn / 3600;
    secIn = secIn % 3600;
    int min = secIn / 60;
    secIn = secIn % 60;
    m_hours_ = hr;
    m_minutes_ = min;
    m_seconds_ = secIn;
}

int TimeSpan::hours() const
{
    return m_hours_;
}
int TimeSpan::minutes() const
{
    return m_minutes_;
}
int TimeSpan::seconds() const
{
    return m_seconds_;
}

int TimeSpan::TotalSeconds() const
{
    return m_seconds_ + (m_minutes_ * 60) + (m_hours_ * 3600);
}

ostream &operator<<(ostream &os, const TimeSpan &obj)
{
    os << "Hours: " << obj.hours() << ", Minutes: " << obj.minutes() << ", Seconds: " << obj.seconds();
    return os;
}

istream &operator>>(istream &is, TimeSpan &obj)
{
    int hrs, mins, secs;
    is >> hrs >> mins >> secs;
    obj.SetFromTotalSeconds((hrs*3600) + (mins * 60) + secs);
    return is;
}

TimeSpan TimeSpan::operator+(const TimeSpan &obj)
{
    return TimeSpan(TotalSeconds() + obj.TotalSeconds());
}

TimeSpan TimeSpan::operator-(const TimeSpan &obj)
{
    return TimeSpan(TotalSeconds() - obj.TotalSeconds());
};

TimeSpan TimeSpan::operator++(const int secondAdd)
{
    SetFromTotalSeconds(TotalSeconds() + secondAdd);
    return *this;
};
TimeSpan TimeSpan::operator--(const int secondRemove)
{
    SetFromTotalSeconds(TotalSeconds() - secondRemove);
    return *this;
}

TimeSpan TimeSpan::operator-=(const TimeSpan &obj)
{
    SetFromTotalSeconds(TotalSeconds() - obj.TotalSeconds());
    return *this;
};

TimeSpan TimeSpan::operator+=(const TimeSpan &obj)
{
    SetFromTotalSeconds(TotalSeconds() + obj.TotalSeconds());
    return *this;
};

bool TimeSpan::operator==(const TimeSpan &obj)
{
    return TotalSeconds() == obj.TotalSeconds();
};

bool TimeSpan::operator!=(const TimeSpan &obj)
{
    return TotalSeconds() != obj.TotalSeconds();
};

bool TimeSpan::operator<=(const TimeSpan &obj)
{
    return TotalSeconds() <= obj.TotalSeconds();
};

bool TimeSpan::operator>=(const TimeSpan &obj)
{
    return TotalSeconds() >= obj.TotalSeconds();
};

bool TimeSpan::operator<(const TimeSpan &obj)
{
    return TotalSeconds() < obj.TotalSeconds();
};

bool TimeSpan::operator>(const TimeSpan &obj)
{
    return TotalSeconds() > obj.TotalSeconds();
};
