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

    void MainGameLoop(Player* player, Dealer* dealer, Deck* deck);
    inline void StartGame(Player* player, Dealer* dealer, Deck* deck);
    void KillGame(Player* player, Dealer* dealer, Deck* deck);
    inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips, bool dealerFinished = false);
    inline void Display(Player* player, Dealer* dealer);
    inline void DisplayFullHands(Player* player, Dealer* dealer);
    inline void ResetGame(Player* player, Dealer* dealer, Deck* deck);
    inline void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck, int wageredChips);

    void MainGameLoop(Player* player, Dealer* dealer, Deck* deck) 
    {
        StartGame(player, dealer, deck);

        int chipsWager = 0;

        while (true) 
        {
            int input = 0;
            Display(player, dealer);
            GameConditions(player, dealer, deck, chipsWager);

            std::cout << "\n| 1. Hit | 2. Stand | 3. Double |\n";
            std::cin >> input;

            switch (input) 
            {
            case 1: // Hit
                player->addCard(deck->dealCard());
                break;

            case 2: // Stand
                DealerStandPlay(player, dealer, deck, chipsWager);
                break;

            //case 3: // Double down
            //    player->doubleDown();
            //    player->addCard(deck->dealCard());
            //    GameConditions(player, dealer, deck, chipsWager);
            //    player->addChips(input); // double down
            //    break;

            //case 4:
				// split :\
				//break;

            default:
                std::cout << "Invalid input\n";
                break;
            }
        }
    }

    inline void StartGame(Player* player, Dealer* dealer, Deck* deck)
    {
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

    inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips, bool dealerFinished)
    {
        // Player Conditions
        if (player->getChips() <= 0) 
        {
            std::cout << "You're out of chips! Game over!\n\n";
            KillGame(player, dealer, deck);
        }
        else if (player->getTotalValue() > BLACKJACK) 
        {
            std::cout << "Busted! Dealer Wins!\n\n";
            player->removeChips(wageredChips);
            ResetGame(player, dealer, deck);
            return;
        }
        else if (player->getTotalValue() == BLACKJACK) 
        {
            std::cout << "Blackjack! You win!\n\n";
            player->addChips(wageredChips);
            ResetGame(player, dealer, deck);
            return;
        }
        else if (player->getTotalValue() > dealer->getTotalValue())
        {
            std::cout << "Player has " << player->getTotalValue() << ", Player Wins!\n\n";
        }

        // Dealer Conditions
        if (dealerFinished)
        {
            if (dealer->getTotalValue() > BLACKJACK)
            {
                std::cout << "Dealer busts! You win!\n\n";
                player->addChips(wageredChips);
                ResetGame(player, dealer, deck);
            }
            else if (dealer->getTotalValue() == BLACKJACK)
            {
                std::cout << "Dealer has blackjack! You lose!\n\n";
                player->removeChips(wageredChips);
                ResetGame(player, dealer, deck);
            }
            else if (dealer->getTotalValue() == player->getTotalValue())
            {
                std::cout << "Push! Both Player and Dealer have the same amount!\n\n";
                ResetGame(player, dealer, deck);
            }
            else if (dealer->getTotalValue() > player->getTotalValue())
            {
                std::cout << "Dealer has " << dealer->getTotalValue() << ", Dealer Wins!\n\n";
                player->removeChips(wageredChips);
                ResetGame(player, dealer, deck);
            }
        }
    }

    inline void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck, int wagerChips)
    {
        while (dealer->getTotalValue() < DEALER_STAND_THRESHOLD) 
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            dealer->addCard(deck->dealCard());
            std::cout << "\nDealer hits...\n";
            DisplayFullHands(player, dealer);
        }
        GameConditions(player, dealer, deck, wagerChips, true);
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
        std::cout << std::endl << "Hand total: " << player->getTotalValue() << "\nPlayer's Chips: " << player->getChips() << std::endl;
    }

    void KillGame(Player* player, Dealer* dealer, Deck* deck) 
    {
        delete player;
        delete dealer;
        delete deck;
        exit(1);
    }
}