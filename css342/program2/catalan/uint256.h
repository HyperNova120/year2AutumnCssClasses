#ifndef UINT256_H_
#define UINT256_H_
#include <iostream>
#include <bitset>
using namespace std;

const bool KDEBUG = true;

string addStringDec(string base, string add);

class UInt256
{
public:
    using Kbase_type_ = __uint128_t;
    static const int Kbase_size_ = 128;
    static const int Khalf_base_size = Kbase_size_ / 2;
    UInt256();
    UInt256(const UInt256 &other);
    UInt256(Kbase_type_ value);
    UInt256(Kbase_type_ high, Kbase_type_ low);

    bool operator<(const UInt256 &other) const;
    bool operator<(const Kbase_type_ value) const;
    bool operator()(const UInt256 &other, const UInt256 &other2) const;

    UInt256 &operator+=(const UInt256 &other);
    UInt256 operator+(const UInt256 &other) const;
    UInt256 operator+(const Kbase_type_ &other) const;
    UInt256 &operator++(int value);

    UInt256 operator-(const UInt256 &other);
    UInt256 operator+(const Kbase_type_ value);

    UInt256 &operator=(const UInt256 &other);

    bool operator==(const UInt256 &other) const;
    bool operator==(const Kbase_type_ value) const;
    bool operator!=(const UInt256 &other) const;
    bool operator!=(const Kbase_type_ value) const;

    UInt256 operator*(const UInt256 &other);

    friend ostream &operator<<(ostream &os, const UInt256 &obj);

    UInt256 operator<<(int shift) const;
    UInt256 operator>>(int shift) const;
    UInt256 &operator<<=(int shift);
    UInt256 &operator>>=(int shift);
    UInt256 operator&(const UInt256 &other) const;
    UInt256 &operator|=(const UInt256 &other);

    bitset<256> GetBitSet() const;

    static UInt256 GetBitwiseAndValue();

    Kbase_type_ high() const;
    Kbase_type_ low() const;

private:
    Kbase_type_ low_;
    Kbase_type_ high_;
};

#endif // UINT256_H_