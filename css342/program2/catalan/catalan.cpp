#include "catalan.h"

UInt512 Catalan::FindCatalanNumber(int n)
{
    
    if (n == 0)
    {
        return 1;
    }
    else if (known_numbers_.find(n) != known_numbers_.end())
    {
        // cout << "known number" << endl;
        debug_lookups_++;
        return known_numbers_[n];
    }

    debug_calculations_++;
    UInt512 sum_ = 0;
    for (int i = 0; i < n; i++)
    {
        sum_ += FindCatalanNumber(i) * FindCatalanNumber((n - 1) - i);
    }
    known_numbers_[n] = sum_;
    return sum_;
}

Catalan::Catalan(int n)
{
    if (n < 0)
    {
        cout << "Catalan: Malformed Input; Cannot Be Negative" << endl;
        return;
    }
    else if (n > 262 && !KDEBUG) // yes this has been tested, 512bit is big enough to be correct until n=262
    {
        cout << "Catalan: Input Too Large, Will Cause Overflow" << endl;
        return;
    }
}


long Catalan::debug_calculations()
{
    return debug_calculations_;
}

long Catalan::debug_lookups()
{
    return debug_lookups_;
}



int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "Catalan: Malformed Input; Missing Input Parameters" << endl;
        return -1;
    }
    else if (argc > 2)
    {
        cout << "Catalan: Malformed Input; Too Many Input Parameters" << endl;
        return -1;
    }

    int n;
    try
    {
        n = stoi(argv[1]);
    }
    catch(const std::exception& e)
    {
        cout << "Catalan: Malformed Input; Input Must Be Integer" << endl;
    }
    

    Catalan finder(n);

    chrono::system_clock::time_point start;

    if (KDEBUG)
    {
        start = chrono::system_clock::now();
    }

    UInt512 result = finder.FindCatalanNumber(n);

    if (KDEBUG)
    {
        chrono::system_clock::time_point end = chrono::system_clock::now();
        cout << "lookups to Calculations:" << finder.debug_lookups() << "/" << finder.debug_calculations() << " Ratio:" << ((double)finder.debug_lookups() / (double)finder.debug_calculations()) << ":1" << endl;
        cout << "Calculation Time:" << ((end) - start).count() / 1000000.0 << "ms" << endl;
    }

    cout << result << endl;
    return 0;
}


