#ifndef movieFactory_H
#define movieFactory_H
#include <string>
#include "transaction.h"
#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
using namespace std;

class MovieFactory{

    public:
    static Movie* createMovie(CommandTransaction t);//Will create the 3 types of movies
};
#endif