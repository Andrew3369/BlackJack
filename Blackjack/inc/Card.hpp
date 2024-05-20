#pragma once
#include <iostream>
#include <string>

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

public:
	Card(Suit s, Rank r) : suit(s), rank(r) {}
	void display() const;
	int getValue() const;
};