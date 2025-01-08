/*
 *  Square.cpp
 *  Class-example
 *
 */

#include "Square.h"

void Square::setSize(int newSize)
{
   theSize = newSize;
}


int Square::getSize(void) const
{
   return theSize;
}

Square& Square::operator = (const Square& other)
{
	theSize = other.getSize();
	return *this;
}

bool Square::operator<(const Square &other)
{
   return theSize < other.theSize;
}

ostream &operator<<(ostream &os, const Square &other)
{
    os << other.theSize;
    return os;
}
