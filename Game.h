#pragma once
#include "Player.h"
#include <random>

class Game
{
public:
    Player player1;
    Player player2;
    
    int lauchGame(Player& firstPlayer, Player& secondPlayer);
    void takeTurn(Player& attacker, Player& defender);
    void awakeCards(Player& player);
};
