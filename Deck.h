#pragma once

#include <algorithm>

#include "Card.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

class Deck
{
public:

	std::vector<Card> cards;

	void readDeckFromFile(const std::string& path)
	{
		std::ifstream deckFile(path);
		std::string cardLine;
		int i = 0;

		while (std::getline(deckFile, cardLine)) {
			Card currentCard;

			std::string del = "_";
            auto pos = cardLine.find(del);
			std::vector<std::string> v;
            while (pos != std::string::npos) {
				v.push_back(cardLine.substr(0, pos));
                cardLine.erase(0, pos + del.length());
                pos = cardLine.find(del);
            }
			v.push_back(cardLine);
			currentCard.cost = std::stoi(v[0]);
			v.erase(v.begin());
			currentCard.atk = std::stoi(v[0]);
			v.erase(v.begin());
			currentCard.def = std::stoi(v[0]);
			currentCard.max_def = currentCard.def;
			v.erase(v.begin());
			
			for (std::string s : v)
			{
				if (s == "0") { currentCard.capa.push_back(false); }
				else {currentCard.capa.push_back(true); }
			}
			cards.push_back(currentCard);
			i++;
		}
		deckFile.close();
	}
	
	void saveDeckToFile(const std::string& path)
	{
		std::ofstream deckFile(path);
		std::string cardLine;

		for (auto card : cards) {
			deckFile << card.cost << "_" << card.atk << "_" << card.def;
			for (bool capa : card.capa)
			{
				deckFile << "_" << capa;
			}
			deckFile << "\n";
		}

		deckFile.close();
	}
	
	void createRandomDeck()
	{
		std::ifstream cardListFile("completeCardList.txt");
		std::string cardLine;
		std::vector<std::vector<std::string>> bigV;
		while (std::getline(cardListFile, cardLine)) {
			Card currentCard;
			std::string del = "_";
			auto pos = cardLine.find(del);
			std::vector<std::string> v;
			while (pos != std::string::npos) {
				v.push_back(cardLine.substr(0, pos));
				cardLine.erase(0, pos + del.length());
				pos = cardLine.find(del);
			}
			v.push_back(cardLine);
			bigV.push_back(v);
		}
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(std::begin(bigV), std::end(bigV), g);
		for (int i = 0; i < 40; i++)
		{
			Card card;

			card.cost = std::stoi(bigV[i][0]);
			bigV[i].erase(bigV[i].begin());
			card.atk = std::stoi(bigV[i][0]);
			bigV[i].erase(bigV[i].begin());
			card.def = std::stoi(bigV[i][0]);
			card.max_def = card.def;
			bigV[i].erase(bigV[i].begin());
			
			for (std::string s : bigV[i])
			{
				if (s == "0") { card.capa.push_back(false); }
				else {card.capa.push_back(true); }
			}
			cards.push_back(card);
		}
		cardListFile.close();
	}
	
	void generateCardList(int maxCost)
	{
		float guardCost = 2.0;
		float flyCost = 1.0;
		float chargeCost = 2.0;
		std::vector<Card> cardList;
		float card_cost = 0.0;
		for (int attack = 0; attack <= maxCost * 2; attack++) {
			for (int defense = 1; defense <= maxCost * 2 + 1; defense++) {
				for (int i = 0; i < 8; i++)
				{
					bool capaArray[3] = {false, false, false};
					std::vector<bool> capaVector;
					if ((i >> 2) & 1)
					{
						card_cost += guardCost;
						capaArray[0] = true;
					}
					if ((i >> 1) & 1)
					{
						card_cost += flyCost;
						capaArray[1] = true;
					}
					if (i & 1)
					{
						card_cost += chargeCost;
						capaArray[2] = true;
					}
					card_cost += (float) (attack + defense) / 2.0;
					card_cost = std::floor(card_cost);
					
					if (card_cost <= 7.0)
					{
						for (bool capa : capaArray)
						{
							if (capa) { capaVector.push_back(true); }
							else {capaVector.push_back(false); }
						}
						cardList.push_back(Card{static_cast<int>(card_cost), attack, defense, capaVector, defense});
					}
					
					card_cost = 0;
				}
			}
		}
		cards = cardList;
	}
};