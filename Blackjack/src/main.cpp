#include <iostream>
#include "../inc/Card.h"
#include "../inc/Player.h"
#include "../inc/Dealer.h"
#include "../inc/Deck.h"
#include <chrono> // eventually :c
#include <cstdlib>


int main()
{
	// Initializing the game
	Player player(1000);
	Dealer dealer;
	Deck deck;

	// Variables
	constexpr auto BLACKJACK = 21;
	int input = 0;

	// Deal the cards
	player.addCard(deck.dealCard());
	dealer.addCard(deck.dealCard());
	player.addCard(deck.dealCard());
	dealer.addCard(deck.dealCard());


	// Main game loop >:)
	for (;;)
	{
		// Print out the Dealer & Player's hands
		std::cout << "Dealer's Hand: ";
		dealer.displayHand();
		std::cout << std::endl << "Hand total: " << dealer.getFirstCardValue();
		std::cout << std::endl << std::endl;

		std::cout << "Player's Hand: ";
		player.displayHand();
		std::cout << std::endl << "Hand total: " << player.getTotalValue() << "\nPlayer's Chips: " << player.getChips() << std::endl;

		//// Conditions
		//if (dealer.getTotalValue() == BLACKJACK)
		//{
		//	std::cout << "Dealer has blackjack! You lose!\n";
		//	return 1;
		//}
		//if (player.getTotalValue() == BLACKJACK)
		//{
		//	std::cout << "You have blackjack! You win!\n";
		//	return 1;
		//}
		//else if (player.getTotalValue() > BLACKJACK)
		//{
		//	std::cout << "Busted! Dealer Wins!\n";
		//	return 1;
		//}

		std::cout << "\n\n1. Hit | 2. Stand | 3. Double\n";
		std::cin >> input;

		system("cls"); // Clear the console, easier to read and debug

		switch (input)
		{
			case 1: // Hit
				player.addCard(deck.dealCard());
				player.displayHand(); 
				std::cout << std::endl << "Hand total: " << player.getTotalValue() << std::endl;
				break;

			case 2: // Stand
				dealer.displayFullHand();
				dealer.getTotalValue();
				break;

			case 3: // Double down
				player.addCard(deck.dealCard());
				break;

			case 4: // Split (whenever I get to this :/)
				break;

			default:
				std::cout << "Invalid input\n";
				break;
		}
	}


	return 0;
}