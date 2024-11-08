#include <iostream>
#include <string>
#include "list342.h"

using namespace std;

// Tests for Program 3, all tests should return true and no memory leaks should occur when ran.

string kA = "a", kB = "b", kC = "c", kD = "d", kE = "e", kF = "f", kG = "g";

bool TestEquals()
{
    List342<string> list1, list2;
    
    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kD);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    list2.Insert(&kA);
    list2.Insert(&kB);
    list2.Insert(&kC);
    list2.Insert(&kD);
    list2.Insert(&kE);
    list2.Insert(&kF);
    list2.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "list2: " << list2 << endl;
    cout << "list1 == list2: " << (list1 == list2) << endl;

    return list1 == list2;
}

bool TestEqualsListsNotEqual()
{
    List342<string> list1, list2;
    
    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kD);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    list2.Insert(&kA);
    list2.Insert(&kB);
    list2.Insert(&kC);
    list2.Insert(&kE);
    list2.Insert(&kF);
    list2.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "list2: " << list2 << endl;
    cout << "list1 == list2: " << (list1 == list2) << endl;

    return !(list1 == list2);
}

bool TestNotEquals()
{
    List342<string> list1, list2;
    
    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kD);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    list2.Insert(&kA);
    list2.Insert(&kB);
    list2.Insert(&kC);
    list2.Insert(&kE);
    list2.Insert(&kF);
    list2.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "list2: " << list2 << endl;
    cout << "list1 != list2: " << (list1 != list2) << endl;

    return list1 != list2;
}

bool TestNotEqualsListsEqual()
{
    List342<string> list1, list2;
    
    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kD);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    list2.Insert(&kA);
    list2.Insert(&kB);
    list2.Insert(&kC);
    list2.Insert(&kD);
    list2.Insert(&kE);
    list2.Insert(&kF);
    list2.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "list2: " << list2 << endl;
    cout << "list1 != list2: " << (list1 != list2) << endl;

    return !(list1 != list2);
}

bool TestInsertToEmptyList()
{
    List342<string> calling_list, expected;

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list insert a." << endl;
    bool res = calling_list.Insert(&kA);
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    expected.Insert(&kA);

    return calling_list == expected && res && calling_list.Size() == 1;
}

bool TestInsertNewHead()
{
    List342<string> calling_list, expected;

    calling_list.Insert(&kB);

    expected.Insert(&kA);
    expected.Insert(&kB);

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list insert a." << endl;
    bool res = calling_list.Insert(&kA);
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && res && calling_list.Size() == 2;
}

bool TestInsertToEnd()
{
    List342<string> calling_list, expected;

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kB);
    expected.Insert(&kC);
    expected.Insert(&kD);
    expected.Insert(&kE);
    expected.Insert(&kF);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list insert g." << endl;
    bool res = calling_list.Insert(&kG);
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && res && calling_list.Size() == 7;
}

bool TestInsertToMiddle()
{
    List342<string> calling_list, expected;

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kB);
    expected.Insert(&kC);
    expected.Insert(&kD);
    expected.Insert(&kE);
    expected.Insert(&kF);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list insert d." << endl;
    bool res = calling_list.Insert(&kD);
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && res && calling_list.Size() == 7;
}

bool TestInsertDuplicate()
{
    List342<string> calling_list, expected;

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kB);
    expected.Insert(&kC);
    expected.Insert(&kD);
    expected.Insert(&kE);
    expected.Insert(&kF);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list insert d." << endl;
    bool res = calling_list.Insert(&kD);
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && !res;
}

bool TestRemoveFromEmptyList()
{
    List342<string> calling_list, expected;
    string reference = "empty";

    cout << "calling_list: " << calling_list << endl;
    cout << "reference: " << reference << endl;
    cout << "calling_list remove a." << endl;
    bool res = calling_list.Remove(kA, reference);
    cout << "calling_list result: " << calling_list << endl;
    cout << "reference result: " << reference << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && !res && reference == "empty";
}

