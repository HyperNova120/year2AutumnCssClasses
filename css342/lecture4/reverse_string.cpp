#include <iostream>

using namespace std;

string reverseString(string &str)
{
    string returner = "";
    for (int i = str.length()-1; i >= 0; i--)
    {
        returner += str[i];
    }
    str = returner;
    return returner;
}

int main()
{
    string tmp = "Hello World!";
    cout << reverseString(tmp) << endl;
}