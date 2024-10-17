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
    using KBase_Type = UInt256;
    static const int KBase_Size = 256;

    UInt512();
    UInt512(const UInt512 &other);
    UInt512(KBase_Type value);
    UInt512(__uint128_t value);
    UInt512(KBase_Type high, KBase_Type low);

    bool operator<(const UInt512 &other) const;
    bool operator<(const __uint128_t value) const;
    bool operator()(const UInt512 &other, const UInt512 &other2) const;

    UInt512 &operator+=(const UInt512 &other);
    UInt512 operator*(const UInt512 &other);

    friend ostream &operator<<(ostream &os, const UInt512 &obj);

    bitset<512> GetBitSet() const;

    KBase_Type high() const;
    KBase_Type low() const;

private:
    KBase_Type low_;
    KBase_Type high_;
};

#endif // UInt512_H_