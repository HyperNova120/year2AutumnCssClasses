#include "movieFactory.h"

Movie *MovieFactory::createMovie(CommandTransaction t)
{
    if (t.Movie_Type() == 'F')
    {
        return new Comedy(t.Stock(), t.Director(), t.Title(), t.Date_Year());
    }
    else if (t.Movie_Type() == 'D')
    {
        return new Drama(t.Stock(), t.Director(), t.Title(), t.Date_Year());
    } 
    else if (t.Movie_Type() == 'C')
    {
        return new Classic(t.Stock(), t.Director(), t.Title(), t.Major_Actor(), t.Date_Month(), t.Date_Year());
    }
    return nullptr;
}