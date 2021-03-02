#include "include/Table.h"

Table::Table()
{
	defaultFunds = 100; //Starting funds for player.
}

bool Table::hasSoft17(vector<Card>& pile)
{
	bool hasAce = false;
	unsigned int sum = 0;

	for (size_t i = 0; i < pile.size(); i++)
	{
		if (pile[i].getValue() == 1)
		{
			hasAce = true;
		}

		sum = sum + pile[i].getValue();
	}

	if (hasAce && sum == 7) //Dealer has an ace and so far has a low score of 7.
	{
		return true;
	}

	return false;
}

bool Table::splitPossible(vector<Card>& pile, bool firstTurn)
{ 
	/*
	In order for a user to split, you must have all of the same cards in your hand
	along with enough money in your funds to be able to drop an additional bet
	equivalent to your current bet.
	*/

	if (pile.size() < 2 || firstTurn == false)
	{
		return false; //You can't split if you don't have two cards or not on first turn
	}

	string temp = pile[0].getName();
	int counter = 0;

	for (size_t i = 0; i < pile.size(); i++)
	{
		if (pile[i].getName() == temp)
		{
			counter++;
		}
	}

	if (counter == pile.size() && funds >= bet * 2) 
	{
		return true;
	}

	return false;
}

unsigned int Table::determineRoundOutcome(bool firstTurnBJ, bool surrendered) //1 = You Win, 2 = Dealer Win, 3 = Push, 4 = Win with 1.5x
{
	if (surrendered)
	{
		return 2;															//User surrendered
	}

	if (calculateScore(usersCards) > 21)									//If user busted
	{
		return 2;
	}
	else if (calculateScore(dealersCards) > 21)								//If dealer busted
	{
		return 1;
	}
	else if (calculateScore(usersCards) > calculateScore(dealersCards))		//User has a higher score than dealer
	{
		if (firstTurnBJ)													//User blackjacked on opening hand.
		{
			return 4;
		}
		else
		{
			return 1;
		}
	}
	else if (calculateScore(dealersCards) > calculateScore(usersCards))		//Dealer has a higher score than user
	{
		return 2;
	}
	else																	//Tie between user and dealer
	{
		return 3;
	}
}

unsigned int Table::getDefaultFunds()
{
	return defaultFunds;
}

unsigned int Table::getFunds()
{
	return funds;
}

unsigned int Table::getInsurance()	//Return the user's insurance bet.
{
	return insurance;
}

unsigned int Table::getUsersBet()
{
	return bet;
}

unsigned int Table::getPlayersScore(bool which)
{
	if (which)	//User
	{
		return calculateScore(usersCards);
	}
	else        //Dealer
	{
		return calculateScore(dealersCards);
	}
}

unsigned int Table::calculateScore(vector<Card>& pile) //Calculate a specific entities' score. Maximize aces if possible.
{
	unsigned int total, total_wo_Aces, aceCounter;
	total_wo_Aces = 0;
	aceCounter = 0;

	for (size_t i = 0; i < pile.size(); i++) //First we need to find the plain score without considering the Aces. 
	{
		if (pile[i].getValue() == 1) //If the card being looking at is an ace...
		{
			aceCounter++;
		}
		else
		{
			total_wo_Aces = total_wo_Aces + pile[i].getValue();
		}
	}

	//If the total w/o aces added with one ace turning from a 1 to an 11 doesn't bust you...
	if (aceCounter > 0)
	{
		if (total_wo_Aces + (aceCounter - 1) + 11 <= 21)
		{
			total = total_wo_Aces + (aceCounter - 1) + 11;
		}
		else //Otherwise just count the aces as 1 point.
		{
			total = total_wo_Aces + aceCounter;
		}

		return total;
	}
	else
	{
		return total_wo_Aces;
	}
}

vector<Card>& Table::getDealersCards()
{
	return dealersCards;
}

vector<Card>& Table::getDiscard()
{
	return discard;
}

vector<Card>& Table::getSplitHand()
{
	return splitHand;
}

vector<Card>& Table::getUsersCards()
{
	return usersCards;
}

void Table::setBet(unsigned int newBet)
{
	bet = newBet;
}

void Table::handleMoney(unsigned int outcome)
{
	if (outcome == 1)							//User won.
	{
		funds = funds + bet;
	}
	else if (outcome == 2)						//User lost.
	{
		funds = funds - bet;
	}
	else if (outcome == 4)						//User got blackjack on first two cards.
	{
		funds = funds + ((int)bet * 1.5);
	}
}

void Table::setDefaultFunds(unsigned int newFunds)
{
	defaultFunds = newFunds;
}

void Table::setFunds(int newFunds)
{
	funds = newFunds;
}

void Table::setInsurance(unsigned int newInsurance)
{
	insurance = newInsurance;
}

void Table::toDiscardPile() //Send all cards on the table into the discard pile.
{
	for (unsigned int i = 0; i < usersCards.size(); i++)
	{
		discard.push_back(usersCards[i]);
	}

	for (unsigned int h = 0; h < dealersCards.size(); h++)
	{
		discard.push_back(dealersCards[h]);
	}

	for (unsigned int i = 0; i < splitHand.size(); i++)
	{
		discard.push_back(splitHand[i]);
	}

	dealersCards.clear();
	usersCards.clear();
	splitHand.clear();
}