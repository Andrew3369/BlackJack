#pragma once
#include "../inc/Card.h"
#include <vector>


class Player
{
private:
	int chips;
	std::vector<Card> hand;
	bool doubleDowned;

public:
	Player(int startingChips)
	{
		chips = startingChips;
		doubleDowned = false;
	}
	
	void displayHand() const;
	void addChips(int amount);
	int getChips() const;
	void removeChips(int amount);
	void addCard(Card card);
	int getTotalValue() const;
	void doubleDown();
	bool doubleDownded() const;
};