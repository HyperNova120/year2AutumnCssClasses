#include <iostream>

using namespace std;

void MySwap(string &name1, string &name2);


typedef struct
{
    int length;
    int width;
} Rectangle;

int Area(Rectangle &rect);

int main()
{
    string name1 = "sue";
    string name2 = "ravi";
    cout << name1 << " " << name2 << endl;
    MySwap(name1, name2);
    cout << name1 << " " << name2 << endl;

    Rectangle my_yard = {5, 7};
    int result = Area(my_yard);
    cout << "Area Of Rectange my_yard:" << my_yard.width << " X " << my_yard.length << " Y = " << result << " TESTING:" << my_yard.width << " X " << my_yard.length << " Y" << endl;
}

void MySwap(string &name1, string &name2)
{
    string tmp = name1;
    name1 = name2;
    name2 = tmp;
}

int Area(Rectangle &rect)
{
    int area = 0;
    area = rect.length * rect.width;
    rect.width = -13;
    return area;
}