#include "PlayingCard.h"

Card::Card()
{
    suite_ = KSpade;
    value_ = 13;
}

Card::Card(CardSuite suite_in, int value_in)
{
    suite_ = suite_in;
    if (value_in < 1 || value_in > 13)
    {
        value_in = 1;
    }
    value_ = value_in;
}

CardSuite Card::Suite() const
{
    return suite_;
}

int Card::value() const
{
    return value_;
}
