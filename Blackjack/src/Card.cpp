#include "../inc/Card.hpp"

#pragma warning (disable : 6031) // removes the warning from lines 10 and 21

void Card::display() const
{
	const wchar_t* suitStr = getSuitSymbol();
	const wchar_t* rankStr = getRankSymbol();

	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << L"┌─────────┐\n";
	if (rankStr == L"\x0031\x0030")
	{
		std::wcout << L"\x2502 " << rankStr;
		std::wcout << L"      \x2502\n";
	}
	else
	{
		std::wcout << L"\x2502 " << rankStr;
		std::wcout << L"       \x2502\n";
	}
	std::wcout << L"│         │\n";
	std::wcout << L"│    " << suitStr << L"    │\n";
	std::wcout << L"│         │\n";
	if (rankStr == L"\x0031\x0030")
	{
		std::wcout << L"│       " << rankStr;
		std::wcout << L"│\n";
	}
	else
	{
		std::wcout << L"│       " << rankStr;
		std::wcout << L" │\n";
	}
	std::wcout << L"└─────────┘\n";
	std::wcout << std::endl;
	_setmode(_fileno(stdout), _O_TEXT);
}


int Card::getValue() const
{
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
		case Rank::Ace: return 11; // not sure how to handle if the Ace is either 1 or 11
	}
	return 0;
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
	return L"";
}

const wchar_t* Card::getRankSymbol() const
{
	switch (rank)
	{
		case Rank::Ace: return L"\x0041";
		case Rank::Two: return L"\x0032";
		case Rank::Three: return L"\x0033";
		case Rank::Four: return L"\x0034";
		case Rank::Five: return L"\x0035";
		case Rank::Six: return L"\x0036";
		case Rank::Seven: return L"\x0037";
		case Rank::Eight: return L"\x0038";
		case Rank::Nine: return L"\x0039";
		case Rank::Ten: return L"\x0031\x0030";
		case Rank::Jack: return L"\x004A";
		case Rank::Queen: return L"\x0051";
		case Rank::King: return L"\x004B";
	}
	return L"";
}