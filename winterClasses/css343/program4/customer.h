#ifndef customer_H
#define customer_H
#include <string>
#include <iostream>
#include <vector>
#include "transaction.h"
#include "movie.h"
using namespace std;

class Customer
{

public:
    /// @brief default constructor
    Customer();
    /// @brief constructor
    Customer(int id, string name);

    /// @brief get ID
    /// @return ID
    int ID();

    /// @brief get Name
    /// @return name
    string Name();

    /// @brief get transaction history
    /// @return vector of transaction history
    vector<CommandTransaction> History() const;

    /// @brief get outstanding borrows
    /// @return vector of Movie* for outstanding borrows
    vector<Movie *> OutstandingBorrows() const;

    /// @brief adds command to history
    void AddToHistory(CommandTransaction &t);

    /// @brief add movie to outstanding borrows
    void AddToOutstandingBorrows(Movie *movie);

    /// @brief removes movie from outstanding borrows
    void removeFromOutstandingBorrows(Movie *movie);

private:
    /// @brief customer id
    int id_ = 0;

    /// @brief customer name
    string name_ = "";

    /// @brief list of transaction history
    vector<CommandTransaction> history_ = vector<CommandTransaction>();

    /// @brief hist of currently borrowed movies
    vector<Movie *> outstandingBorrows_ = vector<Movie *>();
};
#endif