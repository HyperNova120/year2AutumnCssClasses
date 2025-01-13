#include "poly.h"

Poly::Poly()
{
    setCoeff(0, 0);
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
        coeff = 0;
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
    coeffPtr = nullptr;
    arraySize = 0;
}

int Poly::getCoeff(int exp)
{
    if (arraySize <= exp || exp < 0)
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

    if (arraySize <= exp)
    {
        ChangeSize(exp + 1);
    }
    *(coeffPtr + exp) = coeff;
}

Poly &Poly::operator=(const Poly &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->~Poly();
    ChangeSize(other.arraySize);
    for (int i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(other.coeffPtr + i);
    }
    return *this;
}

void Poly::ChangeSize(int newArraySize)
{
    if (arraySize == newArraySize)
    {
        return;
    }
    int *tmpPtr = new int[newArraySize];
    for (int i = 0; i < newArraySize; i++)
    {
        *(tmpPtr + i) = 0;
    }
    for (int i = 0; i < arraySize; i++)
    {
        *(tmpPtr + i) = *(coeffPtr + i);
    }

    arraySize = newArraySize;
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
        if (*(coeffPtr + i) != *(other.coeffPtr + i))
        {
            return false;
        }
    }

    return true;
}

bool Poly::operator!=(const Poly &other) const
{
    return !(*this == other);
}

Poly &Poly::operator+=(const Poly &other)
{
    int maxSize = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    ChangeSize(maxSize);
    for (int i = 0; i < other.arraySize; i++)
    {
        *(coeffPtr + i) = *(coeffPtr + i) + *(other.coeffPtr + i);
    }
    return *this;
}

Poly &Poly::operator-=(const Poly &other)
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

Poly &Poly::operator*=(const Poly &other)
{
    Poly tmp(other); //ensures functionality if &other == &this; 
    int *tmpPtr = coeffPtr;
    coeffPtr = nullptr;
    int tmpArraySize = arraySize;
    this->~Poly();

    for (int i = 0; i < tmpArraySize; i++)
    {
        for (int j = 0; j < tmp.arraySize; j++)
        {
            int coeff = *(tmpPtr + i) * *(tmp.coeffPtr + j);
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
    for (int i = obj.arraySize; i >= 0; i--)
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

        adder += to_string(*(obj.coeffPtr + i));

        // handle how x and exp are printed
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

    // if all coeff were 0
    if (output.size() == 0)
    {
        output = " 0";
    }
    os << output;
    return os;
}

istream &operator>>(istream &is, Poly &obj)
{
    obj.~Poly();
    int coeff = 0;
    int exp = 0;
    while (!(coeff == -1 && exp == -1))
    {
        try
        {
            is >> coeff >> exp;
            obj.setCoeff(coeff, exp);
        }
        catch (exception &e)
        {
            return is;
        }
    }
    return is;
}
