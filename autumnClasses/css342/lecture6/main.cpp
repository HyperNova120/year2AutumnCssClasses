
#include <iostream>
#include <vector>
using namespace std;

long recursiveFunc(long h, long b)
{
    if (h == 1)
    {
        return 1;
    }
    return b * recursiveFunc(h - 1, b);
}

int main()
{
    vector<int> vec = {1,4,5,6,7,43,64,24,65,24,76,2145};
    int target = 222;
}