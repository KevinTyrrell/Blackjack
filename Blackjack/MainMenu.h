//=================================
// include guard
#ifndef __MAINMENU_H_INCLUDED__
#define __MAINMENU_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <Windows.h>			//For colors.
#include "InputOutput.h"		//For user inputs.

//=================================

/*
DESCRIPTION:
MainMenu handles everything to do with the main menu.
*/

using namespace std;

class MainMenu
{
public:
	MainMenu();																					//Constructor.
	bool processInput(unsigned int input);														//Processes user arrow/space inputs.
	unsigned int menuTemplate(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, string *parameter);
	void initializeMenu();																		//Fills in values for the string arrays.
	void printBJAscii(string spaces);															//Prints out BLACKJACK in Ascii
	void printMenu(string *parameter);															//Prints a given array with color.
	void printRuleBookSection(unsigned int theLine);											//Prints a section of the rulebook.
	void ruleBookMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable);			//Shows various rules of the game.
	void selectColor(int color);																//Sets the font color.
	void settingsMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, Deck& theDeck);//Begin the options submenu.
	void shoeSizeMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, Deck& theDeck);//Sets how many decks are to be in the shoe.
	void startingFundsMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable);		//Change the money you start with.
	void startMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, Deck& theDeck);//Begin the menu from the start.
	void textSpeedMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable);			//Change the text speed.

private:
	const static int menuSize = 4;
	HANDLE hConsole;						//Allows colors to be implemented.
	string menuChoices[menuSize];			//Array to hold main menu choices.
	string optionsMenuChoices[menuSize];	//Array to hold option menu choices.
	string rulebook[30];					//Array to hold all the text in the rulebook.
	string shoeSizeChoices[menuSize];		//Array to hold shoe size options.
	string startingFundsChoices[menuSize];	//Array to hold starting funds choices.
	string textSpeedChoices[menuSize];		//Array to hold text speed choices.
	unsigned int currentlySelected = 0;		//Value to indicate what option the user wants.
};

#endif //__MAINMENU_H_