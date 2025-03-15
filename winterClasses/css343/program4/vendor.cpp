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
    //printInventory();
}

vendor::vendor() {}

vendor::~vendor()
{
    for (Classic &c : classicMovies_)
    {
        Classic *c_ptr = &c;
        delete c_ptr;
    }
    for (Drama &d : dramaMovies_)
    {
        Drama *d_ptr = &d;
        delete d_ptr;
    }
    for (Comedy &c : comedyMovies_)
    {
        Comedy *c_ptr = &c;
        delete c_ptr;
    }
}

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
        //cout << "added:" << *((Comedy *)newMovie) << endl;
        comedyMovies_.insert((Comedy *)newMovie);
        /* if (comedyMovies_.contains((Comedy *)newMovie))
        {
            cout << "\tSUCCESS ADD" << endl;
        }
        cout << "CURRENT COMEDY MOVIES:" << endl;
        for (Comedy &d : comedyMovies_)
        {
            cout << "\t" << d << endl;
        }
        cout << endl << endl; */
    }
    else if (t.Movie_Type() == 'D')
    {
        //cout << "added:" << *((Drama *)newMovie) << endl;
        dramaMovies_.insert((Drama *)newMovie);
        /* if (dramaMovies_.contains((Drama *)newMovie))
        {
            cout << "\tSUCCESS ADD" << endl;
        }
        cout << "CURRENT DRAMA MOVIES:" << endl;
        for (Drama &d : dramaMovies_)
        {
            cout << "\t" << d << endl;
        }
        cout << endl << endl; */
    }
    else if (t.Movie_Type() == 'C')
    {
        //cout << "added:" << *((Classic *)newMovie) << endl;
        classicMovies_.insert((Classic *)newMovie);
        /* if (classicMovies_.contains((Classic *)newMovie))
        {
            cout << "\tSUCCESS ADD" << endl;
        }
        cout << "CURRENT CLASSIC MOVIES:" << endl;
        for (Classic &d : classicMovies_)
        {
            cout << "\t" << d << endl;
        }
        cout << endl << endl; */
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

    cout << endl;
    cout << "==COMEDY==" << endl;
    cout << endl;
    for (Comedy &c : comedyMovies_)
    {
        cout << c << endl;
    }

    cout << endl;
    cout << "==Drama==" << endl;
    cout << endl;
    for (Drama &d : dramaMovies_)
    {
        cout << d << endl;
    }

    cout << endl;
    cout << "==Classic==" << endl;
    cout << endl;
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
        delete tmpClassicMovie;
        tmpClassicMovie = nullptr;
        tmpMovie = nullptr;
    }

    if (tmpMovie != nullptr)
    {
        delete tmpMovie;
        tmpMovie = nullptr;
    }

    if (returner == nullptr)
    {
        // movie not found
        return nullptr;
    }
    return returner;
}

void vendor::validateCommand(CommandTransaction &t)
{
    // user validation
    if (t.GetTransactionType() == TransactionType::History ||
        t.GetTransactionType() == TransactionType::Borrow ||
        t.GetTransactionType() == TransactionType::Return)
    {
        if (findCustomer(t) == nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Does Not Exist";
            return;
        }
    }
    else if (t.GetTransactionType() == TransactionType::InitCustomer)
    {
        Customer *tmpCustomer = findCustomer(t);
        if (tmpCustomer != nullptr)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "User Already Exists";
            return;
        }
    }

    // movie validation
    Movie *tmpMovie = findMovie(t);
    if (t.GetTransactionType() == TransactionType::Borrow ||
        t.GetTransactionType() == TransactionType::Return)
    {
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
                return;
            }
        }
    }

    if (t.GetTransactionType() == TransactionType::Borrow)
    {
        // stock validation
        if (tmpMovie->Stock() < 1)
        {
            t.isInvalid_ = true;
            t.errorMessage_ = "Movie Is Out Of Stock";
            return;
        }
    }
    else if (t.GetTransactionType() == TransactionType::Return)
    {
        // previously borrowed validation
        bool found = false;
        for (Movie *tmp : findCustomer(t)->OutstandingBorrows())
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
            return;
        }
    }
    else if (t.GetTransactionType() == TransactionType::InitMovie)
    {
        // movie does not already exist validation
        if (t.Movie_Type() == 'C')
        {
            // if classical movie validate major actor is not already present
            for (Classic &tmpClassicMovie : classicMovies_)
            {
                if (tmpClassicMovie.Director() == t.Director() &&
                    tmpClassicMovie.Title() == t.Title() &&
                    tmpClassicMovie.Year() == t.Date_Year() &&
                    tmpClassicMovie.Month() == t.Date_Month() &&
                    tmpClassicMovie.Major_Actors().contains(t.Major_Actor()))
                {
                    // check if
                    t.isInvalid_ = true;
                    t.errorMessage_ = "Movie Already Exists";
                    return;
                }
            }
        }
        else
        {
            // validate movie does not already exist
            Movie *tmpMovie = findMovie(t);
            if (tmpMovie != nullptr)
            {
                t.isInvalid_ = true;
                t.errorMessage_ = "Movie Already Exists";
                return;
            }
        }
    }
}
