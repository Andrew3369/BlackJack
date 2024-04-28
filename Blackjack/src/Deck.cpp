#include "../inc/Deck.h"
#include "../inc/Player.h"

// Initialize the deck
Deck::Deck()
{
    for (int suit = 0; suit < static_cast<int>(Suit::Count); ++suit)
    {
        for (int rank = 0; rank <= static_cast<int>(Rank::King); ++rank)
        {
            cards.push_back(Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
        }
    }
    shuffle();
}

// shuffle the deck
void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);
}


void Deck::displayDeck()
{
    // For each card in the vector deck, display each card
	for (const Card& card : cards)
	{
		//print to console
		card.display();
	}
}

Card Deck::dealCard()
{
    // If the cards vector is NOT empty
    if (!cards.empty())
    {
        // Remove the card from the top and display it
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

void Deck::burnCard()
{
    if (!cards.empty())
        cards.pop_back();
}