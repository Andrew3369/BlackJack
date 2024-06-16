#include "../inc/Card.hpp"


void Card::display() const
{
	const wchar_t* suitStr = getSuitSymbol();
	const wchar_t * rankStr = getRankSymbol();

	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << L"┌─────────┐\n";
	std::wcout << L"\x2502 " << rankStr;
	std::wcout << L"       \x2502\n";
	std::wcout << L"│         │\n";
	std::wcout << L"│    " << suitStr << L"    │\n";
	std::wcout << L"│         │\n";
	std::wcout << L"│       " << rankStr;
	std::wcout << L" │\n";
	std::wcout << L"└─────────┘\n";
	std::wcout << std::endl;
	_setmode(_fileno(stdout), _O_TEXT);
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

const wchar_t* Card::getSuitSymbol() const
{
	switch (suit)
	{
		case Suit::Hearts: return L"\x2665";
		case Suit::Diamonds: return L"\x2666";
		case Suit::Clubs: return L"\x2663";
		case Suit::Spades: return L"\x2660";
	}
}

const wchar_t * Card::getRankSymbol() const
{
	const wchar_t * returnsymbol;
	switch (rank)
	{
		case Rank::Ace:
			returnsymbol = L"\x0041";
			return returnsymbol;
		case Rank::Two:
			returnsymbol = L"\x0032";
			return returnsymbol;
		case Rank::Three:
			returnsymbol = L"\x0033";
			return returnsymbol;
		case Rank::Four:
			returnsymbol = L"\x0034";
			return returnsymbol;
		case Rank::Five:
			returnsymbol = L"\x0035";
			return returnsymbol;
		case Rank::Six:
			returnsymbol = L"\x0036";
			return returnsymbol;
		case Rank::Seven:
			returnsymbol = L"\x0037";
			return returnsymbol;
		case Rank::Eight:
			returnsymbol = L"\x0038";
			return returnsymbol;
		case Rank::Nine:
			returnsymbol = L"\x0039";
			return returnsymbol;
		case Rank::Ten:
			returnsymbol = L"\x0031\x0030";
			return returnsymbol;
		case Rank::Jack:
			returnsymbol = L"\x004A";
			return returnsymbol;
		case Rank::Queen:
			returnsymbol = L"\x0051";
			return returnsymbol;
		case Rank::King:
			returnsymbol = L"\x004B";
			return returnsymbol;
	}
}