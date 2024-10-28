#include "child.h"

Child::Child()
{
}

Child::Child(string first_name, string last_name, int age)
{
    first_name_ = first_name;
    last_name_ = last_name;
    age_ = age;
}

Child::Child(const Child &other)
{
    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    age_ = other.age_;
}

string Child::first_name() const
{
    return first_name_;
}

string Child::last_name() const
{
    return last_name_;
}

int Child::age() const
{
    return age_;
}

void Child::set_first_name(string name)
{
    first_name_ = name;
}

void Child::set_last_name(string name)
{
    last_name_ = name;
}

void Child::set_age(int age)
{
    age_ = age;
}

bool Child::operator<(const Child &other)
{
    return (last_name_ == other.last_name_) ? (first_name_ == other.first_name_) ? age_ < other.age_ : first_name_ < other.first_name_ : last_name_ < other.last_name_;
}

bool Child::operator>(const Child &other)
{
    return (last_name_ == other.last_name_) ? (first_name_ == other.first_name_) ? age_ > other.age_ : first_name_ > other.first_name_ : last_name_ > other.last_name_;
}

bool Child::operator<=(const Child &other)
{
    return (*this < other) || (*this == other);
}

bool Child::operator>=(const Child &other)
{
    return (*this > other) || (*this == other);
}

bool Child::operator==(const Child &other)
{
    return (last_name_ == other.last_name_) && (first_name_ == other.first_name_) && (age_ == other.age_);
}

bool Child::operator!=(const Child &other)
{
    return !(*this == other);
}

void Child::operator=(const Child &other)
{
    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    age_ = other.age_;
}

istream &operator>>(istream &is, Child &obj)
{
    string first, last;
    int age;
    is >> first >> last >> age;
    obj.set_first_name(first);
    obj.set_last_name(last);
    obj.set_age(age);
    return is;
}

ostream &operator<<(ostream &os, const Child &obj)
{
    os << obj.first_name_ << obj.last_name_ << obj.age_;
    return os;
}
