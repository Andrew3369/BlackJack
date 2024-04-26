#pragma once
#include "../inc/Card.h"
#include <vector>


class Player
{
private:
	int chips;
	std::vector<Card> hand;

public:
	Player(int startingChips) : chips(startingChips) {}

	void displayHand() const;

	void addChips(int amount);

	int constexpr getChips() const;

	void removeChips(int amount);

	void addCard(Card card);

};