#ifndef vendor_H
#define vendor_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "transaction.h"
#include <unordered_map>
#include "avltree.h"

#include "customer.h"
#include "movie.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"
#include "movieFactory.h"
using namespace std;

class vendor
{
public:
    /// @brief default constructor
    vendor();

    /// @brief deconstructor
    ~vendor();

    /// @brief read and run commands from a text file
    /// @param infile file name to read from
    void readFile(ifstream &infile);

    /// @brief process and execute the commandTransaction
    void processCommand(CommandTransaction &t);

private:

    /// @brief create new movie and add to sotred lists
    void createMovie(CommandTransaction &t);

    /// @brief create new customer with id and name, add to customer hash table
    /// @return true if successful
    bool createAccount(CommandTransaction &t);

    /// @brief print current inventory to cout
    /// @return true if successful
    bool printInventory();

    /// @brief print user history to cout
    /// @return true if successful
    bool printUserHistory(CommandTransaction &t);

    /// @brief increment movie stock by 1 and remove movie from customer outstanding borrows
    /// @return true if successful
    bool returnMovie(CommandTransaction &t);

    /// @brief decrement movie stock by 1 and add movie to customer outstanding borrows
    /// @return true if successful
    bool borrowMovie(CommandTransaction &t);

    /// @brief find and return read/write pointer to customer
    /// @return customer * if found, nullptr if not
    Customer *findCustomer(CommandTransaction &t);

    /// @brief find and return read/write pointer to movie
    /// @return movie* if found, nullptr if not
    Movie *findMovie(CommandTransaction &t);

    /// @brief validate that t is a valid command to run
    void validateCommand(CommandTransaction &t);

    /// @brief hash table of customers
    unordered_map<int, Customer> customer_data_ = unordered_map<int, Customer>();

    /// @brief sorted list of classic movies
    AVLTree<Classic *> classicMovies_ = AVLTree<Classic *>();

    /// @brief sotred list of drama movies
    AVLTree<Drama *> dramaMovies_ = AVLTree<Drama *>();

    /// @brief sorted list of comedy movies
    AVLTree<Comedy *> comedyMovies_ = AVLTree<Comedy *>();
};
#endif