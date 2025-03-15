#include "vendor.h"
#include "transaction.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int main()
{
    string moviesFile = "data4movies.txt";
    string customersFile = "data4customers.txt";
    string commandsFile = "data4commands.txt";

    ifstream moviesStream = ifstream(moviesFile);
    ifstream customersStream = ifstream(customersFile);
    ifstream commandsStream = ifstream(commandsFile);

    vendor MovieVendor = vendor();
    MovieVendor.readFile(moviesStream);
    MovieVendor.readFile(customersStream);
    MovieVendor.readFile(commandsStream); 
    return 0;
}