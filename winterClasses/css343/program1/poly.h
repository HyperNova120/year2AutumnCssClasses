#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>

using namespace std;

class Poly
{
public:
    Poly();
    Poly(int coeff);
    Poly(int coeff, int exp);
    Poly(const Poly &other);
    ~Poly();

    int getCoeff(int exp);
    void setCoeff(int coeff, int exp);

    Poly operator+(const Poly &other) const;
    Poly operator-(const Poly &other) const;
    Poly operator*(const Poly &other) const;
    bool operator==(const Poly &other) const;
    bool operator!=(const Poly &other) const;

    Poly &operator+=(const Poly &other);
    Poly &operator-=(const Poly &other);
    Poly &operator*=(const Poly &other);
    Poly &operator=(const Poly &other);

    friend ostream &operator<<(ostream &os, const Poly &obj);
    friend istream &operator>>(istream &is, Poly &obj);

private:
    void ChangeSize(int expToSizeTo);

    int *coeffPtr = nullptr;
    int arraySize = 0;
};

#endif //_POLY_H_