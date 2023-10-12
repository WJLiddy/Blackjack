#include <unordered_map>

class Strategy
{
    public:
        static const int PLAYER_MIN = 2;
        static const int PLAYER_MAX = 20;

        static const int DEALER_MIN = 2;
        static const int DEALER_MAX = 11;
        enum PlayerAction
        {
            H,S,D
        };

        Strategy()
        {
            // player card first
            for(int i = PLAYER_MIN; i <= PLAYER_MAX; i++)
            {
                auto dealer = std::unordered_map<int,PlayerAction>();
                // dealer card second
                for(int d = DEALER_MIN; d <= DEALER_MAX; d++)
                {
                    dealer[d] = PlayerAction::H;
                }
                strategy[i] = dealer;
            }        
        }

        PlayerAction getAction(int player, int dealer)
        {
            if(strategy.count(player) == 0)
            {
                throw std::invalid_argument("No such player card " + std::to_string(player));
            }
            if(strategy[player].count(dealer) == 0)
            {
                throw std::invalid_argument("No such dealer card " + std::to_string(dealer));
            }
            return strategy[player][dealer];
        }

        void setAction(int player, int dealer, PlayerAction action)
        {
            if(strategy.count(player) == 0)
            {
                return;
            }
            if(strategy[player].count(dealer) == 0)
            {
                return;
            }
            strategy[player][dealer] = action;
        }


    private:
        // player upcard, dealer upcard, action
        typedef std::unordered_map<int,std::unordered_map<int,PlayerAction>> StratMap;
        StratMap strategy;

};
