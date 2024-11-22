#include <iostream>
#include "list342.h"
#include "child.h"
#include <vector>
using namespace std;

void TestEquality() {
    List342<int> list1, list2;
    int a = 1, b = 2, c = 3;
    list1.Insert(&a);
    list1.Insert(&b);
    list1.Insert(&c);
    list2 = list1;  
    cout << "Equality Test: " << (list1 == list2 ? "Passed" : "Failed") << endl;
    int d = 4;
    list2.Insert(&d);
    cout << "Inequality After Modification: " << (list1 != list2 ? "Passed" : "Failed") << endl;
}
void TestAssignmentOperator() {
    List342<int> list1;
    int a = 1, b = 3, c = 5;
    list1.Insert(&a);
    list1.Insert(&b);
    list1.Insert(&c);
    List342<int> list2;
    list2 = list1;  
    int d = 7;
    list2.Insert(&d);  
    cout << "Original List After Assignment: " << list1 << " (Expected: 1 3 5)" << endl;
    cout << "Modified Copy After Assignment: " << list2 << " (Expected: 1 3 5 7)" << endl;
}
void TestMergeSelf() {
    List342<int> list;
    int a = 1, b = 3, c = 5;
    list.Insert(&a);
    list.Insert(&b);
    list.Insert(&c);
    bool mergedWithSelf = list.Merge(list);  
    cout << "Merge Self Test: " << (mergedWithSelf ? "Failed" : "Passed") << endl;
    cout << "List After Self-Merge Attempt: " << list << " (Expected: 1 3 5)" << endl;
}
void TestDeepCopy() {
    List342<int> list1;
    int a = 2, b = 4, c = 6;
    list1.Insert(&a);
    list1.Insert(&b);
    list1.Insert(&c);
    List342<int> list2 = list1;  
    int d = 8;
    list2.Insert(&d); 
    cout << "Original List After Copy: " << list1 << " (Expected: 2 4 6)" << endl;
    cout << "Modified Copy: " << list2 << " (Expected: 2 4 6 8)" << endl;
}



void stringTests()
{
    string s1 = "AA";
    string s2 = "BB";
    string s3 = "CC";
    string s4 = "ZZ";
    string s5 = "JJ";
    List342<string> stringList1;
    List342<string> stringList2;
    stringList1.Insert(&s2);
    stringList1.Insert(&s1);
    stringList1.Insert(&s3);
    stringList2.Insert(&s4);
    stringList2.Insert(&s5);
    cout<<"Printing Lists of strings:"<<endl;
    cout<<stringList1<<endl;
    cout<<stringList2<<endl;
    cout<<"Testing peek"<<endl;
    string result;
    if(stringList1.Peek(s2, result)){
        cout<<"It has found it"<<endl;
    }
    List342<string>stringList3;
    stringList3 = stringList1+stringList2;
    cout<<"Adding two lists"<<endl;
    cout<<stringList3<<endl;
    cout<<"Adding two lists but diferen order"<<endl;
    List342<string>stringList4;
    stringList4 = stringList2+stringList1;
    cout<<stringList4<<endl;
    cout<<"Are they equal?"<<endl;
    if(stringList3==stringList4){
        cout<<"they are!"<<endl;
    }else{
        cout<<"No they werent!"<<endl;
    }
    cout<<"Adding list2 into list1"<<endl;
    stringList1 += stringList2;
    cout<<stringList1<<endl;
    cout<<"Deleting Lists 2-4"<<endl;
    stringList2.DeleteList();
    stringList3.DeleteList();
    stringList4.DeleteList();
    cout<<"Lets check their size"<<endl;
    cout<<"List2 size "<<stringList2.Size()<<endl;
    cout<<"List3 size "<<stringList3.Size()<<endl;
    cout<<"List4 size "<<stringList4.Size()<<endl;
    List342<string> stringList5;
    string s6 = "MM";
    string s7 = "11";
    string s8 ="MM";
    vector<string> vect;
    vect.push_back(s7);
    vect.push_back(s4);
    vect.push_back(s3);
    vect.push_back(s1);
    vect.push_back(s5);
    vect.push_back(s6);
    vect.push_back(s2);
    stringList5.Insert(&s6);
    stringList5.Insert(&s7);
    cout<<stringList5<<endl;
    cout<<"Lets merge our List1 with out new list5"<<endl;
    stringList1.Merge(stringList5);
    cout<<stringList1<<endl;
    cout<<"Whats list1's size?"<<endl;
    cout<<stringList1.Size()<<endl;
    cout<<stringList5<<endl;
    cout<<"Lets add a duplicate"<<endl;
    cout<<stringList1.Insert(&s8)<<endl;;
    cout<<stringList1<<endl;
    cout<<"Removing elements"<<endl;
    for(int i = 0; i < vect.size();i++){
        string temp;
        stringList1.Remove(vect[i], temp);
        cout<<temp<<endl;
    }
    cout<<stringList1.Size()<<endl;
}

