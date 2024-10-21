#include "MySubClass.h"

MySubClass::MySubClass(int data) : MyClass()
{
    subClassData = data;
}

MySubClass::MySubClass(const MySubClass &other) : MyClass(other)
{
    copy(other);
}

MySubClass &MySubClass::operator=(const MySubClass &other)
{
    if (this != &other)
    {
        MyClass::operator=(other);
        subClassData = other.subClassData;
    }
    return *this;
}

void MySubClass::copy(const MySubClass &other)
{
    MySubClass::operator=(other);
}
