#include "include/MainMenu.h"

MainMenu::MainMenu()							//Deefault constructor.
{
	initializeMenu();							//Fill in default values for all the choices.
}

void MainMenu::initializeMenu()
{
	menuChoices[0] = "START GAME";
	menuChoices[1] = "RULEBOOK";
	menuChoices[2] = "SETTINGS";
	menuChoices[3] = "EXIT";
	optionsMenuChoices[0] = "TEXT SPEED";
	optionsMenuChoices[1] = "STARTING FUNDS";
	optionsMenuChoices[2] = "SHOE SIZES";
	optionsMenuChoices[3] = "BACK";
	textSpeedChoices[0] = "FASTER";
	textSpeedChoices[1] = "FAST";
	textSpeedChoices[2] = "NORMAL";
	textSpeedChoices[3] = "BACK";
	startingFundsChoices[0] = "5000";
	startingFundsChoices[1] = "1000";
	startingFundsChoices[2] = "10";
	startingFundsChoices[3] = "BACK";
	shoeSizeChoices[0] = "x8 DECKS";
	shoeSizeChoices[1] = "x5 DECKS";
	shoeSizeChoices[2] = "x2 DECKS";
	shoeSizeChoices[3] = "BACK";

	rulebook[0] = "BLACKJACK";
	rulebook[1] = "Blackjack will yield a 3:2 payout.";
	rulebook[2] = "To get a Blackjack, you must score 21 with your first two cards.";
	rulebook[3] = "If you have more than two cards, the hand is just called a '21'.\n\n";

	rulebook[5] = "SHOE";
	rulebook[6] = "In Blackjack, multiple decks are combined together to make a 'shoe'.";
	rulebook[7] = "The shoe by default has eight decks mixed together.";
	rulebook[8] = "Every eight rounds, the shoe is shuffled with the discard pile.\n\n";

	rulebook[10] = "DOUBLE DOWN";
	rulebook[11] = "To Double Down, you must double your current bet.";
	rulebook[12] = "You are then dealt one card, but may not hit afterwards.";
	rulebook[13] = "You may ONLY double down with your first two cards, and not after a split.\n\n";

	rulebook[15] = "SPLITTING";
	rulebook[16] = "Having two cards of the same name, you can seperate them into individual hands.";
	rulebook[17] = "You must have enough money to put down an equivalent bet to your current one.";
	rulebook[18] = "A two-card 21 after a split is NOT a Blackjack and will not pay 3:2.\n\n";

	rulebook[20] = "INSURANCE";
	rulebook[21] = "If the dealer has an ace, and a hidden card, you may be eligible for Insurance.";
	rulebook[22] = "You will need to wager one half of your current bet for the Insurance.";
	rulebook[23] = "If the dealer's hidden card's value was 10, you will be paid 3:2 on your bet.";
}

//A template that ALL menus will follow. Requires quite a lot of parameters to work properly.
unsigned int MainMenu::menuTemplate(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, string *parameter)
{
	unsigned int userChoice;
	system("cls");											//CLEAR CONSOLE.
	theBanner.printBanner();								//Print Banner.
	printBJAscii("     ");									//ASCII
	printMenu(parameter);									//Print menu options.
	Sleep(200);												//Pause to prevent duplicate inputs.

	do
	{														//Take input, check if it's correct.
		userChoice = consoleWindow.grabUserInput(false, false, false, true, theTable);
	}
	while (!(userChoice == 15 || userChoice == 16 || userChoice == 10));//Make sure button was either, UP DOWN or SPACE.

	return userChoice;
}

void MainMenu::settingsMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, Deck& theDeck)
{
start:
	theBanner.changeBanner("Settings Menu.", "Use the ARROW KEYS to select an option. Press the SPACEBAR to confirm.");
	currentlySelected = 3;											//Set cursor on 'Back'
	unsigned int userChoice;

	while (true)													//Infinite loop.
	{
		userChoice = menuTemplate(theBanner, consoleWindow, theTable, optionsMenuChoices);//Return the user's decision on what to do.

		if (processInput(userChoice))								//User pressed spacebar.
		{
			if (currentlySelected == 0)
			{
				textSpeedMenu(theBanner, consoleWindow, theTable);	//Enter menu for text speed.
				goto start;											//Reprint banner, etc.
			}
			else if (currentlySelected == 1)
			{
				startingFundsMenu(theBanner, consoleWindow, theTable);//Enter menu for starting funds.
				goto start;											//Reprint the banner, etc.
			}
			else if (currentlySelected == 2)
			{
				shoeSizeMenu(theBanner, consoleWindow, theTable, theDeck);//Enter menu for selecting shoe size.
				goto start;												//Reprint the banner, etc.
			}
			else
			{
				goto leaveLoop;										//Leave the nested loop.
			}
		}
	}

leaveLoop:
	system("cls");													//CLEAR CONSOLE.
}

