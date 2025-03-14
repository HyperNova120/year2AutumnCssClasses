#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_
#include <string>
using namespace std;
enum TransactionType
{
    B,
    R,
    I,
    H,
    NAt
};
enum TransactionMovieType
{
    F,
    D,
    C,
    NAm
};

class Transaction
{
public:
    Transaction();
    Transaction(const Transaction &other);

    bool SetupMovieData(int movieStock, string movieDirector, string movieTitle, int releaseYear);
    bool SetupMovieData(int movieStock, string movieDirector, string movieTitle, int releaseYear, int releaseMonth, string majorActorFirstName, string majorActorLastName);

    bool SetupActionData(TransactionType type, int customerID, string mediaType);

    bool SetupTransaction(string rawCommand);

    // movie params
    TransactionType Command_type() const;
    TransactionMovieType Movie_type() const;
    int Stock();
    string Director() const;
    string MajorActor_First() const;
    string MajorActor_First() const;
    string Title() const;
    int ReleaseYear() const;
    int ReleaseMonth() const;

    // customer params
    int Id() const;
    string Customer_First() const;
    string Customer_Last() const;

    // state
    bool invalid = false;

private:
    TransactionType command_type = NAt;

    // movie params
    TransactionMovieType movie_type = NAm;
    int stock = 0;
    string director = "";
    string majorActor_First = "";
    string majorActor_First = "";
    string title = "";
    int releaseYear = 0;
    int releaseMonth = 0;

    // customer params
    int id = 0;
    string customer_First = "";
    string customer_Last = "";

    // state
    bool invalid = false;
    string invalidReason = "";
};

#endif //_TRANSACTION_H_