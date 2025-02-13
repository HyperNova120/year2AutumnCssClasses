#include "avltree.h"

#include <iostream>
#include <set>
#include <chrono>

using namespace std;

class testing
{
public:
    testing(int a) { key1 = a; }
    testing(int a, int b)
    {
        key1 = a;
        key2 = b;
    }
    bool operator<(const testing &other) const { return key1 < other.key1; }
    bool operator>(const testing &other) const { return key1 > other.key1; }
    bool operator==(const testing &other) const { return key1 == other.key1; }
    bool operator!=(const testing &other) const { return key1 != other.key1; }
    friend ostream &operator<<(ostream &os, testing &obj)
    {
        os << to_string(obj.key1);
        return os;
    }
    int key1 = 0;
    int key2 = 0;
};
struct Compare
{
    int operator()(testing a, testing b) const { return a.key1 < b.key1; }
    int operator()(testing *a, testing *b) const { return a->key1 < b->key1; }
};

int main()
{
    cout << "#_Elements,AVL_Insert,AVL_Delete,SET_Insert,SET_Delete,INSERT_DIFF,DELETE_DIFF" << endl;
    //int randCount2 = 1000000;
    /* for (int randCount2 = 100000; randCount2 <= 1000000; randCount2 += 100000)
    {
        AVLTree<int> largeTest2;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < randCount2; i++)
        {
            largeTest2.insert(rand() % randCount2);
            // cout << "INSERT " << tmp << endl;
            // largeTest.print();
        }
        auto t2 = chrono::high_resolution_clock::now();
        auto t3 = chrono::high_resolution_clock::now();
        for (int i = 0; i < randCount2; i++)
        {
            largeTest2.remove(rand() % randCount2);
        }
        auto t4 = chrono::high_resolution_clock::now();
        //largeTest2.clear();
        //cout << largeTest2.size() << endl;
        set<int> setTest2;
        auto t5 = chrono::high_resolution_clock::now();
        /* for (int i = 0; i < randCount2; i++)
        {
            setTest2.insert(rand() % randCount2);
        } 
        auto t6 = chrono::high_resolution_clock::now();
        auto t7 = chrono::high_resolution_clock::now();
        /* for (int i = 0; i < randCount2; i++)
        {
            setTest2.erase(rand() % randCount2);
        }
        auto t8 = chrono::high_resolution_clock::now();
        cout << randCount2;
        cout << "," << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
        cout << "," << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count();
        cout << "," << chrono::duration_cast<chrono::milliseconds>(t6 - t5).count();
        cout << "," << chrono::duration_cast<chrono::milliseconds>(t8 - t7).count();
        int insertTMP = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() - chrono::duration_cast<chrono::milliseconds>(t6 - t5).count();
        int deleteTMP = chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() - chrono::duration_cast<chrono::milliseconds>(t8 - t7).count();

        cout << "," << ((double)insertTMP / chrono::duration_cast<chrono::milliseconds>(t6 - t5).count()) * 100;
        cout << "," << ((double)deleteTMP / chrono::duration_cast<chrono::milliseconds>(t8 - t7).count()) * 100 << endl;
    }

    return 0; */

    AVLTree<testing, Compare> test = AVLTree<testing, Compare>();
    test.insert(testing(4, 5));
    test.insert(testing(2, 6));
    test.insert(testing(6, 9));
    test.insert(testing(1, 14));
    test.insert(testing(3, 52));
    test.insert(testing(5, 8));
    test.insert(testing(7, 4));

    test.insert(testing(16, 41));
    test.insert(testing(15, 12));
    test.insert(testing(14, 17));
    test.insert(testing(13, 18));
    test.insert(testing(12, 64));
    test.insert(testing(11, 24));
    test.insert(testing(10, 13));
    test.insert(testing(8, 89));
    test.insert(testing(9, 67));

    test.print();
    cout << "=================================" << endl;
    cout << "Size:" << test.size() << endl;
    for (auto i : test)
    {
        cout << i << endl;
    }

    test.remove(testing(11, 24));
    test.remove(testing(12, 64));
    test.remove(testing(8, 89));
    test.remove(testing(14, 17));
    test.remove(testing(16, 41));
    test.remove(testing(10, 13));
    test.remove(testing(15, 12));
    test.remove(testing(9, 67));
    // delete test.remove(testing(6, 9));
    test.print();
    cout << "=================================" << endl;


    // test2.print();
    //  test2.print();
    cout << "Size:" << test.size() << endl;
    for (auto i : test)
    {
        cout << i << endl;
    }

    cout << "=================================" << endl;
    int randCount = 5000000;
    AVLTree<int> largeTest;
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < randCount; i++)
    {
        largeTest.insert(rand() % randCount);
        // cout << "INSERT " << tmp << endl;
        // largeTest.print();
    }
    auto t2 = chrono::high_resolution_clock::now();
    // largeTest.print();
    cout << "=================================" << endl;
    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < randCount; i++)
    {
        largeTest.remove(rand() % randCount);
    }
    auto t4 = chrono::high_resolution_clock::now();
    cout << "=================================" << endl;
    cout << "SET TEST" << endl;
    set<int> setTest;

    auto t5 = chrono::high_resolution_clock::now();
    for (int i = 0; i < randCount; i++)
    {
        setTest.insert(rand() % randCount);
    }
    auto t6 = chrono::high_resolution_clock::now();
    // largeTest.print();
    cout << "=================================" << endl;
    auto t7 = chrono::high_resolution_clock::now();
    for (int i = 0; i < randCount; i++)
    {
        setTest.erase(rand() % randCount);
    }
    auto t8 = chrono::high_resolution_clock::now();
    cout << "=================================" << endl;
    cout << "AVL INSERT TIME:" << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << endl;
    cout << "AVL DELETE TIME:" << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() << endl;
    cout << "SET INSERT TIME:" << chrono::duration_cast<chrono::milliseconds>(t6 - t5).count() << endl;
    cout << "SET DELETE TIME:" << chrono::duration_cast<chrono::milliseconds>(t8 - t7).count() << endl;
    int insertTMP = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() - chrono::duration_cast<chrono::milliseconds>(t6 - t5).count();
    int deleteTMP = chrono::duration_cast<chrono::milliseconds>(t4 - t3).count() - chrono::duration_cast<chrono::milliseconds>(t8 - t7).count();

    cout << "AVL INSERT Percent DIFF:" << ((double)insertTMP / chrono::duration_cast<chrono::milliseconds>(t6 - t5).count()) * 100 << endl;
    cout << "AVL DELETE Percent DIFF:" << ((double)deleteTMP / chrono::duration_cast<chrono::milliseconds>(t8 - t7).count()) * 100 << endl;

    cout << "=================================" << endl;

    AVLTree<int *> ptr_test;
    int *tmp = new int(5);
    int *tmp2 = new int(3);
    int *tmp3 = new int(7);
    ptr_test.insert(tmp);
    ptr_test.insert(tmp2);
    ptr_test.insert(tmp3);
    ptr_test.print();
    cout << "Size:" << ptr_test.size() << endl;
    for (auto i : ptr_test)
    {
        cout << i << endl;
    }
    *tmp = 6;
    cout << "=================================" << endl;
    ptr_test.print();
    cout << "Size:" << ptr_test.size() << endl;
    for (auto i : ptr_test)
    {
        cout << i << endl;
    }
    cout << "=================================" << endl;
    delete tmp;
    delete tmp2;
    delete tmp3;
}