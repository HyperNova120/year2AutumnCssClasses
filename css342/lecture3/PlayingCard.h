#ifndef LECTURE3_CARD_H_
#define LECTURE3_CARD_H_

enum CardSuite
{
    KHeart,
    KDiamond,
    KClub,
    KSpade
};

class Card
{
public:
    Card();
    Card(CardSuite suite_in, int value_in);

    CardSuite Suite() const;
    int value() const;

private:
    bool joker_;
    CardSuite suite_;
    int value_;
};

#endif // LECTURE3_CARD_H_