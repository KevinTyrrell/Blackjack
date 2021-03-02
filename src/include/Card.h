//=================================
// include guard
#ifndef __CARD_H_INCLUDED__
#define __CARD_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <string>

//=================================

/*
DESCRIPTION:
Card class defines what a card is.
Cards have a name (King), suit (Spades), and value (10).
*/

using namespace std;

class Card
{
public:
	Card(); //Default Constructor
	Card(string n, string s, int v); //Constructor
	string getName();
	string getSuit();
	int getValue();
	void setName(string thename);
	void setSuit(string thesuit);
	void setValue(int thevalue);

private:
	string name, suit;
	int value;
};

#endif //__CARD_H_