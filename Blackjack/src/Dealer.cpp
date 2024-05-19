#include "../inc/Dealer.h"

Dealer::Dealer() {}

Dealer::~Dealer() {}

// Start of the game (i think this is a good approach?)
void Dealer::displayHand()
{
	if (!hand.empty())
	{
		hand[0].display();
		std::cout << " [Hidden Card]";
	}
	else
	{
		std::cout << "No cards in hand?" << std::endl;
	}
}

// after the player chooses their action, THEN display the full hand
void Dealer::displayFullHand()
{
	// just in case things break :/
	for (const Card& card : hand)
	{
		card.display();
	}
}

void Dealer::addCard(Card card)
{
	hand.push_back(card);
}

int Dealer::getTotalValue() const
{
	int totalValue = 0;
	for (const Card& card : hand)
	{
		totalValue += card.getValue();
	}
	return totalValue;
}

int Dealer::getFirstCardValue() const
{
	if (!hand.empty())
	{
		return hand[0].getValue();
	}
	return NULL;
}