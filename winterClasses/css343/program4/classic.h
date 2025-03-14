#ifndef classic_H
#define classic_H
#include <string>
#include "movie.h"
#include "avltree.h"
using namespace std;

class Classic : public Movie
{

public:
    Classic(int stock, string director, string title, string major_actor, int month, int year);
	Classic(const Classic &other);
    ~Classic();
    int Month();
    void incrementStock(int amount);

    bool operator<(const Movie &other) const override;

    string toString() const override;

    friend ostream &operator<<(ostream &stream, const Classic &movie);

    AVLTree<string>Major_Actors() const;
    void addToMajorActors(string major_actor);

private:
    int month_made_ = 0;
    AVLTree<string> major_actors_ = AVLTree<string>();
};
#endif 