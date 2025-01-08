#ifndef SOTRED_LIST_H_
#define SOTRED_LIST_H_
#include <vector>
using namespace std;

template <class T>
class SortedList
{
public:
    SortedList();
    void Add(const T &obj);
    void Print() const;
    void Sort();
private:
    vector<T> list_;
    void swap(T &obj1, T &obj2);
};
#include "sorted_list.cpp"
#endif // SOTRED_LIST_H_
