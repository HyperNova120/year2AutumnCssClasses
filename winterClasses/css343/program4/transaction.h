#ifndef transaction_H
#define transaction_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum class TransactionType
{
    Borrow,
    Return,
    Inventory,
    History,
    InitMovie,
    InitCustomer,
    Invalid
};
class CommandTransaction
{
public:
    CommandTransaction();
    CommandTransaction(vector<string> segmentedCommand);

    friend ostream &operator<<(ostream &stream, const CommandTransaction &transaction);

    TransactionType GetTransactionType() const;
    int User_Id() const;
    string User_Name() const;
    char Media_Type() const;
    char Movie_Type() const;
    string Director() const;
    string Title() const;
    int Date_Month() const;
    int Date_Year() const;
    string Major_Actor() const;
    int Stock() const;

    bool isInvalid_ = false;
    string errorMessage_ = "Default Error";

private:
    void setupMovieInfo(vector<string> segmentedCommand, int &index);
    string concatUntilComma(vector<string> segmentedCommand, int &index);

    TransactionType t_type_ = TransactionType::Invalid;
    int user_id_ = 0;
    string user_name_ = "";
    char media_type_ = 'D';
    char movie_type_ = ' ';

    string director_ = "";
    string title_ = "";
    int date_month_ = 0;
    int date_year_ = 0;
    string major_actor_ = "";
    int stock_ = 0;
};
#endif