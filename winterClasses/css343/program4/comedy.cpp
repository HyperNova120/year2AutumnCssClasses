#include "comedy.h"

Comedy::Comedy(int stock, string director, string title, int year) : Movie(stock, director, title, year) {}

Comedy::Comedy(const Comedy &other) : Movie(other){}

Comedy::~Comedy()
{
}

bool Comedy::operator<(const Movie &other) const
{
    const Comedy *otherComedy = dynamic_cast<const Comedy *>(&other);
    if (otherComedy != nullptr)
    {
        if (title_ < otherComedy->title_)
        {
            return true;
        }
        else if (title_ == otherComedy->title_ &&
                 year_made_ < otherComedy->year_made_)
        {
            return true;
        }
    }
    return false;
}

string Comedy::toString() const
{
    string type = "F, ";
    string stock = to_string(stock_) + ", ";
    string director = director_ + ", ";
    string title = title_ + ", ";
    string releaseDate = to_string(year_made_);
    return type + stock + director + title + releaseDate;
}

ostream &operator<<(ostream &stream, const Comedy &movie)
{
    stream << movie.toString();
    return stream;
}
