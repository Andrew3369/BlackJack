#include "../inc/Blackjack.hpp"

//HELLO ANDREW AND CARTER
int main(int argc, char* argv[])
{
	// Initializing the game
	Player* player = new Player(10000);
	Dealer* dealer = new Dealer();
	Deck* deck = new Deck();

	// smart pointers
	/*auto player = std::make_unique<Player>(10000);
	auto dealer = std::make_unique<Dealer>();
	auto deck = std::make_unique<Deck>();*/

	blackjack::MainDisplayPrint();
	blackjack::MainGameLoop(player, dealer, deck);
	blackjack::KillGame(player, dealer, deck);

	return 0;
}
