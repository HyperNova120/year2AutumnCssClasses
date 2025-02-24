#include "rbtree.h"
#include <iostream>

int main()
{
    cout << "Hello World!" << endl;
    RBTree<int> test;
    test.insert(5);
    test.insert(10);
    test.insert(1);
    test.insert(20);
    test.insert(30);
    test.insert(0);
    test.insert(2);
    test.insert(3);
    test.insert(7);
    test.insert(40);
    test.insert(50);
    test.print();
    return 0;
}