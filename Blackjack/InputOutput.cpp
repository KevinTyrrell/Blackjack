#include "InputOutput.h"

InputOutput::InputOutput()
{
	selectColor(15); //Default color for the game.
}

int InputOutput::grabUserBet(Table& theTable)
{
	int userChoice;
	int theBet = 0;

	selectColor(11); cout << "                           ";
	cout << "You currently have $" << theTable.getFunds() << ".00\n\n" << endl;
	cout << "                           "; selectColor(15); cout << "Please place your bets now:\n" << endl;
	cout << "          "; cout << "1 ("; selectColor(10); cout << "$10"; selectColor(15);
	cout << ")   2 ("; selectColor(10); cout << "$25"; selectColor(15); cout << ")   3 ("; selectColor(14);
	cout << "$50"; selectColor(15); cout << ")"; cout << "   4 ("; selectColor(14); cout << "$100";
	selectColor(15); cout << ")   5 ("; selectColor(12); cout << "$500"; selectColor(15);
	cout << ")   6 ("; selectColor(12); cout << "ALL-IN"; selectColor(15); cout << ")\n" << endl;

	while (theBet == 0)
	{
		userChoice = grabUserInput(true, false, false, false, theTable); //Pass in 1 because we are only seeking 1-6 inputs.

		if (userChoice < 7) //Check for valid input
		{
			int moneyAvailable = theTable.getFunds();

			if (userChoice == 1)
			{
				theBet = 10;
			}
			else if (userChoice == 2 && moneyAvailable >= 25)
			{
				theBet = 25;
			}
			else if (userChoice == 3 && moneyAvailable >= 50)
			{
				theBet = 50;
			}
			else if (userChoice == 4 && moneyAvailable >= 100)
			{
				theBet = 100;
			}
			else if (userChoice == 5 && moneyAvailable >= 500)
			{
				theBet = 500;
			}
			else if (userChoice == 6)
			{
				theBet = moneyAvailable;
			}
			else
			{
				cout << '\a';
				Sleep(200);
			}
		}
	}

	system("cls"); //CLEAR CONSOLE

	return theBet;
}

unsigned int InputOutput::grabUserChoice(bool firstTurn, bool ableToSplit, Table& theTable)
{
	bool doubledown = false;
	stringstream ss;	//Stringstream to combine strings.

	ss << "SPACE (Hit)   S (Stand)"; //Hit and Stand are ALWAYS available options.

	if (theTable.getFunds() >= (theTable.getUsersBet() * 2) && firstTurn)
	{
		doubledown = true;
		ss << "   D (Double Down)";
	}
	if (firstTurn)
	{
		ss << "   F (Forfeit)";
	}
	if (ableToSplit)
	{
		ss << "   G (Split)";
	}


	string temp = ss.str();							//So we can figure out how to center the text.
	unsigned int spaces = (80 - temp.size()) / 2;	//How many spaces we're going to need.

	cout << "\n\n                           "; selectColor(11); cout << "What would you like to do?\n" << endl; selectColor(15);
	for (unsigned int i = 0; i < spaces; i++)
	{
		cout << ' ';
	}

	cout << "SPACE ("; selectColor(14); cout << "Hit"; selectColor(15); cout << ")   S (";
	selectColor(10); cout << "Stand"; selectColor(15); cout << ')';

	if (doubledown)
	{
		cout << "   D ("; selectColor(12); cout << "Double Down"; selectColor(15); cout << ')';
	}
	if (firstTurn) //User can only forfeit hands on the opening hand.
	{
		cout << "   F ("; selectColor(4); cout << "Forfeit"; selectColor(15); cout << ')';
	}
	if (ableToSplit) //User can only split hand if he/she has all cards of same name.
	{
		cout << "   G ("; selectColor(13); cout << "Split"; selectColor(15); cout << ')';
	}

	cout << '\n' << endl;

	return grabUserInput(false, ableToSplit, firstTurn, false, theTable);
}

