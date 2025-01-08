#include <iostream>

using namespace std;

bool isPalindrome(string chars)
{
    for (int i = 0; i < chars.length()/2; i++)
    {
        //cout << "test:" << chars[i] << ":" << chars[chars.length()-1-i] << endl;
        if (chars[i] != chars[chars.length()-1-i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << "intput a word:";
    string word;
    cin >> word;
    if (isPalindrome(word))
    {
        cout << "true" << endl;
    }
    else 
    {
        cout << "false" << endl;
    }
}