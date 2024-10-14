#ifndef UINT256_H_
#define UINT256_H_
#include <iostream>
using namespace std;

const bool KDEBUG = false;
class UInt256
{
public:
    UInt256();
    UInt256(const UInt256 &other);
    UInt256(__uint128_t value);
    UInt256(__uint128_t high, __uint128_t low);

    bool operator<(const UInt256 &other) const;
    bool operator<(const __uint128_t value) const;
    bool operator() (const UInt256 &other, const UInt256 &other2) const;

    UInt256 &operator+=(const UInt256 &other);
    UInt256 &operator++(int value);

    UInt256 &operator-(const UInt256 &other);
    UInt256 &operator+(const __uint128_t value);

    bool operator==(const UInt256 &other);
    bool operator==(const __uint128_t value);
    bool operator!=(const UInt256 &other);
    bool operator!=(const __uint128_t value);

    UInt256 operator*(const UInt256 &other);

    friend ostream &operator<<(ostream &os, UInt256 &obj);

private:
    __uint128_t high_;
    __uint128_t low_;
};

#endif // UINT256_H_