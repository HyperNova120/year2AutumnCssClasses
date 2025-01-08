#pragma once
#include "MyClass.h"

class MySubClass : MyClass
{
public:
    MySubClass(int data);
    MySubClass(const MySubClass &other);

    MySubClass &operator=(const MySubClass &other);


private:
    void copy(const MySubClass &other);
    int subClassData;
};