bool TestRemoveFromHead()
{
    List342<string> calling_list, expected;
    string reference = "empty";

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);

    expected.Insert(&kB);

    cout << "calling_list: " << calling_list << endl;
    cout << "reference: " << reference << endl;
    cout << "calling_list remove a." << endl;
    bool res = calling_list.Remove(kA, reference);
    cout << "calling_list result: " << calling_list << endl;
    cout << "reference result: " << reference << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && res && reference == "a";
}

bool TestRemoveFromEnd()
{
    List342<string> calling_list, expected;
    string reference = "empty";

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kB);
    expected.Insert(&kC);
    expected.Insert(&kD);
    expected.Insert(&kE);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "reference: " << reference << endl;
    cout << "calling_list remove g." << endl;
    bool res = calling_list.Remove(kG, reference);
    cout << "calling_list result: " << calling_list << endl;
    cout << "reference result: " << reference << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && reference == "g" && res;
}

bool TestRemoveFromMiddle()
{
    List342<string> calling_list, expected;
    string reference = "empty";

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kB);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kF);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "reference: " << reference << endl;
    cout << "calling_list remove d." << endl;
    bool res = calling_list.Remove(kD, reference);
    cout << "calling_list result: " << calling_list << endl;
    cout << "reference result: " << reference << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;

    return calling_list == expected && res && reference == "d";
}

bool TestRemoveMissingValue()
{
    List342<string> calling_list, expected;
    string reference = "empty";

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kB);
    expected.Insert(&kC);
    expected.Insert(&kD);
    expected.Insert(&kE);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "reference: " << reference << endl;
    cout << "calling_list remove g." << endl;
    bool res = calling_list.Remove(kG, reference);
    cout << "calling_list result: " << calling_list << endl;
    cout << "reference result: " << reference << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;

    return calling_list == expected && !res && calling_list.Size() == 6 && reference == "empty";
}

bool TestInterlockingMerge()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kC);
    calling_list.Insert(&kE);
    calling_list.Insert(&kG);

    other_list.Insert(&kB);
    other_list.Insert(&kD);
    other_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged other_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestEmptyCallingListMerge()
{
    List342<string> calling_list, other_list, expected;
    other_list.Insert(&kA);
    other_list.Insert(&kC);
    other_list.Insert(&kE);
    other_list.Insert(&kG);
    other_list.Insert(&kB);
    other_list.Insert(&kD);
    other_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged other_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestEmptyOtherListMerge()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged other_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestEmptyListsMerge()
{
    List342<string> calling_list, other_list, expected;

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged other_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestSameListMerge()
{
    List342<string> calling_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list merged calling_list. " << endl;
    bool res = calling_list.Merge(calling_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestCallingListEndMerge()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kG);

    other_list.Insert(&kA);
    other_list.Insert(&kB);
    other_list.Insert(&kC);
    other_list.Insert(&kD);
    other_list.Insert(&kE);
    other_list.Insert(&kF);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged calling_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestOtherListEndMerge()
{
    List342<string> calling_list, other_list, expected;

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);

    other_list.Insert(&kG);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged calling_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}


bool TestPartialOtherListMerge()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    other_list.Insert(&kA);
    other_list.Insert(&kB);
    other_list.Insert(&kC);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged calling_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestPartialCallingListMerge()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);

    other_list.Insert(&kA);
    other_list.Insert(&kB);
    other_list.Insert(&kC);
    other_list.Insert(&kD);
    other_list.Insert(&kE);
    other_list.Insert(&kF);
    other_list.Insert(&kG);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged calling_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestSurroundingCallingListMerge()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kG);

    other_list.Insert(&kB);
    other_list.Insert(&kC);
    other_list.Insert(&kD);
    other_list.Insert(&kE);
    other_list.Insert(&kF);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list merged calling_list. " << endl;
    bool res = calling_list.Merge(other_list);
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Return: " << res << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected && other_list.Size() == 0;
}

bool TestPlusOperator()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kC);
    calling_list.Insert(&kE);
    calling_list.Insert(&kG);

    other_list.Insert(&kB);
    other_list.Insert(&kD);
    other_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "Adding calling_list to other_list and assigning to res" << endl;
    List342<string> res = calling_list + other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "res result: " << res << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "res Size: " << res.Size() << endl;
    cout << "Expected: " << expected << endl;

    return res == expected;
}

