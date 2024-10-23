#ifndef UINT512_H_
#define UINT512_H_
#include <iostream>
#include "uint256.h"
#include <bitset>
using namespace std;

class UInt512
{
public:
    using Kbase_type_ = UInt256;
    static const int Kbase_size_ = 256;
    static const int Khalf_base_size = Kbase_size_ / 2;

    UInt512();
    UInt512(const UInt512 &other);
    UInt512(__uint128_t value);
    UInt512(Kbase_type_ high, Kbase_type_ low);

    bool operator<(const UInt512 &other) const;
    bool operator<(const __uint128_t value) const;
    bool operator()(const UInt512 &other, const UInt512 &other2) const;

    UInt512 &operator+=(const UInt512 &other);
    UInt512 &operator+=(const __uint128_t &value);
    UInt512 operator+(const UInt512 &other) const;
    UInt512 operator+(const __uint128_t &other) const;
    UInt512 &operator++(int value);

    UInt512 operator-(const UInt512 &other);

    UInt512 &operator=(const UInt512 &other);
    UInt512 &operator=(const __uint128_t &value);

    bool operator==(const UInt512 &other) const;
    bool operator==(const __uint128_t value) const;
    bool operator!=(const UInt512 &other) const;
    bool operator!=(const __uint128_t value) const;

    UInt512 operator*(const UInt512 &other);

    friend ostream &operator<<(ostream &os, const UInt512 &obj);

    UInt512 operator<<(int shift) const;
    UInt512 operator>>(int shift) const;
    UInt512 &operator<<=(int shift);
    UInt512 &operator>>=(int shift);
    UInt512 operator&(const UInt512 &other) const;
    UInt512 &operator|=(const UInt512 &other);

    bitset<Kbase_size_ * 2> GetBitSet() const;

    static UInt512 GetBitwiseAndValue();

    Kbase_type_ high() const;
    Kbase_type_ low() const;

private:
    Kbase_type_ low_;
    Kbase_type_ high_;
    Kbase_type_ bitwise_and_mask_;
};

#endif // UINT512_H_