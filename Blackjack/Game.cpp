//DEPENDENCIES
#include "Banner.h"
#include "Deck.h"
#include "InputOutput.h"
#include "MainMenu.h"
#include "Table.h"
#include "TextboxStream.h"
#include <sstream>				//For initialize function.
#include <windows.h>			//For getConsoleWindow
//#include <MMsystem.h> //For sounds //PlaySound(TEXT("hello.wav"), NULL, SND_LOOP); //Song

using namespace std;

//FUNCTIONS
void checkForEvent(bool which);	
void dealAndUpdate(bool which, bool hiddenCard);
void doAction(int parameter);
void SetWindow(int Width, int Height);
void splitLoop();
void splitScoring();

//VARIABLES
Banner theBanner;					//Controls the banner at the top of the console window.
Deck theDeck;						//Handles the deck and its functions.
Table theTable;						//Deals with all game related calculations.
InputOutput consoleWindow;			//Handles all output preperation to the textbox.
MainMenu theMenu;					//Main menu to handle options and game.
TextboxStream textbox;				//A scrolling textbox within the console window.
bool dealerCardIsHidden, roundIsOver, turnIsOver, firstTurn, blackJackOnOpeningDeal, surrendered, alreadyPromptedInsurance;
unsigned int roundNumber = 1;

int main()
{
	//SETUP
	SetWindow(80, 28);														//Make window size correct.
	consoleWindow.gameStartIntroduction();									//Print all rights reserved.

	while (true)															//PRIMARY GAME LOOP
	{
		theMenu.startMenu(theBanner, consoleWindow, theTable, theDeck);		//MAIN MENU
		consoleWindow.goodLuckMessage("                        ");			//Good luck ASCII
		theDeck.initializeDeck();											//User might have changed the deck, initialize it now instead.
		theTable.setFunds(theTable.getDefaultFunds());						//RESET FUNDS

		while (theTable.getFunds() >= 10) //PLAY
		{
			//INITIALIZE VARIABLES FOR THE ROUND
			theTable.setInsurance(0);
			roundNumber++;
			dealerCardIsHidden = false;
			alreadyPromptedInsurance = false;
			roundIsOver = false;
			turnIsOver = false;
			blackJackOnOpeningDeal = false;
			surrendered = false;
			firstTurn = true;

			//BETTING STAGE
			theBanner.changeBanner("Welcome to Blackjack", "Press a corresponding key to the desired bet value");
			theBanner.printBanner();
			theTable.setBet(consoleWindow.grabUserBet(theTable));		//Ask user to bet, store that value.

			//DEAL STAGE
			theBanner.changeBanner("The round has begun!", "The dealer will deal the cards out at this time.");
			dealAndUpdate(true, dealerCardIsHidden);					//Deal to player.
			dealAndUpdate(false, dealerCardIsHidden);					//Deal to dealer.
			dealAndUpdate(true, dealerCardIsHidden);					//Deal to player.
			dealerCardIsHidden = true;									//Dealer hidden card.
			theDeck.deal(theTable.getDealersCards());					//Dealer hidden card.
			textbox.newEntry("The dealer is dealt a card face down.");	//Dealer hidden card.
			theBanner.changeBanner("Player's Turn.", "When prompted, press a corresponding key to your desired choice.");
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);
			checkForEvent(true);										//Check if User hit Blackjack already.
			
			//PLAYER TURN STAGE
			while (!turnIsOver) //As long as player doesn't bust...
			{
				int actionRequested = consoleWindow.grabUserChoice(firstTurn, theTable.splitPossible(theTable.getUsersCards(), firstTurn), theTable);
				doAction(actionRequested);	//Take the user's choice, do what he wanted, hit split double down etc.
				firstTurn = false;			//No longer first turn. Don't allow user to 'Forfeit' or 'Double Down'
				checkForEvent(true);		//Check if user hit Blackjack or Busted
			}
			splitLoop();					//If the user split, deal out his second hand.

			//DEALER TURN STAGE
			if (!roundIsOver)
			{
				theBanner.changeBanner("Dealer's Turn.", "The dealer must stop when at or above 17 points.");
				textbox.newEntry("The dealer will now begin his turn.");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);	//Update textbox
				dealerCardIsHidden = false;															//Indicate that the hidden card can be revealed.
				textbox.newEntry(consoleWindow.getImmediateEvent(5, theTable, firstTurn));			//The dealer reveals his hidden card...
				consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);	//Update textbox
				firstTurn = true;
				checkForEvent(false);																//Check if the dealer has above 16 already.
			}
			while (!roundIsOver) //As long as the round isn't already considered over...
			{
				firstTurn = false;				//For 21 vs. Blackjack reasons.
				dealAndUpdate(false, false);	//Deal a card to the dealer.
				checkForEvent(false);			//Check to see if bust, 21, or above 16 points.
			}			
			
			//SCORING STAGE
			dealerCardIsHidden = false;
			theBanner.changeBanner("The round is over.", "Round results and bets will be handled at this time.");
			textbox.newEntry(consoleWindow.prepareRoundOutcome(theTable.determineRoundOutcome(blackJackOnOpeningDeal, surrendered)));			//Who won, who lost?
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);													//Print the above information.
			textbox.newEntry(consoleWindow.prepareRoundWinnings(theTable.determineRoundOutcome(blackJackOnOpeningDeal, surrendered), theTable));//State who lost or won money.
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);													//Print the above information.
			theTable.handleMoney(theTable.determineRoundOutcome(blackJackOnOpeningDeal, surrendered));											//Deduct or add the money.
			splitScoring();																														//Handle splits if they were done.
			consoleWindow.printInsuranceResult(theTable, textbox, theBanner);																	//If user made insurance bet, sort it out.

			//CLEANUP STAGE
			theTable.toDiscardPile();	//Put all cards that were played into the discard pile.
			if (roundNumber % 8 == 0)	//Every 8th round, put the cards from the discard back into the deck.
			{
				theDeck.cardsBackIntoDeck(theTable.getDiscard());
			}

			Sleep(1500);
			textbox.clearStream();
			system("cls"); //CLEAR CONSOLE
		}

		consoleWindow.gameOverAnimation();		//GAME OVER
	}

	system("PAUSE"); //As an EXE, it will close automatically without this line.
	return 0;
}

