#include "uint256.h"
#include <iomanip>
#include <bitset>
#include <cmath>
#include <climits>
#include <algorithm>
UInt256::UInt256()
{
    low_ = 0;
    high_ = 0;
}

UInt256::UInt256(const UInt256 &other)
{
    low_ = other.low_;
    high_ = other.high_;
}

UInt256::UInt256(Kbase_type_ value)
{
    low_ = value;
    high_ = 0;
}

UInt256::UInt256(Kbase_type_ high, Kbase_type_ low)
{
    high_ = high;
    low_ = low;
}

bool UInt256::operator<(const UInt256 &other) const
{
    return (high_ == other.high_) ? low_ < other.low_ : high_ < other.high_;
}

bool UInt256::operator<(const Kbase_type_ value) const
{
    return low_ < value;
}

UInt256 &UInt256::operator+=(const UInt256 &other)
{
    Kbase_type_ old_low = low_;
    low_ += other.low_;
    high_ += other.high_;
    if (low_ < old_low)
    {
        high_++;
    }
    return *this;
}

UInt256 UInt256::operator+(const UInt256 &other) const
{
    UInt256 tmp(*this);
    return tmp += other;
}

UInt256 UInt256::operator+(const Kbase_type_ &value) const
{
    UInt256 tmp(*this + UInt256(value));
    return tmp;
}

UInt256 &UInt256::operator++(int value)
{
    *this += UInt256(1);
    return *this;
}

UInt256 UInt256::operator+(const Kbase_type_ value)
{
    return *this += UInt256(value);
}

bool UInt256::operator==(const Kbase_type_ value) const
{
    return high_ == 0 && low_ == value;
}

bool UInt256::operator==(const UInt256 &other) const
{
    return high_ == other.high_ && low_ == other.low_;
}

UInt256 UInt256::operator*(const UInt256 &other)
{
    // low bits
    // low bits (KBase_Size / 2) most significant bits
    Kbase_type_ low_upper = low_ >> Khalf_base_size;
    // low bits (KBase_Size / 2) least significant bits
    Kbase_type_ low_lower = low_ & 0xFFFFFFFFFFFFFFFF;

    // other low bits
    // high bits (KBase_Size / 2) most significant bits
    Kbase_type_ other_low_upper = other.low_ >> Khalf_base_size;
    // high bits (KBase_Size / 2) least significant bits
    Kbase_type_ other_low_lower = other.low_ & 0xFFFFFFFFFFFFFFFF;

    Kbase_type_ TU_OU = low_upper * other_low_upper;
    Kbase_type_ TU_OL = low_upper * other_low_lower;
    Kbase_type_ OU_TL = other_low_upper * low_lower;
    Kbase_type_ OL_TL = other_low_lower * low_lower;

    Kbase_type_ tmp = (TU_OL & 0xFFFFFFFFFFFFFFFF) << Khalf_base_size;
    Kbase_type_ tmp2 = (OU_TL & 0xFFFFFFFFFFFFFFFF) << Khalf_base_size;

    long cc = ((tmp + tmp2) < tmp);
    tmp += tmp2;
    cc += ((tmp + OL_TL) < tmp);
    Kbase_type_ carry = (TU_OU) + (TU_OL >> Khalf_base_size) + (OU_TL >> Khalf_base_size);
    return UInt256(this->high_ * other.low_ + this->low_ * other.high_ + carry + cc, tmp + OL_TL);
}

UInt256 UInt256::operator<<(int shift) const
{
    UInt256 tmp(high_, low_);
    if (shift < Kbase_size_)
    {
        tmp.high_ <<= shift;
        tmp.high_ |= (tmp.low_ >> (Kbase_size_ - shift));
        tmp.low_ <<= shift;
    }
    else
    {
        tmp.high_ = tmp.low_;
        tmp.high_ <<= shift - Kbase_size_;
        tmp.low_ = 0;
    }
    return tmp;
}

