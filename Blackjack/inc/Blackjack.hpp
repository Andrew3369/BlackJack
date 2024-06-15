#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "../inc/Card.hpp"
#include "../inc/Player.hpp"
#include "../inc/Dealer.hpp"
#include "../inc/Deck.hpp"
#define KNRM  "\x1B[0m"
#define KBLK  "\x1b[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\x1B[0m"
#define BGREN "\x1b[42m"
namespace blackjack
{
    constexpr int BLACKJACK = 21;
    constexpr int DEALER_STAND_THRESHOLD = 17;

    void MainGameLoop(Player* player, Dealer* dealer, Deck* deck);
    inline void StartGame(Player* player, Dealer* dealer, Deck* deck);
    void KillGame(Player* player, Dealer* dealer, Deck* deck);
    inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips, bool dealerFinished = false);
    void Display(Player* player, Dealer* dealer);
    inline void DisplayFullHands(Player* player, Dealer* dealer);
    inline void ResetGame(Player* player, Dealer* dealer, Deck* deck);
    inline void DealerStandPlay(Player* player, Dealer* dealer, Deck* deck, int wageredChips);

    void MainGameLoop(Player* player, Dealer* dealer, Deck* deck) 
    {
        StartGame(player, dealer, deck);

        int chipsWager = 0;

        std::cout << "========================\n";
        std::cout << "       BLACKJACK        \n";
        std::cout << "========================\n\n";

        while (true) 
        {
            int input = 0;
            Display(player, dealer);
            GameConditions(player, dealer, deck, chipsWager);

            std::cout << "\n| 1. Hit | 2. Stand | 3. Double |\n";

            std::cin >> input;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }

            switch (input) 
            {
            case 1: // Hit
                player->addCard(deck->dealCard());
                break;

            case 2: // Stand
                DealerStandPlay(player, dealer, deck, chipsWager);
                break;

			//case 3: // Double down
			//	if (player->getChips() >= chipsWager)
			//	{
			//		player->addCard(deck->dealCard());
			//		chipsWager *= 2;
			//		player->removeChips(chipsWager);
			//		DealerStandPlay(player, dealer, deck, chipsWager);
   //             }

            //case 4:
				// split :\
				//break;

            default:
                std::cout << "Invalid input\n\n";
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
            std::cerr << error.what() << " Inside of [blackjack::StartGame()]" << std::endl;
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
            std::cerr << error.what() << " Inside of [blackjack::ResetGame()]" << std::endl;
        }
    }

    inline void GameConditions(Player* player, Dealer* dealer, Deck* deck, int wageredChips, bool dealerFinished)
    {
        // Player Conditions
        if (player->getChips() <= 0) 
        {
            std::cout << "You're out of chips! Game over!\n\n\n\n";
            KillGame(player, dealer, deck);
        }
        else if (player->getTotalValue() > BLACKJACK) 
        {
            std::cout << "Busted! Dealer Wins!\n\n\n\n";
            player->removeChips(wageredChips);
            ResetGame(player, dealer, deck);
            return;
        }
        else if (player->getTotalValue() == BLACKJACK) 
        {
            std::cout << "Blackjack! You win!\n\n\n\n";
            player->addChips(wageredChips);
            ResetGame(player, dealer, deck);
            return;
        }
        /*else if (player->getTotalValue() > dealer->getTotalValue())
        {
            std::cout << "Player has " << player->getTotalValue() << ", Player Wins!\n\n";
        }*/

        // Dealer Conditions
        if (dealerFinished)
        {
            if (dealer->getTotalValue() > BLACKJACK)
            {
                std::cout << "Dealer busts! You win!\n\n\n\n";
                player->addChips(wageredChips);
                ResetGame(player, dealer, deck);
                return;
            }
            else if (dealer->getTotalValue() == BLACKJACK)
            {
                std::cout << "Dealer has blackjack! You lose!\n\n\n\n";
                player->removeChips(wageredChips);
                ResetGame(player, dealer, deck);
                return;
            }
            else if (dealer->getTotalValue() == player->getTotalValue())
            {
                std::cout << "Push! Both Player and Dealer have the same amount!\n\n\n\n";
                ResetGame(player, dealer, deck);
                return;
            }
            else if (dealer->getTotalValue() > player->getTotalValue())
            {
                std::cout << "Dealer has " << dealer->getTotalValue() << ", Dealer Wins!\n\n\n\n";
                player->removeChips(wageredChips);
                ResetGame(player, dealer, deck);
                return;
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

    void Display(Player* player, Dealer* dealer)
    {
       
        std::cout << "Dealer's Hand: \n";
        dealer->displayHand();
        std::cout << "\nHand total: " << dealer->getFirstCardValue();
        std::cout << "\n------------------------\n";

        std::cout << "Player's Hand: \n";
        player->displayHand();
        std::cout << "\nHand total: " << player->getTotalValue();
        std::cout << "\nPlayer's Chips: " << player->getChips();
        std::cout << "\n========================\n";
    }

    inline void DisplayFullHands(Player* player, Dealer* dealer)
    {
        std::cout << "Dealer's Hand: \n";
        dealer->displayFullHand();
        std::cout << "\nHand total: " << dealer->getTotalValue();
        std::cout << "\n------------------------\n";

        std::cout << "Player's Hand: \n";
        player->displayHand();
        std::cout << "\nHand total: " << player->getTotalValue();
        std::cout << "\nPlayer's Chips: " << player->getChips();
        std::cout << "\n========================\n";
    }

    void KillGame(Player* player, Dealer* dealer, Deck* deck) 
    {
        delete player;
        delete dealer;
        delete deck;
        exit(1);
    }


    void maindisplayprint(void)
    {
        std::cout << KRED " /$$$$$$$  /$$                     /$$          /$$$$$                     /$$      \n" RESET;
        std::cout << KRED "| $$__  $$| $$                    | $$         |__  $$                    | $$      \n" RESET;
        std::cout << KRED "| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$      | $$  /$$$$$$   /$$$$$$$| $$   /$$\n" RESET;
        std::cout << KRED "| $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/      | $$ |____  $$ /$$_____/| $$  /$$/\n" RESET;
        std::cout << KRED "| $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/  /$$  | $$  /$$$$$$$| $$      | $$$$$$/ \n" RESET;
        std::cout << KRED "| $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$ | $$  | $$ /$$__  $$| $$      | $$_  $$ \n" RESET;
        std::cout << KRED "| $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$\\  $$\n" RESET;
        std::cout << KRED "|_______/ |__/ \\_______/ \\_______/|__/  \\__/ \\______/  \\_______/ \\_______/|__/  \\__/\n" RESET;
    }
}