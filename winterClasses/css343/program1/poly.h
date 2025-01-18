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
    void ChangeSize(const long newArraySize); //increases size of heap array if newArraySize > arraySize

    long *coeffPtr = nullptr; //ptr to array
    long arraySize = 0; //array size

public:
    Poly(); //default constructor
    Poly(const long coeff); //sets constant coeff
    Poly(long coeff, long exp); //sets coeff of exp
    Poly(const Poly &other); //deep copy 
    ~Poly(); //deconstructor

    long getCoeff(const long exp) const; //returns coeff of exp, 0 if invalid exp
    void setCoeff(const long coeff, const long exp); //sets coeff of exp, does nothing if exp < 0

    Poly operator+(const Poly &other) const; //adds other 
    Poly operator-(const Poly &other) const; //subtracts other
    Poly operator*(const Poly &other) const; //multiplies other
    bool operator==(const Poly &other) const; //returns equality of other
    bool operator!=(const Poly &other) const; //returns not equality of other
 
    Poly &operator+=(const Poly &other); //adds other to this
    Poly &operator-=(const Poly &other); //subracts other from this
    Poly &operator*=(const Poly &other); //multiplies other to this
    Poly &operator=(const Poly &other); //sets this to deep copy of other

    friend ostream &operator<<(ostream &os, const Poly &obj); //returns string expressing poly
    friend istream &operator>>(istream &is, Poly &obj); //sets this based on input
};

#endif //_POLY_H_