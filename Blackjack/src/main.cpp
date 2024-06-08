#include "../inc/Blackjack.hpp"

//HELLO ANDREW AND CARTER
int main(int argc, char* argv[])
{
	// Initializing the game
	Player* player = new Player(10000);
	Dealer* dealer = new Dealer();
	Deck* deck = new Deck();
	// smart pointers
	/*std::unique_ptr<Player> player = std::make_unique<Player>(10000);
	std::unique_ptr<Dealer> dealer = std::make_unique<Dealer>();
	std::unique_ptr<Deck> deck = std::make_unique<Deck>();*/


	//blackjack::StartGame(player, dealer, deck);
	blackjack::MainGameLoop(player, dealer, deck);
	blackjack::KillGame(player, dealer, deck);

	return 0;
}
