//file poly.cpp
#include "poly.h"

//---------------------------------------------------------
//constructor
//default constructor 
Poly::Poly()
{
    setCoeff(0, 0);
}

//---------------------------------------------------------
//constructor
//sets poly constant 
Poly::Poly(const long coeff)
{
    setCoeff(coeff, 0);
}

//---------------------------------------------------------
//constructor
//sets coeff for exp
Poly::Poly(long coeff, long exp)
{
    if (exp < 0)
    {
        exp = 0;
        coeff = 0;
    }
    setCoeff(coeff, exp);
}

//---------------------------------------------------------
//constructor
//copy constructor
Poly::Poly(const Poly &other)
{
    *this = other;
}

//---------------------------------------------------------
//deconstructor constructor
//deconstructs poly
Poly::~Poly()
{
    delete[] coeffPtr;
    coeffPtr = nullptr;
    arraySize = 0;
}

//---------------------------------------------------------
//method
//returns ceoff of exp, 0 if exp invalid
long Poly::getCoeff(const long exp) const
{
    if (arraySize <= exp || exp < 0)
    {
        return 0;
    }
    return *(coeffPtr + exp);
}

//---------------------------------------------------------
//method
// sets coeff of exp, does nothing if exp invalid
void Poly::setCoeff(const long coeff, const long exp)
{
    if (exp < 0)
    {
        return;
    }

    if (arraySize <= exp)
    {
        ChangeSize(exp + 1);
    }
    *(coeffPtr + exp) = coeff;
}

//---------------------------------------------------------
//assignment overload
//makes deep copy of other
Poly &Poly::operator=(const Poly &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->~Poly();
    ChangeSize(other.arraySize);
    for (long i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(other.coeffPtr + i);
    }
    return *this;
}

//---------------------------------------------------------
//method
//increases internal array size to newArraySize if arraySize is <
void Poly::ChangeSize(const long newArraySize)
{
    if (arraySize >= newArraySize)
    {
        return;
    }
    long *tmpPtr = new long[newArraySize];
    //set array to default as 0
    for (long i = 0; i < newArraySize; i++)
    {
        *(tmpPtr + i) = 0;
    }
    //copy old arrya over
    int sizeToCopy = (arraySize < newArraySize) ? arraySize : newArraySize;
    for (long i = 0; i < sizeToCopy; i++)
    {
        *(tmpPtr + i) = *(coeffPtr + i);
    }

    arraySize = newArraySize;
    delete[] coeffPtr;
    coeffPtr = tmpPtr;
}

//---------------------------------------------------------
//equivalence overload
// returns true if other is equal to this
bool Poly::operator==(const Poly &other) const
{
    if (coeffPtr == other.coeffPtr)
    {
        return true;
    }
    else if (arraySize != other.arraySize)
    {
        return false;
    }

    for (long i = 0; i < arraySize; i++)
    {
        if (*(coeffPtr + i) != *(other.coeffPtr + i))
        {
            return false;
        }
    }

    return true;
}

//---------------------------------------------------------
//not equivalence overload
// returns true if other not equal to this
bool Poly::operator!=(const Poly &other) const
{
    return !(*this == other);
}

//---------------------------------------------------------
//addition assignment overload
//adds other to this
Poly &Poly::operator+=(const Poly &other)
{
    long maxSize = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    ChangeSize(maxSize);
    for (long i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(coeffPtr + i) + *(other.coeffPtr + i);
    }
    return *this;
}

//---------------------------------------------------------
//subtraction assignment overload
// subtracts other from this
Poly &Poly::operator-=(const Poly &other)
{
    long maxSize = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    ChangeSize(maxSize);
    for (long i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(coeffPtr + i) - *(other.coeffPtr + i);
    }
    return *this;
}

//---------------------------------------------------------
//addition overload
// reutrns new poly with other added to this
Poly Poly::operator+(const Poly &other) const
{
    return Poly(*this) += other;
}

//---------------------------------------------------------
//subtraction overload
// returns new poly with other subracted from this
Poly Poly::operator-(const Poly &other) const
{
    return Poly(*this) -= other;
}

//---------------------------------------------------------
//multiplication overload
// returns new poly with other multiplied by this
Poly Poly::operator*(const Poly &other) const
{
    return Poly(*this) *= other;
}

//---------------------------------------------------------
//multiplication assignment overload
// sets this to the product of other and this
Poly &Poly::operator*=(const Poly &other)
{
    Poly tmp(other); // ensures functionality if &other == &this;
    long *tmpPtr = coeffPtr;
    coeffPtr = nullptr;
    long tmpArraySize = arraySize;
    this->~Poly();

    for (long i = 0; i < tmpArraySize; i++)
    {
        for (long j = 0; j < tmp.arraySize; j++)
        {
            long coeff = *(tmpPtr + i) * *(tmp.coeffPtr + j);
            long exp = i + j;
            Poly tmp2(coeff, exp);
            *this += tmp2;
        }
    }
    delete[] tmpPtr;
    return *this;
}

//---------------------------------------------------------
//ostream overload
// prints obj in form of +ax^2 +bx +c
ostream &operator<<(ostream &os, const Poly &obj)
{
    string output = "";
    for (long i = obj.arraySize-1; i >= 0; i--)
    {
        if (*(obj.coeffPtr + i) == 0)
        {
            continue;
        }

        string adder = " ";

        if (*(obj.coeffPtr + i) > 0)
        {
            adder += "+";
        }

        // add coeff value
        adder += to_string(*(obj.coeffPtr + i));

        // handle how x and exp are printed
        if (i == 1)
        {
            adder += "x";
        }
        else if (i != 0)
        {
            // add exp value
            adder += "x^" + to_string(i);
        }

        output += adder;
    }

    // if all coeff were 0
    if (output.size() == 0)
    {
        output = " 0";
    }
    os << output;
    return os;
}

//---------------------------------------------------------
//istream overload
// sets obj to given coeff exp sets until -1 -1
istream &operator>>(istream &is, Poly &obj)
{
    obj.~Poly();
    long coeff = 0;
    long exp = 0;
    while (!(coeff == -1 && exp == -1))
    {
        try
        {
            is >> coeff >> exp;
            obj += Poly(coeff, exp);
        }
        catch (exception &e)
        {
            return is;
        }
    }
    return is;
}
