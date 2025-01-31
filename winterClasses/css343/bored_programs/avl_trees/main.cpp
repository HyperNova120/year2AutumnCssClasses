#include "avltree.h"

#include <iostream>

using namespace std;

int main()
{
    // cout << "Hello World!" << endl;
    AVLTree<int> test = AVLTree<int>();
    test.insert(4);
    test.insert(2);
    test.insert(6);
    test.insert(1);
    test.insert(3);
    test.insert(5);
    test.insert(7);

    test.insert(16);
    test.insert(15);
    test.insert(14);
    test.insert(13);
    test.insert(12);
    test.insert(11);
    test.insert(10);
    test.insert(8);
    test.insert(9);

    test.print();
    cout << "=================================" << endl;
    AVLTree<int> test2 = AVLTree<int>(test);
    test2.print();
    cout << "Test:" << (test == test2) << endl;
    cout << "Test2:" << (test != test2) << endl;
    cout << "Test:" << (test == test) << endl;
}