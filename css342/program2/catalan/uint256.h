#ifndef UINT256_H_
#define UINT256_H_
#include <iostream>
#include <bitset>
using namespace std;

const bool KDEBUG = true;
class UInt256
{
public:
    UInt256();
    UInt256(const UInt256 &other);
    UInt256(__uint128_t value);
    UInt256(__uint128_t high, __uint128_t low);

    bool operator<(const UInt256 &other) const;
    bool operator<(const __uint128_t value) const;
    bool operator()(const UInt256 &other, const UInt256 &other2) const;

    UInt256 &operator+=(const UInt256 &other);
    UInt256 &operator+(const UInt256 &other) const;
    UInt256 &operator+(const __uint128_t &other) const;
    UInt256 &operator++(int value);

    UInt256 &operator-(const UInt256 &other);
    UInt256 &operator+(const __uint128_t value);

    bool operator==(const UInt256 &other) const;
    bool operator==(const __uint128_t value) const;
    bool operator!=(const UInt256 &other) const;
    bool operator!=(const __uint128_t value) const;

    UInt256 operator*(const UInt256 &other);

    friend ostream &operator<<(ostream &os, const UInt256 &obj);

    UInt256 operator<<(int shift) const;
    UInt256 operator>>(int shift) const;
    UInt256 operator&(const UInt256 &other) const;

    bitset<256> GetBitSet() const;

    static UInt256 GetBitwiseAndValue();

    __uint128_t high() const;
    __uint128_t low() const;

private:
    __uint128_t low_;
    __uint128_t high_;
};

#endif // UINT256_H_