void checkForEvent(bool which)
{
	/*
	Check if the User or Dealer has busted or blackjacked during their round.
	If the one we are checking has, immediately notify the user of this occuring.
	From there, assuming something happened, end the round accordingly.
	*/

	if (which)	//User
	{
		if (theTable.getDealersCards()[0].getName() == "Ace" && theTable.getFunds() >= theTable.getUsersBet() * 2 && alreadyPromptedInsurance == false && which) //Offer insurace
		{
			consoleWindow.promptInsurance(theBanner, theTable);
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);
		}
		
		alreadyPromptedInsurance = true; //We don't want to prompt the user for insurance later down the line.

		if (theTable.getPlayersScore(true) > 21)				//User Bust
		{
			turnIsOver = true;
			if (theTable.getSplitHand().size() == 0)			//If user didn't split
			{
				roundIsOver = true;								//Then dealer no longer needs to play out his hand.
			}
			textbox.newEntry(consoleWindow.getImmediateEvent(2, theTable, firstTurn));
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);
		}
		else if (theTable.getPlayersScore(true) == 21)			//User 21
		{
			turnIsOver = true;
			textbox.newEntry(consoleWindow.getImmediateEvent(1, theTable, firstTurn));
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);

			if (firstTurn)	//If it's still the first turn...
			{
				blackJackOnOpeningDeal = true;	//User must have Blackjacked on opening deal.
			}
		}
	}
	else        //Dealer
	{
		if (theTable.getPlayersScore(false) > 21)			//Dealer Bust
		{
			roundIsOver = true;
			textbox.newEntry(consoleWindow.getImmediateEvent(4, theTable, firstTurn));
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);
		}
		else if (theTable.getPlayersScore(false) == 21)		//Dealer 21
		{
			roundIsOver = true;
			textbox.newEntry(consoleWindow.getImmediateEvent(3, theTable, firstTurn));
			consoleWindow.printUserInterface(textbox, theTable, theBanner, dealerCardIsHidden);
		}
												//If the dealer is at or above 17, not including a soft 17.
		else if (theTable.getPlayersScore(false) >= 17 && theTable.hasSoft17(theTable.getDealersCards()) == false)
		{
			roundIsOver = true;
		}
	}
}

void dealAndUpdate(bool which, bool hiddenCard) //Deals a card and then prints out the message.
{
	if (which)	//User
	{
		theDeck.deal(theTable.getUsersCards());
		textbox.newEntry(consoleWindow.prepareCardDealt(true, 0, theTable.getUsersCards()));
		
	}
	else        //Dealer
	{
		theDeck.deal(theTable.getDealersCards());
		textbox.newEntry(consoleWindow.prepareCardDealt(false, 0, theTable.getDealersCards()));
	}

	consoleWindow.printUserInterface(textbox, theTable, theBanner, hiddenCard);
}

