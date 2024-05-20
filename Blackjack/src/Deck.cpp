#include "../inc/Deck.hpp"
#include "../inc/Player.hpp"
#include <thread>

Deck::Deck()
{
    std::thread createDeck(&Deck::CreateDeck, this);
	createDeck.join();
	std::thread shuffleDeck(&Deck::shuffle, this);
	shuffleDeck.join();
}

void Deck::CreateDeck()
{
    try
    {
        for (int suit = 0; suit < static_cast<int>(Suit::Count); ++suit)
        {
            for (int rank = 0; rank <= static_cast<int>(Rank::King); ++rank)
            {
                cards.push_back(Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
            }
        }
    }
	catch (const std::exception& ex)
	{
		std::cerr << "Exception occured inside of [Deck::CreateDeck()" << ex.what() << std::endl;
	}
}

void Deck::shuffle()
{
    try
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception occured inside of [Deck::CreateDeck()" << ex.what() << std::endl;
    }
}

void Deck::displayDeck()
{
    // For each card in the vector deck, display each card
	for (const Card& card : cards)
	{
		card.display();
	}
}

Card Deck::dealCard()
{
    // If the cards vector is NOT empty
    if (!cards.empty())
    {
        // Remove the card from the top
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
    else
    {
        // idk i just threw this here, not sure how to handle an empty deck
        return Card(Suit::Spades, Rank::Seven);
    }
}

void Deck::burnDeck()
{
    cards.clear();
}