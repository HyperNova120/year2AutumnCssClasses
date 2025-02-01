#include "avltree.h"

#include <iostream>

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
    bool operator==(const testing &other) const { return key2 == other.key2; }
    bool operator!=(const testing &other) const { return key2 != other.key2; }
    friend ostream &operator<<(ostream &os, testing &obj)
    {
        os << to_string(obj.key2);
        return os;
    }
    int key1 = 0;
    int key2 = 0;
};
struct Compare
{
    int operator()(testing a, testing b) const { return a.key2 < b.key2; }
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
    delete test.remove(testing(11, 24));
    delete test.remove(testing(12, 64));
    delete test.remove(testing(8, 89));
    delete test.remove(testing(14, 17));
    delete test.remove(testing(16, 41));
    delete test.remove(testing(10, 13));
    delete test.remove(testing(15, 12));
    delete test.remove(testing(9, 67));
    test.print();
    cout << "=================================" << endl;
    /*AVLTree<int> test2 = AVLTree<int>(test);
    test2.print();
    cout << "Test:" << (test == test2) << endl;
    cout << "Test2:" << (test != test2) << endl;
    cout << "Test:" << (test == test) << endl; */

    AVLTree<int> test2 = AVLTree<int>();
    for (int i = 0; i < 10000; i++)
    {
        test2.insert(rand() % 100000);
    }
    test2.print();
    //test2.print();
}