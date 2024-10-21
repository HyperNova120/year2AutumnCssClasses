#ifndef UInt512_H_
#define UInt512_H_
#include <iostream>
#include <bitset>
#include "uint256.h"
#include <chrono>
#include <ctime>
using namespace std;

class UInt512
{
public:
    using Kbase_type_ = UInt256;
    static const int Kbase_size_ = 256;
    static const int Khalf_base_size = Kbase_size_ / 2;

    UInt512();
    UInt512(const UInt512 &other);
    UInt512(Kbase_type_ value);
    UInt512(__uint128_t value);
    UInt512(Kbase_type_ high, Kbase_type_ low);

    bool operator<(const UInt512 &other) const;
    bool operator<(const __uint128_t value) const;
    bool operator()(const UInt512 &other, const UInt512 &other2) const;

    UInt512 &operator+=(const UInt512 &other);
    UInt512 operator*(const UInt512 &other);

    friend ostream &operator<<(ostream &os, const UInt512 &obj);

    bitset<512> GetBitSet() const;

    Kbase_type_ high() const;
    Kbase_type_ low() const;

private:
    Kbase_type_ low_;
    Kbase_type_ high_;
};

#endif // UInt512_H_