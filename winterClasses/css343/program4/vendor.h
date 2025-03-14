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

class vendor{
    public:
    vendor();
    void readFile(ifstream& infile);
    void processCommand(CommandTransaction &t);

    private:
    void createMovie(CommandTransaction &t);
    bool createAccount(CommandTransaction &t);
    bool printInventory();
    bool printUserHistory(CommandTransaction &t);
    bool returnMovie(CommandTransaction &t);
    bool borrowMovie(CommandTransaction &t);
    Customer* findCustomer(CommandTransaction &t);
    Movie* findMovie(CommandTransaction &t);
    void validateCommand(CommandTransaction &t);


    unordered_map<int, Customer> customer_data_ = unordered_map<int, Customer>();
    AVLTree<Classic*> classicMovies_ = AVLTree<Classic*>();
    AVLTree<Drama*> dramaMovies_ = AVLTree<Drama*>();
    AVLTree<Comedy*> comedyMovies_ = AVLTree<Comedy*>(); 

    


};
#endif