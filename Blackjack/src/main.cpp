#include <iostream>
#include "../inc/Card.h"
#include "../inc/Player.h"
#include "../inc/Dealer.h"
#include "../inc/Deck.h"
#include <chrono> // eventually :c

int main()
{
	// Debugging stuff
	Player player(1000);
	Dealer dealer;
	Deck deck;
	int input = 0;

	//deck.displayDeck();
	player.addCard(deck.dealCard());
	dealer.addCard(deck.dealCard());

	player.addCard(deck.dealCard());
	dealer.addCard(deck.dealCard());

	std::cout << "Dealer's Hand: ";
	dealer.displayHand();
	std::cout << std::endl << "Hand total: " << dealer.getFirstCardValue();
	std::cout << std::endl << std::endl;

	std::cout << "Player's Hand: ";
	player.displayHand();
	std::cout << std::endl << "Hand total: " << player.getTotalValue();

	for (;;)
	{
		//player.addCard(deck.dealCard());
		//dealer.addCard(deck.dealCard());

		//player.addCard(deck.dealCard());
		//dealer.addCard(deck.dealCard());

		/*std::cout << "Dealer's Hand: ";
		dealer.displayHand();
		std::cout << std::endl << "Hand total: " << dealer.getFirstCardValue();
		std::cout << std::endl << std::endl;

		std::cout << "Player's Hand: ";
		player.displayHand();
		std::cout << std::endl << "Hand total: " << player.getTotalValue();*/

		std::cout << std::endl << std::endl << "1. Hit | 2. Stand | 3. Double\n";
		std::cin >> input;

		switch (input)
		{
		case 1:
			player.addCard(deck.dealCard());
			break;
		case 2:
			dealer.displayFullHand();
			dealer.getTotalValue();
			std::cout << std::endl << "Hand total: " << dealer.getTotalValue();
			//dealer.addCard(deck.dealCard());
			break;
		}
	}


	return 0;
}