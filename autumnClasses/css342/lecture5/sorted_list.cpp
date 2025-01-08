#ifndef SORTED_LIST_CPP_
#define SORTED_LIST_CPP_
#include "sorted_list.h"

#include <iostream>

template <class T>
SortedList<T>::SortedList()
{
}

template <class T>
void SortedList<T>::Add(const T &obj)
{
    list_.push_back(obj);
}

template <class T>
void SortedList<T>::Print() const
{
    for (int i = 0; i < list_.size(); i++)
    {
        cout << list_[i];
        if (i < list_.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
}

template <class T>
void SortedList<T>::Sort()
{
    for (int i = 1; i < list_.size(); i++)
    {
        T temp = list_[i];
        int j = i;
        while ((j > 0) && (list_[j-1] > temp))
        {
            list_[j] = list_[j-1];
            j--;
        }
        list_[j] = temp;
    }
}

template <class T>
inline void SortedList<T>::swap(T &obj1, T &obj2)
{
    T tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

#endif // SORTED_LIST_CPP_
