#ifndef UINT1024_H_
#define UINT1024_H_
#include <iostream>
#include "uint256.h"
#include "uint512.h"
#include <bitset>
using namespace std;

class UInt1024
{
public:
    using Kbase_type_ = UInt512;
    static const int Kbase_size_ = 512;
    static const int Khalf_base_size = Kbase_size_ / 2;

    UInt1024();
    UInt1024(const UInt1024 &other);
    UInt1024(__uint128_t value);
    UInt1024(Kbase_type_ high, Kbase_type_ low);

    bool operator<(const UInt1024 &other) const;
    bool operator<(const __uint128_t value) const;
    bool operator()(const UInt1024 &other, const UInt1024 &other2) const;

    UInt1024 &operator+=(const UInt1024 &other);
    UInt1024 operator+(const UInt1024 &other) const;
    UInt1024 operator+(const __uint128_t &other) const;
    UInt1024 &operator++(int value);

    UInt1024 operator-(const UInt1024 &other);

    UInt1024 &operator=(const UInt1024 &other);

    bool operator==(const UInt1024 &other) const;
    bool operator==(const __uint128_t value) const;
    bool operator!=(const UInt1024 &other) const;
    bool operator!=(const __uint128_t value) const;

    UInt1024 operator*(const UInt1024 &other);

    friend ostream &operator<<(ostream &os, const UInt1024 &obj);

    UInt1024 operator<<(int shift) const;
    UInt1024 operator>>(int shift) const;
    UInt1024 &operator<<=(int shift);
    UInt1024 &operator>>=(int shift);
    UInt1024 operator&(const UInt1024 &other) const;
    UInt1024 &operator|=(const UInt1024 &other);

    bitset<Kbase_size_ * 2> GetBitSet() const;

    static UInt1024 GetBitwiseAndValue();

    Kbase_type_ high() const;
    Kbase_type_ low() const;

private:
    Kbase_type_ low_;
    Kbase_type_ high_;
    Kbase_type_ bitwise_and_mask_;
};

#endif // UINT1024_H_