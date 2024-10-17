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
    using KBase_Type = __uint128_t;
    static const int KBase_Size = 128;
    UInt256();
    UInt256(const UInt256 &other);
    UInt256(KBase_Type value);
    UInt256(KBase_Type high, KBase_Type low);

    bool operator<(const UInt256 &other) const;
    bool operator<(const KBase_Type value) const;
    bool operator()(const UInt256 &other, const UInt256 &other2) const;

    UInt256 &operator+=(const UInt256 &other);
    UInt256 operator+(const UInt256 &other) const;
    UInt256 operator+(const KBase_Type &other) const;
    UInt256 &operator++(int value);

    UInt256 operator-(const UInt256 &other);
    UInt256 operator+(const KBase_Type value);

    UInt256 &operator=(const UInt256 &other);

    bool operator==(const UInt256 &other) const;
    bool operator==(const KBase_Type value) const;
    bool operator!=(const UInt256 &other) const;
    bool operator!=(const KBase_Type value) const;

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

    KBase_Type high() const;
    KBase_Type low() const;

private:
    KBase_Type low_;
    KBase_Type high_;
};

#endif // UINT256_H_