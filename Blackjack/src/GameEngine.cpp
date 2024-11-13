#include "../inc/GameEngine.hpp"

void GameEngine::MainGameLoop()
{
    //StartGame();
    bool gameReset = false;

    while (true)
    {
        int32_t input, chipsWager = 0;

        if (gameReset || p_Player->getHandSize() == 0)
        {
            ResetGame();
			gameReset = false;
        }

        Display();
        if (GameConditions(chipsWager)) 
        {
            std::cout << "Press Enter to continue...\n";
            std::cin.ignore(1000, '\n');
            continue;
        }

        std::cout << "\n| 1. Hit | 2. Stand | 3. Double |\n";

        std::cin >> input;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (input)
        {
        case 1: // Hit
            p_Player->addCard(p_Deck->dealCard());
            break;

        case 2: // Stand
            DealerStandPlay(chipsWager);
            break;

        case 3: // Double down
            PlayerDoubleDown(chipsWager);
            break;

            //case 4:
                // split :\
				//break;

        default:
            std::cout << "Invalid input\n\n";
            break;
        }
    }
}

inline void GameEngine::StartGame()
{
    try
    {
        p_Player->addCard(p_Deck->dealCard());
        p_Dealer->addCard(p_Deck->dealCard());
        p_Player->addCard(p_Deck->dealCard());
        p_Dealer->addCard(p_Deck->dealCard());
    }

    catch (const std::exception& error)
    {
        std::cerr << error.what() << " Inside of [StartGame()]" << std::endl;
    }
}

inline void GameEngine::ResetGame()
{
    try
    {
        p_Player->removeCards();
        p_Dealer->removeCards();
        StartGame();
    }

    catch (const std::exception& error)
    {
        std::cerr << error.what() << " Inside of [ResetGame()]" << std::endl;
    }
}

inline bool GameEngine::GameConditions(int32_t wageredChips, bool dealerFinished)
{
    // p_Player Conditions
    if (p_Player->getChips() <= 0)
    {
        std::cout << "You're out of chips! Game over!\n\n\n\n";
        //KillGame(p_Player, dealer, deck);
        return true;
    }
    else if (p_Player->getTotalValue() > g_BLACKJACK)
    {
        std::cout << "Busted! Dealer Wins!\n\n\n\n";
        p_Player->removeChips(wageredChips);
        ResetGame();
        return true;
    }
    else if (p_Player->getTotalValue() == g_BLACKJACK)
    {
        std::cout << "Blackjack! You win!\n\n\n\n";
        p_Player->addChips(wageredChips);
        ResetGame();
        return true;
    }

    // Dealer Conditions if it was set to true on stand
    if (dealerFinished)
    {
        if (p_Dealer->getTotalValue() > g_BLACKJACK)
        {
            std::cout << "Dealer has " << p_Dealer->getTotalValue();
            std::cout << "Dealer busts! You win!\n\n\n\n";
            p_Player->addChips(wageredChips);
            ResetGame();
            return true;
        }
        else if (p_Dealer->getTotalValue() == g_BLACKJACK)
        {
            std::cout << "Dealer has blackjack! You lose!\n\n\n\n";
            p_Player->removeChips(wageredChips);
            ResetGame();
            return true;
        }
        else if (p_Dealer->getTotalValue() == p_Player->getTotalValue())
        {
            std::cout << "Push! Both Player and Dealer have the same amount!\n\n\n\n";
            ResetGame();
            return true;
        }
        else if (p_Dealer->getTotalValue() > p_Player->getTotalValue())
        {
            std::cout << "Dealer has " << p_Dealer->getTotalValue() << ", Dealer Wins!\n\n\n\n";
            p_Player->removeChips(wageredChips);
            ResetGame();
            return true;
        }
    }
    return false;
}

inline void GameEngine::DealerStandPlay(int32_t wageredChips)
{
    while (p_Dealer->getTotalValue() < g_DEALER_STAND_THRESHOLD)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p_Dealer->addCard(p_Deck->dealCard());
        std::cout << "\nDealer hits...\n";
        DisplayFullHands();
    }
    GameConditions(wageredChips, true);
}

inline void GameEngine::PlayerDoubleDown(int32_t chipsWager)
{
    if (p_Player->getChips() < chipsWager)
    {
        std::cout << "You don't have enough chips to double down!\n";
        return;
    }
    else
    {
        chipsWager *= 2;
        //chipsWager * 2;
        p_Player->addCard(p_Deck->dealCard());
        DealerStandPlay(chipsWager);
        GameConditions(chipsWager, true);
    }
}

void GameEngine::Display() const
{
    std::cout << "Dealer's Hand: \n"; p_Dealer->displayHand();
    std::cout << "\nHand total: " << p_Dealer->getFirstCardValue();
    std::cout << "\n------------------------\n";
    std::cout << "Player's Hand: \n"; p_Player->displayHand();
    std::cout << "\nHand total: " << p_Player->getTotalValue();
    std::cout << "\nPlayer's Chips: " << p_Player->getChips();
    std::cout << "\n========================\n";
}

inline void GameEngine::DisplayFullHands() const
{
    std::cout << "Dealer's Hand: \n"; p_Dealer->displayFullHand();
    std::cout << "\nHand total: " << p_Dealer->getTotalValue();
    std::cout << "\n------------------------\n";

    std::cout << "Player's Hand: \n"; p_Player->displayHand();
    std::cout << "\nHand total: " << p_Player->getTotalValue();
    std::cout << "\nPlayer's Chips: " << p_Player->getChips();
    std::cout << "\n========================\n";
}

//void Engine::KillGame(p_Player* p_Player, Dealer* dealer, Deck* deck)
//{
//    delete p_Player;
//    delete dealer;
//    delete deck;
//    exit(1);
//}

const void GameEngine::MainDisplayPrint(void)
{
    std::cout << color::printwithcolor <color::ansi_color_codes::bright_red>(" /$$$$$$$  /$$                     /$$          /$$$$$                     /$$      \n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("| $$__  $$| $$                    | $$         |__  $$                    | $$      \n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$      | $$  /$$$$$$   /$$$$$$$| $$   /$$\n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("| $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/      | $$ |____  $$ /$$_____/| $$  /$$/\n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("| $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/  /$$  | $$  /$$$$$$$| $$      | $$$$$$/ \n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("| $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$ | $$  | $$ /$$__  $$| $$      | $$_  $$ \n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("| $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$\\  $$\n");
    std::cout << color::printwithcolor < color::ansi_color_codes::bright_red>("|_______/ |__/ \\_______/ \\_______/|__/  \\__/ \\______/  \\_______/ \\_______/|__/  \\__/\n");
}