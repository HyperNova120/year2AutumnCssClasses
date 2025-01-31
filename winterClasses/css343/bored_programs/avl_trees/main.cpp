#include "avltree.h"

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    AVLTree<int> test = AVLTree<int>();
    test.insert(4);
    test.print();
    cout << "============================" << endl;
    test.insert(2);
    test.print();
    cout << "============================" << endl;
    test.insert(6);
    test.print();
    cout << "============================" << endl;
    test.insert(1);
    test.print();
    cout << "============================" << endl;
    test.insert(3);
    test.print();
    cout << "============================" << endl;
    test.insert(5);
    test.print();
    cout << "============================" << endl;
    test.insert(7);
    test.print();
    cout << "============================" << endl;

    test.insert(16);
    test.print();
    cout << "============================" << endl;
    test.insert(15);
    test.print();
    cout << "============================" << endl;
    test.insert(14);
    test.print();
    cout << "============================" << endl;
    test.insert(13);
    test.print();
    cout << "============================" << endl;
    test.insert(12);
    test.print();
    cout << "============================" << endl;
    test.insert(11);
    test.print();
    cout << "============================" << endl;
    test.insert(10);
    test.print();
    cout << "============================" << endl;
    test.insert(8);
    test.print();
    cout << "============================" << endl;
    test.insert(9);
    test.print();
    cout << "============================" << endl;

    test.print();
}