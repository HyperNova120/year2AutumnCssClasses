#include <string>
#include <iostream>
#include <sstream>

#include "list342.h"
using namespace std;

#define Test(name) RunTest(#name, name)

void RunTest(string name, bool (*func)()) {
    bool success = func();
    cout << name << ": " << (success ? "PASSED" : "FAILED") << endl;
}

template<class T>
bool CompareValue(const T &correct, const T &value) {
    if (correct == value) return true;

    cout << "Failed: expected " << correct << ", found " << value << endl;

    return false;
}

template<class T>
bool CompareList(const string &correct, const int size, const List342<T> &list) {
    stringstream out{};

    out << list;

    bool textCheck = CompareValue(correct, out.str());
    bool sizeCheck = CompareValue(size, list.Size());

    return textCheck && sizeCheck;
}

bool TestSimple() {
    List342<int> list;

    int a = 7, b = 27, c = -4, d = 7, e = 7, f = 8;

    if (!CompareValue(true, list.Insert(&a))) return false;
    if (!CompareValue(false, list.Insert(&a))) return false;

    list.Insert(&b);
    list.Insert(&c);

    if (!CompareValue(false, list.Insert(&d))) return false;
    list.Insert(&e);

    list.Insert(&f);

    if (!CompareValue(false, list.Insert(nullptr))) return false;

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;

    return true;
}

bool TestAdd() {
    List342<int> list;

    int a = 7, b = 27, c = -4, d = 7, e = 7, f = 8;

    list.Insert(&a);
    list.Insert(&b);
    list.Insert(&c);
    list.Insert(&d);
    list.Insert(&e);
    list.Insert(&f);

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;

    List342<int> list2;

    int g = 9, h = 2437, i = -3, j = 8;

    list2.Insert(&g);
    list2.Insert(&h);
    list2.Insert(&i);
    list2.Insert(&j);

    if (!CompareList("-3, 8, 9, 2437", 4, list2)) return false;

    List342<int> list3 = list + list2;

    if (!CompareList("-4, -3, 7, 8, 9, 27, 2437", 7, list3)) return false;

    list3 += list;
    list3 += list2;
    list3 += list3;

    if (!CompareList("-4, -3, 7, 8, 9, 27, 2437", 7, list3)) return false;

    list += list2;

    if (!CompareList("-4, -3, 7, 8, 9, 27, 2437", 7, list)) return false;
    if (!CompareList("-3, 8, 9, 2437", 4, list2)) return false;
    if (!CompareList("-4, -3, 7, 8, 9, 27, 2437", 7, list3)) return false;

    if (!CompareValue(list, list3)) return false;
    if (!CompareValue(true, list2 != list3)) return false;

    return true;
}

bool TestRemovePeek() {
    List342<int> list;

    int a = 7, b = 27, c = -4, d = 7, e = 7, f = 8;

    list.Insert(&a);
    list.Insert(&b);
    list.Insert(&c);
    list.Insert(&d);
    list.Insert(&e);
    list.Insert(&f);

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;

    int result = 0;

    if (!CompareValue(true, list.Remove(8, result))) return false;
    if (!CompareValue(8, result)) return false;
    if (!CompareList("-4, 7, 27", 3, list)) return false;

    if (!CompareValue(true, list.Peek(-4, result))) return false;
    if (!CompareValue(-4, result)) return false;
    if (!CompareList("-4, 7, 27", 3, list)) return false;

    if (!CompareValue(true, list.Peek(7, result))) return false;
    if (!CompareValue(7, result)) return false;

    if (!CompareValue(true, list.Peek(27, result))) return false;
    if (!CompareValue(27, result)) return false;

    if (!CompareValue(true, list.Remove(-4, result))) return false;
    if (!CompareValue(-4, result)) return false;

    if (!CompareValue(true, list.Remove(27, result))) return false;
    if (!CompareValue(27, result)) return false;

    if (!CompareValue(false, list.Remove(27, result))) return false;
    if (!CompareValue(false, list.Peek(27, result))) return false;

    List342<int> emptyList;

    if (!CompareValue(false, emptyList.Remove(10, result))) return false;
    if (!CompareValue(false, emptyList.Peek(10, result))) return false;

    return true;
}