UInt256 UInt256::operator>>(int shift) const
{
    UInt256 tmp(high_, low_);
    if (shift < Kbase_size_)
    {
        tmp.low_ >>= shift;
        tmp.low_ |= (tmp.high_ << (Kbase_size_ - shift));
        tmp.high_ >>= shift;
    }
    else
    {
        tmp.low_ = tmp.high_;
        tmp.low_ >>= shift - Kbase_size_;
        tmp.high_ = 0;
    }
    return tmp;
}

UInt256 &UInt256::operator<<=(int shift)
{
    if (shift < Kbase_size_)
    {
        high_ <<= shift;
        high_ |= (low_ >> (Kbase_size_ - shift));
        low_ <<= shift;
    }
    else
    {
        high_ = low_;
        high_ <<= shift - Kbase_size_;
        low_ = 0;
    }
    return *this;
}

UInt256 &UInt256::operator>>=(int shift)
{
    if (shift < Kbase_size_)
    {
        low_ >>= shift;
        low_ |= (high_ << (Kbase_size_ - shift));
        high_ >>= shift;
    }
    else
    {
        low_ = high_;
        low_ >>= shift - Kbase_size_;
        high_ = 0;
    }
    return *this;
}

UInt256 UInt256::operator&(const UInt256 &other) const
{
    return UInt256(high_ & other.high_, low_ & other.low_);
}

UInt256 &UInt256::operator|=(const UInt256 &other)
{
    high_ |= other.high_;
    low_ |= other.low_;
    return *this;
}

bitset<UInt256::Kbase_size_ * 2> UInt256::GetBitSet() const
{
    unsigned long long high_high_part = high_ >> Khalf_base_size;
    unsigned long long high_Low_part = high_ & 0xFFFFFFFFFFFFFFFF;
    unsigned long long low_high_part = low_ >> Khalf_base_size;
    unsigned long long low_low_part = low_ & 0xFFFFFFFFFFFFFFFF;
    bitset<Kbase_size_ * 2> tmp;
    tmp |= high_high_part;
    tmp <<= Khalf_base_size;
    tmp |= high_Low_part;
    tmp <<= Khalf_base_size;
    tmp |= low_high_part;
    tmp <<= Khalf_base_size;
    tmp |= low_low_part;
    return tmp;
}

UInt256 UInt256::GetBitwiseAndValue()
{
    Kbase_type_ tmp = ULLONG_MAX;
    tmp <<= Khalf_base_size;
    tmp |= ULLONG_MAX;
    return UInt256(0, tmp);
}

UInt256::Kbase_type_ UInt256::high() const
{
    return high_;
}

UInt256::Kbase_type_ UInt256::low() const
{
    return low_;
}

bool UInt256::operator!=(const UInt256 &other) const
{
    return !(*this == other);
}

bool UInt256::operator!=(const Kbase_type_ value) const
{
    return !(*this == value);
}

bool UInt256::operator()(const UInt256 &other, const UInt256 &other2) const
{
    return other < other2;
}

string addStringDec(string base, string add)
{
    string current_value = "";
    int carry = 0;
    int max_length = max(base.length(), add.length());
    for (int i = 0; i < max_length; i++)
    {
        int base_at = (i < base.length()) ? base[i] - '0' : 0;
        int add_at = (i < add.length()) ? add[i] - '0' : 0;

        int tmp = base_at + add_at + carry;
        carry = 0;
        if (tmp > 9)
        {
            tmp -= 10;
            carry++;
        }
        current_value = current_value + to_string(tmp);
    }
    if (carry != 0)
    {
        current_value = current_value + "1";
    }
    return current_value;
}

ostream &operator<<(ostream &os, const UInt256 &obj)
{
    bitset<UInt256::Kbase_size_ * 2> set = obj.GetBitSet();
    if (KDEBUG)
    {
        os << "set after bitops:" << set << "\n";
    }
    string current_add = "1";
    string current_value = "0";
    for (int i = 0; i < set.size(); i++)
    {
        if (set[i] == 1)
        {
            current_value = addStringDec(current_value, current_add);
        }
        current_add = addStringDec(current_add, current_add);
    }
    reverse(current_value.begin(), current_value.end());
    os << current_value;
    return os;
}

UInt256 &UInt256::operator=(const UInt256 &other)
{
    low_ = other.low_;
    high_ = other.high_;
    return *this;
}
