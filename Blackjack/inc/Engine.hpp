#pragma once
#include "../inc/Card.hpp"
#include "../inc/Player.hpp"
#include "../inc/Dealer.hpp"
#include "../inc/Deck.hpp"
#include "../inc/colors.hpp"


class Engine
{
private:
	// instantiations of the objects required to play
	const Player* player;
	const Dealer* dealer;
	const Deck* deck;

private:
	// 
	const int g_BLACKJACK = 21;
	const int g_DEALER_STAND_THRESHOLD = 17;

public:
	// game logic
	const void MainDisplayPrint(void);
	void MainGameLoop(Player* player, Dealer* dealer, Deck* deck);
	inline void StartGame(Player* player, Dealer* dealer, Deck* deck);
	inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips, bool dealerFinished = false);
	void Display(const Player* player, const Dealer* dealer);
	inline void DisplayFullHands(const Player* player, const Dealer* dealer);
	inline void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck, int wageredChips);
	inline void PlayerDoubleDown(Player* player, Dealer* dealer, Deck* deck, int wageredChips);
	//void KillGame(Player* player, Dealer* dealer, Deck* deck);
	//inline void ResetGame(Player* player, Dealer* dealer, Deck* deck);

	Engine()
	{
		Player* player = new Player(10000);
		Dealer* dealer = new Dealer();
		Deck* deck = new Deck();
		try
		{
			player->addCard(deck->dealCard());
			dealer->addCard(deck->dealCard());
			player->addCard(deck->dealCard());
			dealer->addCard(deck->dealCard());
		}

		catch (const std::exception& error)
		{
			std::cerr << error.what() << " Inside of [blackjack::StartGame()]" << std::endl;
		}
	}
	~Engine()
	{
		delete player;
		delete dealer;
		delete deck;
		exit(0);
	}
};