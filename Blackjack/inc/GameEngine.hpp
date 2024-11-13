#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "../inc/Card.hpp"
#include "../inc/Player.hpp"
#include "../inc/Dealer.hpp"
#include "../inc/Deck.hpp"
#include "../inc/colors.hpp"

const int g_BLACKJACK = 21;
const int g_DEALER_STAND_THRESHOLD = 17;


class GameEngine
{
private:
	Player* p_Player;
	Dealer* p_Dealer;
	Deck* p_Deck;

public:
	// game logic
	const void MainDisplayPrint(void);
	void MainGameLoop();
	inline void StartGame();
	inline bool GameConditions(int32_t wageredChips, bool dealerFinished = false);
	void Display() const;
	inline void DisplayFullHands() const;
	inline void DealerStandPlay(int32_t wageredChips);
	inline void PlayerDoubleDown(int32_t wageredChips);
	//void KillGame(Player* player, Dealer* dealer, Deck* deck);
	inline void ResetGame();

	GameEngine(int32_t chips) : p_Player(), p_Dealer(), p_Deck()
	{
		p_Player = new Player(chips);
		p_Dealer = new Dealer();
		p_Deck = new Deck();

		try
		{
			p_Player->addCard(p_Deck->dealCard());
			p_Dealer->addCard(p_Deck->dealCard());
			p_Player->addCard(p_Deck->dealCard());
			p_Dealer->addCard(p_Deck->dealCard());
		}

		catch (const std::exception& error)
		{
			std::cerr << error.what() << " Inside of [blackjack::StartGame()]" << std::endl;
		}
	}

	~GameEngine()
	{
		delete p_Player;
		delete p_Dealer;
		delete p_Deck;
		printf("ending game completely...\n");
		exit(0);
	}
};