#include "Card.h"

Card::Card()
{

}

Card::Card(string n, string s, int v)
{
	name = n;
	suit = s;
	value = v;
}

string Card::getName()
{
	return name;
}

string Card::getSuit()
{
	return suit;
}

int Card::getValue()
{
	return value;
}

void Card::setName(string thename)
{
	name = thename;
}

void Card::setSuit(string thesuit)
{
	suit = thesuit;
}

void Card::setValue(int thevalue)
{
	value = thevalue;
}