bool TestPlusOperatorEmptyCallingList()
{
    List342<string> calling_list, other_list, expected;

    other_list.Insert(&kB);
    other_list.Insert(&kD);
    other_list.Insert(&kF);

    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "Adding calling_list to other_list and assigning to res" << endl;
    List342<string> res = calling_list + other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "res result: " << res << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "res Size: " << res.Size() << endl;
    cout << "Expected: " << expected << endl;

    return res == expected;
}

bool TestPlusOperatorEmptyOtherList()
{
    List342<string> calling_list, other_list, expected;

    calling_list.Insert(&kA);
    calling_list.Insert(&kC);
    calling_list.Insert(&kE);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "Adding calling_list to other_list and assigning to res" << endl;
    List342<string> res = calling_list + other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "res result: " << res << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "res Size: " << res.Size() << endl;
    cout << "Expected: " << expected << endl;

    return res == expected;
}

bool TestInterlockingPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kC);
    calling_list.Insert(&kE);
    calling_list.Insert(&kG);

    other_list.Insert(&kB);
    other_list.Insert(&kD);
    other_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestEmptyCallingListPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    other_list.Insert(&kA);
    other_list.Insert(&kC);
    other_list.Insert(&kE);
    other_list.Insert(&kG);
    other_list.Insert(&kB);
    other_list.Insert(&kD);
    other_list.Insert(&kF);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestEmptyOtherListPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestEmptyListsPlusEquals()
{
    List342<string> calling_list, other_list, expected;

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestSameListPlusEquals()
{
    List342<string> calling_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "calling_list += calling_list. " << endl;
    calling_list += calling_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestCallingListEndPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kG);

    other_list.Insert(&kA);
    other_list.Insert(&kB);
    other_list.Insert(&kC);
    other_list.Insert(&kD);
    other_list.Insert(&kE);
    other_list.Insert(&kF);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestOtherListEndPlusEquals()
{
    List342<string> calling_list, other_list, expected;

    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);

    other_list.Insert(&kG);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}


bool TestPartialOtherListPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);
    calling_list.Insert(&kD);
    calling_list.Insert(&kE);
    calling_list.Insert(&kF);
    calling_list.Insert(&kG);

    other_list.Insert(&kA);
    other_list.Insert(&kB);
    other_list.Insert(&kC);

    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestPartialCallingListPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kB);
    calling_list.Insert(&kC);

    other_list.Insert(&kA);
    other_list.Insert(&kB);
    other_list.Insert(&kC);
    other_list.Insert(&kD);
    other_list.Insert(&kE);
    other_list.Insert(&kF);
    other_list.Insert(&kG);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kG);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestSurroundingCallingListPlusEquals()
{
    List342<string> calling_list, other_list, expected;
    calling_list.Insert(&kA);
    calling_list.Insert(&kG);

    other_list.Insert(&kB);
    other_list.Insert(&kC);
    other_list.Insert(&kD);
    other_list.Insert(&kE);
    other_list.Insert(&kF);
    
    expected.Insert(&kA);
    expected.Insert(&kC);
    expected.Insert(&kE);
    expected.Insert(&kB);
    expected.Insert(&kD);
    expected.Insert(&kF);
    expected.Insert(&kG);

    cout << "calling_list: " << calling_list << endl;
    cout << "other_list: " << other_list << endl;
    cout << "calling_list += other_list. " << endl;
    calling_list += other_list;
    cout << "calling_list result: " << calling_list << endl;
    cout << "other_list result: " << other_list << endl;
    cout << "calling_list Size: " << calling_list.Size() << endl;
    cout << "other_list Size: " << other_list.Size() << endl;
    cout << "Expected: " << expected << endl;

    return calling_list == expected;
}

bool TestPeek()
{
    List342<string> list1;
    string reference = "empty";

    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kD);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "Peeking for value d." << endl;
    bool res = list1.Peek("d", reference);
    cout << "list1 result: " << list1 << endl;
    cout << "reference result: " << reference << endl;
    cout << "return: " << res << endl;

    return res && reference == "d";
}

