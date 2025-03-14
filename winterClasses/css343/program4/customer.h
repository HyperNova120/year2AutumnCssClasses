#ifndef customer_H
#define customer_H
#include <string>
#include <iostream>
#include <vector>
#include "transaction.h"
#include "movie.h"
using namespace std;

class Customer{

    public:
    Customer();
    Customer(int id, string name);

    int ID();
    string Name();


    vector<CommandTransaction> History() const;
    vector<Movie *> OutstandingBorrows() const;

    void AddToHistory(CommandTransaction &t);
    void AddToOutstandingBorrows(Movie *movie);
    void removeFromOutstandingBorrows(Movie *movie);

    private:
    int id_ = 0;
    string name_ = "";
    vector<CommandTransaction> history_ = vector<CommandTransaction>();
    vector<Movie *> outstandingBorrows_ = vector<Movie *>();
};
#endif