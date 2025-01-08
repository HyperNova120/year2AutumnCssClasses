#include <iostream>
#include <math.h>
using namespace std;

int myRoundingFunction(double num)
{
    if (num >= 0)
    {
        if ((double)num - (int)num < 0.5)
        {
            return (int)num;
        }
        return (int)num + 1;
    }
    else
    {
        num *= -1;
        if ((double)num - (int)num < 0.5)
        {
            return -(int)num;
        }
        return -((int)num + 1);
    }
}

bool test(double num)
{
    return myRoundingFunction(num) == round(num);
}

int main()
{
    cout << "TESTING 0.5 " << myRoundingFunction(0.5) << endl;
    cout << "TESTING 0.4 " << myRoundingFunction(0.4) << endl;
    cout << "TESTING 1.5 " << myRoundingFunction(1.5) << endl;
    cout << "TESTING 1.4 " << myRoundingFunction(0.4) << endl;
    cout << "TESTING -0.5 " << myRoundingFunction(-0.5) << endl;
    cout << "TESTING -0.4 " << myRoundingFunction(-0.4) << endl;
    cout << "TESTING -1.5 " << myRoundingFunction(-1.5) << endl;
    cout << "TESTING -1.4 " << myRoundingFunction(-1.4) << endl;
    for (float i = -10.0; i <= 10.0; i += 0.1)
    {
        if (!test(i))
        {
            cout << "TEST FAIL: " << i << endl;
        }
        else
        {
            cout << "TEST PASS: " << i << endl;
        }
    }
}