void MainMenu::printBJAscii(string spaces)
{
	cout << "\n\n\n";
	cout << spaces << "######  #          #     #####  #    #       #    #     #####  #    #" << endl;
	cout << spaces << "#     # #         # #   #     # #   #        #   # #   #     # #   #" << endl;
	cout << spaces << "#     # #        #   #  #       #  #         #  #   #  #       #  #" << endl;
	cout << spaces << "######  #       #     # #       ###          # #     # #       ###" << endl;
	cout << spaces << "#     # #       ####### #       #  #   #     # ####### #       #  #" << endl;
	cout << spaces << "#     # #       #     # #     # #   #  #     # #     # #     # #   #" << endl;
	cout << spaces << "######  ####### #     #  #####  #    #  #####  #     #  #####  #    #\n\n\n" << endl;
}

void MainMenu::printRuleBookSection(unsigned int theLine)//We want this to scroll, so don't print out the entire rulebook.
{
	unsigned int endingLocation, spaces;

	if (theLine + 12 <= 25)
	{
		endingLocation = theLine + 12;				//We should only print out a dozen or so lines.
	}
	else
	{
		endingLocation = 25;						//If we would overshoot, just print up to the 25th.
	}

	for (unsigned int i = theLine; i <= endingLocation; i++)//End at the designated spot.
	{
		spaces = (80 - rulebook[i].size()) / 2;		//How many spaces we're going to need.
		for (unsigned int h = 0; h < spaces; h++)	//Format what we're printing out properly.
		{
			cout << ' ';
		}

		if (rulebook[i].size() < 15)				//If the current line is a TOPIC, print teal.
		{
			selectColor(11); cout << rulebook[i] << endl; selectColor(15);
		}
		else
		{
			cout << rulebook[i] << endl;			//Print line normally.
		}
	}
}

void MainMenu::ruleBookMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable)
{
	theBanner.changeBanner("House Rules.", "Use the ARROW KEYS to scroll up and down. Press the SPACEBAR to go back.");
	unsigned int topLine = 0;
	unsigned int userChoice;

	while (true)						//Infinite loop. Space will break out.
	{
		system("cls");					//CLEAR CONSOLE.
		theBanner.printBanner();		//Print banner.
		printRuleBookSection(topLine);	//Print a section of the rules.
		Sleep(200);						//So user doesn't do double inputs.

		backToInput:
		do
		{								//Take input, check if it's correct.
			userChoice = consoleWindow.grabUserInput(false, false, false, true, theTable);
		}
		while (!(userChoice == 15 || userChoice == 16 || userChoice == 10));//Make sure button was either, UP DOWN or SPACE.

		if (userChoice == 15 && topLine == 0)	//User entered up but we can't go any more up.
		{
			goto backToInput;
		}
		else if (userChoice == 16 && topLine > 12)
		{
			goto backToInput;
		}

		if (userChoice == 15)
		{
			topLine = topLine - 2;	//Scroll up
		}
		else if (userChoice == 16)
		{
			topLine = topLine + 2;	//Scroll down
		}
		else if (userChoice == 10)	//User is done reading.
		{
			break;
		}
	}
}

void MainMenu::printMenu(string *parameter)
{
	unsigned int spaces;

	for (int i = 0; i < 4; i++)					//Print out the choices.
	{
		spaces = (80 - parameter[i].size()) / 2;	//How many spaces we're going to need.
		for (unsigned int h = 0; h < spaces; h++)	//Format what we're printing out properly.
		{
			cout << ' ';
		}

		if (i == currentlySelected)				//If option is what we are currently 'on'...
		{
			selectColor(224);					//BLACK ON YELLOW BACKGROUND
			cout << parameter[i] << endl;		//Print with color.
			selectColor(15);					//Reset color.
		}
		else
		{
			cout << parameter[i] << endl;		//Print out option without color.
		}
	}
}

bool MainMenu::processInput(unsigned int input)
{
	if (input == 15)				//UP.
	{
		if (currentlySelected == 0)	//Already on top option, need to wrap around.
		{
			currentlySelected = 3;	//Set pointer to other side.
		}
		else
		{
			currentlySelected--;	//Go up one unit.
		}
	}
	else if (input == 16)			//DOWN.
	{
		if (currentlySelected == 3)	//Already on bottom option, need to wrap around.
		{
			currentlySelected = 0;	//Set pointer to other side.
		}
		else
		{
			currentlySelected++;	//Go down one unit.
		}
	}
	else
	{
		return true;				//User pressed spacebar.
	}

	return false;					//Did not press spacebar.
}

