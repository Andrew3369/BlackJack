#include <iostream>
#include "../inc/Card.h"
#include "../inc/Player.h"
#include "../inc/Dealer.h"
#include "../inc/Deck.h"
#include <chrono>
#include <thread>
//#include <cstdlib>


void InitializeGame(Player* player, Dealer* dealer, Deck deck);
void killGame(Player* player, Dealer* dealer);


int main()
{
	// Initializing the game
	Player* player = new Player(1000);
	Dealer* dealer = new Dealer();
	Deck deck;

	// Variables
	constexpr auto BLACKJACK = 21;
	int input = 0;

	InitializeGame(player, dealer, deck);
	

	// Main game
	for (;;)
	{
		// Player wagers the # of chips
		if (player->getChips() <= 0)
		{
			std::cout << "You're out of chips! Game over!\n";
			return 1;
		}
		else
		{
			std::cout << "Total Chips: " << player->getChips() << "\nHow many chips do you want to bet: ";
			std::cin >> input;
			player->removeChips(input);
			std::cout << std::endl;
		}

		if (player->getTotalValue() > BLACKJACK)
		{
			std::cout << "Busted! Dealer Wins!\n";
			/*return 1;*/
		}

		std::cout << "Dealer's Hand: ";
		dealer->displayHand();
		std::cout << std::endl << "Hand total: " << dealer->getFirstCardValue();
		std::cout << std::endl << std::endl;

		std::cout << "Player's Hand: ";
		player->displayHand();
		std::cout << std::endl << "Hand total: " << player->getTotalValue() << "\nPlayer's Chips: " << player->getChips() << std::endl;

		std::cout << "\n\n1. Hit | 2. Stand | 3. Double\n";
		std::cin >> input;

		//system("cls"); // Clear the console, easier to read and debug

		switch (input)
		{
			case 1: // Hit
				player->addCard(deck.dealCard());
				//player.displayHand(); 
				std::cout << std::endl << "Hand total: " << player->getTotalValue() << std::endl;
				break;

			case 2: // Stand
				std::cout << "Dealer's Hand: "; dealer->displayFullHand();
				std::cout << std::endl << "Hand total: " << dealer->getTotalValue() << std::endl;
				std::cout << std::endl << std::endl;
				while (dealer->getTotalValue() < 17)
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
					dealer->addCard(deck.dealCard());
					std::cout << "\nDealer hits...\n";
					std::this_thread::sleep_for(std::chrono::seconds(1));
					std::cout << "\nDealer's hand: ";
					dealer->displayFullHand();
					std::cout << std::endl << "Hand total: " << dealer->getTotalValue() << std::endl;
				}

				if (dealer->getTotalValue() > BLACKJACK)
				{
					std::cout << "Dealer busts! You win!\n";
					player->addChips(input * 2);
					//return 1;
				}
				else if (dealer->getTotalValue() >= player->getTotalValue())
				{
					std::cout << "Dealer busts! You win!\n";
					player->addChips(input * 2);
					//return 1;
				}
				else
				{
					std::cout << "Dealer wins!\n";
					//return 1;
				}

				break;

			//case 3: // Double down
			//	player.addCard(deck.dealCard());
			//	break;

			//case 4: // Split (whenever I get to this :/)
			//	break;

			default:
				std::cout << "Invalid input\n";
				break;
		}
	}

	/*delete dealer;
	delete player;*/

	killGame(player, dealer);
	return 0;
}

void InitializeGame(Player* player, Dealer* dealer, Deck deck)
{
	// Deal the cards
	player->addCard(deck.dealCard());
	dealer->addCard(deck.dealCard());
	player->addCard(deck.dealCard());
	dealer->addCard(deck.dealCard());
}

void killGame(Player* player, Dealer* dealer)
{
	delete player;
	delete dealer;
}