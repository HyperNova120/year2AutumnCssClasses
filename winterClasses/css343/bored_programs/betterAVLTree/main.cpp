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
};

int main()
{
    // cout << "Hello World!" << endl;
    AVLTree<testing, Compare> test = AVLTree<testing, Compare>();
    /* test.insert(5);
    test.insert(4);
    test.insert(8);
    test.insert(7);
    test.insert(9);
    test.insert(6);
    test.print();
    delete test.remove(6);
    cout << "=========================" << endl;
    test.print();
    delete test.remove(8);
    cout << "=========================" << endl;
    test.print();
    delete test.remove(9);
    cout << "=========================" << endl;
    test.print();
    test.~AVLTree(); */
    test.insert(testing(4, 5));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(2, 6));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(6, 9));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(1, 14));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(3, 52));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(5, 8));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(7, 4));
    test.print();
    cout << "=================================" << endl;

    test.insert(testing(16, 41));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(15, 12));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(14, 17));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(13, 18));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(12, 64));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(11, 24));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(10, 13));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(8, 89));
    test.print();
    cout << "=================================" << endl;
    test.insert(testing(9, 67));

    test.print();
    cout << "=================================" << endl;
    cout << "Size:" << test.size() << endl;
    /* for (auto i : test)
    {
        cout << i << endl;
    } */
    cout << "=============REMOVE===========" << endl;

    test.remove(testing(11, 24));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(12, 64));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(8, 89));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(14, 17));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(16, 41));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(10, 13));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(15, 12));
    test.print();
    cout << "=================================" << endl;
    test.remove(testing(9, 67));
    // delete test.remove(testing(6, 9));
    test.print();
    cout << "=================================" << endl;
    /*AVLTree<int> test2 = AVLTree<int>(test);
    test2.print();
    cout << "Test:" << (test == test2) << endl;
    cout << "Test2:" << (test != test2) << endl;
    cout << "Test:" << (test == test) << endl; */

    /* AVLTree<int> test2 = AVLTree<int>();
    for (int i = 0; i < 10000; i++)
    {
        test2.insert(rand() % 100000);
    } */
    // test2.print();
    //  test2.print();
    cout << "Size:" << test.size() << endl;
    /* for (auto i : test)
    {
        cout << i << endl;
    } */

    /* AVLTree<int> failTest;
    for (int i = 0; i < 25; i++)
    {
        cout << "INSERT " << (25 - i) << endl;
        failTest.insert(25 - i);
        failTest.print();
    } */

    cout << "=================================" << endl;
    int randCount = 10000000;
    AVLTree<int> largeTest;
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < randCount; i++)
    {
        largeTest.insert(rand() % randCount);
        // cout << "INSERT " << tmp << endl;
        // largeTest.print();
    }
    auto t2 = chrono::high_resolution_clock::now();
    //largeTest.print();
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
}