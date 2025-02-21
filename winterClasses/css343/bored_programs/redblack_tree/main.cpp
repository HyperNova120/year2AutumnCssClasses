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
    test.print();
    return 0;
}