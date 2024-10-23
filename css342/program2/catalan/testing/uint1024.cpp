#include "uint256.h"
#include "uint1024.h"
#include <iomanip>
#include <bitset>
#include <cmath>
#include <climits>
#include <algorithm>
UInt1024::UInt1024()
{
    low_ = 0;
    high_ = 0;
    bitwise_and_mask_ = Kbase_type_::GetBitwiseAndValue();
}

UInt1024::UInt1024(const UInt1024 &other)
{
    low_ = other.low_;
    high_ = other.high_;
    bitwise_and_mask_ = Kbase_type_::GetBitwiseAndValue();
}

UInt1024::UInt1024(__uint128_t value)
{
    low_ = value;
    high_ = 0;
    bitwise_and_mask_ = Kbase_type_::GetBitwiseAndValue();
}

UInt1024::UInt1024(Kbase_type_ high, Kbase_type_ low)
{
    high_ = high;
    low_ = low;
    bitwise_and_mask_ = Kbase_type_::GetBitwiseAndValue();
}

bool UInt1024::operator<(const UInt1024 &other) const
{
    return (high_ == other.high_) ? low_ < other.low_ : high_ < other.high_;
}

bool UInt1024::operator<(const __uint128_t value) const
{
    return high_ == 0 && low_ < value;
}

UInt1024 &UInt1024::operator+=(const UInt1024 &other)
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

UInt1024 UInt1024::operator+(const UInt1024 &other) const
{
    UInt1024 tmp(*this);
    return tmp += other;
}

UInt1024 UInt1024::operator+(const __uint128_t &value) const
{
    UInt1024 tmp(*this + UInt1024(value));
    return tmp;
}

UInt1024 &UInt1024::operator++(int value)
{
    *this += UInt1024(1);
    return *this;
}

bool UInt1024::operator==(const __uint128_t value) const
{
    return high_ == 0 && low_ == value;
}

bool UInt1024::operator==(const UInt1024 &other) const
{
    return high_ == other.high_ && low_ == other.low_;
}

UInt1024 UInt1024::operator*(const UInt1024 &other)
{
    // low bits
    // low bits (KBase_Size / 2) most significant bits
    Kbase_type_ low_upper = low_ >> Khalf_base_size;
    // low bits (KBase_Size / 2) least significant bits
    Kbase_type_ low_lower = low_ & bitwise_and_mask_;

    // other low bits
    // high bits (KBase_Size / 2) most significant bits
    Kbase_type_ other_low_upper = other.low_ >> Khalf_base_size;
    // high bits (KBase_Size / 2) least significant bits
    Kbase_type_ other_low_lower = other.low_ & bitwise_and_mask_;

    Kbase_type_ TU_OU = low_upper * other_low_upper;
    Kbase_type_ TU_OL = low_upper * other_low_lower;
    Kbase_type_ OU_TL = other_low_upper * low_lower;
    Kbase_type_ OL_TL = other_low_lower * low_lower;

    Kbase_type_ tmp = (TU_OL & bitwise_and_mask_) << Khalf_base_size;
    Kbase_type_ tmp2 = (OU_TL & bitwise_and_mask_) << Khalf_base_size;

    long cc = ((tmp + tmp2) < tmp);
    tmp += tmp2;
    cc += ((tmp + OL_TL) < tmp);
    Kbase_type_ carry = (TU_OU) + (TU_OL >> Khalf_base_size) + (OU_TL >> Khalf_base_size);
    return UInt1024(this->high_ * other.low_ + this->low_ * other.high_ + carry + cc, tmp + OL_TL);
}

UInt1024 UInt1024::operator<<(int shift) const
{
    UInt1024 tmp(high_, low_);
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

UInt1024 UInt1024::operator>>(int shift) const
{
    UInt1024 tmp(high_, low_);
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

UInt1024 &UInt1024::operator<<=(int shift)
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

UInt1024 &UInt1024::operator>>=(int shift)
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

UInt1024 UInt1024::operator&(const UInt1024 &other) const
{
    return UInt1024(high_ & other.high_, low_ & other.low_);
}

UInt1024 &UInt1024::operator|=(const UInt1024 &other)
{
    high_ |= other.high_;
    low_ |= other.low_;
    return *this;
}

bitset<UInt1024::Kbase_size_ * 2> UInt1024::GetBitSet() const
{
    bitset<Kbase_size_> lower_bit_set(low_.GetBitSet());
    bitset<Kbase_size_> higher_bit_set(high_.GetBitSet());
    bitset<Kbase_size_ * 2> tmp;
    for (ulong i = 0; i < lower_bit_set.size(); i++)
    {
        tmp[i] = lower_bit_set[i];
        tmp[i + Kbase_size_] = higher_bit_set[i];
    }
    return tmp;
}

UInt1024 UInt1024::GetBitwiseAndValue()
{
    __uint128_t tmp = ULLONG_MAX;
    tmp <<= 64;
    tmp |= ULLONG_MAX;
    return UInt1024(0, UInt512(UInt256(tmp, tmp), UInt256(tmp, tmp)));
}

UInt1024::Kbase_type_ UInt1024::high() const
{
    return high_;
}

UInt1024::Kbase_type_ UInt1024::low() const
{
    return low_;
}

bool UInt1024::operator!=(const UInt1024 &other) const
{
    return !(*this == other);
}

bool UInt1024::operator!=(const __uint128_t value) const
{
    return !(*this == value);
}

bool UInt1024::operator()(const UInt1024 &other, const UInt1024 &other2) const
{
    return other < other2;
}

ostream &operator<<(ostream &os, const UInt1024 &obj)
{
    bitset<UInt1024::Kbase_size_ * 2> set = obj.GetBitSet();
    if (KDEBUG)
    {
        os << "set after bitops:" << set << "\n";
    }
    string current_add = "1";
    string current_value = "0";
    for (ulong i = 0; i < set.size(); i++)
    {
        if (set[i] == 1)
        {
            current_value = addStringDec(current_value, current_add);
            if (KDEBUG)
            {
                cout << "ADD VALUE:" << i << endl;
            }
        }
        current_add = addStringDec(current_add, current_add);
    }
    reverse(current_value.begin(), current_value.end());
    os << current_value;
    return os;
}

UInt1024 &UInt1024::operator=(const UInt1024 &other)
{
    low_ = other.low_;
    high_ = other.high_;
    return *this;
}
