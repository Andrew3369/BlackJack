#include "../inc/main.h"


int main(int argc, char* argv[])
{
	// Initializing the game
	Player* player = new Player(10000);
	Dealer* dealer = new Dealer();
	Deck deck;

	// Variables
	int input = 0;

	blackjack::InitializeGame(player, dealer, deck);

	//Display(player, dealer);
	// Main game
	for (;;)
	{
		blackjack::checkConditions(player, dealer);
		blackjack::Display(player, dealer);


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

			if (dealer->getTotalValue() > blackjack::BLACKJACK) 
			{
				std::cout << "Dealer busts! You win!\n";
				player->addChips(input * 2);
			}
			else if (dealer->getTotalValue() >= player->getTotalValue())
			{
				std::cout << "Dealer busts! You win!\n";
				player->addChips(input * 2);
			}
			else
			{
				std::cout << "Dealer wins!\n";
			}
			break;

		case 3: // Double down
			player->doubleDown();
			player->addCard(deck.dealCard());
			break;

		//case 4: // Split (whenever I get to this :/)
			//	break;

		default:
			std::cout << "Invalid input\n";
			break;
		}
	}

	blackjack::killGame(player, dealer);
	return 0;
}