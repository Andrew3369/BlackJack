#include "../inc/main.hpp"


int main(int argc, char* argv[])
{
	// Initializing the game
	Player* player = new Player(10000);
	Dealer* dealer = new Dealer();
	Deck* deck = new Deck();
	int input = 0;

	blackjack::StartGame(player, dealer, deck);

	// Main game
	for (;;)
	{
		blackjack::Display(player, dealer);
		blackjack::GameConditions(player, dealer, deck);

		std::cout << "\n| 1. Hit | 2. Stand | 3. Double |\n";
		std::cin >> input;

		//system("cls"); // Clear the console, easier to read and debug

		switch (input)
		{
		case 1: // Hit
			player->addCard(deck->dealCard());
			break;

		case 2: // Stand
			blackjack::DealerStandPlay(player, dealer, deck);
			//blackjack::ResetGame(player, dealer, deck);
			break;

		//case 3: // Double down
		//	player->doubleDown();
		//	player->addCard(deck.dealCard());
		//	player->addChips(input * 2); // double down
		//	break;

		//case 4: // Split (whenever I get to this :/)
			//	break;

		default:
			std::cout << "Invalid input\n";
			break;
		}
	}

	blackjack::KillGame(player, dealer, deck);
	return 0;
}