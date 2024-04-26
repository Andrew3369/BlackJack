﻿#include "../inc/Card.h"
using namespace std;

void Card::display() const
{
	string suitStr;
	string rankStr;

	switch (suit)
	{
		case Suit::Hearts:
				suitStr = "Hearts";
				break;
		case Suit::Diamonds:
				suitStr = "Diamonds";
				break;
		case Suit::Clubs:
				suitStr = "Clubs";
				break;
		case Suit::Spades:
				suitStr = "Spades";
				break;
	}

	switch (rank)
	{
		case Rank::Ace:
				rankStr = "Ace";
				break;
		case Rank::Two:
				rankStr = "Two";
				break;
		case Rank::Three:
				rankStr = "Three";
				break;
		case Rank::Four:
				rankStr = "Four";
				break;
		case Rank::Five:
				rankStr = "Five";
				break;
		case Rank::Six:
				rankStr = "Six";
				break;
		case Rank::Seven:
				rankStr = "Seven";
				break;
		case Rank::Eight:
				rankStr = "Eight";
				break;
		case Rank::Nine:
				rankStr = "Nine";
				break;
		case Rank::Ten:
				rankStr = "Ten";
				break;
		case Rank::Jack:
				rankStr = "Jack";
				break;
		case Rank::Queen:
				rankStr = "Queen";
				break;
		case Rank::King:
				rankStr = "King";
				break;
	}

	std::cout << suitStr << " " << rankStr << std::endl;
}


Card::~Card()
{
}