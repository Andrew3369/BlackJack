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
		blackjack::checkConditions(player, dealer, deck);


		std::cout << "\n1. Hit | 2. Stand | 3. Double\n";
		std::cin >> input;

		//system("cls"); // Clear the console, easier to read and debug

		switch (input)
		{
		case 1: // Hit
			player->addCard(deck->dealCard());
			break;

		case 2: // Stand
			while (dealer->getTotalValue() < 17)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				dealer->addCard(deck->dealCard());
				std::cout << "\nDealer hits...\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));
				blackjack::Display(player, dealer);
				std::cout << std::endl << "Hand total: " << dealer->getTotalValue() << std::endl;
				//blackjack::checkConditions(player, dealer, deck);
				// ^^^ should probably be here
			}
			blackjack::checkConditions(player, dealer, deck);
			blackjack::ResetGame(player, dealer, deck);

			/*if (dealer->getTotalValue() > blackjack::BLACKJACK) 
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
			}*/
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

	blackjack::killGame(player, dealer, deck);
	return 0;
}