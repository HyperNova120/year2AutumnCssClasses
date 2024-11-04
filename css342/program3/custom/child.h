#ifndef CHILD_H_
#define CHILD_H_
#include <string>
#include <iostream>

using namespace std;

class Child
{
public:
    Child();
    Child(string first_name, string last_name, int age);
    Child(const Child &other);

    string first_name() const;
    string last_name() const;
    int age() const;

    void set_first_name(string name);
    void set_last_name(string name);
    void set_age(int age);

    friend istream &operator>>(istream &is, Child &obj);
    friend ostream &operator<<(ostream &os, const Child &obj);

    bool operator<(const Child &other);
    bool operator>(const Child &other);
    bool operator<=(const Child &other);
    bool operator>=(const Child &other);
    bool operator==(const Child &other);
    bool operator!=(const Child &other);
    void operator=(const Child &other);

private:
    string first_name_ = "";
    string last_name_ = "";
    int age_ = 0;
};

#endif // CHILD_H_