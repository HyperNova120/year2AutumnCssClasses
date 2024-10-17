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

UInt512::UInt512(KBase_Type value)
{
    low_ = value;
    high_ = 0;
}

UInt512::UInt512(__uint128_t value)
{
    high_ = 0;
    low_ = KBase_Type(value);
}

UInt512::UInt512(KBase_Type high, KBase_Type low)
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
    KBase_Type old_low = low_;
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
    KBase_Type mask = KBase_Type::GetBitwiseAndValue();
    // low bits
    // low bits (KBase_Size / 2) most significant bits
    KBase_Type low_Upper = low_ >> (KBase_Size / 2);
    // low bits (KBase_Size / 2) least significant bits
    KBase_Type low_Lower = low_ & mask;

    // other low bits
    // high bits (KBase_Size / 2) most significant bits
    KBase_Type other_low_Upper = other.low_ >> (KBase_Size / 2);
    // high bits (KBase_Size / 2) least significant bits
    KBase_Type other_low_Lower = other.low_ & mask;

    // KBase_Type TU_OU = low_Upper * other_low_Upper;
    KBase_Type TU_OL = low_Upper * other_low_Lower;
    KBase_Type OU_TL = other_low_Upper * low_Lower;
    KBase_Type OL_TL = other_low_Lower * low_Lower;

    KBase_Type tmp = (TU_OL & mask) << (KBase_Size / 2);
    KBase_Type tmp2 = (OU_TL & mask) << (KBase_Size / 2);

    long cc = ((tmp + tmp2) < tmp);
    tmp += tmp2;
    cc += ((tmp + OL_TL) < tmp);
    KBase_Type carry = low_Upper * other_low_Upper;
    carry += (TU_OL >> (KBase_Size / 2));
    carry += (OU_TL >> (KBase_Size / 2));

    return UInt512((this->high_ * other.low_) + (this->low_ * other.high_) + carry + cc, tmp += OL_TL);
}

bitset<512> UInt512::GetBitSet() const
{
    bitset<KBase_Size> lowerBitSet(low_.GetBitSet());
    bitset<KBase_Size> HigherBitSet(high_.GetBitSet());
    bitset<512> tmp;
    for (int i = 0; i < lowerBitSet.size(); i++)
    {
        tmp[i] = lowerBitSet[i];
    }

    for (int i = 0; i < HigherBitSet.size(); i++)
    {
        tmp[i + KBase_Size] = HigherBitSet[i];
    }
    return tmp;
}

UInt512::KBase_Type UInt512::high() const
{
    return high_;
}

UInt512::KBase_Type UInt512::low() const
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
    string currentAdd = "1";
    string currentValue = "0";
    for (int i = 0; i < set.size(); i++)
    {
        if (set[i] == 1)
        {
            currentValue = addStringDec(currentValue, currentAdd);
        }
        currentAdd = addStringDec(currentAdd, currentAdd);
    }
    reverse(currentValue.begin(), currentValue.end());
    os << currentValue;
    return os;
}
