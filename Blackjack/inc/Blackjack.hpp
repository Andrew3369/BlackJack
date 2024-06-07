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

	void MainGameLoop(Player* player, Dealer* dealer, Deck* deck);
	void StartGame(Player* player, Dealer* dealer, Deck* deck);
	void KillGame(Player* player, Dealer* dealer, Deck* deck);
	void GameConditions(Player* player, Dealer* dealer, Deck* deck);
	/*void checkPlayerConditions(Player* player);
	void checkDealerConditions(Dealer* dealer);*/ //eventually :p
	void Display(Player* player, Dealer* dealer);
	void DisplayFullHands(Player* player, Dealer* dealer);
	void ResetGame(Player* player, Dealer* dealer, Deck* deck);
	void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck);


	void MainGameLoop(Player* player, Dealer* dealer, Deck* deck)
	{
		int input = 0;

		for (;;)
		{
			blackjack::Display(player, dealer);
			blackjack::GameConditions(player, dealer, deck);

			std::cout << "\n| 1. Hit | 2. Stand | 3. Double |\n";
			std::cin >> input;

			switch (input)
			{
			case 1: // Hit
				player->addCard(deck->dealCard());
				break;

			case 2: // Stand
				blackjack::DealerStandPlay(player, dealer, deck);
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
	}

	void StartGame(Player* player, Dealer* dealer, Deck* deck)
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

	void ResetGame(Player* player, Dealer* dealer, Deck* deck)
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

	void GameConditions(Player* player, Dealer* dealer, Deck* deck)
	{
		if (player->getChips() <= 0)
		{
			std::cout << "You're out of chips! Game over!\n\n";
			blackjack::KillGame(player, dealer, deck);
		}
		else if (player->getTotalValue() > BLACKJACK)
		{
			std::cout << "Busted! Dealer Wins!\n\n";
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (player->getTotalValue() == BLACKJACK)
		{
			std::cout << "Blackjack! You win!\n\n";
			blackjack::ResetGame(player, dealer, deck);
		}

		// Dealer Conditions
		if (dealer->getTotalValue() > BLACKJACK)
		{
			std::cout << "Dealer busts! You win!\n\n";
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (dealer->getTotalValue() == BLACKJACK)
		{
			std::cout << "Dealer has blackjack! You lose!\n\n";
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (dealer->getTotalValue() == player->getTotalValue())
		{
			std::cout << "Push! Both Player and Dealer have the same amount!\n\n";
			blackjack::ResetGame(player, dealer, deck);
		}
	}

	void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck)
	{
		while (dealer->getTotalValue() < 17)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			dealer->addCard(deck->dealCard());
			std::cout << "\nDealer hits...\n";
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			blackjack::DisplayFullHands(player, dealer);
			blackjack::GameConditions(player, dealer, deck);
		}
	}

	void Display(Player* player, Dealer* dealer)
	{
		std::cout << "Dealer's Hand: ";
		dealer->displayHand();
		std::cout << std::endl << "Hand total: " << dealer->getFirstCardValue();
		std::cout << std::endl << std::endl;

		std::cout << "Player's Hand: ";
		player->displayHand();
		std::cout << std::endl << "Hand total: " << player->getTotalValue() << "\nPlayer's Chips: " << player->getChips() << std::endl;
	}

	void DisplayFullHands(Player* player, Dealer* dealer)
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