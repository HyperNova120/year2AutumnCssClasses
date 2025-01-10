#include "poly.h"

Poly::Poly()
{
    coeffPtr = nullptr;
    arraySize = 0;
}

Poly::Poly(int coeff)
{
    setCoeff(coeff, 0);
}

Poly::Poly(int coeff, int exp)
{
    if (exp < 0)
    {
        exp = 0;
    }
    setCoeff(coeff, exp);
}

Poly::Poly(const Poly &other)
{
    *this = other;
}

Poly::~Poly()
{
    delete[] coeffPtr;
    arraySize = 0;
}

int Poly::getCoeff(int exp)
{
    if (arraySize < exp)
    {
        return 0;
    }
    return *(coeffPtr + exp);
}

void Poly::setCoeff(int coeff, int exp)
{
    if (exp < 0)
    {
        return;
    }

    if (arraySize < exp)
    {
        ChangeSize(exp);
    }
    *(coeffPtr + exp) = coeff;
}

Poly Poly::operator=(const Poly &other)
{
    this->~Poly();
    ChangeSize(other.arraySize);
    for (int i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(other.coeffPtr + i);
    }
    return *this;
}

void Poly::ChangeSize(int expToSizeTo)
{
    if (arraySize == expToSizeTo)
    {
        return;
    }
    int *tmpPtr = new int[expToSizeTo];
    for (int i = 0; i < expToSizeTo; i++)
    {
        *(tmpPtr + i) = 0;
    }
    for (int i = 0; i < arraySize; i++)
    {
        *(tmpPtr + i) = *(coeffPtr + i);
    }

    arraySize = expToSizeTo;
    delete[] coeffPtr;
    coeffPtr = tmpPtr;
}

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

    for (int i = 0; i < arraySize; i++)
    {
        if (*(coeffPtr) != *(other.coeffPtr))
        {
            return false;
        }
    }

    return true;
}

bool Poly::operator!=(const Poly &other) const
{
    return *this == other;
}

Poly Poly::operator+=(const Poly &other)
{
    int maxSize = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    ChangeSize(maxSize);
    for (int i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(coeffPtr + i) + *(other.coeffPtr + i);
    }
    return *this;
}

Poly Poly::operator-=(const Poly &other)
{
    int maxSize = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    ChangeSize(maxSize);
    for (int i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(coeffPtr + i) - *(other.coeffPtr + i);
    }
    return *this;
}

Poly Poly::operator+(const Poly &other) const
{
    return Poly(*this) += other;
}

Poly Poly::operator-(const Poly &other) const
{
    return Poly(*this) -= other;
}

Poly Poly::operator*(const Poly &other) const
{
    return Poly(*this) *= other;
}

Poly Poly::operator*=(const Poly &other)
{
    int *tmpPtr = coeffPtr;
    int tmpArraySize = arraySize;
    this->~Poly();

    for (int i = 0; i < tmpArraySize; i++)
    {
        for (int j = 0; j < other.arraySize; j++)
        {
            int coeff = *(tmpPtr + i) * *(other.coeffPtr + j);
            int exp = i + j;
            Poly tmp(coeff, exp);
            *this += tmp;
        }
    }
    delete[] tmpPtr;
    return *this;
}

ostream &operator<<(ostream &os, const Poly &obj)
{
    string output = "";
    for (int i = obj.arraySize; i > 0; i--)
    {
        if (*(obj.coeffPtr) == 0)
        {
            continue;
        }
        string adder = " +";
        if (*(obj.coeffPtr) < 0)
        {
            adder = " -";
        }
        adder += to_string(*(obj.coeffPtr));
        if (i == 1)
        {
            adder += "x";
        }
        else if (i != 0)
        {
            adder += "x^" + to_string(i);
        }
        output += adder;
    }
    os << output;
    return os;
}
