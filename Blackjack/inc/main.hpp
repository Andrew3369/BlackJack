#include <iostream>
#include "../inc/Card.hpp"
#include "../inc/Player.hpp"
#include "../inc/Dealer.hpp"
#include "../inc/Deck.hpp"
#include <chrono>
#include <thread>
#include <cstdlib>

namespace blackjack
{
	constexpr auto BLACKJACK = 21;

	void InitializeGame(Player* player, Dealer* dealer, Deck deck);
	void killGame(Player* player, Dealer* dealer);
	void checkConditions(Player* player, Dealer* dealer);
	void Display(Player* player, Dealer* dealer);

	void InitializeGame(Player* player, Dealer* dealer, Deck deck)
	{
		// Deal the cards
		player->addCard(deck.dealCard());
		dealer->addCard(deck.dealCard());
		player->addCard(deck.dealCard());
		dealer->addCard(deck.dealCard());
	}

	void checkConditions(Player* player, Dealer* dealer)
	{
		//int input = 0; // later
		if (player->getChips() <= 0)
		{
			std::cout << "You're out of chips! Game over!\n";
			blackjack::killGame(player, dealer);
		}
		if (player->getTotalValue() > BLACKJACK)
		{
			std::cout << "Busted! Dealer Wins!\n";
		}
		else if (player->getTotalValue() == BLACKJACK)
		{
			std::cout << "Blackjack! You win!\n";
			//player->addChips(input * 2); // later
		}
		else if (dealer->getTotalValue() == BLACKJACK)
		{
			std::cout << "Dealer has blackjack! You lose!\n";
		}
		else if (dealer->getTotalValue() == player->getTotalValue())
		{
			std::cout << "Push!  Both Player and Dealer have the same amount!\n";
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

	void killGame(Player* player, Dealer* dealer)
	{
		delete player;
		delete dealer;
		exit(1);
	}
}