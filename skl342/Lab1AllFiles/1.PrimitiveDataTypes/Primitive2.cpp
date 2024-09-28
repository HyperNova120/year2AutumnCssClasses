/*
 *  Primitive2.cpp
 *
 *  Created by Rob Nash
 *
 *  Modified by Yang Peng on 12/31/17
 */


#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  int a = 3;
  int b, c;
  b = c = 8;
    
  int d = a + b + c;
    
  // What is that "\n" thing?
  std::cout << "Hello, World!\n";

  // Ugly output; how can we improve it a bit?
  cout << "a is " << a;
  cout << "b is " << b;
  cout << "c is " << c;
  cout << "d is " << d;

  // Integer division
  cout << "b/a is " << b/a << endl;
  cout << "a/b is " << a/b << endl;
  cout << "b%a is " << b%a << endl;
  cout << "a%b is " << a%b << endl;

  // Conversion to floating point: try 1
  cout << "double(b/a) is " << double(b/a) << endl;
  cout << "double(a/b) is " << double(a/b) << endl;

  // Conversion to floating point: try 2
  cout << "double(b)/a is " << double(b)/a << endl;
  cout << "double(a)/b is " << double(a)/b << endl;
  // What's the difference?

  // Conversion to floating point: preferred method
  // Says explicitly that you've checked and that this
  // is a safe conversion. No run-time checking done, but
  // the compiler will barf on obviously problematic code.
  cout << "static_cast<double>(b)/a is " << static_cast<double>(b)/a << endl;
  cout << "static_cast<double>(a)/b is " << static_cast<double>(a)/b << endl;

  // Conversion of floating point to integer types: you need to decide
  // what you want to do with the fractional part.
  double e = static_cast<double>(d)/a;
  cout << "e is " << e << endl;
  cout << "ceil(e) is " << ceil(e) << endl;
  cout << "floor(e) is " << floor(e) << endl;
  cout << "trunc(e) is " << trunc(e) << endl;
  cout << "round(e) is " << round(e) << endl;
  cout << "rint(e) is " << rint(e) << endl;
  
  cout << "ceil(-e) is " << ceil(-e) << endl;
  cout << "floor(-e) is " << floor(-e) << endl;
  cout << "trunc(-e) is " << trunc(-e) << endl;
  cout << "round(-e) is " << round(-e) << endl;
  cout << "rint(-e) is " << rint(-e) << endl;
  
  return 0;
}
