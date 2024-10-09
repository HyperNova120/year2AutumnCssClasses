#include "rational_number.h";


int main()
{
    RationalNumber num1(5, 2);
    cout << num1 << endl;
    RationalNumber num2(14, 2);
    cout << num2 << endl;
    RationalNumber num3(-14, 2);
    cout << num3 << endl;
    RationalNumber num4(14, -2);
    cout << num4 << endl;
    RationalNumber num5(-14, -2);
    cout << num5 << endl;


    RationalNumber test2(1, 2);
    RationalNumber test1(3, 4);

    RationalNumber test3 = test1/test2;
    cout << test3 << endl;

}