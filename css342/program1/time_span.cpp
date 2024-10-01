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
    m_hours_ = hoursin;
    m_minutes_ = minutesin;
    m_seconds_ = secondsin;
}

int TimeSpan::SetFromTotalSeconds(double totalSeconds)
{
    int secIn = round(totalSeconds);
    int hr = secIn / 3600;
    secIn = secIn % 3600;
    int min = secIn / 60;
    secIn = secIn % 60;
    set_time(hr, min, secIn);
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

istream &operator>>(istream &is, const TimeSpan &obj)
{
    int hrs, mins, secs;
    is >> obj.m_hours_ >> obj.m_minutes_ >> obj.m_seconds_;
    return is;
}

TimeSpan TimeSpan::operator+(const TimeSpan &obj)
{
    return TimeSpan(m_hours_ + obj.hours(), m_minutes_ + obj.minutes(), m_seconds_ + obj.seconds());
}

TimeSpan TimeSpan::operator++(const int secondAdd)
{
    SetFromTotalSeconds(TotalSeconds() + secondAdd);
};
TimeSpan TimeSpan::operator--(const int secondRemove)
{
    SetFromTotalSeconds(TotalSeconds() - secondRemove);
}

TimeSpan TimeSpan::operator-(const TimeSpan &obj)
{
    this->m_hours_ -= obj.hours();
    this->m_minutes_ -= obj.minutes();
    this->m_seconds_ -= obj.seconds();
    return *this;
};

TimeSpan TimeSpan::operator-=(const TimeSpan &obj)
{
    this->m_hours_ -= obj.hours();
    this->m_minutes_ -= obj.minutes();
    this->m_seconds_ -= obj.seconds();
    return *this;
};

TimeSpan TimeSpan::operator+=(const TimeSpan &obj)
{
    this->m_hours_ += obj.hours();
    this->m_minutes_ += obj.minutes();
    this->m_seconds_ += obj.seconds();
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