unsigned int InputOutput::grabUserInput(bool bettingPhase, bool split, bool firstTurn, bool inMainMenu, Table& theTable)
//1 - 6 = $10 - $All-In Bets
//1 = Space (Hit), 2 = S (Stand), 3 = D (Double Down), 4 = F (Forfeit), 5 = G (Split) 
//Parameter: 1 (betting), 2 (First turn), 3 (no surrender)
{
	while (true) //Await a user's input
	{
		if (GetConsoleWindow() == GetForegroundWindow())//Check if the console window is the primary window.
		{
			if (bettingPhase)//Betting phase
			{
				if (GetAsyncKeyState(0x31) & 0x8000)
				{
					return 1; //User pressed 1 key
				}
				else if (GetAsyncKeyState(0x32) & 0x8000)
				{
					return 2; //User pressed 2 key
				}
				else if (GetAsyncKeyState(0x33) & 0x8000)
				{
					return 3; //User pressed 3 key
				}
				else if (GetAsyncKeyState(0x34) & 0x8000)
				{
					return 4; //User pressed 4 key
				}
				else if (GetAsyncKeyState(0x35) & 0x8000)
				{
					return 5; //User pressed 5 key
				}
				else if (GetAsyncKeyState(0x36) & 0x8000)
				{
					return 6; //User pressed 6 key
				}
			}
			else
			{
				if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					return 10; //User pressed spacebar key
				}
				else if (GetAsyncKeyState(0x53) & 0x8000)
				{
					return 11; //User pressed S key
				}
				else if (GetAsyncKeyState(0x44) & 0x8000 && (theTable.getFunds() >= theTable.getUsersBet() * 2) && firstTurn)
				{
					return 12; //User pressed D key
				}
				else if (GetAsyncKeyState(0x46) & 0x8000 && firstTurn)
				{
					return 13; //User pressed F key
				}
				else if (GetAsyncKeyState(0x47) & 0x8000 && split)
				{
					return 14; //User pressed G key
				}
				else if (GetAsyncKeyState(VK_UP) & 0x8000 && inMainMenu)
				{
					return 15; //User pressed UP key
				}
				else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && inMainMenu)
				{
					return 16; //User pressed DOWN key
				}
			}
		}
	}
}

void InputOutput::gameStartIntroduction()
{
	selectColor(10);
	cout << "\n\n\n\n\n\n\n\n\n\n                           PROJECT NAME: Blackjack Simulator" << endl;
	cout << "                           CREATED BY:   Kevin Tyrrell" << endl;
	cout << "                           COMPLETED:    8/18/2015" << endl;
	selectColor(15); Sleep(1500); system("cls");	//CLEAR CONSOLE	
}

string InputOutput::prepareCardDealt(bool which, int howRecent, vector<Card>& pile) //True = Player, False = Dealer, howRecent = 0 would mean card just dealt
{
	stringstream ss;	//Stringstream to combine strings.

	if (which)	//User
	{
		ss << "You are ";
	}
	else       //Dealer
	{
		ss << "The dealer is ";
	}

	ss << "dealt the " << pile[pile.size() - 1 - howRecent].getName() << " of " << pile[pile.size() - 1 - howRecent].getSuit() << '.';

	return ss.str();
}

string InputOutput::prepareRoundOutcome(unsigned int outcome)
//1 = Player Win, 2 = Dealer Win, 3 = Push
{
	string result = "";

	if (outcome == 1 || outcome == 4)
	{
		result = "***** YOU have won the round! *****";
	}
	else if (outcome == 2)
	{
		result = "***** The dealer has won the round! *****";
	}
	else if (outcome == 3)
	{
		result = "***** PUSH! The round is a draw! *****";
	}

	return result;
}

