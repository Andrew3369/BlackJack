#pragma once
#include "../inc/Card.hpp"
#include <vector>
#include <algorithm>
#include <random>


class Deck
{
private:
	std::vector<Card> cards;

private:
    void shuffle();
    void CreateDeck();
    void burnDeck();

public:
    Deck();
    void displayDeck();
    Card dealCard();
};