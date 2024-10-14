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

UInt256 &UInt256::operator+(const UInt256 &other) const
{
    UInt256 tmp(*this);
    return tmp += other;
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

bool UInt256::operator==(const __uint128_t value) const
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

UInt256 UInt256::operator<<(int shift) const
{
    UInt256 tmp;
    tmp.high_ = high_ << shift;
    tmp.low_ = low_;
    for (int i = 0; i < shift; i++)
    {
        if (tmp.low_ >> 127 == 1)
        {
            tmp.high_++;
        }
        tmp.low_ <<= 1;
        tmp.high_ <<= 1;
    }
    return tmp;
}

UInt256 UInt256::operator>>(int shift) const
{
    UInt256 tmp;
    tmp.high_ = high_;
    tmp.low_ = low_ >> shift;
    __uint128_t mask = 1;
    __uint128_t digitAdder = 1;
    digitAdder <<= 127;

    for (int i = 0; i < shift; i++)
    {
        if (tmp.high_ & mask == 1)
        {
            tmp.low_ |= digitAdder;
        }
        tmp.high_ >>= 1;
        tmp.low_ >>= 1;
    }
    return tmp;
}

UInt256 UInt256::operator&(const UInt256 &other) const
{
    return UInt256(high_ & other.high_, low_ & other.low_);
}

bitset<256> UInt256::GetBitSet() const
{
    unsigned long long high_highPart = high_ >> 64;
    unsigned long long high_LowPart = high_ & 0xFFFFFFFFFFFFFFFF;
    unsigned long long low_highPart = low_ >> 64;
    unsigned long long low_LowPart = low_ & 0xFFFFFFFFFFFFFFFF;
    bitset<256> tmp;
    tmp |= high_highPart;
    tmp <<= 64;
    tmp |= high_LowPart;
    tmp <<= 64;
    tmp |= low_highPart;
    tmp <<= 64;
    tmp |= low_LowPart;

    /* if (KDEBUG)
    {
        cout << "Hex Value:" << hex << setw(16) << setfill('0') << high_highPart << setw(16) << setfill('0') << high_LowPart;
        cout << hex << setw(16) << setfill('0') << low_highPart << setw(16) << setfill('0') << low_LowPart << "\n";
    } */
    return tmp;
}

UInt256 UInt256::GetBitAndValue()
{
    __uint128_t tmp = ULLONG_MAX;
    tmp <<= 64;
    tmp |= ULLONG_MAX;
    return UInt256(0, tmp);
}
__uint128_t UInt256::high()
{
    return high_;
}

__uint128_t UInt256::low()
{
    return low_;
}

UInt256::UInt256(__uint128_t high, __uint128_t low)
{
    high_ = high;
    low_ = low;
}

bool UInt256::operator!=(const UInt256 &other) const
{
    return !(*this == other);
}

bool UInt256::operator!=(const __uint128_t value) const
{
    return !(*this == value);
}

bool UInt256::operator()(const UInt256 &other, const UInt256 &other2) const
{
    return other < other2;
}

string addStringDec256(string base, string add)
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

ostream &operator<<(ostream &os, const UInt256 &obj)
{
    bitset<256> set = obj.GetBitSet();
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
            currentValue = addStringDec256(currentValue, currentAdd);
        }
        currentAdd = addStringDec256(currentAdd, currentAdd);
    }
    reverse(currentValue.begin(), currentValue.end());
    os << currentValue;
    return os;
}
