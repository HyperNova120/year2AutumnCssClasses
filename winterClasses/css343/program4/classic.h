#ifndef classic_H
#define classic_H
#include <string>
#include "movie.h"
#include "avltree.h"
using namespace std;

class Classic : public Movie
{

public:
    /// @brief constructor
    Classic(int stock, string director, string title, string major_actor, int month, int year);
    
    /// @brief copy constructor
    /// @param other Classic to copy
    Classic(const Classic &other);

    /// @brief deconstructor
    ~Classic();

    /// @brief incremend stock
    /// @param amount amount to increment by
    void incrementStock(int amount);

    /// @brief less than override
    /// @param other Movie to test against
    /// @return true if less than, false if not
    bool operator<(const Movie &other) const override;

    /// @brief convert movie to string
    /// @return string value of movie
    string toString() const override;
    void addToMajorActors(string major_actor);

    /// @brief ostream overload
    friend ostream &operator<<(ostream &stream, const Classic &movie);

    /// @brief get Major Actors
    /// @return major actors
    AVLTree<string> Major_Actors() const;

    /// @brief get month made
    /// @return month made
    int Month();

private:
    /// @brief month made
    int month_made_ = 0;

    /// @brief sorted list of major actors
    AVLTree<string> major_actors_ = AVLTree<string>();
};
#endif