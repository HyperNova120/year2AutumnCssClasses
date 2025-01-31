
#ifndef _SRC_FILES_TRANSACTION_H_
#define _SRC_FILES_TRANSACTION_H_

#include <string>
#include <queue>
#include <iostream>
using namespace std;

enum TransactionType
{
    O,
    D,
    W,
    T,
    A,
    F
};
class Transaction
{
public:
    Transaction(vector<string> raw_transaction_order);
    Transaction(TransactionType type, int uid, int fund_id, long amount);
    Transaction(TransactionType type, int uid_from, int fund_id_from, int uid_to, int fund_id_to, long amount);
    Transaction(TransactionType type, int uid);
    Transaction(TransactionType type, int uid, int fund_id);
    Transaction(TransactionType type, int uid, string first_name, string last_name);
    Transaction(const Transaction &other);

    void MarkAsFailed();

    friend ostream &operator<<(ostream &os, const Transaction &obj);

    void SetAmount(int amount);

    TransactionType transaction_type() const;
    int uid() const;
    int uid_to() const;
    int fund_id() const;
    int fund_id_to() const;
    int amount() const;
    string first_name() const;
    string last_name() const;
    bool failed() const;

private:
    TransactionType transaction_type_;
    int uid_ = 0;
    int uid_to_ = 0;
    int fund_id_ = 0;
    int fund_id_to_ = 0;
    int amount_ = 0;
    string first_name_ = "";
    string last_name_ = "";
    bool failed_ = false;
};

#endif //_SRC_FILES_TRANSACTION_H_