#include "uint256.h"
#include <iomanip>
#include <bitset>
#include <cmath>
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

UInt256::UInt256(__uint128_t value)
{
    low_ = value;
    high_ = 0;
}

bool UInt256::operator<(const UInt256 &other) const
{
    return (high_ == other.high_) ? low_ < other.low_ : high_ < other.high_;
}

bool UInt256::operator<(const __uint128_t value) const
{
    return low_ < value;
}

UInt256 &UInt256::operator+=(const UInt256 &other)
{
    __uint128_t old_low = low_;
    low_ += other.low_;
    high_ += other.high_;
    if (old_low > low_)
    {
        high_++;
    }
    return *this;
}

UInt256 &UInt256::operator++(int value)
{
    *this += UInt256(1);
    return *this;
}

UInt256 &UInt256::operator+(const __uint128_t value)
{
    return *this += UInt256(value);
}

bool UInt256::operator==(const __uint128_t value)
{
    return high_ == 0 && low_ == value;
}

bool UInt256::operator==(const UInt256 &other)
{
    return high_ == other.high_ && low_ == other.low_;
}

UInt256 UInt256::operator*(const UInt256 &other)
{
    // low bits
    // low bits 64 most significant bits
    __uint128_t low_Upper = low_ >> 64;
    // low bits 64 least significant bits
    __uint128_t low_Lower = low_ & 0xFFFFFFFFFFFFFFFF;

    // other low bits
    // high bits 64 most significant bits
    __uint128_t other_low_Upper = other.low_ >> 64;
    // high bits 64 least significant bits
    __uint128_t other_low_Lower = other.low_ & 0xFFFFFFFFFFFFFFFF;

    __uint128_t TU_OU = low_Upper * other_low_Upper;
    __uint128_t TU_OL = low_Upper * other_low_Lower;
    __uint128_t OU_TL = other_low_Upper * low_Lower;
    __uint128_t OL_TL = other_low_Lower * low_Lower;

    __uint128_t tmp = (TU_OL & 0xFFFFFFFFFFFFFFFF) << 64;
    __uint128_t tmp2 = (OU_TL & 0xFFFFFFFFFFFFFFFF) << 64;

    long cc = ((tmp + tmp2) < tmp);
    tmp += tmp2;
    cc += ((tmp + OL_TL) < tmp);
    __uint128_t carry = TU_OU + (TU_OL >> 64) + (OU_TL >> 64);
    return UInt256(this->high_ * other.low_ + this->low_ * other.high_ + carry + cc, tmp + OL_TL);
}

UInt256::UInt256(__uint128_t high, __uint128_t low)
{
    high_ = high;
    low_ = low;
}

bool UInt256::operator!=(const UInt256 &other)
{
    return !(*this == other);
}

bool UInt256::operator!=(const __uint128_t value)
{
    return !(*this == value);
}

bool UInt256::operator()(const UInt256 &other, const UInt256 &other2) const
{
    return other < other2;
}

string addStringDec(string base, string add)
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

ostream &operator<<(ostream &os, UInt256 &obj)
{
    unsigned long long high_highPart = obj.high_ >> 64;
    unsigned long long high_LowPart = obj.high_ & 0xFFFFFFFFFFFFFFFF;
    unsigned long long low_highPart = obj.low_ >> 64;
    unsigned long long low_LowPart = obj.low_ & 0xFFFFFFFFFFFFFFFF;
    if (KDEBUG)
    {
        os << "Hex Value:" << hex << setw(16) << setfill('0') << high_highPart << setw(16) << setfill('0') << high_LowPart;
        os << hex << setw(16) << setfill('0') << low_highPart << setw(16) << setfill('0') << low_LowPart << "\n";
    }

    bitset<256> set(high_highPart);
    set <<= 192;
    bitset<256> tempSet(high_LowPart);
    tempSet <<= 128;
    bitset<256> tempSet2(low_highPart);
    tempSet2 <<= 64;
    bitset<256> tempSet3(low_LowPart);
    if (KDEBUG)
    {
        //os << "set:             " << set << "\ntempSet:         " << tempSet << "\n";
    }
    set |= tempSet;
    set |= tempSet2;
    set |= tempSet3;
    if (KDEBUG)
    {
        os << "set after bitops:" << set << "\n";
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
