#include "PlayingCard.h"

Card::Card()
{
    suite_ = KSpade;
    value_ = 13;
}

Card::Card(int value_in, CardSuite suite_in)
{
    suite_ = suite_in;
    if (value_in < 1 || value_in > 13)
    {
        value_in = 1;
    }
    value_ = value_in;
}

ostream& operator<<(ostream &os, const Card &card)
{
    os << card.value() << " of " << kSuites[card.suite()] << endl;
    return os;
}

CardSuite Card::suite() const
{
    return suite_;
}

int Card::value() const
{
    return value_;
}
