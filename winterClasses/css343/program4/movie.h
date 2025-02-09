#ifndef _MOVIE_H_
#define _MOVIE_H_

using namespace std;
#include <string>
enum MovieType
{
    Comedy,
    Drama,
    Classic,
    UNKNOWN
};
class Movie
{
public:
    Movie(MovieType type, int stock, string directorFirstName, string directorLastName, string title, int releaseYear);
    Movie(Movie &other);

    bool operator<(const Movie &other) const;
    bool operator<=(const Movie &other) const;
    bool operator>(const Movie &other) const;
    bool operator>=(const Movie &other) const;
    bool operator==(const Movie &other) const;
    bool operator!=(const Movie &other) const;

    int Stock() const;
    string Director() const;
    string Title() const;
    int ReleaseYear() const;

    bool IncreaseStock(const int amount);
    bool DecreaseStock(const int amount);

private:
    MovieType type = UNKNOWN;
    int stock = 0;
    string director = "";
    string title = "";
    int releaseYear = 0;
};

#endif //_MOVIE_H_