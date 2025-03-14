#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include "transaction.h"
class Customer
{
public:
    Customer(int ID, string firstName, string lastName);
    Customer(const Customer &other);

    bool operator<(const Customer &other) const;
    bool operator<=(const Customer &other) const;
    bool operator>(const Customer &other) const;
    bool operator>=(const Customer &other) const;
    bool operator==(const Customer &other) const;
    bool operator!=(const Customer &other) const;

    void addTransactionToHistory(Transaction transactionToAdd);
    void printTransactionHistory();

private:
    int id = 0;
    string firstName = "";
    string lastName = "";

    struct transactionHistory
    {
        Transaction transaction;
        transactionHistory *next;
    };
    transactionHistory *root;
};

#endif //_CUSTOMER_H_