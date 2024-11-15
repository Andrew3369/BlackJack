#include "../inc/Player.hpp"
#include <numeric>


void Player::addChips(int amount)
{
	chips += amount; // add chips to player
}


int Player::getChips() const
{
	return chips; // return the current amount of chips
}

const size_t Player::getHandSize()
{
	//size_t size = hand.size();
	return hand.size();
}

void Player::removeChips(int amount)
{
	chips -= amount; // remove chips from player
}

void Player::addCard(Card card)
{
	hand.push_back(card); // add card to hand
}

int Player::getTotalValue() const
{
	/*int totalValue = 0;
	for (const Card& card : hand) 
	{
		totalValue += card.getValue();
	}
	return totalValue;*/

	return std::accumulate(hand.begin(), hand.end(), 0,
		[](int sum, const Card& card) {
			return sum + card.getValue();
		});
}

void Player::doubleDown()
{
	doubleDowned = true;
}

bool Player::getIsDoubleDowned() const
{
	return doubleDowned;
}

void Player::removeCards()
{
	try
	{
		hand.clear(); // clear the hand after winning/losing
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << " Inside Player::removeCards()" << std::endl;
	}
}

void Player::displayHand() const
{
	// For both cards in the vector 'hand', display each
	for (const Card& card : hand)
	{
		card.display();
	}
}