bool TestPeekValueMissing()
{
    List342<string> list1;
    string reference = "empty";

    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "Peeking for value d." << endl;
    bool res = list1.Peek("d", reference);
    cout << "list1 result: " << list1 << endl;
    cout << "reference result: " << reference << endl;
    cout << "return: " << res << endl;

    return !res && reference == "empty";
}

bool TestDeleteList()
{
    List342<string> list1, expected;

    list1.Insert(&kA);
    list1.Insert(&kB);
    list1.Insert(&kC);
    list1.Insert(&kE);
    list1.Insert(&kF);
    list1.Insert(&kG);

    cout << "list1: " << list1 << endl;
    cout << "Deleting list1 values." << endl;
    list1.DeleteList();
    cout << "list1 result: " << list1 << endl;
    cout << "list1 Size: " << list1.Size() << endl;
    
    return list1 == expected;
}

bool TestCopyConstructor()
{
    List342<string> original;

    original.Insert(&kA);
    original.Insert(&kB);
    original.Insert(&kC);
    original.Insert(&kE);
    original.Insert(&kF);
    original.Insert(&kG);

    cout << "original list: "<< original << endl;
    cout << "copying original list to copy list. " << endl;
    List342<string> copy(original);
    cout << "original result: " << original << endl;
    cout << "copy result: " << copy << endl;
    cout << "original Size: " << original.Size() << endl;
    cout << "copy Size: " << copy.Size() << endl;

    return original == copy;
}

bool TestAssignmentOperator()
{
    List342<string> original, copy;

    original.Insert(&kA);
    original.Insert(&kB);
    original.Insert(&kC);
    original.Insert(&kD);
    original.Insert(&kE);
    original.Insert(&kF);
    original.Insert(&kG);

    cout << "original list: "<< original << endl;
    cout << "copy list: " << copy << endl;
    cout << "assigning original list to copy list. " << endl;
    copy = original;
    cout << "original result: " << original << endl;
    cout << "copy result: " << copy << endl;
    cout << "original Size: " << original.Size() << endl;
    cout << "copy Size: " << copy.Size() << endl;

    return original == copy;
}

bool TestAssignmentOperatorAssignToFullCopyList()
{
    List342<string> original, copy;

    original.Insert(&kA);
    original.Insert(&kB);
    original.Insert(&kC);
    original.Insert(&kD);
    original.Insert(&kE);
    original.Insert(&kF);
    original.Insert(&kG);

    copy.Insert(&kA);
    copy.Insert(&kB);
    copy.Insert(&kC);
    copy.Insert(&kD);
    copy.Insert(&kE);
    copy.Insert(&kF);
    copy.Insert(&kG);

    cout << "original list: "<< original << endl;
    cout << "copy list: " << copy << endl;
    cout << "assigning original list to copy list. " << endl;
    copy = original;
    cout << "original result: " << original << endl;
    cout << "copy result: " << copy << endl;
    cout << "original Size: " << original.Size() << endl;
    cout << "copy Size: " << copy.Size() << endl;

    return original == copy;
}

