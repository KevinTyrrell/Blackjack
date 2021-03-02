//=================================
// include guard
#ifndef __INPUTOUTPUT_H_INCLUDED__
#define __INPUTOUTPUT_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include "Banner.h"				//For Banner printing
#include "Table.h"				//For specific print statements regarding bets
#include "TextboxStream.h"		//For Textbox Printing
#include <iomanip>				//Fixed and setprecision
#include <iostream>				//Input/Output
#include <sstream>				//For preparing statements for TextboxStream.
#include <windows.h>			//For KeyStates/Colors to work

//=================================

/*
DESCRIPTION:
InputOutput class handles all user inputs and print statements.
Handles key presses, formatting, user prompts, etc.
*/

using namespace std;

class InputOutput
{
public:
	InputOutput();															//Default Constructor
	int grabUserBet(Table& theTable);										//Return the User's bet after he/she chooses.
	unsigned int grabUserChoice(bool firstTurn, bool ableToSplit, Table& theTable);//Call grabUserInput to Return a value. Print out the correct options.
	unsigned int grabUserInput(bool bettingPhase, bool split, bool firstTurn, bool inMainMenu, Table& theTable);//Return the User's input from the keyboard.
	string formatSpaces(unsigned int spaces);								//Return a string with how many spaces the user asked for.
	string getImmediateEvent(unsigned int eventNumber, Table& theTable, bool firstTurn);//Return a given event string depending on the situation.
	string prepareCardDealt(bool which, int howRecent, vector<Card>& pile);	//Print a card that was dealt out recently.
	string prepareRoundOutcome(unsigned int outcome);						//Prepare a string for textbox showing the outcome of the round.
	string prepareRoundWinnings(unsigned int outcome, Table& theTable);		//Prepare a string for textbox showing the round's winnings.
	void gameOverAnimation();												//Print a game over animation.
	void gameStartIntroduction();											//Print the instructions before the game starts.
	void gameOverText();													//Print game over message.
	void goodLuckMessage(string spaces);									//Prints a good luck message before game starts.
	void printHandAscii(bool dealerCardHidden, Table& theTable);			//Print the given player's cards in ASCII form.
	void printInsuranceResult(Table& theTable, TextboxStream& textbox, Banner& theBanner);//Print the result of the insurance bet.
	void printUserInterface(TextboxStream& textbox, Table& theTable, Banner& theBanner, bool hiddenCard);//Print multiple elements of the User interface.
	void promptInsurance(Banner& theBanner, Table& theTable);				//Prompt insuance for the user, 
	void selectColor(int color);											//Sets the font color.
	void setTextSpeed(unsigned int newSpeed);								//Sets a new text speed.

private:
	HANDLE hConsole; //Allows colors to be implemented.

	void printClubsSymbol(string spaces);
	void printDiamondsSymbol(string spaces);
	void printSpadesSymbol(string spaces);
	void printHeartsSymbol(string spaces);
	unsigned int textSpeed = 2700;											//Time in miliseconds.
};

#endif //__INPUTOUTPUT_H_