#include "classic.h"

Classic::Classic(int stock, string director, string title, string major_actor, int month, int year) : Movie(stock, director, title, year)
{
    major_actors_.insert(major_actor);
    month_made_ = month;
}

Classic::Classic(const Classic &other) : Movie(other)
{
    major_actors_ = other.major_actors_;
    month_made_ = other.month_made_;
}

Classic::~Classic()
{
    major_actors_.~AVLTree();
}

int Classic::Month()
{
    return month_made_;
}

void Classic::incrementStock(int amount)
{
    stock_ += amount;
}

bool Classic::operator<(const Movie &other) const
{
    const Classic *otherClassic = dynamic_cast<const Classic *>(&other);
    if (otherClassic != nullptr)
    {
        if (year_made_ < otherClassic->year_made_)
        {
            return true;
        }
        else if (year_made_ == otherClassic->year_made_ &&
                 month_made_ < otherClassic->month_made_)
        { 
            return true;
        }
        else if (year_made_ == otherClassic->year_made_ &&
                 month_made_ == otherClassic->month_made_ &&
                 *const_cast<Classic*>(this)->major_actors_.last() < *const_cast<Classic*>(otherClassic)->major_actors_.begin())
        {
            return true; 
        }
    }
    
    return false;
}

string Classic::toString() const
{
    string returner = "";
    for (string curMajorActor : const_cast<Classic*>(this)->major_actors_)
    {
        string type = "C, ";
        string stock = to_string(stock_) + ", ";
        string director = director_ + ", ";
        string title = title_ + ", ";
        string majorActor = curMajorActor + " ";
        string releaseDate = to_string(month_made_) + " " + to_string(year_made_);
        returner += type + stock + director + title + majorActor + releaseDate;
        if (curMajorActor != *const_cast<Classic*>(this)->major_actors_.last())
        {
            returner += "\n";
        }
    }
    return returner;
}

AVLTree<string> Classic::Major_Actors() const
{
    return major_actors_;
}

void Classic::addToMajorActors(string major_actor)
{
    major_actors_.insert(major_actor);
}

ostream &operator<<(ostream &stream, const Classic &movie)
{
    stream << movie.toString();
    return stream;
}
