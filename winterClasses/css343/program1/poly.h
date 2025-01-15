#ifndef _POLY_H_
#define _POLY_H_
// ------------------------------------------------ file name -------------------------------------------------------
// Aidan Messmer, CSS343A
// Creation Date: 9/1/25
// Date of Last ModificationL 14/1/25
// --------------------------------------------------------------------------------------------------------------------
// Purpose - represent a polynomial, handle operating overloading, printing,
//    and input as polynomial
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//    non-negative exponents, polynomial stored as an heap allocated array
//
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>

using namespace std;

class Poly
{

private:
    void ChangeSize(const long expToSizeTo);

    long *coeffPtr = nullptr;
    long arraySize = 0;

public:
    Poly();
    Poly(const long coeff);
    Poly(long coeff, long exp);
    Poly(const Poly &other);
    ~Poly();

    long getCoeff(const long exp) const;
    void setCoeff(const long coeff, const long exp);

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
};

#endif //_POLY_H_