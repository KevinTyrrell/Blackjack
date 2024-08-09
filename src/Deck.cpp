#include "include/Deck.h"

Deck::Deck()
{
	howManyDecks = 8; //Starting value for shoe, user can change this.
}

vector<Card>& Deck::getDeck()
{
	return deck;
}

void Deck::cardsBackIntoDeck(vector<Card>& discardPile) //Puts all cards back in the original shoe.
{
	for (size_t i = 0; i < discardPile.size(); i++)
	{
		deck.push_back(discardPile[i]);
	}

	discardPile.clear(); //Erase all contents in discard pile.
}

void Deck::deal(vector<Card>& pile) //Deal a card to whichever pile on the table.
{
	pile.push_back(deck[deck.size() - 1]);
	deck.pop_back();
}

void Deck::initializeDeck() //Add all cards into the deck. Needs shuffling of course.
{
	deck.clear();									//Erase deck so user doesn't accidentally add more together.
	string s;
	for (unsigned int i = 0; i < howManyDecks; i++) //How many decks to meld into the shoe
	{
		for (int h = 0; h < 4; h++) //Each Suit 
		{
			switch (h)
			{
			case 0: s = "Spades"; break;
			case 1: s = "Hearts"; break;
			case 2: s = "Clubs"; break;
			case 3: s = "Diamonds"; break;
			}

			for (int z = 2; z <= 10; z++) //No such thing as a 1. Start at 2.
			{
				string converted = to_string(z); //Make int Z into String Z
				deck.push_back(Card(converted, s, z));
			}

			deck.push_back(Card("Ace", s, 1));
			deck.push_back(Card("King", s, 10));
			deck.push_back(Card("Queen", s, 10));
			deck.push_back(Card("Jack", s, 10));
		}
	}

	shuffle();
}

void Deck::setHowManyDecks(unsigned int howMany)
{
	howManyDecks = howMany;
}

void Deck::shuffle() //Shuffles the deck.
{
	int random;
	srand(time(0)); // This will ensure a really randomized number by help of time.

	for (size_t i = 0; i < deck.size(); i++)
	{
		random = rand() % (deck.size()); // Randomizing the number between 1 and the deck's size.

		swap(deck[i], deck[random]);
	}
}

unsigned int Deck::getHowManyDecks()
{
	return howManyDecks;
}