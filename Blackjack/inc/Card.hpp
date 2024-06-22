#pragma once
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>


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

private:
	const wchar_t* getSuitSymbol(void) const;
	const wchar_t* getRankSymbol(void) const;

public:
	Card(Suit s, Rank r) : suit(s), rank(r) {}
	void display() const;
	int getValue() const;
};