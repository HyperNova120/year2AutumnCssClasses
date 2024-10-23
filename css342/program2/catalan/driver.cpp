#include <iostream>
#include "catalan.h"
using namespace std;

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

    stringstream ss;
    ss << argv[1];
    int n;
    ss >> n;

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