#include "time_span.h"

// constructors
TimeSpan::TimeSpan()
{
    hours_ = 0;
    minutes_ = 0;
    seconds_ = 0;
}

TimeSpan::TimeSpan(double secondsin)
{
    SetFromTotalSeconds(secondsin);
}

TimeSpan::TimeSpan(double minutesin, double secondsin) : TimeSpan(secondsin + (minutesin * 60)) {}

TimeSpan::TimeSpan(double hoursin, double minutesin, double secondsin) : TimeSpan(minutesin + (hoursin * 60), secondsin) {}

void TimeSpan::set_time(int hoursin, int minutesin, int secondsin)
{
    SetFromTotalSeconds((hoursin * 3600) + (minutesin * 60) + secondsin);
}

// getters
int TimeSpan::hours() const
{
    return hours_;
}

int TimeSpan::minutes() const
{
    return minutes_;
}

int TimeSpan::seconds() const
{
    return seconds_;
}

// i/ostream operator overloads
ostream &operator<<(ostream &os, const TimeSpan &obj)
{
    os << "Hours: " << obj.hours() << ", Minutes: " << obj.minutes() << ", Seconds: " << obj.seconds();
    return os;
}

// takes istream input as int int int
istream &operator>>(istream &is, TimeSpan &obj)
{
    int hrs, mins, secs;
    is >> hrs >> mins >> secs;
    obj.SetFromTotalSeconds((hrs * 3600) + (mins * 60) + secs);
    return is;
}

// operator overloads
TimeSpan TimeSpan::operator+(const TimeSpan &obj) const
{
    return TimeSpan(TotalSeconds() + obj.TotalSeconds());
}

TimeSpan TimeSpan::operator-(const TimeSpan &obj) const
{
    return TimeSpan(TotalSeconds() - obj.TotalSeconds());
};

TimeSpan TimeSpan::operator-() const
{
    return TimeSpan(TotalSeconds() * -1);
}

TimeSpan TimeSpan::operator++(const int secondAdd)
{
    SetFromTotalSeconds(TotalSeconds() + 1);
    return *this;
};

TimeSpan TimeSpan::operator--(const int secondRemove)
{
    SetFromTotalSeconds(TotalSeconds() - 1);
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

bool TimeSpan::operator==(const TimeSpan &obj) const
{
    return TotalSeconds() == obj.TotalSeconds();
};

bool TimeSpan::operator!=(const TimeSpan &obj) const
{
    return TotalSeconds() != obj.TotalSeconds();
};

bool TimeSpan::operator<=(const TimeSpan &obj) const
{
    return TotalSeconds() <= obj.TotalSeconds();
};

bool TimeSpan::operator>=(const TimeSpan &obj) const
{
    return TotalSeconds() >= obj.TotalSeconds();
};

bool TimeSpan::operator<(const TimeSpan &obj) const
{
    return TotalSeconds() < obj.TotalSeconds();
};

bool TimeSpan::operator>(const TimeSpan &obj) const
{
    return TotalSeconds() > obj.TotalSeconds();
};

// private functions

// converts a number of seconds to appropriate # of hrs and mins using
// conversion ratios of 3600sec:1hr and 60sec:1min
void TimeSpan::SetFromTotalSeconds(double totalSeconds)
{
    int secIn = round(totalSeconds);
    hours_ = secIn / 3600;
    secIn = secIn % 3600;
    minutes_ = secIn / 60;
    seconds_ = secIn % 60;
}

int TimeSpan::TotalSeconds() const
{
    return seconds_ + (minutes_ * 60) + (hours_ * 3600);
}
