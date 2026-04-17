#pragma once
#include <unordered_map>

#include "Card.h"
#include "Deck.h"

class AlgoMMC
{
public:
    Deck completeCardList;
    std::unordered_map<int,int> cardQuality;
    
    // void initCardQualityList();
    // void readCardQualityList(std::string path);
    void saveCardQualityList(std::string path);
    
    void changeOneCard(Deck& deck);
};
