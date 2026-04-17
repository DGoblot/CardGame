#include "Game.h"

int Game::lauchGame(Player& firstPlayer, Player& secondPlayer)
{
    int turn = 1;
    
    player1.shuffleDeck();
    player2.shuffleDeck();
        
    player1.draw(player1.handSize);
    player2.draw(player2.handSize);
        
    while (player1.hp > 0 && player2.hp > 0)
    {
        awakeCards(firstPlayer);
        takeTurn(firstPlayer, secondPlayer);
        firstPlayer.draw(1);
        if (secondPlayer.hp > 0)
        {
            awakeCards(secondPlayer);
            takeTurn(secondPlayer, firstPlayer);
            secondPlayer.draw(1);
        }
        turn++;
    }
    if (player1.hp > 0) {return 1;}
    else {return 2;}
}
    
void Game::takeTurn(Player& attacker, Player& defender)
{
    attacker.current_mp = attacker.max_mp;
    while (attacker.highestPossibleCostInHand() != 99)
    {
        attacker.playCard(attacker.highestPossibleCostInHand());
    }
    
    int nbGuard = 0;
    int nbFlyGuard = 0;
    
    std::vector<Card> guardCards;
    
    for (Card& card : defender.activeCards)
    {
        if (card.capa[0])
        {
            if (card.capa[1])
            {
                nbFlyGuard++;
            }
            nbGuard++;
            guardCards.push_back(card);
        }
    }
    
    int i = 0;
    while (i < attacker.activeCards.size())
    {
        Card& attackingCard = attacker.activeCards[i];
        if (attackingCard.awake || attackingCard.capa[2])
        {
            if (nbGuard == 0 || (nbFlyGuard == 0 && attackingCard.capa[1])) { defender.hp -= attackingCard.atk;}
            else
            {
                int j = 0;
                while (j < defender.activeCards.size())
                {
                    Card& defenderCard = defender.activeCards[j];
                    if ((defenderCard.capa[0] && defenderCard.capa[1]) || defenderCard.capa[0] && !attackingCard.capa[1])
                    {
                        defenderCard.def -= attackingCard.atk;
                        attackingCard.def -= defenderCard.atk;
                        if (defenderCard.def <= 0)
                        {
                            defender.activeCards.erase(defender.activeCards.begin() + j);
                        } 
                        if (attackingCard.def <= 0)
                        {
                            attacker.activeCards.erase(attacker.activeCards.begin() + i);
                            i--;
                        }
                        break;
                    }
                    j++;
                }
            }
        }
        i++;
    }
    for (Card& card : defender.activeCards)
    {
        card.def = card.max_def;
    }
    attacker.max_mp += 1;
        
}
    
void Game::awakeCards(Player& player)
{
    for (Card& card : player.activeCards)
    {
        if (!card.awake) {card.awake = true;}
    }
}