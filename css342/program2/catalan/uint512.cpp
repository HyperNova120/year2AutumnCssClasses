#include "uint512.h"
#include <bitset>
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

UInt512::UInt512(Kbase_type_ value)
{
    low_ = value;
    high_ = 0;
}

UInt512::UInt512(__uint128_t value)
{
    high_ = 0;
    low_ = Kbase_type_(value);
}

UInt512::UInt512(Kbase_type_ high, Kbase_type_ low)
{
    high_ = high;
    low_ = low;
}

bool UInt512::operator<(const UInt512 &other) const
{
    return (high_ == other.high_) ? low_ < other.low_ : high_ < other.high_;
}

bool UInt512::operator<(const __uint128_t value) const
{
    return low_ < value;
}

UInt512 &UInt512::operator+=(const UInt512 &other)
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

UInt512 UInt512::operator*(const UInt512 &other)
{
    Kbase_type_ mask = Kbase_type_::GetBitwiseAndValue();
    // low bits
    // low bits (KBase_Size / 2) most significant bits
    Kbase_type_ low_upper = low_ >> (Kbase_size_ / 2);
    // low bits (KBase_Size / 2) least significant bits
    Kbase_type_ low_lower = low_ & mask;

    // other low bits
    // high bits (KBase_Size / 2) most significant bits
    Kbase_type_ other_low_upper = other.low_ >> (Kbase_size_ / 2);
    // high bits (KBase_Size / 2) least significant bits
    Kbase_type_ other_low_lower = other.low_ & mask;

    // KBase_Type TU_OU = low_Upper * other_low_Upper;
    Kbase_type_ TU_OL = low_upper * other_low_lower;
    Kbase_type_ OU_TL = other_low_upper * low_lower;
    Kbase_type_ OL_TL = other_low_lower * low_lower;

    Kbase_type_ tmp = (TU_OL & mask) << (Kbase_size_ / 2);
    Kbase_type_ tmp2 = (OU_TL & mask) << (Kbase_size_ / 2);

    long cc = ((tmp + tmp2) < tmp);
    tmp += tmp2;
    cc += ((tmp + OL_TL) < tmp);
    Kbase_type_ carry = low_upper * other_low_upper;
    carry += (TU_OL >> (Kbase_size_ / 2));
    carry += (OU_TL >> (Kbase_size_ / 2));

    return UInt512((this->high_ * other.low_) + (this->low_ * other.high_) + carry + cc, tmp += OL_TL);
}

bitset<512> UInt512::GetBitSet() const
{
    bitset<Kbase_size_> lower_bit_set(low_.GetBitSet());
    bitset<Kbase_size_> higher_bit_set(high_.GetBitSet());
    bitset<512> tmp;
    for (int i = 0; i < lower_bit_set.size(); i++)
    {
        tmp[i] = lower_bit_set[i];
    }

    for (int i = 0; i < higher_bit_set.size(); i++)
    {
        tmp[i + Kbase_size_] = higher_bit_set[i];
    }
    return tmp;
}

UInt512::Kbase_type_ UInt512::high() const
{
    return high_;
}

UInt512::Kbase_type_ UInt512::low() const
{
    return low_;
}
bool UInt512::operator()(const UInt512 &other, const UInt512 &other2) const
{
    return other < other2;
}
ostream &operator<<(ostream &os, const UInt512 &obj)
{
    bitset<512> set = obj.GetBitSet();
    if (KDEBUG)
    {
        os << "Bits:" << set << "\n";
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
