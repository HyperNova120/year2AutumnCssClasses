#include "uint512.h"
#include <iomanip>
#include <bitset>
#include <cmath>
#include <climits>
#include <algorithm>
UInt512::UInt512()
{
    low_ = 0;
    high_ = 0;
}

UInt512::UInt512(const UInt512 &other)
{
    low_ = other.low_;
    high_ = other.high_;
}

UInt512::UInt512(UInt256 value)
{
    low_ = value;
    high_ = 0;
}

UInt512::UInt512(__uint128_t value)
{
    high_ = 0;
    low_ = UInt256(value);
}

bool UInt512::operator<(const UInt512 &other) const
{
    return (high_ == other.high_) ? low_ < other.low_ : high_ < other.high_;
}

bool UInt512::operator<(const UInt256 value) const
{
    return low_ < value;
}

UInt512 &UInt512::operator+=(const UInt512 &other)
{
    UInt256 old_low = low_;
    low_ += other.low_;
    high_ += other.high_;
    if (low_ < old_low)
    {
        high_++;
    }
    return *this;
}

UInt512 &UInt512::operator+(const UInt512 &other) const
{
    UInt512 tmp(*this);
    return tmp += other;
}

UInt512 &UInt512::operator++(int value)
{
    *this += UInt512(1);
    return *this;
}

UInt512 &UInt512::operator+(const UInt256 value)
{
    return *this += UInt512(value);
}

bool UInt512::operator==(const UInt256 value) const
{
    return high_ == 0 && low_ == value;
}

bool UInt512::operator==(const UInt512 &other) const
{
    return high_ == other.high_ && low_ == other.low_;
}

UInt512 UInt512::operator*(const UInt512 &other)
{
    // low bits
    // low bits 128 most significant bits
    UInt256 low_Upper = low_ >> 128;
    // low bits 128 least significant bits
    UInt256 low_Lower = low_ & UInt256::GetBitwiseAndValue();

    // other low bits
    // high bits 128 most significant bits
    UInt256 other_low_Upper = other.low_ >> 128;
    // high bits 128 least significant bits
    UInt256 other_low_Lower = other.low_ & UInt256::GetBitwiseAndValue();

    UInt256 TU_OU = low_Upper * other_low_Upper;
    UInt256 TU_OL = low_Upper * other_low_Lower;
    UInt256 OU_TL = other_low_Upper * low_Lower;
    UInt256 OL_TL = other_low_Lower * low_Lower;

    UInt256 tmp = (TU_OL & UInt256::GetBitwiseAndValue()) << 128;
    UInt256 tmp2 = (OU_TL & UInt256::GetBitwiseAndValue()) << 128;

    long cc = ((tmp + tmp2) < tmp);
    tmp += tmp2;
    cc += ((tmp + OL_TL) < tmp);
    UInt256 carry = TU_OU;
    carry += (TU_OL >> 128);
    carry += (OU_TL >> 128);

    UInt256 tempHigh(this->high_ * other.low_);
    tempHigh += (this->low_ * other.high_);
    tempHigh += carry;
    tempHigh += cc;
    UInt256 tempLow(tmp);
    tempLow += OL_TL;

    return UInt512(tempHigh, tempLow);
}

UInt512 UInt512::operator<<(int shift) const
{
    UInt512 tmp;
    tmp.high_ = high_ << shift;
    tmp.low_ = low_;
    for (int i = 0; i < shift; i++)
    {
        if (tmp.low_ >> 256 == 1)
        {
            tmp.high_ = tmp.high_ << 1;
            tmp.high_++;
        }
        tmp.low_ = tmp.low_ << 1;
    }
    return tmp;
}

UInt512 UInt512::operator>>(int shift) const
{
    UInt512 tmp;
    tmp.high_ = high_;
    tmp.low_ = low_ >> shift;
    UInt256 mask = 1;
    UInt256 digitAdder = 1;
    digitAdder = digitAdder << 256;

    for (int i = 0; i < shift; i++)
    {
        if ((tmp.high_ & mask) == 1)
        {
            tmp.low_ = tmp.low_ >> 1;
            tmp.low_ += digitAdder;
        }
        tmp.high_ = tmp.high_ >> 1;
    }
    return tmp;
}

UInt512 UInt512::operator&(const UInt512 &other) const
{
    return UInt512(high_ & other.high_, low_ & other.low_);
}

bitset<512> UInt512::GetBitSet() const
{
    bitset<256> lowerBitSet(low_.GetBitSet());
    bitset<256> HigherBitSet(high_.GetBitSet());
    bitset<512> tmp;
    for (int i = 0; i < lowerBitSet.size(); i++)
    {
        tmp[i] = lowerBitSet[i];
    }

    for (int i = 0; i < HigherBitSet.size(); i++)
    {
        tmp[i + 256] = HigherBitSet[i];
    }

    /* cout << "Hex Value:";
    for (int i = tmp.size()-1; i >= 0; i--)
    {
        cout << tmp[i];
    }
    cout << endl; */

    return tmp;
}

UInt512 UInt512::GetBitAndValue()
{
    UInt256 tmp(ULLONG_MAX, ULLONG_MAX);
    return UInt512(0, tmp);
}

UInt256 UInt512::high() const
{
    return high_;
}

UInt256 UInt512::low() const
{
    return low_;
}

UInt512::UInt512(UInt256 high, UInt256 low)
{
    high_ = high;
    low_ = low;
}

bool UInt512::operator!=(const UInt512 &other) const
{
    return !(*this == other);
}

bool UInt512::operator!=(const UInt256 value) const
{
    return !(*this == value);
}

bool UInt512::operator()(const UInt512 &other, const UInt512 &other2) const
{
    return other < other2;
}

string addStringDec512(string base, string add)
{
    string currentValue = "";
    int carry = 0;
    int maxLength = max(base.length(), add.length());
    for (int i = 0; i < maxLength; i++)
    {
        int baseAt = (i < base.length()) ? base[i] - '0' : 0;
        int addAt = (i < add.length()) ? add[i] - '0' : 0;

        int tmp = baseAt + addAt + carry;
        carry = 0;
        if (tmp > 9)
        {
            tmp -= 10;
            carry++;
        }
        currentValue = currentValue + to_string(tmp);
    }
    if (carry != 0)
    {
        currentValue = currentValue + "1";
    }
    return currentValue;
}

ostream &operator<<(ostream &os, UInt512 &obj)
{
    bitset<512> set = obj.GetBitSet();
    if (KDEBUG)
    {
        os << "Set:" << set << "\n";
    }
    string currentAdd = "1";
    string currentValue = "0";
    for (int i = 0; i < set.size(); i++)
    {
        if (set[i] == 1)
        {
            currentValue = addStringDec512(currentValue, currentAdd);
        }
        currentAdd = addStringDec512(currentAdd, currentAdd);
    }
    reverse(currentValue.begin(), currentValue.end());
    os << currentValue;
    return os;
}
