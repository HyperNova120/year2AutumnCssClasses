#ifndef LECTURE3_CARD_H_
#define LECTURE3_CARD_H_

#include <iostream>
using namespace std;

enum CardSuite
{
    KHeart,
    KDiamond,
    KClub,
    KSpade
};
const string kSuites[4] = {"heart","diamond","club","spade"};

class Card
{
public:
    Card();
    Card(int value_in, CardSuite suite_in);

    CardSuite suite() const;
    int value() const;

    friend ostream &operator<<(ostream &os, const Card &card);

private:
    CardSuite suite_;
    int value_;
};

#endif //LECTURE3_CARD_H_