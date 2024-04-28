#include "../inc/Player.h"


void Player::addChips(int amount)
{
	chips += amount; // add chips to player
}


int Player::getChips() const
{
	return chips; // return the current amount of chips
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
	int totalValue = 0;
	for (const Card& card : hand) 
	{
		totalValue += card.getValue();
	}
	return totalValue;
}

void Player::displayHand() const
{
	// For both cards in the vector 'hand', display each
	for (const Card& card : hand)
	{
		card.display();
	}
}