#include "../inc/Dealer.h"

Dealer::Dealer()
{
}

Dealer::~Dealer()
{
}

void Dealer::displayHand()
{
	for (const Card& card : hand)
	{
		card.display();
	}
}

void Dealer::addCard(Card card)
{
	hand.push_back(card);
}

