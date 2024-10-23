#include <iostream>
using namespace std;

bool PrintBase(int num, int base, string &ans)
{
    string static kDigitArray = "0123456789ABCDEF";
    if (num == 0 && base != 2 && base != 16)
    {
        return false;
    }

    if (num < base)
    {
        ans = kDigitArray[num] + ans;
        return true;
    }
    else
    {
        ans = kDigitArray[num % base] + ans;
        PrintBase(num / base, base, ans);
    }
}

int main()
{
    string ans = "";
    PrintBase(255, 16, ans);
    cout << ans << endl;
    return 0;
}
