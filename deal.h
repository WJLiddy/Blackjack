#include <list>
#include "hand.h"
#include "strategy.h"

class Deal
{
    public:
        Hand playerHand;
        Hand dealerHand;

    int execute(Strategy& strategy)
    {
        // deal cards
        playerHand.giveCard();
        playerHand.giveCard();

        dealerHand.giveCard();

        bool dd = false;

        // player hits.
        while(true)
        {
            // BJ
            if(playerHand.value() >= 21)
            {
                break;
            }
            // do the action
            auto action = strategy.getAction(playerHand.value(), dealerHand.value());
            
            if(action == Strategy::PlayerAction::H)
            {
                playerHand.giveCard();
            }
            else if(action == Strategy::PlayerAction::S)
            {
                break;
            }
            else if(action == Strategy::PlayerAction::D)
            {
                if(playerHand.cards.size() == 2)
                {
                    dd = true;
                }
                playerHand.giveCard();
                break;
            }
        }

        // player done hitting.
        // dealer shows upcard.
        dealerHand.giveCard();
        
        // handle BJs.
        if(dealerHand.BJ())
        {
            // push
            if(playerHand.BJ())
            {
                return 0;
            }
            // dealer win
            else
            {
                return -1;
            }
        }

        if(playerHand.BJ())
        {
            return 1;
        }

        // handle player bust
        if(playerHand.value() > 21)
        {
            return dd ? -2 : -1;
        }

        // dealer hits.
        while(true)
        {
            if(dealerHand.value() < 17)
            {
                dealerHand.giveCard();
            }
            else
            {
                if(dealerHand.value() > 21)
                {
                    return dd ? 2 : 1;
                }
                break;
            }
        }

        if(playerHand.value() == dealerHand.value())
        {
            return 0;
        }

        if(playerHand.value() > dealerHand.value())
        {
            return dd ? 2 : 1;
        }
        else
        {
            return dd ? -2 : -1;
        }
    }

    std::string print()
    {
        std::string s = "P ";
        for(auto card : playerHand.cards)
        {
            s += std::to_string(card) + " ";
        }
        s += " | D ";
        for(auto card : dealerHand.cards)
        {
            s += std::to_string(card) + " ";
        }
        return s;
    }
};