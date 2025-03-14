#include "transaction.h"

CommandTransaction::CommandTransaction(vector<string> segmentedCommand)
{

    if (segmentedCommand[0] == "F," ||
        segmentedCommand[0] == "D," ||
        segmentedCommand[0] == "C,")
    {
        t_type_ = TransactionType::InitMovie;
        int i = 0;
        setupMovieInfo(segmentedCommand, i);
        return;
    }
    else if (segmentedCommand[0] == "I")
    {
        t_type_ = TransactionType::Inventory;
        if (segmentedCommand.size() > 1)
        {
            isInvalid_ = true;
            errorMessage_ = "Invalid Number Of Fields For Inventory Command";
            return;
        }
        return;
    }
    else if (segmentedCommand[0] == "H")
    {
        t_type_ = TransactionType::History;
        user_id_ = stoi(segmentedCommand[1]);
        return;
    }
    else if (segmentedCommand[0] == "B")
    {
        t_type_ = TransactionType::Borrow;
    }
    else if (segmentedCommand[0] == "R")
    {
        t_type_ = TransactionType::Return;
    }
    else
    {
        bool isID = false;
        try
        {
            stoi(segmentedCommand[0]);
            isID = true;
        }
        catch (exception &e)
        {
        }
        if (segmentedCommand[0].length() == 4 && isID)
        {
            t_type_ = TransactionType::InitCustomer;
            user_id_ = stoi(segmentedCommand[0]);
            user_name_ = segmentedCommand[1] + " " + segmentedCommand[2];
        }
        else
        {
            isInvalid_ = true;
            errorMessage_ = "Invalid Command Type";
        }
        return;
    }

    // setup B or R
    int index = 1;
    user_id_ = stoi(segmentedCommand[index++]);
    media_type_ = segmentedCommand[index++][0];
    if (media_type_ != 'D')
    {
        isInvalid_ = true;
        errorMessage_ = "Invalid Media Type";
        return;
    }
    movie_type_ = segmentedCommand[index++][0];
    if (movie_type_ == 'F')
    {
        title_ = concatUntilComma(segmentedCommand, index);
        date_year_ = stoi(segmentedCommand[index++]);
    }
    else if (movie_type_ == 'D')
    {
        director_ = concatUntilComma(segmentedCommand, index);
        title_ = concatUntilComma(segmentedCommand, index);
    }
    else if (movie_type_ == 'C')
    {
        date_month_ = stoi(segmentedCommand[index++]);
        date_year_ = stoi(segmentedCommand[index++]);
        major_actor_ = segmentedCommand[index++] + " ";
        major_actor_ += segmentedCommand[index++];
    }
    else{
        isInvalid_ = true;
        errorMessage_ = "Invalid Movie Type";
    }
}

void CommandTransaction::setupMovieInfo(vector<string> segmentedCommand, int &index)
{
    string movieType = segmentedCommand[index++];
    if (movieType[movieType.length() - 1] == ',')
    {
        movieType = movieType.substr(0, movieType.length() - 1);
    }
    movie_type_ = movieType[0];
    stock_ = stoi(concatUntilComma(segmentedCommand, index));
    director_ = concatUntilComma(segmentedCommand, index);
    title_ = concatUntilComma(segmentedCommand, index);
    if (movie_type_ == 'C')
    {
        major_actor_ = segmentedCommand[index++] + " " ;
        major_actor_ += segmentedCommand[index++];
        date_month_ = stoi(segmentedCommand[index++]);
    }
    date_year_ = stoi(segmentedCommand[index++]);
}

string CommandTransaction::concatUntilComma(vector<string> segmentedCommand, int &index)
{
    string returner = "";

    while (returner.length() == 0 || returner[returner.length() - 1] != ',')
    {
        returner += " " + segmentedCommand[index++];
    }
    returner = returner.substr(1, returner.length() - 1);
    if (returner[returner.length() - 1] == ',')
    {
        returner = returner.substr(0, returner.length() - 1);
    }
    return returner;
}

ostream &operator<<(ostream &stream, const CommandTransaction &transaction)
{
    if (transaction.GetTransactionType() == TransactionType::InitMovie)
    {
        stream << transaction.Movie_Type() << ", " << transaction.Stock() << ", " << transaction.Director() << ", " << transaction.Title();
        if (transaction.movie_type_ == 'C')
        {
            stream << ", " << transaction.Major_Actor() << " " << transaction.Date_Month() << " " << transaction.Date_Year();
        }
        else
        {
            stream << ", " << transaction.Date_Year();
        }
    }
    else if (transaction.GetTransactionType() == TransactionType::InitCustomer)
    {
        stream << transaction.user_id_ << " " << transaction.user_name_;
    }
    else if (transaction.GetTransactionType() == TransactionType::Inventory)
    {
        stream << "I";
    }
    else if (transaction.GetTransactionType() == TransactionType::History)
    {
        stream << "H" << " " << transaction.User_Id();
    }
    else if (transaction.GetTransactionType() == TransactionType::Borrow ||
             transaction.GetTransactionType() == TransactionType::Return)
    {
        stream << ((transaction.GetTransactionType() == TransactionType::Borrow) ? "B" : "R");
        stream << " " << transaction.User_Id() << " " << transaction.Media_Type() << " " << transaction.Movie_Type();
        if (transaction.Movie_Type() == 'F')
        {
            stream << " " << transaction.Title() << ", " << transaction.Date_Year();
        }
        else if (transaction.Movie_Type() == 'C')
        {
            stream << " " << transaction.Date_Month() << " " << transaction.Date_Year();
            stream << " " << transaction.Major_Actor();
        }
        else if (transaction.Movie_Type() == 'D')
        {
            stream << " " << transaction.Director();
            stream << ", " << transaction.Title() << ",";
        }
    }
    return stream;
}

TransactionType CommandTransaction::GetTransactionType() const
{
    return t_type_;
}

int CommandTransaction::User_Id() const
{
    return user_id_;
}

string CommandTransaction::User_Name() const
{
    return user_name_;
}

char CommandTransaction::Media_Type() const
{
    return media_type_;
}

char CommandTransaction::Movie_Type() const
{
    return movie_type_;
}

string CommandTransaction::Director() const
{
    return director_;
}

string CommandTransaction::Title() const
{
    return title_;
}

int CommandTransaction::Date_Month() const
{
    return date_month_;
}

int CommandTransaction::Date_Year() const
{
    return date_year_;
}

string CommandTransaction::Major_Actor() const
{
    return major_actor_;
}

int CommandTransaction::Stock() const
{
    return stock_;
}