string InputOutput::prepareRoundWinnings(unsigned int outcome, Table& theTable)
//1 = Player Win, 2 = Dealer Win, 3 = Push, 4 Win with a Blackjack on first two cards.
{
	stringstream ss;	//Stringstream to combine strings.

	if (outcome == 1)
	{
		ss << "You have earned $" << theTable.getUsersBet() << ".00 in winnings.";
	}
	else if (outcome == 2)
	{
		ss << "You have lost your bet of $" << theTable.getUsersBet() << ".00.";
	}
	else if (outcome == 3)
	{
		ss << "Your bet of $" << theTable.getUsersBet() << ".00 has been returned.";
	}
	else if (outcome == 4)
	{
		ss << "You have earned $" << setprecision(0) << fixed << (theTable.getUsersBet()*1.5) << ".00 (1.5x) in winnings.";
	}

	return ss.str();
}

void InputOutput::gameOverAnimation()
{
	/*
	Prints out an animation after the user game-overs.
	Order is spades, hearts, diamonds, clubs.
	*/
	int horizontalAxis = 0;
	selectColor(7);											//White color

	do
	{
		cout << "\n";
		printSpadesSymbol(formatSpaces(horizontalAxis));	//Print spades symbol with certain spaces before it.
		Sleep(30);											//Pause to simulation animation.
		system("cls");										//CLEAR CONSOLE
		horizontalAxis = horizontalAxis + 3;				//Jump two units to the right.
	}
	while (horizontalAxis < 68);

	horizontalAxis = 60;									//Reset the horizontalAxis for next loop.
	selectColor(12);										//Red color

	do
	{
		cout << "\n\n\n\n\n";								//Go down a few lines.
		printHeartsSymbol(formatSpaces(horizontalAxis));	//Print hearts symbol with certain spaces before it
		Sleep(30);											//Pause to simulation animation.
		system("cls");										//CLEAR CONSOLE
		horizontalAxis = horizontalAxis - 3;				//Jump three units to the left.
	}
	while (horizontalAxis > 5);


	horizontalAxis = 6;
	selectColor(7);

	do
	{
		cout << "\n\n\n\n\n\n\n\n\n";				//Go down a few lines.
		printClubsSymbol(formatSpaces(horizontalAxis));		//Print clubs symbol with certain spaces before it
		Sleep(30);											//Pause to simulation animation.
		system("cls");										//CLEAR CONSOLE
		horizontalAxis = horizontalAxis + 3;				//Jump three units to the left.
	}
	while (horizontalAxis < 63);


	horizontalAxis = 66;
	selectColor(12);

	do
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
		printDiamondsSymbol(formatSpaces(horizontalAxis));	//Print diamond symbol with certain spaces before it.
		Sleep(30);											//Pause to simulation animation.
		system("cls");										//CLEAR CONSOLE
		horizontalAxis = horizontalAxis - 3;				//Jump three units to the right.
	}
	while (horizontalAxis > 5);



	selectColor(11);
	for (unsigned int i = 0; i < 10; i++)
	{
		system("cls");										//CLEAR CONSOLE

		for (unsigned int h = 0; h < i; h++)				//ADD SPACES
		{
			cout << '\n';
		}

		gameOverText();										//Print GAME OVER
		Sleep(30);											//Pause to simulate animation.
	}

	Sleep(7000);
	selectColor(15);										//Standard color.
	system("cls"); //CLEAR CONSOLE
}

