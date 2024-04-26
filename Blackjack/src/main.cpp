#include <iostream>
#include "../inc/Card.h"
#include "../inc/Player.h"
#include "../inc/Dealer.h"
#include "../inc/Deck.h"

int main()
{
	Card card(Suit::Hearts, Rank::Ace);
	Player player(100);
	Dealer dealer;

	player.addCardToHand(card);
	
	Deck deck;
	deck.displayDeck();
	deck.dealCard().display();
	std::cout << std::endl;
	deck.burnCard();
	deck.displayDeck();
	int run = 0;
	
	// Main Game loop
	for (;;)
	{
		std::cout << "Dealer's Hand: ";

	}

	


	return 0;
}