bool TestMerge() {
    List342<int> list;

    int a = 7, b = 27, c = -4, d = 7, e = 7, f = 8;

    list.Insert(&a);
    list.Insert(&b);
    list.Insert(&c);
    list.Insert(&d);
    list.Insert(&e);
    list.Insert(&f);

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;

    List342<int> list2;

    int g = 9, h = 2437, i = -3, j = 8;

    list2.Insert(&g);
    list2.Insert(&h);
    list2.Insert(&i);
    list2.Insert(&j);

    if (!CompareList("-3, 8, 9, 2437", 4, list2)) return false;

    list.Merge(list2);

    if (!CompareList("-4, -3, 7, 8, 9, 27, 2437", 7, list)) return false;
    if (!CompareList("", 0, list2)) return false;

    list.Merge(list);
    list2.Merge(list2);

    if (!CompareList("-4, -3, 7, 8, 9, 27, 2437", 7, list)) return false;
    if (!CompareList("", 0, list2)) return false;

    if (!CompareValue(list, list)) return false;
    if (!CompareValue(true, list != list2)) return false;

    int o1 = -10, o2 = 5, o3 = 100000;

    list2.Insert(&o1);
    list2.Insert(&o2);
    list2.Insert(&o3);

    if (!CompareList("-10, 5, 100000", 3, list2)) return false;

    list2.Merge(list);

    if (!CompareList("-10, -4, -3, 5, 7, 8, 9, 27, 2437, 100000", 10, list2)) return false;
    if (!CompareList("", 0, list)) return false;

    int l1 = -31, l2 = -58, l3 = 328, l4 = -5;

    list.Insert(&l1);
    list.Insert(&l2);
    list.Insert(&l3);
    list.Insert(&l4);

    if (!CompareList("-58, -31, -5, 328", 4, list)) return false;

    if (!CompareValue(true, list2.Merge(list))) return false;

    if (!CompareList("-58, -31, -10, -5, -4, -3, 5, 7, 8, 9, 27, 328, 2437, 100000", 14, list2)) return false;
    if (!CompareList("", 0, list)) return false;

    List342<int> emptyList;

    if (!CompareValue(false, emptyList.Merge(emptyList))) return false;
    if (!CompareValue(false, emptyList.Merge(list))) return false;
    if (!CompareValue(false, list2.Merge(list))) return false;

    if (!CompareValue(true, list.Merge(list2))) return false;

    if (!CompareList("-58, -31, -10, -5, -4, -3, 5, 7, 8, 9, 27, 328, 2437, 100000", 14, list)) return false;
    if (!CompareList("", 0, list2)) return false;

    int p1 = -8888;
    int p2 = -847577;

    list2.Insert(&p1);
    list2.Insert(&p2);

    if (!CompareList("-847577, -8888", 2, list2)) return false;

    if (!CompareValue(true, list.Merge(list2))) return false;

    if (!CompareList("-847577, -8888, -58, -31, -10, -5, -4, -3, 5, 7, 8, 9, 27, 328, 2437, 100000", 16, list)) return
            false;

    return true;
}

bool TestEqualsAndSet() {
    List342<int> list;

    int a = 7, b = 27, c = -4, d = 7, e = 7, f = 8;

    list.Insert(&a);
    list.Insert(&b);
    list.Insert(&c);
    list.Insert(&d);
    list.Insert(&e);
    list.Insert(&f);

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;

    List342<int> emptyList;

    if (!CompareList("", 0, emptyList)) return false;

    emptyList = list;

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;
    if (!CompareList("-4, 7, 8, 27", 4, emptyList)) return false;
    if (!CompareValue(list, emptyList)) return false;

    list = list;
    emptyList = emptyList;
    list = emptyList;
    emptyList = list;

    if (!CompareList("-4, 7, 8, 27", 4, list)) return false;
    if (!CompareList("-4, 7, 8, 27", 4, emptyList)) return false;
    if (!CompareValue(list, emptyList)) return false;

    return true;
}

bool TestBuildList() {
    List342<int> list;

    list.BuildList("custom_test_data.txt");

    if (!CompareList("-13, -5, 0, 1, 9, 32, 44, 68, 87, 439, 548, 689", 12, list)) return false;

    return true;
}

int main() {
    Test(TestSimple);
    Test(TestAdd);
    Test(TestRemovePeek);
    Test(TestMerge);
    Test(TestEqualsAndSet);
    Test(TestBuildList);
}