void InputOutput::printHandAscii(bool dealerCardHidden, Table& theTable) //True = Player, False = Dealer
{														//      __
	string n;                                        	//     |A |
	vector<Card> hand;                                  //     |__|

	for (int z = 0; z < 3; z++)
	{
		if (z == 2 && theTable.getSplitHand().size() == 0)
		{
			break;	//Avoid For loop going three times if user did not split
		}

		if (z == 1) //Depending on whose hand we want drawn.
		{
			hand = theTable.getUsersCards();
		}
		else if (z == 0)
		{
			hand = theTable.getDealersCards();
		}
		else
		{
			hand = theTable.getSplitHand();
		}

		cout << "                        ";
		for (size_t i = 0; i < hand.size(); i++) //Top Layer
		{
			cout << " __ ";

			if (i + 1 != hand.size()) //If we are not yet on the last card.
			{
				cout << ' '; //Add a space for the next card.
			}
		}
		cout << endl;

		if (z == 1)
		{
			selectColor(10); cout << "                PLAYER: "; selectColor(15);
		}
		else if (z == 0)
		{
			selectColor(12); cout << "                DEALER: "; selectColor(15);
		}
		else
		{
			selectColor(14); cout << "                SPLIT : "; selectColor(15);
		}
		for (size_t i = 0; i < hand.size(); i++) //Middle Layer
		{
			if (z == 0 && dealerCardHidden && i == hand.size() - 1)
			{
				n = ' '; //Card is hidden, print blank
			}
			else
			{
				if (hand[i].getName() == "10") //If card is a 10, needs to be treated differently
				{
					n = "10";
				}
				else
				{
					n = hand[i].getName().substr(0, 1); //Get the first letter of the card we're drawing.
				}
			}

			cout << "|" << n;
			if (n == "10")
			{
				cout << "|";
			}
			else
			{
				cout << " |";
			}

			if (i + 1 != hand.size()) //If we are not yet on the last card.
			{
				cout << ' '; //Add a space for the next card.
			}
		}
		cout << endl;

		cout << "                        ";
		for (size_t i = 0; i < hand.size(); i++) //Bottom Layer
		{
			cout << "|__|";

			if (i + 1 != hand.size()) //If we are not yet on the last card.
			{
				cout << ' '; //Add a space for the next card.
			}
		}

		cout << endl;
	}
}

string InputOutput::getImmediateEvent(unsigned int eventNumber, Table& theTable, bool firstTurn)
//1 = Player 21/BJ, 2 = Player Bust, 3 = Dealer 21/BJ, 4 = Dealer Bust, 5 = Dealer Hidden Card
{
	string theEvent = "";	//The string we will return.
	stringstream ss;		//Stringstream to combine strings.

	if (eventNumber == 1)
	{
		if (firstTurn)
		{
			theEvent = "!!!!! BLACKJACK !!!!!";
		}
		else
		{
			theEvent = "!!!!! TWENTY-ONE !!!!!";
		}
	}
	else if (eventNumber == 2)
	{
		theEvent = "!!!!! BUST !!!!!";
	}
	else if (eventNumber == 3)
	{
		if (firstTurn)
		{
			theEvent = "!!!!! DEALER BLACKJACK !!!!!";
		}
		else
		{
			theEvent = "!!!!! DEALER TWENTY-ONE !!!!!";
		}
	}
	else if (eventNumber == 4)
	{
		theEvent = "!!!!! DEALER BUST !!!!!";
	}
	else if (eventNumber == 5)						//Reveal the Dealer's Hidden Card, name & suit
	{
		ss << "The dealer reveals the " << theTable.getDealersCards()[theTable.getDealersCards().size() - 1].getName() <<
			" of " << theTable.getDealersCards()[theTable.getDealersCards().size() - 1].getSuit() << '.';
		theEvent = ss.str();
	}

	return theEvent;
}

void InputOutput::printInsuranceResult(Table& theTable, TextboxStream& textbox, Banner& theBanner)
{
	if (theTable.getInsurance() > 0)																									//If the user insured his bet.
	{
		stringstream ss;

		if (theTable.getDealersCards()[1].getValue() == 10)																				//If the insurance was successful...
		{
			theTable.setFunds(theTable.getFunds() + theTable.getInsurance() + ((int)theTable.getInsurance() * 1.5));					//Pay the user 1.5x his bet.
			ss << "You have won your Insurance bet and gain $" << ((int)(theTable.getInsurance() * 1.5)) << ".00";						//Use stringstream to output the message.
		}
		else
		{
			ss << "You have lost your insurance bet of $" << theTable.getInsurance() << ".00";											//Use stringstream to output the message.
		}

		textbox.newEntry(ss.str());																										//Prepare the statement for printing.
		printUserInterface(textbox, theTable, theBanner, false);																		//Print the result of the insurance bet.
	}
}

