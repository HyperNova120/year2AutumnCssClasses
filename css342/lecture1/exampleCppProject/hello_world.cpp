#include <iostream>
using namespace std;

int main()
{
    int intOne = 0;
    int intTwo = 0;
    cout << "Int 1:";
    cin >> intOne;
    cout << "Int 2:";
    cin >> intTwo;
    cout << "Result:" << max(intOne, intTwo) << " is the largest"<< endl;

}