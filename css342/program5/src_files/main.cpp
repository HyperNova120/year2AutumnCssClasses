#include <iostream>
#include <fstream>
#include <queue>
#include "Bank.h"
#include <string>
#include <sstream>

using namespace std;

vector<string> split(string s, char delim)
{
    vector<string> tmp = vector<string>();
    stringstream ss = stringstream(s);
    string token;
    while (getline(ss, token, delim))
    {
        if (token.length() != 0)
        {
            tmp.push_back(token);
        }
    }
    return tmp;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Must Use With a File Name" << endl;
        return 0;
    }
    queue<vector<string>> transaction_orders;
    string file_name(argv[1]);

    ifstream ifs(file_name);
    if (!ifs.is_open())
    {
        cout << "File Does Not Exist" << endl;
        return 0;
    }
    string line;
    while (getline(ifs, line))
    {
        if (line.at(line.length() - 1) == '\r')
        {
            line.pop_back();
        }
        vector<string> tmp = split(line, ' ');
        transaction_orders.push(tmp);
    }
    ifs.close();
    Bank bank = Bank();

    while (!transaction_orders.empty())
    {
        bank.RunTransaction(transaction_orders.front());
        transaction_orders.pop();
    }
    cout << bank << endl;
}