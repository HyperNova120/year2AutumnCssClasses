
#include <iostream>

using namespace std;

long recursiveFunc(long h, long b)
{
    if (h == 1)
    {
        return 1;
    }
    return b * recursiveFunc(h-1,b);
}



int main()
{
    cout << recursiveFunc(5, 5) << endl;
}