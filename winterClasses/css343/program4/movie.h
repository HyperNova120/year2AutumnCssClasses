#ifndef movie_H
#define movie_H
#include <string>
using namespace std;

class Movie
{

public:
    Movie();
    Movie(int stock, string director, string title, int year);
    Movie(const Movie &other);
    ~Movie();
    int Stock();
    int Year();
    string Director();
    string Title();
    char MediaType();

    bool incrementStock();
    bool decrementStock();

    virtual bool operator<(const Movie &other) const = 0;

    virtual string toString() const = 0;

protected:
    char media_type_ = 'D'; // Dvd or vieo streaming
    string title_ = "";
    int stock_ = 0;
    int year_made_ = 0;
    string director_ = "";
};
#endif