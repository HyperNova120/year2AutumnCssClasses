#ifndef _CLASSIC_MOVIE_H_
#define _CLASSIC_MOVIE_H_

#include "movie.h"

class ClassicMovie : public Movie
{
public:
    ClassicMovie(MovieType type, int stock, string directorFirstName, string directorLastName, string title, int releaseYear, string majorActorFirstName, string majorActorLastName);
    ClassicMovie(ClassicMovie &other);

    bool operator<(const ClassicMovie &other) const;
    bool operator<=(const ClassicMovie &other) const;
    bool operator>(const ClassicMovie &other) const;
    bool operator>=(const ClassicMovie &other) const;
    bool operator==(const ClassicMovie &other) const;
    bool operator!=(const ClassicMovie &other) const;

    int ReleaseMonth() const;
    string MajorActorFirstName() const;
    string MajorActorLastName() const;

private:
    int releaseMonth = 0;
    string majorActorFirstName = "";
    string majorActorLastName = "";
};

#endif //_CLASSIC_MOVIE_H_