//=================================
// include guard
#ifndef __TABLE_H_INCLUDED__
#define __TABLE_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <iostream>	//Input/Output
#include <vector>	//Holds Card objects
#include "Card.h"	//Card objects
#include "Deck.h"	//Deck object

//=================================

/*
DESCRIPTION:
Table class handles all game related calculations. 
Table will handle cards being moved around the table, 
cards held by players, and cards that have been discarded.
*/

using namespace std;

class Table
{
public:
	Table(); //Default Constructor
	bool hasSoft17(vector<Card>& pile);					//Check if the given player has a soft 17.
	bool splitPossible(vector<Card>& pile, bool firstTurn);//Check if the given player can split.
	unsigned int determineRoundOutcome(bool firstTurnBJ, bool surrendered);//Return the numerical outcome of the round.
	unsigned int getDefaultFunds();						//Return the default funds for the game.
	unsigned int getFunds();							//Return User's current money count.
	unsigned int getInsurance();						//Return the user's insurance bet.
	unsigned int getUsersBet();							//Return User's bet.
	unsigned int getPlayersScore(bool which);			//Return the player's score.
	unsigned int calculateScore(vector<Card>& pile);	//Return the current score of all cards on the board for a given player.
	vector<Card>& getDealersCards();					//Return the cards infront of Dealer.
	vector<Card>& getDiscard();							//Return the discard pile.
	vector<Card>& getSplitHand();						//Return the cards that belong to the split hand.
	vector<Card>& getUsersCards();						//Return the cards infront of the User.
	void handleMoney(unsigned int outcome);				//Deduct or add money from/to funds depending on outcome.
	void setDefaultFunds(unsigned int newFunds);		//Set the default funds for the game.
	void setFunds(int newFunds);						//Set the User's money.
	void setBet(unsigned int newBet);					//Set the User's bet.
	void setInsurance(unsigned int newInsurance);		//Sets an insurance bet.
	void toDiscardPile();								//Put all cards on table into discard pile.

private:
	vector<Card> usersCards, dealersCards, discard, splitHand;
	unsigned int funds, defaultFunds, bet, insurance;
};

#endif //__TABLE_H_