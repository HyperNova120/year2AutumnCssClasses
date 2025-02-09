#ifndef _AUTOMATED_INVENTORY_SYSTEM_H_
#define _AUTOMATED_INVENTORY_SYSTEM_H_
#include "avltree.h"
#include "movie.h"
#include "classicMovie.h"
#include "transaction.h"
#include "customer.h"

class AutomatedInventorySystem
{
public:
    AutomatedInventorySystem();

    void ProcessCommand(string rawCommandLine);

private:
    bool CreateCustomer(Transaction transaction);
    bool CreateMovie(Transaction transaction);

    bool BorrowMovie(Transaction transaction);
    bool ReturnMovie(Transaction transaction);
    bool PrintInventory();
    bool PrintHistory(Transaction transaction);

    AVLTree<Movie> movies;

    // TODO Implement!!!
    // HashTable<Customer> customers
};

#endif //_AUTOMATED_INVENTORY_SYSTEM_H_