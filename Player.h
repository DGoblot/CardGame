#pragma once
#include "Deck.h"

class Player
{
public:
    int hp = 30;
    int max_mp = 4;
    int current_mp = 4;
    int handSize = 7;
    std::vector<Card> hand;
    Deck deck;
    std::vector<Card> discard;
    std::vector<Card> activeCards;
    void shuffleDeck();
    void draw(int nb_cards);
    int highestPossibleCostInHand();
    void playCard(int cardIndex);
};
