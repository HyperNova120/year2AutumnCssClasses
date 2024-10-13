#include <iostream>
#include <map>
#include <sstream>

using namespace std;

map<__uint128_t, __uint128_t> knownNumbers_;

__uint128_t FindCatalanNumber(__uint128_t n)
{
    if (n == 0)
    {
        return 1;
    }

    if (knownNumbers_.find(n) != knownNumbers_.end())
    {
        // cout << "known number" << endl;
        return knownNumbers_[n];
    }

    __uint128_t sum_ = 0;
    for (__uint128_t i = 0; i < n; i++)
    {
        sum_ += FindCatalanNumber(i) * FindCatalanNumber((n - 1) - i);
    }
    knownNumbers_[n] = sum_;
    return sum_;
}

ostream &operator<<(std::ostream &dest, __uint128_t value)
{
    std::ostream::sentry s(dest);
    if (s)
    {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do
        {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0)
        {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len)
        {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Catalan: Malformed Input; Missing Input Parameter" << endl;
        return -1;
    }

    stringstream ss;
    ss << argv[1];
    int n_;
    ss >> n_;

    if (n_ < 0)
    {
        cout << "Catalan: Malformed Input; Cannot Be Negative" << endl;
        return -1;
    }
    else if (n_ > 69)
    {
        cout << "Catalan: Input Too Large, Will Cause Overflow" << endl;
        return -1;
    }

    cout << FindCatalanNumber(n_) << endl;
}