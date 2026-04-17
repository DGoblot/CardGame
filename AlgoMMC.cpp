#include "AlgoMMC.h"
#include <fstream>
#include <iso646.h>
#include <string>
#include <random>

// void AlgoMMC::initCardQualityList()
// {
//     for (int i = 0; i < completeCardList.cards.size(); i++)
//     {
//         cardQuality.insert_or_assign(completeCardList.cards[i], 0);
//     }
// }
//
// void AlgoMMC::readCardQualityList(std::string path)
// {
//     std::fstream qualityFile(path);
//     std::string qualityLine;
//     int i = 0;
//     while (std::getline(qualityFile, qualityLine))
//     {
//         cardQuality.insert({ completeCardList.cards[i], std::stoi(qualityLine) });
//         i++;
//     }
// }

void AlgoMMC::saveCardQualityList(std::string path)
{
    std::ofstream qualityFile(path);
    std::string qualityLine;

    for (auto quality : cardQuality) {
        qualityFile << quality.second << "\n";
    }

    qualityFile.close();
}

void AlgoMMC::changeOneCard(Deck& deckToChange)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distrib1(0,29);
    int removedCardIndex = distrib1(g);
    //Card removedCard = deckToChange.cards[removedCardIndex];
    deckToChange.cards.erase(deckToChange.cards.begin() + removedCardIndex);
    //cardQuality.insert_or_assign(removedCard, cardQuality.at(removedCard) - 1);
    
    std::uniform_int_distribution<> distrib2(0, completeCardList.cards.size() - 1);
    
    while (true)
    {
        Card newCard = completeCardList.cards[distrib2(g)];
        if (std::count(deckToChange.cards.begin(), deckToChange.cards.end(), newCard) == 0)
        {
            deckToChange.cards.push_back(newCard);
            //cardQuality.insert_or_assign( newCard,  cardQuality.at(newCard) + 1 );
            break;
        }
    }
}
