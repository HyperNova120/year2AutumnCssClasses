/*
 *  Square.h
 *  Class-example
 *
 */

#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <ostream>
using namespace std;

class Square
{
public:
   void setSize(int newSize);
   int getSize(void) const;
   Square &operator=(const Square &);
   bool operator<(const Square &other);

   friend ostream &operator<<(ostream &os, const Square &other);

private:
   int theSize;
};

#endif
