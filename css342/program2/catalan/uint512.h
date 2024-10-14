#ifndef UInt512_H_
#define UInt512_H_
#include <iostream>
#include <bitset>
#include "uint256.h"
using namespace std;

class UInt512
{
public:
    UInt512();
    UInt512(const UInt512 &other);
    UInt512(UInt256 value);
    UInt512(__uint128_t value);
    UInt512(UInt256 high, UInt256 low);

    bool operator<(const UInt512 &other) const;
    bool operator<(const UInt256 value) const;
    bool operator()(const UInt512 &other, const UInt512 &other2) const;

    UInt512 &operator+=(const UInt512 &other);
    UInt512 &operator+(const UInt512 &other) const;
    UInt512 &operator++(int value);

    UInt512 &operator-(const UInt512 &other);
    UInt512 &operator+(const UInt256 value);

    bool operator==(const UInt512 &other) const;
    bool operator==(const UInt256 value) const;
    bool operator!=(const UInt512 &other) const;
    bool operator!=(const UInt256 value) const;

    UInt512 operator*(const UInt512 &other);

    friend ostream &operator<<(ostream &os, UInt512 &obj);

    UInt512 operator<<(int shift) const;
    UInt512 operator>>(int shift) const;
    UInt512 operator&(const UInt512 &other) const;

    bitset<512> GetBitSet() const;

    static UInt512 GetBitAndValue();

    UInt256 high() const;
    UInt256 low() const;

private:
    UInt256 low_;
    UInt256 high_;
};

#endif // UInt512_H_