void doAction(int parameter) //10 = Hit, 11 = Stand, 12 = Double Down, 13 = Forfeit, 14 = Split
{
	if (parameter == 10) //Hit
	{
		dealAndUpdate(true, dealerCardIsHidden);
	}
	else if (parameter == 11) //Stand
	{
		turnIsOver = true;
	}
	else if (parameter == 12) //Double Down
	{
		theTable.setBet(theTable.getUsersBet() * 2);
		dealAndUpdate(true, dealerCardIsHidden);

		turnIsOver = true;
	}
	else if (parameter == 13) //Forfeit
	{
		theTable.setBet(theTable.getUsersBet() / 2);
		surrendered = true;
		turnIsOver = true;
		roundIsOver = true;  
	}
	else if (parameter == 14) //Split
	{
		theTable.getSplitHand().push_back(theTable.getUsersCards()[1]);
		theTable.getUsersCards().pop_back();
		consoleWindow.printUserInterface(textbox, theTable, theBanner, true);
	}
}

void splitLoop()
{
	if (theTable.getSplitHand().size() > 0)	//User split, allow second turn.
	{
		textbox.newEntry("*Now deciding for your split hand.*");
		consoleWindow.printUserInterface(textbox, theTable, theBanner, true);

		while (true)
		{
			//Only two possible situations, the user hits or stands.
			int actionRequested = consoleWindow.grabUserChoice(false, false, theTable);

			if (actionRequested == 10)	//HIT
			{
				theDeck.deal(theTable.getSplitHand());
				textbox.newEntry(consoleWindow.prepareCardDealt(true, 0, theTable.getSplitHand()));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, true);
			}
			else                        //STAND
			{
				break;
			}

			if (theTable.calculateScore(theTable.getSplitHand()) > 21)			//If user busts...
			{
				textbox.newEntry(consoleWindow.getImmediateEvent(2, theTable, false));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, true);
				if (theTable.calculateScore(theTable.getUsersCards()) > 21)
				{
					roundIsOver = true;	//If both split hand and normal hand busted, dealer doesn't need to play out turn.
				}
				break;
			}
			else if (theTable.calculateScore(theTable.getSplitHand()) == 21)	//If user hits 21
			{
				textbox.newEntry(consoleWindow.getImmediateEvent(1, theTable, false));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, true);
				break;
			}
		}
	}
}

void splitScoring()
{
	if (theTable.getSplitHand().size() > 0)		//If the user split...
	{
		if (theTable.calculateScore(theTable.getDealersCards()) > 21)	//Did the dealer bust?
		{
			if (theTable.calculateScore(theTable.getSplitHand()) > 21)	//Did I bust?
			{
				textbox.newEntry("*Your split hand has lost against the dealer.*");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
				theTable.handleMoney(2);
				textbox.newEntry(consoleWindow.prepareRoundWinnings(2, theTable));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
			}
			else
			{
				textbox.newEntry("*Your split hand has won against the dealer.*");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
				theTable.handleMoney(1);
				textbox.newEntry(consoleWindow.prepareRoundWinnings(1, theTable));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
			}
		}
		else                                                              //Dealer did NOT bust.
		{
			if (theTable.calculateScore(theTable.getSplitHand()) > 21)
			{
				textbox.newEntry("*Your split hand has lost against the dealer.*");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
				theTable.handleMoney(2);
				textbox.newEntry(consoleWindow.prepareRoundWinnings(2, theTable));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
			}
			else if (theTable.calculateScore(theTable.getSplitHand()) > theTable.calculateScore(theTable.getDealersCards()))
			{
				textbox.newEntry("*Your split hand has won against the dealer.*");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
				theTable.handleMoney(1);
				textbox.newEntry(consoleWindow.prepareRoundWinnings(1, theTable));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
			}
			else if (theTable.calculateScore(theTable.getSplitHand()) == theTable.calculateScore(theTable.getDealersCards()))
			{
				textbox.newEntry("***** PUSH! Your split hand was a draw! *****");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
				textbox.newEntry(consoleWindow.prepareRoundWinnings(3, theTable));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
			}
			else
			{
				textbox.newEntry("*Your split hand has lost against the dealer.*");
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
				theTable.handleMoney(2);
				textbox.newEntry(consoleWindow.prepareRoundWinnings(2, theTable));
				consoleWindow.printUserInterface(textbox, theTable, theBanner, false);
			}
		}
	}
}

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}