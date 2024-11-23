#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
void swapItems(T &item1, T &item2)
{
    T temp = item1;
    item1 = item2;
    item2 = temp;
};

template <typename T>
bool isValidSortRange(vector<T> &vec, int start, int end)
{
    return start < end && start >= 0 && end < vec.size() && start != end;
}

template <typename T>
void QuickSort(vector<T> &items, int start_index, int end_index)
{
    if (!isValidSortRange(items, start_index, end_index))
    {
        return;
    }

    int middle = 0;
    T pivot = items[start_index];
    int index1 = start_index - 1;
    int index2 = end_index + 1;
    while (true)
    {
        do
        {
            index1++;
        } while (items[index1] < pivot);

        do
        {
            index2--;
        } while (items[index2] > pivot);

        if (index1 >= index2)
        {
            middle = index2;
            break;
        }
        swap(items[index1], items[index2]);
    }
    QuickSort(items, start_index, middle);
    QuickSort(items, middle + 1, end_index);
};

template <typename T>
void MergeSort(vector<T> &items, int start_index, int end_index)
{
    if (!isValidSortRange(items, start_index, end_index))
    {
        return;
    }
    int middle = (end_index - start_index) / 2;
    middle += start_index;
    MergeSort(items, start_index, middle);
    MergeSort(items, middle + 1, end_index);

    int size1 = middle - start_index + 1;
    int size2 = end_index - middle;

    vector<T> first(size1), second(size2);
    for (int i = 0; i < size1; i++)
    {
        first[i] = items[start_index + i];
    }
    for (int i = 0; i < size2; i++)
    {
        second[i] = items[middle + i + 1];
    }

    int index1 = 0;
    int index2 = 0;
    int index = start_index;
    while (index1 < first.size() && index2 < second.size())
    {
        if (first[index1] < second[index2])
        {
            items[index] = first[index1];
            index++;
            index1++;
        }
        else
        {
            items[index] = second[index2];
            index++;
            index2++;
        }
    }
    for (index1; index1 < first.size(); index1++)
    {
        items[index] = first[index1];
        index++;
    }
    for (index2; index2 < second.size(); index2++)
    {
        items[index] = second[index2];
        index++;
    }
};

template <typename T>
void IterativeMergeSort(vector<T> &items, int start_index, int end_index)
{
    if (!isValidSortRange(items, start_index, end_index))
    {
        return;
    }
    vector<T> tmp = items;
    for (int block_size = 1; block_size <= end_index - 1; block_size *= 2)
    {
        // cout << block_size << endl;
        //  creates the block sizes for merge
        for (int left_start = start_index; left_start < end_index; left_start += block_size * 2)
        {
            int right_start = (left_start + block_size <= end_index) ? left_start + block_size : end_index + 1;
            int right_end = (right_start + block_size <= end_index) ? right_start + block_size : end_index + 1;
            // cout << left_start << "," << right_start << "," << right_end << endl;

            int index1 = left_start;
            int index2 = right_start;
            int tmp_index = left_start;
            while (index1 < right_start && index2 < right_end)
            {
                if (items[index1] < items[index2])
                {
                    tmp[tmp_index] = items[index1];
                    tmp_index++;
                    index1++;
                }
                else
                {
                    tmp[tmp_index] = items[index2];
                    tmp_index++;
                    index2++;
                }
            }
            while (index1 < right_start)
            {
                tmp[tmp_index] = items[index1];
                tmp_index++;
                index1++;
            }
            while (index2 < right_end)
            {
                tmp[tmp_index] = items[index2];
                tmp_index++;
                index2++;
            }
        }
        items = tmp;
    }
};

template <typename T>
void BubbleSort(vector<T> &items, int start_index, int end_index)
{
    if (!isValidSortRange(items, start_index, end_index))
    {
        return;
    }
    for (int i = start_index; i < end_index; i++)
    {
        for (int j = start_index; j < end_index; j++)
        {
            if (items[j] > items[j + 1])
            {
                swapItems(items[j], items[j + 1]);
            }
        }
    }
};

template <typename T>
void InsertionSort(vector<T> &items, int start_index, int end_index)
{
    if (!isValidSortRange(items, start_index, end_index))
    {
        return;
    }
    for (int i = start_index + 1; i <= end_index; i++)
    {
        T tmp = items[i];
        for (int j = i - 1; j >= start_index; j--)
        {
            if (items[j] < tmp)
            {
                items[j + 1] = tmp;
                break;
            }
            items[j + 1] = items[j];
            if (j == start_index)
            {
                items[start_index] = tmp;
                break;
            }
        }
    }
};

template <typename T>
void ShellSort(vector<T> &items, int start_index, int end_index)
{
    if (!isValidSortRange(items, start_index, end_index))
    {
        return;
    }
    int n = end_index - start_index + 1;
    for (int inter = n / 2; inter > 0; inter /= 2)
    {
        for (int i = start_index + inter; i <= end_index; i++)
        {
            T tmp = items[i];
            int j;
            for (j = i; (j >= start_index + inter) && (items[j - inter] > tmp); j -= inter)
            {
                items[j] = items[j - inter];
                // items.at(j) = items.at(j - inter);
            }
            items[j] = tmp;
            // items.at(j) = tmp;
        }
    }
};

#endif // SORTS_H_