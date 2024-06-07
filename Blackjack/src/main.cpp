#include "../inc/Blackjack.hpp"

//HELLO ANDREW AND CARTER
int main(int argc, char* argv[])
{
	// Initializing the game
	Player* player = new Player(10000);
	Dealer* dealer = new Dealer();
	Deck* deck = new Deck();

	blackjack::StartGame(player, dealer, deck);
	blackjack::MainGameLoop(player, dealer, deck);
	blackjack::KillGame(player, dealer, deck);

	return 0;
}
