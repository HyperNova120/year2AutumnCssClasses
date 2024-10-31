#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <map>
using namespace std;

int main()
{
    cout << "INT:" << numeric_limits<int>::min() << "," << numeric_limits<int>::max() << endl;
    cout << "unsigned INT:" << numeric_limits<unsigned int>::min() << "," << numeric_limits<unsigned int>::max() << endl;
    cout << "long:" << numeric_limits<long>::min() << "," << numeric_limits<long>::max() << endl;
    cout << "double:" << numeric_limits<double>::min() << "," << numeric_limits<double>::max() << endl;
    cout << "float:" << numeric_limits<float>::min() << "," << numeric_limits<float>::max() << endl;

    vector<int> vec(5);
    for (int i = 0; i < 5; i++)
    {
        vec[i] = ((i * 2) % 2 == 0) ? i * 2 : (i * 2) + 1;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        vec.push_back(((i * 2) % 2 == 0) ? i * 2 - 1 : (i * 2));
    }
    sort(vec.begin(), vec.end());
    cout << "after sort:" << endl;
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << endl;
    }

    list<int> intList;
    for (int i = 1; i <= 9; i += 2)
    {
        intList.push_back(i);
    }
    for (int i = 2; i <= 10; i += 2)
    {
        intList.push_front(i);
    }
    cout << "int list:" << endl;
    for (int n : intList)
    {
        cout << n << endl;
    }
    list<int>::iterator itr = intList.begin();
    advance(itr, 3);
    intList.erase(itr);
    intList.sort();
    cout << "int list sorted:" << endl;
    for (int n : intList)
    {
        cout << n << endl;
    }
    intList.remove_if([](int n) {return n%2==1;});
    cout << "int removed:" << endl;
    for (int n : intList)
    {
        cout << n << endl;
    }

    map<string, int> stringIntMap;
    stringIntMap["one"] = 1;
    stringIntMap["two"] = 2;
    stringIntMap["three"] = 3;
    stringIntMap["four"] = 4;
    stringIntMap["five"] = 5;
    for (auto m : stringIntMap)
    {
        cout << m.first << ":" << m.second << endl;
    }
    stringIntMap.insert(pair<string,int>("five",6));
    stringIntMap.insert(pair<string,int>("six",6));
    stringIntMap["five"] = 4;
    stringIntMap["eight"] = 7;
    for (auto m : stringIntMap)
    {
        cout << m.first << ":" << m.second << endl;
    }
}