int main()
{
    /* stringTests();

    cout << "====================================================" << endl;
    TestEquality();
    TestAssignmentOperator();
    TestMergeSelf();
    TestDeepCopy();
    cout << "====================================================" << endl; */
    Child c1("Angie", "Ham", 7), c2("Pradnya", "Dhala", 8),
        c3("Bill", "Vollmann", 13), c4("Cesar", "Ruiz", 6);
    Child c5("Piqi", "Tangi", 7), c6("Russell", "Wilson", 13),
        c7("Hank", "Aaron", 3), c8("Madison", "Fife", 7);
    Child c9("Miles", "Davis", 65), c10("John", "Zorn", 4), c11;
    List342<Child> class1, class2, soccer, chess;

    int a = 1, b = -1, c = 13;
    class1.Insert(&c1);
    class1.Insert(&c2);
    class1.Insert(&c3);
    class1.Insert(&c4);
    class1.Insert(&c5);
    class1.Insert(&c6);
    class1.Insert(&c5);
    cout << "class1: " << class1 << endl;
    if (!class1.Insert(&c1))
    {
        cout << "ERROR::: Duplicate" << endl;
    }
    class2.Insert(&c4);
    class2.Insert(&c5);
    class2.Insert(&c6);
    class2.Insert(&c7);
    class2.Insert(&c10);
    class2.Size();
    cout << "Class2: " << class2 << endl;
    class1.Merge(class2);
    class2.Merge(class1);
    class1.Merge(class2);
    class1.Merge(class1);
    class1.Size();
    cout << "class1 and 2 Merged: " << class1 << endl;
    class1.Remove(c4, c11);
    class1.Remove(c5, c11);
    class1.Remove(c11, c11);
    class1.Size();
    if (class1.Remove(c1, c11))
    {
        cout << "Removed from class1, student " << c11 << endl;
    }
    class1 += class1;
    cout << "class1: " << class1 << endl;
    soccer.Insert(&c6);
    soccer.Insert(&c4);
    soccer.Insert(&c9);
    soccer.Size();
    cout << "soccer: " << soccer << endl;
    soccer += class1;
    soccer.Size();
    cout << "soccer += class1 : " << soccer << endl;
    List342<Child> football = soccer;
    if (football == soccer)
    {
        cout << "football: " << football << endl;
    }
    if (football.Peek(c6, c11))
    {
        cout << c11 << " is on the football team" << endl;
    }
    soccer.DeleteList();
    
    soccer.Size();
    List342<int> numbers;
    numbers.Insert(&a);
    numbers.Insert(&b);
    numbers.Insert(&c);
    numbers.Size();
    cout << "These are the numbers: " << numbers << endl;
    numbers.DeleteList();
/* 
    List342<Child> fileChildren;
    if (fileChildren.BuildList("testfile.txt"))
    {
        cout << "File Children: " << fileChildren << endl;
        cout << "File Children Size: " << fileChildren.Size() << endl;
    } */
}