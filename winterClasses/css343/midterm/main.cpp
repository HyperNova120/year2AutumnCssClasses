#include <iostream>
using namespace std;

int multiplyEvens(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    int recurseResult = multiplyEvens(n - 1);
    return (2 * n) * ((recurseResult == 0) ? 1 : recurseResult);
}

int main()
{
    cout << multiplyEvens(1) << endl;
    cout << multiplyEvens(4) << endl;
    return 0;
}