void MainMenu::selectColor(int color)
//7: Dark White, 8: Dark Gray, 9: Dark Blue, 10: Neon Green, 11: Neon Teal, 12: Neon Red, 13: Neon Purple, 14: Neon Yellow, 15: Neon White
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void MainMenu::shoeSizeMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, Deck& theDeck)
{
	theBanner.changeBanner("Shoe Sizes Menu.", "Use the ARROW KEYS to select an option. Press the SPACEBAR to confirm.");
	currentlySelected = 3;									//Set cursor on 'Back'
	unsigned int userChoice;

	while (true)											//Infinite loop.
	{
		userChoice = menuTemplate(theBanner, consoleWindow, theTable, shoeSizeChoices);//Return the user's decision on what to do.

		if (processInput(userChoice))						//User pressed spacebar.
		{
			if (currentlySelected == 0)
			{
				theDeck.setHowManyDecks(8);					//EIGHT DECKS
			}
			else if (currentlySelected == 1)
			{
				theDeck.setHowManyDecks(5);					//FIVE DECKS
			}
			else if (currentlySelected == 2)
			{
				theDeck.setHowManyDecks(2);					//TWO DECKS
			}

			goto leaveLoop;									//Leave the nested loop.
		}
	}

leaveLoop:
	system("cls");											//CLEAR CONSOLE.
}

void MainMenu::startingFundsMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable)
{
	theBanner.changeBanner("Starting Funds Menu.", "Use the ARROW KEYS to select an option. Press the SPACEBAR to confirm.");
	currentlySelected = 3;									//Set cursor on 'Back'
	unsigned int userChoice;

	while (true)											//Infinite loop.
	{
		userChoice = menuTemplate(theBanner, consoleWindow, theTable, startingFundsChoices);//Return the user's decision on what to do.

		if (processInput(userChoice))						//User pressed spacebar.
		{
			if (currentlySelected == 0)
			{
				theTable.setDefaultFunds(5000);				//5000
			}
			else if (currentlySelected == 1)
			{
				theTable.setDefaultFunds(1000);				//1000
			}
			else if (currentlySelected == 2)
			{
				theTable.setDefaultFunds(10);				//10
			}

			goto leaveLoop;									//Leave the nested loop.
		}
	}

leaveLoop:
	system("cls");											//CLEAR CONSOLE.
}

void MainMenu::startMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable, Deck& theDeck)
{
start:
	theBanner.changeBanner("Main Menu.", "Use the ARROW KEYS to select an option. Press the SPACEBAR to confirm.");
	currentlySelected = 0;									//Set cursor on 'Back'
	unsigned int userChoice;

	while (true)													//Infinite loop.
	{
		userChoice = menuTemplate(theBanner, consoleWindow, theTable, menuChoices);//Return the user's decision on what to do.

		if (processInput(userChoice))								//User pressed spacebar.
		{
			if (currentlySelected == 0)
			{
				goto leaveLoop;										//Leave the nested loop.
			}
			else if (currentlySelected == 1)
			{
				ruleBookMenu(theBanner, consoleWindow, theTable);	//Start the rulebook menu
				goto start;											//Reprint banner, etc.
			}
			else if (currentlySelected == 2)
			{
				settingsMenu(theBanner, consoleWindow, theTable, theDeck);//Start the options submenu.
				goto start;											//When they come back, change banner, etc.
			}
			else
			{
				exit(0);											//Quit the program.
			}
		}
	}

leaveLoop:
	system("cls");													//CLEAR CONSOLE.
	Sleep(300);														//Pause for a moment.
}

void MainMenu::textSpeedMenu(Banner& theBanner, InputOutput& consoleWindow, Table& theTable)
{
	theBanner.changeBanner("Text Speed Menu.", "Use the ARROW KEYS to select an option. Press the SPACEBAR to confirm.");
	currentlySelected = 3;									//Set cursor on 'Back'
	unsigned int userChoice;

	while (true)											//Infinite loop.
	{
		userChoice = menuTemplate(theBanner, consoleWindow, theTable, textSpeedChoices);//Return the user's decision on what to do.

		if (processInput(userChoice))						//User pressed spacebar.
		{
			if (currentlySelected == 0)
			{
				consoleWindow.setTextSpeed(1500);			//Faster
			}
			else if (currentlySelected == 1)
			{
				consoleWindow.setTextSpeed(2100);			//Fast
			}
			else if (currentlySelected == 2)
			{
				consoleWindow.setTextSpeed(2700);			//Normal
			}

			goto leaveLoop;									//Leave the nested loop.
		}
	}

leaveLoop:
	system("cls");											//CLEAR CONSOLE.
}