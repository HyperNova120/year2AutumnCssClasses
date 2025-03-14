#include "customer.h"

Customer::Customer()
{
}

Customer::Customer(int id, string name)
{
    id_ = id;
    name_ = name;
}

int Customer::ID()
{
    return id_;
}

string Customer::Name()
{
    return name_;
}

vector<CommandTransaction> Customer::History() const
{
    return history_;
}

vector<Movie *> Customer::OutstandingBorrows() const
{
    return outstandingBorrows_;
}

void Customer::AddToHistory(CommandTransaction &t)
{
    history_.push_back(t);
}

void Customer::AddToOutstandingBorrows(Movie *movie)
{
    outstandingBorrows_.push_back(movie);
}

void Customer::removeFromOutstandingBorrows(Movie *movie)
{
    auto itr = outstandingBorrows_.begin();
    while (itr != outstandingBorrows_.end() && *itr != movie)
    {
        ++itr;
    }
    if (*itr == movie)
    {
        outstandingBorrows_.erase(itr);
    }
}
