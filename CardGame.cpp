#include "Game.h"
#include "AlgoMMC.h"

int main()
{
    Game game;
    Deck deckSubject;
    Deck bestDeck;
    Deck ennemyDeck;
    
    deckSubject.createRandomDeck();
    ennemyDeck.createRandomDeck();
    
    bestDeck = deckSubject;
    
    AlgoMMC algoMMC;
    algoMMC.completeCardList.readDeckFromFile("completeCardList.txt");
    
    int nbWinPlayer1 = 0;
    int nbWinPlayer2 = 0;
    int result;
    float bestWinrate = 0.0;
    for (int i = 0; i < 10000; i++)
    {
        std::string resultString;
        for (int j = 0; j < 500; j++)
        {
            Game newGame;
            newGame.player1.deck = deckSubject;
            newGame.player2.deck = ennemyDeck;
            if (j > 249) { result = newGame.lauchGame(newGame.player2, newGame.player1); }
            else { result = newGame.lauchGame(newGame.player1, newGame.player2); }
            if (result == 1) { nbWinPlayer1 += 1; }
            else { nbWinPlayer2 += 1; }
            
        }
        float winrate = nbWinPlayer1/500.0;
        if (winrate < bestWinrate)
        {
            deckSubject = bestDeck;
            algoMMC.changeOneCard(deckSubject);
        }
        else
        {
            bestDeck = deckSubject;
            deckSubject.saveDeckToFile("resultDeck.txt");
            bestWinrate = winrate;
        }
        
        std::cout << "Deck number " << (i+1) << ", the win-ratio for player 1 is " << winrate << ". Best winrate is " << bestWinrate << "\n";
        
        nbWinPlayer1 = 0;
        nbWinPlayer2 = 0;
        
        if (bestWinrate > 0.8)
        {
            ennemyDeck.readDeckFromFile("resultDeck.txt");
            bestWinrate = 0.0;
        }
    }
    deckSubject.saveDeckToFile("resultDeck.txt");
}