#ifndef movie_H
#define movie_H
#include <string>
using namespace std;

class Movie
{

public:
    /// @brief default constructor
    Movie();

    /// @brief constructor
    Movie(int stock, string director, string title, int year);

    /// @brief copy constructor
    /// @param other movie to copy from
    Movie(const Movie &other);

    /// @brief deconstructor
    ~Movie();

    /// @brief get stock
    /// @return stock
    int Stock();

    /// @brief get year
    /// @return year made
    int Year();

    /// @brief get director
    /// @return director
    string Director();

    /// @brief get title
    /// @return title
    string Title();

    /// @brief get media type
    /// @return media type
    char MediaType();

    /// @brief increment stock
    /// @return true
    bool incrementStock();

    /// @brief decrement stock
    /// @return true
    bool decrementStock();

    /// @brief virtual less than override
    /// @param other move to compare against
    /// @return true if less than, false if not
    virtual bool operator<(const Movie &other) const = 0;

    /// @brief virtual to string
    /// @return movie with data as string
    virtual string toString() const = 0;

protected:
    char media_type_ = 'D'; // Dvd or vieo streaming
    string title_ = "";     // movie title
    int stock_ = 0;         // stock
    int year_made_ = 0;     // year made
    string director_ = "";  // director
};
#endif