#include "Player.h"

void Player::draw(int nb_cards)
{
    if (deck.cards.size() < nb_cards)
    {
        hp -= deck.cards.size() - nb_cards;
        return;
    }
    for (int i = 0; i < nb_cards; i++)
    {
        hand.push_back(deck.cards[i]);
        deck.cards.erase(deck.cards.begin() + i);
    }
}

void Player::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 g(rd());
        
    std::shuffle(std::begin(deck.cards), std::end(deck.cards), g);
}

int Player::highestPossibleCostInHand()
{
    int largestCostPossible = 0;
    int resultIndex = 99;
    int cardIndex = 0;
    for (Card card : hand)
    {
        if (card.cost > largestCostPossible && card.cost <= current_mp)
        {
            resultIndex = cardIndex;
            largestCostPossible = card.cost;
        }
        cardIndex++;
    }
    return resultIndex;
}

void Player::playCard(int cardIndex)
{
    current_mp -= hand[cardIndex].cost;
    activeCards.push_back(hand[cardIndex]);
    hand.erase(hand.begin() + cardIndex);
    
}