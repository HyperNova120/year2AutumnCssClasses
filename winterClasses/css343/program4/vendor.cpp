#include "vendor.h"

void vendor::readFile(ifstream &infile)
{
    string line = "";
    while (getline(infile, line))
    {
        if (line[line.length() - 1] == '\r')
        {
            line = line.substr(0, line.length() - 1);
        }

        istringstream iss(line);
        string tmpstr = "";
        vector<string> segments;
        while (iss >> tmpstr)
        {
            segments.push_back(tmpstr);
        }
        CommandTransaction tmpTransaction(segments);
        validateCommand(tmpTransaction);
        if (tmpTransaction.isInvalid_)
        {
            cout << tmpTransaction.errorMessage_ << endl;
            continue;
        }
        processCommand(tmpTransaction);
    }
}

vendor::vendor() {}

void vendor::processCommand(CommandTransaction &t)
{
    if (t.isInvalid_)
    {
        cout << t.errorMessage_ << endl;
        return;
    }

    switch (t.GetTransactionType())
    {
    case TransactionType::Borrow:
        borrowMovie(t);
        break;
    case TransactionType::History:
        printUserHistory(t);
        break;
    case TransactionType::Inventory:
        printInventory();
        break;
    case TransactionType::Return:
        returnMovie(t);
        break;
    case TransactionType::InitCustomer:
        createAccount(t);
        break;
    case TransactionType::InitMovie:
        createMovie(t);
        break;
    }
}

void vendor::createMovie(CommandTransaction &t)
{
    if (t.Movie_Type() == 'C')
    {
        // classic
        for (Classic &tmpClassicMovie : classicMovies_)
        {
            if (tmpClassicMovie.Director() == t.Director() &&
                tmpClassicMovie.Title() == t.Title() &&
                tmpClassicMovie.Year() == t.Date_Year() &&
                tmpClassicMovie.Month() == t.Date_Month())
            {
                Classic *tmpMovie = classicMovies_.retrieve(&tmpClassicMovie);
                tmpMovie->incrementStock(t.Stock());
                tmpMovie->addToMajorActors(t.Major_Actor());
                return;
            }
        }
    }
    Movie *newMovie = MovieFactory::createMovie(t);
    if (t.Movie_Type() == 'F')
    {
        comedyMovies_.insert((Comedy *)newMovie);
    }
    else if (t.Movie_Type() == 'D')
    {
        dramaMovies_.insert((Drama *)newMovie);
    }
    else if (t.Movie_Type() == 'C')
    {
        classicMovies_.insert((Classic *)newMovie);
    }
}

bool vendor::createAccount(CommandTransaction &t)
{
    Customer newCustomer(t.User_Id(), t.User_Name());
    customer_data_[t.User_Id()] = newCustomer;
    return true;
}

bool vendor::printInventory()
{
    cout << "======INVENTORY======" << endl;

    cout << "==COMEDY==" << endl;
    for (Comedy &c : comedyMovies_)
    {
        cout << c << endl;
    }

    cout << "==Drama==" << endl;
    for (Drama &d : dramaMovies_)
    {
        cout << d << endl;
    }

    cout << "==Classic==" << endl;
    for (Classic &c : classicMovies_)
    {
        cout << c << endl;
    }

    cout << "======END INVENTORY======" << endl;

    return true;
}

bool vendor::printUserHistory(CommandTransaction &t)
{
    Customer *tmpCustomer = findCustomer(t);
    cout << "======User History For " << tmpCustomer->Name() << " ID:" << tmpCustomer->ID() << "======" << endl;
    for (CommandTransaction tmpT : tmpCustomer->History())
    {
        cout << "\t" << tmpT << endl;
    }
    cout << "======End User History======" << endl;
    return true;
}

bool vendor::returnMovie(CommandTransaction &t)
{

    Movie *requestedMovie = findMovie(t);
    Customer *currentCustomer = findCustomer(t);
    currentCustomer->removeFromOutstandingBorrows(requestedMovie);
    currentCustomer->AddToHistory(t);
    requestedMovie->incrementStock();

    return true;
}

bool vendor::borrowMovie(CommandTransaction &t)
{
    Movie *requestedMovie = findMovie(t);
    Customer *currentCustomer = findCustomer(t);
    currentCustomer->AddToOutstandingBorrows(requestedMovie);
    currentCustomer->AddToHistory(t);
    requestedMovie->decrementStock();
    return true;
}

