#include "rational_number.h"

RationalNumber::RationalNumber()
{
    set_value(0, 1);
}

RationalNumber::RationalNumber(int num, int den)
{
    set_value(num, den);
}

bool RationalNumber::set_value(int num, int den)
{
    if (den == 0)
    {
        return false;
    }
    num_ = num;
    den_ = den;
    reduce();
    return true;
}

int RationalNumber::denominator() const
{
    return den_;
}

int RationalNumber::numerator() const
{
    return num_;
}

void RationalNumber::reduce()
{
    double min = abs(fmin(num_, den_));
    double max = abs(fmax(num_, den_));
    int GCF = 0;
    for (int i = min; i > 1; i--)
    {
        if ((max / i) == (int)(max / i) && (min / i) == (int)(min / i))
        {
            GCF = i;
            break;
        }
    }
    if (GCF == 0)
    {
        return;
    }
    num_ = num_ / GCF;
    den_ = den_ / GCF;
    if (den_ < 0 && num_ < 0)
    {
        num_ *= -1;
        den_ *= -1;
    }
}

ostream &operator<<(ostream &os, RationalNumber &obj)
{
    os << obj.num_ << "/" << obj.den_;
    return os;
}

RationalNumber RationalNumber::operator*(const RationalNumber &other) const
{
    RationalNumber returner(num_ * other.num_, den_ * other.den_);
    return returner;
}

RationalNumber RationalNumber::operator/(const RationalNumber &other) const
{
    RationalNumber returner(num_ * other.den_, den_ * other.num_);
    return returner;
}

RationalNumber RationalNumber::operator+(const RationalNumber &other) const
{
    int tmpNum, tmpDen, tmpOtherNum;
    tmpNum = num_ * other.den_;
    tmpOtherNum = den_ * other.num_;
    tmpDen = den_ * other.den_;
    RationalNumber returner(tmpNum + tmpOtherNum, tmpDen);
    return returner;
}

RationalNumber RationalNumber::operator-(const RationalNumber &other) const
{
    int tmpNum, tmpDen, tmpOtherNum;
    tmpNum = num_ * other.den_;
    tmpOtherNum = den_ * other.num_;
    tmpDen = den_ * other.den_;
    RationalNumber returner(tmpNum - tmpOtherNum, tmpDen);
    return returner;
}

bool RationalNumber::operator>(const RationalNumber &other) const
{
    int tmpNum, tmpDen, tmpOtherNum;
    tmpNum = num_ * other.den_;
    tmpOtherNum = den_ * other.num_;
    return tmpNum > tmpOtherNum;
}

bool RationalNumber::operator<(const RationalNumber &other) const
{
    int tmpNum, tmpDen, tmpOtherNum;
    tmpNum = num_ * other.den_;
    tmpOtherNum = den_ * other.num_;
    return tmpNum < tmpOtherNum;
}

bool RationalNumber::operator>=(const RationalNumber &other) const
{
    int tmpNum, tmpDen, tmpOtherNum;
    tmpNum = num_ * other.den_;
    tmpOtherNum = den_ * other.num_;
    return tmpNum >= tmpOtherNum;
}

bool RationalNumber::operator<=(const RationalNumber &other) const
{
    int tmpNum, tmpDen, tmpOtherNum;
    tmpNum = num_ * other.den_;
    tmpOtherNum = den_ * other.num_;
    return tmpNum <= tmpOtherNum;
}

bool RationalNumber::operator==(const RationalNumber &other) const
{
    return num_ == other.num_ && den_ == other.den_;
}

bool RationalNumber::operator!=(const RationalNumber &other) const
{
    return num_ != other.num_ || den_ != other.den_;
}
