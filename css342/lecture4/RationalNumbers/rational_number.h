#ifndef RADIONAL_NUMBER_H_
#define RADIONAL_NUMBER_H_

#include <iostream>
#include <cmath>
using namespace std;

class RationalNumber
{
public:
    RationalNumber();
    RationalNumber(int numerator, int denominator);

    bool set_value(int numerator, int denominator);

    int numerator() const;
    int denominator() const;

    RationalNumber operator*(const RationalNumber &other) const;
    RationalNumber operator/(const RationalNumber &other) const;
    RationalNumber &operator*=(const RationalNumber &other);
    RationalNumber &operator/=(const RationalNumber &other);
    RationalNumber operator+(const RationalNumber &other) const;
    RationalNumber operator-(const RationalNumber &other) const;
    RationalNumber &operator+=(const RationalNumber &other);
    RationalNumber &operator-=(const RationalNumber &other);

    bool operator>(const RationalNumber &other) const;
    bool operator<(const RationalNumber &other) const;
    bool operator>=(const RationalNumber &other) const;
    bool operator<=(const RationalNumber &other) const;
    bool operator==(const RationalNumber &other) const;
    bool operator!=(const RationalNumber &other) const;

    friend ostream &operator<<(ostream &os, RationalNumber &other);

private:
    int num_;
    int den_;
    void reduce();
};

#endif //RADIONAL_NUMBER_H_