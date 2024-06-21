#include "../inc/Dealer.hpp"

Dealer::Dealer() {}

Dealer::~Dealer() {}

// Start of the game (i think this is a good approach?)
void Dealer::displayHand()
{
	if (!hand.empty())
	{
		hand[0].display();
		//std::cout << " [Hidden Card]";
		displayBackCard();
	}
	else
	{
		std::cout << "Error in Dealer::displayHand()" << std::endl;
	}
}

// after the player chooses their action, THEN display the full hand
void Dealer::displayFullHand()
{
	for (const Card& card : hand)
	{
		card.display();
	}
}

void Dealer::displayBackCard() const
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << L"┌─────────┐\n";
	std::wcout << L"│	  │\n";
	std::wcout << L"│	  │\n";
	std::wcout << L"│	  │\n";
	std::wcout << L"|	  │\n";
	std::wcout << L"│	  │\n";
	std::wcout << L"│	  │\n";
	std::wcout << L"│	  │\n";
	std::wcout << L"└─────────┘\n";
	std::wcout << std::endl;
	_setmode(_fileno(stdout), _O_TEXT);
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

void Dealer::removeCards()
{
	hand.clear();
}