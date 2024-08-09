//=================================
// include guard
#ifndef __DECK_H_INCLUDED__
#define __DECK_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <algorithm>	//Random
#include <cstdlib>		//Random Generator
#include <ctime>		//Time
#include <iostream>		//Input/Output
#include <sstream>		//For initialize function.
#include <vector>		//Holds Card objects
#include "Card.h"		//Card objects

//=================================

/*
DESCRIPTION:
Table class handles all functions pertaining to the main deck.
Holds array of cards, gets intialized with 52 cards times how
many decks the player desires.
*/

using namespace std;

class Deck
{
public:
	Deck();												//Default constructor.
	vector<Card>& getDeck();						//Return the deck.
	void cardsBackIntoDeck(vector<Card>& discardPile);	//Puts cards from all piles back into the deck.
	void deal(vector<Card>& pile);						//Deals a card from the deck to a given player.
	void initializeDeck();								//Initializes shoe with Playing Cards.
	void setHowManyDecks(unsigned int howMany);			//Sets how many decks are to be added to the shoe.
	void shuffle();										//Shuffles the deck pseudo-randomly.
	unsigned int getHowManyDecks();						//Returns how many decks are to be formed for the shoe.
	
private:
	unsigned int deckSize = howManyDecks * 52;
	unsigned int howManyDecks; //Change this depending on how many decks you would like shuffled in.
	vector<Card> deck;
};

#endif //__DECK_H_