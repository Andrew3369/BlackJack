#include "../inc/Card.hpp"


void Card::display() const
{
	std::string suitStr = getSuitSymbol();
	std::string rankStr = getRankSymbol();

	std::cout << "┌─────────┐\n";
	std::cout << "│ " << rankStr;
	std::cout << "       │\n";
	std::cout << "│         │\n";
	std::cout << "│    " << suitStr << "    │\n";
	std::cout << "│         │\n";
	std::cout << "│       " << rankStr;
	std::cout << " │\n";
	std::cout << "└─────────┘\n";
	std::cout << std::endl;

	/*switch (suit)
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
	}*/
	//std::cout << suitStr << " " << rankStr << " ";

	// TODO:
	// ascciii stuff figure out something lol
}


int Card::getValue() const
{
	// my eyes hurt
	switch (rank)
	{
		case Rank::Two: return 2;
		case Rank::Three: return 3;
		case Rank::Four: return 4;
		case Rank::Five: return 5;
		case Rank::Six: return 6;
		case Rank::Seven: return 7;
		case Rank::Eight: return 8;
		case Rank::Nine: return 9;
		case Rank::Ten:
		case Rank::Jack:
		case Rank::Queen:
		case Rank::King: return 10;

		case Rank::Ace: return 11; // not sure how to handle if the
			// ace is either 1 or 11 yet
	}
}

std::string Card::getSuitSymbol() const
{
	switch (suit)
	{
		case Suit::Hearts: return "♥";
		case Suit::Diamonds: return "♦";
		case Suit::Clubs: return "♣";
		case Suit::Spades: return "♠";
		default: return "Invalid suit";
	}
}

std::string Card::getRankSymbol() const
{
	switch (rank)
	{
		case Rank::Ace:
			return "A";
		case Rank::Two:
			return "2";
		case Rank::Three:
			return "3";
		case Rank::Four:
			return "4";
		case Rank::Five:
			return "5";
		case Rank::Six:
			return "6";
		case Rank::Seven:
			return "7";
		case Rank::Eight:
			return "8";
		case Rank::Nine:
			return "9";
		case Rank::Ten:
			return "10";
		case Rank::Jack:
			return "J";
		case Rank::Queen:
			return "Q";
		case Rank::King:
			return "K";
	}
}