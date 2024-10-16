#include "sorted_list.h"
#include <iostream>

int main()
{
    SortedList<string> names;
    SortedList<int> ages;

    names.Add("joe");
    names.Add("josh");
    ages.Add(42);
    ages.Add(43);
    ages.Add(29);
    ages.Add(8);

    names.Print();
    ages.Print();
    ages.Sort();
    ages.Print();
}
