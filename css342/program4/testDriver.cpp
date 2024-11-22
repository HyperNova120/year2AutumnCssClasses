#include <iostream>
#include <vector>
#include <cmath>
#include "sorts.h"
#include <sys/time.h>
using namespace std;

void print(vector<int> tmp)
{
    for (int i : tmp)
    {
        cout << i << ", ";
    }
    cout << endl;
}

int Elapsed(const timeval &start, const timeval &end)
{
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

void validateSorted(vector<int> vec)
{
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < vec[i - 1])
        {
            throw new exception();
        }
    }
}

void runTest(int size)
{
    vector<int> test;
    for (int i = 0; i < size; i++)
    {
        test.push_back(rand() % 100);
    }
    struct timeval start_time, end_time;
    double time;

    gettimeofday(&start_time, 0);
    QuickSort(test, 0, test.size() - 1);
    gettimeofday(&end_time, 0);
    validateSorted(test);
    time = Elapsed(start_time, end_time);
    time = time / 1000.0;
    cout << time << ",";
    test.clear();
    for (int i = 0; i < size; i++)
    {
        test.push_back(rand() % 100);
    }

    gettimeofday(&start_time, 0);
    IterativeMergeSort(test, 0, test.size() - 1);
    gettimeofday(&end_time, 0);
    validateSorted(test);
    time = Elapsed(start_time, end_time);
    time = time / 1000.0;
    cout << time << ",";
    test.clear();
    for (int i = 0; i < size; i++)
    {
        test.push_back(rand() % 100);
    }

    gettimeofday(&start_time, 0);
    MergeSort(test, 0, test.size() - 1);
    gettimeofday(&end_time, 0);
    validateSorted(test);
    time = Elapsed(start_time, end_time);
    time = time / 1000.0;
    cout << time << ",";
    test.clear();
    for (int i = 0; i < size; i++)
    {
        test.push_back(rand() % 100);
    }

    gettimeofday(&start_time, 0);
    ShellSort(test, 0, test.size() - 1);
    gettimeofday(&end_time, 0);
    validateSorted(test);
    time = Elapsed(start_time, end_time);
    time = time / 1000.0;
    cout << time << ",";
    test.clear();
    for (int i = 0; i < size; i++)
    {
        test.push_back(rand() % 100);
    }


    gettimeofday(&start_time, 0);
    InsertionSort(test, 0, test.size() - 1);
    gettimeofday(&end_time, 0);
    validateSorted(test);
    time = Elapsed(start_time, end_time);
    time = time / 1000.0;
    cout << time << ",";
    test.clear();
    for (int i = 0; i < size; i++)
    {
        test.push_back(rand() % 100);
    }

    gettimeofday(&start_time, 0);
    BubbleSort(test, 0, test.size() - 1);
    gettimeofday(&end_time, 0);
    validateSorted(test);
    time = Elapsed(start_time, end_time);
    time = time / 1000.0;
    cout << time << ",";
    test.clear();
}

int main()
{

    vector<int> test;
    for (int i = 0; i < 10; i++)
    {
        test.push_back(rand() % 100);
    }
    print(test);
    QuickSort(test, 0, test.size() - 1);
    print(test);
    return 0;

    cout << ",QuickSort,IterativeMergeSort,MergeSort,ShellSort,InsertionSort,BubbleSort";
    for (int i = 100; i <= 1000; i += 100)
    {
        cout << endl;
        cout << i << ",";
        runTest(i);
    }
    for (int i = 2000; i <= 10000; i += 1000)
    {
        cout << endl;
        cout << i << ",";
        runTest(i);
    }
    for (int i = 20000; i <= 100000; i += 10000)
    {
        cout << endl;
        cout << i << ",";
        runTest(i);
    }
    cout << endl;
}