void InputOutput::printUserInterface(TextboxStream& textbox, Table& theTable, Banner& theBanner, bool hiddenCard)
{
	system("cls");							//CLEAR CONSOLE
	theBanner.printBanner();				//Banner
	textbox.printTextbox();					//Textbox
	printHandAscii(hiddenCard, theTable);	//ASCII

	Sleep(textSpeed);
}

void InputOutput::promptInsurance(Banner& theBanner, Table& theTable)
{
	theBanner.changeBanner("Insurance Offer!", "Insurance pays out 3:2 on a successful bet");
	system("cls");																//CLEAR CONSOLE
	theBanner.printBanner();													//Print Banner

	cout << "\n                 The dealer has shown an "; selectColor(14); cout << "Ace"; selectColor(15); cout << " as his first card." << endl;
	cout << "          Would you like Insurance in case the dealer hits Blackjack?" << endl;
	cout << "\n\n         You will need to wager an additional half of your current bet.\n\n";

	printHandAscii(true, theTable);

	cout << "\n\n\n                  SPACE ("; selectColor(10); cout << "Accept"; selectColor(15); cout << ")                  S (";
	selectColor(12); cout << "Decline"; selectColor(15); cout << ')' << endl;


	unsigned int choice = 0;
	do
	{
		choice = grabUserInput(false, false, false, false, theTable);
	}
	while (choice > 11);

	if (choice == 10)															//User wants to insure his bet. 
	{
		theTable.setInsurance(theTable.getUsersBet() / 2);						//Set the user's insurance.
		theTable.setFunds(theTable.getFunds() - (theTable.getUsersBet() / 2));	//Subtract funds now, just so we don't mess up other functions.
	}
	theBanner.changeBanner("Player's Turn.", "When prompted, press a corresponding key to your desired choice."); //Reset banner
	system("cls");																//CLEAR CONSOLE	
}

void InputOutput::selectColor(int color)
//7: Dark White, 8: Dark Gray, 9: Dark Blue, 10: Neon Green, 11: Neon Teal, 12: Neon Red, 13: Neon Purple, 14: Neon Yellow, 15: Neon White
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void InputOutput::setTextSpeed(unsigned int newSpeed)
{
	textSpeed = newSpeed;
}

string InputOutput::formatSpaces(unsigned int spaces)
{
	stringstream ss;

	for (unsigned int i = 0; i < spaces; i++)
	{
		ss << ' ';
	}

	return ss.str();
}

void InputOutput::printClubsSymbol(string spaces)
{
	cout << spaces << "    ,db." << endl;
	cout << spaces << "    MMMM" << endl;
	cout << spaces << "    YMMP" << endl;
	cout << spaces << " dMb_][_dMb" << endl;
	cout << spaces << "(MMMMMMMMMM)" << endl;
	cout << spaces << " YMP~][~YMP" << endl;
	cout << spaces << "     db" << endl;
	cout << spaces << "   ,dMMb." << endl;
}

void InputOutput::printDiamondsSymbol(string spaces)
{
	cout << spaces << "    A" << endl;
	cout << spaces << "   dMb" << endl;
	cout << spaces << "  dMMMb" << endl;
	cout << spaces << " dMMMMMb" << endl;
	cout << spaces << "(MMMMMMM)" << endl;
	cout << spaces << " YMMMMMP" << endl;
	cout << spaces << "  YMMMP" << endl;
	cout << spaces << "   YMP" << endl;
	cout << spaces << "    Y" << endl;
}

