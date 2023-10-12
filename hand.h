#include <list>
#include <random>

class Hand
{
    int deck[13] = {1,2,3,4,5,6,7,8,9,10,10,10,10};

    int randCard()
    {
        return deck[rand() % 13];
    }

public:    
    // things that ain't an ace
    std::list<int> cards;
    void giveCard()
    {
        cards.push_back(randCard());
    }

    int value()
    {
        int total = 0;
        int aces = 0;
        for(auto card : this->cards)
        {
            total += card;
            if(card == 1)
            {
                aces += 1;
            }
        }
        // choose if we should promote an ace or not.
        if(total <= 11 && aces > 0)
        {
            total += 10;
        }
        return total;
    }

    bool BJ()
    {
        return cards.size() == 2 && value() == 21;
    }
};