#include "../inc/Card.h"
using namespace std;

void Card::display() const
{
	string suitStr;
	string rankStr;

	// my eyes hurt even more now
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

	std::cout << suitStr << " " << rankStr << " ";
}


int Card::getValue() const
{
	// my eyes hurt
	switch (rank)
	{
		case Rank::Two:
			return 2;
		case Rank::Three:
			return 3;
		case Rank::Four:
			return 4;
		case Rank::Five:
			return 5;
		case Rank::Six:
			return 6;
		case Rank::Seven:
			return 7;
		case Rank::Eight:
			return 8;
		case Rank::Nine:
			return 9;

		// anything 10 and over is the same
		case Rank::Ten:
		case Rank::Jack:
		case Rank::Queen:
		case Rank::King:
			return 10;
		case Rank::Ace:
			// the value of Ace can be 1 or 11 depending on the situation
			return 11; // not sure how to handle this
	}
}