Customer *vendor::findCustomer(CommandTransaction &t)
{
    if (customer_data_.find(t.User_Id()) != customer_data_.end())
    {
        // customer exists
        return &(*customer_data_.find(t.User_Id())).second;
    }
    else
    {
        // customer does not exist
        // cout << "No Customer With ID " << t.User_Id() << " Exists" << endl;
    }
    return nullptr;
}

Movie *vendor::findMovie(CommandTransaction &t)
{
    Movie *tmpMovie = MovieFactory::createMovie(t);
    Movie *returner = nullptr;
    if (t.Movie_Type() == 'F')
    {
        returner = comedyMovies_.retrieve((Comedy *)tmpMovie);
    }
    else if (t.Movie_Type() == 'D')
    {
        returner = dramaMovies_.retrieve((Drama *)tmpMovie);
    }
    else if (t.Movie_Type() == 'C')
    {
        Classic *tmpClassicMovie = (Classic *)tmpMovie;
        for (Classic &c : classicMovies_)
        {
            if (tmpClassicMovie->Year() == c.Year() &&
                tmpClassicMovie->Month() == c.Month())
            {
                returner = &c;
                break;
            }
        }
    }

    delete tmpMovie;
    tmpMovie = nullptr;

    if (returner == nullptr)
    {
        // movie not found
        return nullptr;
    }
    return returner;
}

void vendor::validateCommand(CommandTransaction &t)
{
    if (t.GetTransactionType() == TransactionType::History)
    {
        if (findCustomer(t) == nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Does Not Exist";
        }
        return;
    }
    else if (t.GetTransactionType() == TransactionType::Borrow)
    {
        Customer *tmpCustomer = findCustomer(t);
        if (tmpCustomer == nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Does Not Exist";
        }
        Movie *tmpMovie = findMovie(t);
        if (tmpMovie == nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "Movie Does Not Exist";
            return;
        }
        else if (t.Movie_Type() == 'C')
        {
            Classic *tmpClassic = (Classic *)tmpMovie;
            if (!tmpClassic->Major_Actors().contains(t.Major_Actor()))
            {
                t.isInvalid_ = true;
                t.errorMessage_ = "Movie Does Not Exist";
            }
        }

        if (tmpMovie->Stock() < 1)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "Movie Is Out Of Stock";
        }
    }
    else if (t.GetTransactionType() == TransactionType::Return)
    {
        Customer *tmpCustomer = findCustomer(t);
        if (tmpCustomer == nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Does Not Exist";
        }
        Movie *tmpMovie = findMovie(t);
        if (tmpMovie == nullptr)
        {
            // movie doesnt exist
            t.isInvalid_ = true;
            t.errorMessage_ = "Movie Does Not Exist";
            return;
        }
        else if (t.Movie_Type() == 'C')
        {
            Classic *tmpClassic = (Classic *)tmpMovie;
            if (!tmpClassic->Major_Actors().contains(t.Major_Actor()))
            {
                t.isInvalid_ = true;
                t.errorMessage_ = "Movie Does Not Exist";
            }
        }
        bool found = false;
        for (Movie *tmp : tmpCustomer->OutstandingBorrows())
        {
            if (tmp == tmpMovie)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Has Not Borrowed That Movie";
        }
    }
    else if (t.GetTransactionType() == TransactionType::InitCustomer)
    {
        Customer *tmpCustomer = findCustomer(t);
        if (tmpCustomer != nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Alraedy Exists";
        }
    }
    else if (t.GetTransactionType() == TransactionType::InitMovie)
    {
        if (t.Movie_Type() == 'C')
        {
            for (Classic &tmpClassicMovie : classicMovies_)
            {
                auto tmpMajorActors = tmpClassicMovie.Major_Actors();
                if (tmpClassicMovie.Director() == t.Director() &&
                    tmpClassicMovie.Title() == t.Title() &&
                    tmpClassicMovie.Year() == t.Date_Year() &&
                    tmpClassicMovie.Month() == t.Date_Month() &&
                    tmpMajorActors.contains(t.Major_Actor()))
                {
                    t.isInvalid_ = true;
                    t.errorMessage_ = "Movie Alraedy Exists";
                    break;
                }
            }
        }
        else
        {
            Movie *tmpMovie = findMovie(t);
            if (tmpMovie != nullptr)
            {
                t.isInvalid_ = true;
                t.errorMessage_ = "Movie Alraedy Exists";
            }
        }
    }
}
