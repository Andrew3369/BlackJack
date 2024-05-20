#pragma once
#include "../inc/Player.hpp"

class Dealer
{
private:
	std::vector<Card> hand;

public:
	Dealer();
	~Dealer();

	void displayHand();
	void displayFullHand();
	void addCard(Card card);
	int getTotalValue() const;
	int getFirstCardValue() const;
};