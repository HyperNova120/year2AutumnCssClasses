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
    /// @brief constructor
    CommandTransaction();

    /// @brief constructor
    /// @param segmentedCommand command segments to setup from
    CommandTransaction(vector<string> segmentedCommand);

    /// @brief ostream overload
    friend ostream &operator<<(ostream &stream, const CommandTransaction &transaction);

    TransactionType GetTransactionType() const; // get transaction type
    int User_Id() const;                        // get user id
    string User_Name() const;                   // get username
    char Media_Type() const;                    // get media type
    char Movie_Type() const;                    // get movie type
    string Director() const;                    // get director
    string Title() const;                       // get title
    int Date_Month() const;                     // get month
    int Date_Year() const;                      // get year
    string Major_Actor() const;                 // get major actor
    int Stock() const;                          // get stock

    bool isInvalid_ = false;                // is transaction invalid
    string errorMessage_ = "Default Error"; // error message

private:
    /// @brief use raw command segments to fill in movie info
    /// @param segmentedCommand raw command segments
    /// @param index current segment index
    void setupMovieInfo(vector<string> segmentedCommand, int &index);

    /// @brief
    /// @param segmentedCommand raw command segments
    /// @param index current segment index
    /// @return string of all segments until a comma is reached
    string concatUntilComma(vector<string> segmentedCommand, int &index);

    TransactionType t_type_ = TransactionType::Invalid; // transaction type
    int user_id_ = 0;                                   // user id
    string user_name_ = "";                             // user name
    char media_type_ = 'D';                             // media type
    char movie_type_ = ' ';                             // movie type

    string director_ = "";    // director
    string title_ = "";       // title
    int date_month_ = 0;      // month made
    int date_year_ = 0;       // year made
    string major_actor_ = ""; // major actor
    int stock_ = 0;           // stock
};
#endif