#include <iostream>
#include <fstream>

using namespace std;

void printFile(string fileToRead)
{
    ifstream fileStream;
    fileStream.open(fileToRead);
    if (!fileStream.is_open())
    {
        cout << "Failed To Read File " << fileToRead << endl;
        fileStream.close();
        return;
    }
    cout << "============" << fileToRead << "============" << endl;
    string tmp;
    while (fileStream >> tmp)
    {
        cout << tmp << endl;
    }
    cout << "============" << "END" << "============" << endl;
    fileStream.close();
}


int main()
{
    printFile("textfile1.txt");
    printFile("textfile2.txt");
    printFile("textfile3.txt");
}