void InputOutput::printSpadesSymbol(string spaces)
{
	cout << spaces << "    db" << endl;
	cout << spaces << "   dMMb" << endl;
	cout << spaces << "  dMMMMb" << endl;
	cout << spaces << " dMMMMMMb" << endl;
	cout << spaces << "dMMMMMMMMb" << endl;
	cout << spaces << "MMMMMMMMMM" << endl;
	cout << spaces << "`YP~YP~YP'" << endl;
	cout << spaces << "    db" << endl;
	cout << spaces << "   dMMb" << endl;
}

void InputOutput::printHeartsSymbol(string spaces)
{
	cout << spaces << " dMb. ,dMb" << endl;
	cout << spaces << "dMMMMmMMMMb" << endl;
	cout << spaces << "YMMMMMMMMMP" << endl;
	cout << spaces << " YMMMMMMMP" << endl;
	cout << spaces << "  YMMMMMP" << endl;
	cout << spaces << "   YMMMP" << endl;
	cout << spaces << "    YMP" << endl;
	cout << spaces << "     Y" << endl;
}

void InputOutput::goodLuckMessage(string spaces)
{
	system("cls");						//CLEAR CONSOLE	
	selectColor(15);					//White
	cout << "\n\n                  Care to play Blackjack? Please have a seat." << endl;
	cout << "                                 Good luck today.";

	selectColor(7); cout << "\n\n\n";	//Space out the text.

	cout << spaces << "              .-\"\"-." << endl;
	cout << spaces << "             /)    (\\" << endl;
	cout << spaces << "             ( ' \\' )" << endl;
	cout << spaces << "              \\  = /" << endl;
	cout << spaces << "           .---)--(---" << endl;
	cout << spaces << "          /\\\\  <_>  //\\" << endl;
	cout << spaces << "         ;   > / \\ <' _;" << endl;
	cout << spaces << "         |   | | | |   |" << endl;
	selectColor(4); cout << spaces << " ________"; selectColor(7); cout << '|';
	selectColor(4); cout << "__"; selectColor(7); cout << '|'; selectColor(7);
	cout << '\\'; selectColor(4); cout << '_'; selectColor(7); cout << '|';
	selectColor(4); cout << "_"; selectColor(7); cout << '|'; selectColor(4);
	cout << "_"; selectColor(7); cout << "/"; selectColor(4); cout << "___";
	selectColor(7); cout << '|'; selectColor(4); cout << "_______ " << endl;
	cout << spaces << "/     "; selectColor(6); cout << "/.'/   /.'/    /.'/";
	selectColor(4); cout << "      \\" << endl;
	cout << spaces << "********************************" << endl;
	cout << spaces << "********************************" << endl;
	cout << spaces << "||||                        ||||" << endl;
	cout << spaces << "||                            ||" << endl;
	cout << spaces << "||                            ||" << endl;
	selectColor(15); Sleep(5000); system("cls"); //CLEAR CONSOLE	
}

void InputOutput::gameOverText()
{
	cout << "  _______     ___     .___  ___. _______   ______ ____    ____ _______ ._____" << endl;
	cout << " /  _____|   /   \\    |   \\/   ||   ____| /  __  \\\\   \\  /   /|   ____||   _  \\ ";
	cout << "|  |  __    /  ^  \\   |  \\  /  ||  |__   |  |  |  |\\   \\/   / |  |__   |  |_)  |";
	cout << "|  | |_ |  /  /_\\  \\  |  |\\/|  ||   __|  |  |  |  | \\      /  |   __|  |      /" << endl;
	cout << "|  |__| | /  _____  \\ |  |  |  ||  |____ |  `--'  |  \\    /   |  |____ |  |\\  \\ ";
	cout << " \\______|/__/     \\__\\|__|  |__||_______| \\______/    \\__/    |_______||__| `._|" << endl;
}