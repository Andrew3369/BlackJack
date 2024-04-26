#pragma once
#include <iostream>
#include <string>

// Pretty self explanatory
enum class Suit
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
	Count
};
enum class Rank
{
	Ace,
	Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
	Jack,
	Queen,
	King,
};

class Card
{
private:
	Suit suit;
	Rank rank;
	//std::string suitEmojis[4] = { "\u2665", "\u2666", "\u2663", "\u2660" };

public:
	Card(Suit s, Rank r) : suit(s), rank(r) {}

	void display() const;

	int getValue() const;

};