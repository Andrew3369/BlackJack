#include <iostream>
#include "../inc/Card.h"
#include "../inc/Player.h"
#include "../inc/Dealer.h"
#include "../inc/Deck.h"

int main()
{
	// Debugging stuff
	Player player(1000);
	Dealer dealer;
	Deck deck;

	//deck.displayDeck();
	
	player.addCard(deck.dealCard());
	dealer.addCard(deck.dealCard());

	player.addCard(deck.dealCard());
	dealer.addCard(deck.dealCard());
	

	std::cout << "Dealer's Hand: ";
	dealer.displayHand();
	std::cout << std::endl;

	std::cout << "Player's Hand: ";
	player.displayHand();
	std::cout << std::endl << "Hand total: " << player.getTotalValue();
	return 0;
}