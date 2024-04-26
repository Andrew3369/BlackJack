#include "../inc/Dealer.h"

Dealer::Dealer()
{
}

Dealer::~Dealer()
{
}

void Dealer::displayHand()
{
	// Just in case things break :/
	/*for (const Card& card : hand)
	{
		card.display();
	}*/

	if (!hand.empty())
	{
		hand[0].display();
		std::cout << " [Hidden Card]" << std::endl;
	}
	else
	{
		std::cout << "No cards in hand?" << std::endl;
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