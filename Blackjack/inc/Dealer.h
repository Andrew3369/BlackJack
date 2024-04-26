#pragma once
#include "../inc/Player.h"

class Dealer
{
private:
	std::vector<Card> hand;


public:
	Dealer();
	~Dealer();

	void displayHand();
	void addCard(Card card);
};