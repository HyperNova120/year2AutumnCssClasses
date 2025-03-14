#include "drama.h"

Drama::Drama(int stock, string director, string title, int year) : Movie(stock, director, title, year) {}

Drama::Drama(const Drama &other) : Movie(other) {}
Drama::~Drama()
{
}

bool Drama::operator<(const Movie &other) const
{
    const Drama *otherDrama = dynamic_cast<const Drama *>(&other);
    if (otherDrama != nullptr)
    {
        if (director_ < otherDrama->director_)
        {
            return true;
        }
        else if (director_ == otherDrama->director_ && title_ < otherDrama->title_)
        {
            return true;
        }
    }
    return false;
}

string Drama::toString() const
{
    string type = "D, ";
    string stock = to_string(stock_) + ", ";
    string director = director_ + ", ";
    string title = title_ + ", ";
    string releaseDate = to_string(year_made_);
    return type + stock + director + title + releaseDate;
}

ostream &operator<<(ostream &stream, const Drama &movie)
{
    stream << movie.toString();
    return stream;
}