int main()
{
    // == operator
    cout << "TestEquals: " << endl << TestEquals() << endl << endl;
    cout << "TestEqualsListsNotEqual: " << endl << TestEqualsListsNotEqual() << endl << endl;

    // != operator
    cout << "TestNotEquals: " << endl << TestNotEquals() << endl << endl;
    cout << "TestNotEqualsListsEqual: " << endl << TestNotEqualsListsEqual() << endl << endl;

    // Insert()
    cout << "TestInsertToEmptyList: " << endl << TestInsertToEmptyList() << endl << endl;
    cout << "TestInsertNewHead: " << endl << TestInsertNewHead() << endl << endl;
    cout << "TestInsertToMiddle: " << endl << TestInsertToMiddle() << endl << endl;
    cout << "TestInsertToEnd: " << endl << TestInsertToEnd() << endl << endl;
    cout << "TestInsertDuplicate: " << endl << TestInsertDuplicate() << endl << endl;

    // Remove()
    cout << "TestRemoveFromEmptyList: " << endl << TestRemoveFromEmptyList() << endl << endl;
    cout << "TestRemoveFromHead: " << endl << TestRemoveFromHead() << endl << endl;
    cout << "TestRemoveFromMiddle: " << endl << TestRemoveFromMiddle() << endl << endl;
    cout << "TestRemoveFromEnd: " << endl << TestRemoveFromEnd() << endl << endl;
    cout << "TestRemoveMissingValue: " << endl << TestRemoveMissingValue() << endl << endl;

    // Merge()
    cout << "TestInterlockingMerge: " << endl << TestInterlockingMerge() << endl << endl;
    cout << "TestEmptyCallingListMerge: " << endl << TestEmptyCallingListMerge() << endl << endl;
    cout << "TestEmptyOtherListMerge: " << endl << TestEmptyOtherListMerge() << endl << endl;
    cout << "TestEmptyListsMerge: " << endl << TestEmptyListsMerge() << endl << endl;
    cout << "TestSameListMerge: " << endl << TestSameListMerge() << endl << endl;
    cout << "TestCallingListEndMerge: " << endl << TestCallingListEndMerge() << endl << endl;
    cout << "TestCallingListEndMerge: " << endl << TestOtherListEndMerge() << endl << endl;
    cout << "TestPartialCallingListMerge: " << endl << TestPartialCallingListMerge() << endl << endl;
    cout << "TestPartialOtherListMerge: " << endl << TestPartialOtherListMerge() << endl << endl;
    cout << "TestSurroundingCallingListMerge: " << endl << TestSurroundingCallingListMerge() << endl << endl;

    // + operator
    cout << "TestPlusOperator: " << endl << TestPlusOperator() << endl << endl;
    cout << "TestPlusOperatorEmptyCallingList: " << endl << TestPlusOperatorEmptyCallingList() << endl << endl;
    cout << "TestPlusOperatorEmptyOtherList: " << endl << TestPlusOperatorEmptyOtherList() << endl << endl;

    // += operator
    cout << "TestInterlockingPlusEquals: " << endl << TestInterlockingPlusEquals() << endl << endl;
    cout << "TestEmptyCallingListPlusEquals: " << endl << TestEmptyCallingListPlusEquals() << endl << endl;
    cout << "TestEmptyOtherListPlusEquals: " << endl << TestEmptyOtherListPlusEquals() << endl << endl;
    cout << "TestEmptyListsPlusEquals: " << endl << TestEmptyListsPlusEquals() << endl << endl;
    cout << "TestSameListPlusEquals: " << endl << TestSameListPlusEquals() << endl << endl;
    cout << "TestCallingListEndPlusEquals: " << endl << TestCallingListEndPlusEquals() << endl << endl;
    cout << "TestCallingListEndPlusEquals: " << endl << TestOtherListEndPlusEquals() << endl << endl;
    cout << "TestPartialCallingListPlusEquals: " << endl << TestPartialCallingListPlusEquals() << endl << endl;
    cout << "TestPartialOtherListPlusEquals: " << endl << TestPartialOtherListPlusEquals() << endl << endl;
    cout << "TestSurroundingCallingListPlusEquals: " << endl << TestSurroundingCallingListPlusEquals() << endl << endl;

    // Peek()
    cout << "TestPeek: " << endl << TestPeek() << endl << endl;
    cout << "TestPeekValueMissing: " << endl << TestPeekValueMissing() << endl << endl;

    // DeleteList()
    cout << "TestDeleteList: " << endl << TestDeleteList() << endl << endl;

    // Copy Constructor
    cout << "TestCopyConstructor: " << endl << TestCopyConstructor() << endl << endl;

    // Assignment Operator
    cout << "TestAssignmentOperator: " << endl << TestAssignmentOperator() << endl << endl;
    cout << "TestAssignmentOperatorAssignToFullCopyList: " << endl << TestAssignmentOperatorAssignToFullCopyList() << endl << endl;

    // Runs BuildList with a file called "test_letters.txt" and prints the list after.
    // If "test_letters.txt" doesn't exist, the method should return false and not cause a compile error.
    // You may also want to test BuildList on a list with items already in it.
    List342<string> calling_list;
    calling_list.Insert(&kD);
    cout << calling_list << endl;
    cout << "BuildList sucessful: " << calling_list.BuildList("test_letters.txt") << endl;

    cout << calling_list << endl;
}