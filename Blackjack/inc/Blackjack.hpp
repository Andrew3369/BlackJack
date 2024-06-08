#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "../inc/Card.hpp"
#include "../inc/Player.hpp"
#include "../inc/Dealer.hpp"
#include "../inc/Deck.hpp"

namespace blackjack
{
	constexpr int BLACKJACK = 21;
	constexpr int DEALER_STAND_THRESHOLD = 17;
	constexpr bool isRunning = true;

	void MainGameLoop(Player* player, Dealer* dealer, Deck* deck);
	inline void StartGame(Player* player, Dealer* dealer, Deck* deck);
	void KillGame(Player* player, Dealer* dealer, Deck* deck);
	inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips);
	/*void checkPlayerConditions(Player* player);
	void checkDealerConditions(Dealer* dealer);*/ //eventually :p
	inline void Display(Player* player, Dealer* dealer);
	inline void DisplayFullHands(Player* player, Dealer* dealer);
	inline void ResetGame(Player* player, Dealer* dealer, Deck* deck);
	inline void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck, int wageredChips);


	void MainGameLoop(Player* player, Dealer* dealer, Deck* deck)
	{
		blackjack::StartGame(player, dealer, deck);

		int input = 0;
		int chipsWager = 0;

		std::cout << "How much chips do you want to wager?\n";
		std::cin >> chipsWager;

		for (;;)
		{
			blackjack::Display(player, dealer);
			blackjack::GameConditions(player, dealer, deck, chipsWager);

			std::cout << "\n| 1. Hit | 2. Stand | 3. Double |\n";
			std::cin >> input;

			switch (input)
			{
			case 1: // Hit
				player->addCard(deck->dealCard());
				break;

			case 2: // Stand
				blackjack::DealerStandPlay(player, dealer, deck, chipsWager);
				break;

			case 3: // Double down
				player->doubleDown();
				player->addCard(deck->dealCard());
				blackjack::GameConditions(player, dealer, deck, chipsWager);
				player->addChips(input); // double down
				break;

			//case 4: // Split (whenever I get to this :/)
				//	break;

			default:
				std::cout << "Invalid input\n";
				break;
			}
		}
	}

	inline void StartGame(Player* player, Dealer* dealer, Deck* deck)
	{
		// Deal the cards
		try
		{
			player->addCard(deck->dealCard());
			dealer->addCard(deck->dealCard());
			player->addCard(deck->dealCard());
			dealer->addCard(deck->dealCard());
		}
		catch (const std::exception& error)
		{
			std::cerr << error.what() << " Inside of blackjack::StartGame()" << std::endl;
		}
	}

	inline void ResetGame(Player* player, Dealer* dealer, Deck* deck)
	{
		try
		{
			player->removeCards();
			dealer->removeCards();
			StartGame(player, dealer, deck);
		}
		catch (const std::exception& error)
		{
			std::cerr << error.what() << " Inside of blackjack::ResetGame()" << std::endl;
		}
	}

	inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips)
	{
		// Player Conditions
		if (player->getChips() <= 0)
		{
			std::cout << "You're out of chips! Game over!\n\n";
			blackjack::KillGame(player, dealer, deck);
		}
		else if (player->getTotalValue() > BLACKJACK)
		{
			std::cout << "Busted! Dealer Wins!\n\n";
			player->removeChips(wageredChips);
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (player->getTotalValue() == BLACKJACK)
		{
			std::cout << "Blackjack! You win!\n\n";
			player->addChips(wageredChips);
			blackjack::ResetGame(player, dealer, deck);
		}

		// Dealer Conditions
		if (dealer->getTotalValue() > BLACKJACK)
		{
			std::cout << "Dealer busts! You win!\n\n";
			player->addChips(wageredChips);
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (dealer->getTotalValue() == BLACKJACK)
		{
			std::cout << "Dealer has blackjack! You lose!\n\n";
			player->removeChips(wageredChips);
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (dealer->getTotalValue() == player->getTotalValue())
		{
			std::cout << "Push! Both Player and Dealer have the same amount!\n\n";
			blackjack::ResetGame(player, dealer, deck);
		}
	}

	inline void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck, int wagerChips)
	{
		while (dealer->getTotalValue() < 17)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			dealer->addCard(deck->dealCard());
			std::cout << "\nDealer hits...\n";
			blackjack::DisplayFullHands(player, dealer);
			blackjack::GameConditions(player, dealer, deck, wagerChips);
		}
	}

	inline void Display(Player* player, Dealer* dealer)
	{
		std::cout << "Dealer's Hand: ";
		dealer->displayHand();
		std::cout << std::endl << "Hand total: " << dealer->getFirstCardValue();
		std::cout << std::endl << std::endl;

		std::cout << "Player's Hand: ";
		player->displayHand();
		std::cout << std::endl << "Hand total: " << player->getTotalValue() << "\nPlayer's Chips: " << player->getChips() << std::endl;
	}

	inline void DisplayFullHands(Player* player, Dealer* dealer)
	{
		std::cout << "Dealer's Hand: ";
		dealer->displayFullHand();
		std::cout << std::endl << "Hand total: " << dealer->getTotalValue();
		std::cout << std::endl << std::endl;

		std::cout << "Player's Hand: ";
		player->displayHand();
		std::cout << std::endl << "Hand total: " << player->getTotalValue() << "\nPlayer's Chips: "; // << player->getChips() << std::endl;
	}

	void KillGame(Player* player, Dealer* dealer, Deck* deck)
	{
		delete player;
		delete dealer;
		delete deck;
		exit(1);
	}
}