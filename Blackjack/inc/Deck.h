#pragma once
#include "../inc/Card.h"
#include <vector>
#include <vector>
#include <algorithm>
#include <random>


class Deck
{
private:
	std::vector<Card> cards; // Vector to store cards in the deck

    void shuffle();

public:
    Deck();

    void displayDeck();

    Card dealCard();
    void burnCard();

};