#include "Transaction.h"

Transaction::Transaction(vector<string> raw_transaction_order)
{
    if (raw_transaction_order[0] == "O")
    {
        transaction_type_ = O;
        uid_ = stoi(raw_transaction_order[1]);
        first_name_ = raw_transaction_order[2];
        last_name_ = raw_transaction_order[3];
    }
    else if (raw_transaction_order[0] == "D")
    {
        transaction_type_ = D;
        uid_ = stoi(raw_transaction_order[1]);
        fund_id_ = stoi(raw_transaction_order[2]);
        amount_ = stoi(raw_transaction_order[3]);
    }
    else if (raw_transaction_order[0] == "W")
    {
        transaction_type_ = W;
        uid_ = stoi(raw_transaction_order[1]);
        fund_id_ = stoi(raw_transaction_order[2]);
        amount_ = stoi(raw_transaction_order[3]);
    }
    else if (raw_transaction_order[0] == "T")
    {
        transaction_type_ = T;
        uid_ = stoi(raw_transaction_order[1]);
        fund_id_ = stoi(raw_transaction_order[2]);
        uid_to_ = stoi(raw_transaction_order[3]);
        fund_id_to_ = stoi(raw_transaction_order[4]);
        amount_ = stoi(raw_transaction_order[5]);
    }
    else if (raw_transaction_order[0] == "A")
    {
        transaction_type_ = A;
        uid_ = stoi(raw_transaction_order[1]);
    }
    else if (raw_transaction_order[0] == "F")
    {
        transaction_type_ = F;
        uid_ = stoi(raw_transaction_order[1]);
        fund_id_ = stoi(raw_transaction_order[2]);
    }
}

Transaction::Transaction(TransactionType type, int uid, int fund_id, long amount)
{
    transaction_type_ = type;
    uid_ = uid;
    fund_id_ = fund_id;
    amount_ = amount;
}

Transaction::Transaction(TransactionType type, int uid_from, int fund_id_from, int uid_to, int fund_id_to, long amount)
{
    transaction_type_ = type;
    uid_ = uid_from;
    fund_id_ = fund_id_from;

    uid_to_ = uid_to;
    fund_id_to_ = fund_id_to;

    amount_ = amount;
}

Transaction::Transaction(TransactionType type, int uid)
{
    transaction_type_ = type;
    uid_ = uid;
}

Transaction::Transaction(TransactionType type, int uid, int fund_id)
{
    transaction_type_ = type;
    uid_ = uid;
    fund_id_ = fund_id;
}

Transaction::Transaction(TransactionType type, int uid, string first_name, string last_name)
{
    transaction_type_ = type;
    uid_ = uid;
    first_name_ = first_name;
    last_name_ = last_name;
}

Transaction::Transaction(const Transaction &other)
{
    transaction_type_ = other.transaction_type_;
    uid_ = other.uid_;
    fund_id_ = other.fund_id_;
    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    fund_id_to_ = other.fund_id_to_;
    uid_to_ = other.uid_to_;
    amount_ = other.amount_;
    failed_ = other.failed_;
}

void Transaction::MarkAsFailed()
{
    failed_ = true;
}

void Transaction::SetAmount(int amount)
{
    amount_ = amount;
}

TransactionType Transaction::transaction_type() const
{
    return transaction_type_;
}

int Transaction::uid() const
{
    return uid_;
}

int Transaction::uid_to() const
{
    return uid_to_;
}

int Transaction::fund_id() const
{
    return fund_id_;
}

int Transaction::fund_id_to() const
{
    return fund_id_to_;
}

int Transaction::amount() const
{
    return amount_;
}

string Transaction::first_name() const
{
    return first_name_;
}

string Transaction::last_name() const
{
    return last_name_;
}

ostream &operator<<(ostream &os, const Transaction &obj)
{
    switch (obj.transaction_type_)
    {
    case O:
        os << "O " << to_string(obj.uid_) << " " << obj.first_name_ << " " << obj.last_name_;
        break;
    case D:
        os << "D " << to_string(obj.uid_) << " " << to_string(obj.fund_id_) << " " << to_string(obj.amount_);
        break;
    case W:
        os << "W " << to_string(obj.uid_) << " " << to_string(obj.fund_id_) << " " << to_string(obj.amount_);
        break;
    case T:
        os << "T " << to_string(obj.uid_) << " " << to_string(obj.fund_id_) << " " << to_string(obj.uid_to_) << " " << to_string(obj.fund_id_to_) << " " << to_string(obj.amount_);
        break;
    case A:
        os << "A " << to_string(obj.uid_);
        break;
    case F:
        os << "F " << to_string(obj.uid_) << " " << to_string(obj.fund_id_);
        break;
    }
    if (obj.failed_)
    {
        os << " (FAILED)";
    }
    return os;
}
