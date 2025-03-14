#include "movie.h"

Movie::Movie()
{
}

Movie::Movie(int stock, string director, string title, int year)
{
    stock_ = stock;
    director_ = director;
    title_ = title;
    year_made_ = year;
}

Movie::Movie(const Movie &other)
{
    stock_ = other.stock_;
    director_ = other.director_;
    title_ = other.title_;
    year_made_ = other.year_made_;
}

Movie::~Movie()
{
}

int Movie::Stock()
{
    return stock_;
}

int Movie::Year()
{
    return year_made_;
}

string Movie::Director()
{
    return director_;
}

char Movie::MediaType()
{
    return media_type_;
}

bool Movie::incrementStock()
{
    stock_++;
    return true;
}

bool Movie::decrementStock()
{
    stock_--;
    return true;
}

string Movie::Title()
{
    return title_;
}
