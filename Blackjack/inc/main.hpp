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

	void StartGame(Player* player, Dealer* dealer, Deck* deck);
	void killGame(Player* player, Dealer* dealer, Deck* deck);
	void checkConditions(Player* player, Dealer* dealer, Deck* deck);
	void Display(Player* player, Dealer* dealer);
	// new
	void checkPlayerConditions(Player* player);
	void checkDealerConditions(Dealer* dealer);
	void ResetGame(Player* player, Dealer* dealer, Deck* deck);
	void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck);


	void StartGame(Player* player, Dealer* dealer, Deck* deck)
	{
		// Deal the cards
		player->addCard(deck->dealCard());
		dealer->addCard(deck->dealCard());
		player->addCard(deck->dealCard());
		dealer->addCard(deck->dealCard());
	}

	void ResetGame(Player* player, Dealer* dealer, Deck* deck)
	{
		try
		{
			player->removeCards();
			dealer->removeCards();
			StartGame(player, dealer, deck);;
		}
		catch (const std::exception& error)
		{
			std::cerr << error.what() << std::endl;
		}
	}

	void checkConditions(Player* player, Dealer* dealer, Deck* deck)
	{
		//int input = 0; // later
		if (player->getChips() <= 0)
		{
			std::cout << "You're out of chips! Game over!\n";
			blackjack::killGame(player, dealer, deck);
		}
		else if (player->getTotalValue() > BLACKJACK)
		{
			std::cout << "Busted! Dealer Wins!\n";
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (dealer->getTotalValue() > BLACKJACK)
		{
			std::cout << "Dealer busts! You win!\n";
			//player->addChips(input * 2); // later
			blackjack::ResetGame(player, dealer, deck);

		}
		else if (player->getTotalValue() == BLACKJACK)
		{
			std::cout << "Blackjack! You win!\n";
			//player->addChips(input * 2); // later
			blackjack::ResetGame(player, dealer, deck);

		}
		else if (dealer->getTotalValue() == BLACKJACK)
		{
			std::cout << "Dealer has blackjack! You lose!\n";
			blackjack::ResetGame(player, dealer, deck);
		}
		else if (dealer->getTotalValue() == player->getTotalValue())
		{
			std::cout << "Push! Both Player and Dealer have the same amount!\n";
			blackjack::ResetGame(player, dealer, deck);
		}
	}

	// TODO:
		/* when i get around to it, removes unnecessary ifs to check
		for either player or dealer */
		// mainly for the checkConditions() function, just shrink it.
		// we can eventually remove the function above
	void checkPlayerConditions(Player* player)
	{

	}

	void checkDealerConditions(Dealer* dealer)
	{

	}

	void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck)
	{
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

	void killGame(Player* player, Dealer* dealer, Deck* deck)
	{
		delete player;
		delete dealer;
		delete deck;
		exit(1);
	}
}