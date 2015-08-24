#include "Banner.h"

Banner::Banner() //Default constructor
{
	banner[0] = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	banner[1] = "Welcome to Blackjack";
	banner[2] = "Press a corresponding key to the desired bet value";
}

void Banner::changeBanner(string header, string footer)
{
	/*
	Console window had 80 char width.
	Minus that by the header's length (2 extra for spaces), then split it in half
	*/
	unsigned int assignedWidth = (80 - (header.size() + 2)) / 2;
	stringstream ss;	//Stringstream to combine strings.

	for (unsigned int i = 0; i < assignedWidth; i++)
	{
		ss << '~';
	}

	banner[0] = ss.str();
	banner[1] = header;
	banner[2] = footer;
}

void Banner::printBanner()
{
	selectColor(13); 
	cout << '\n' << banner[0]; selectColor(15); cout << ' ' << banner[1] << ' '; selectColor(13); cout << banner[0];
	unsigned int assignedWidth = (80 - banner[2].size()) / 2;
	selectColor(15);
	for (unsigned int i = 0; i < assignedWidth; i++)
	{
		cout << ' ';							//Put correct number of spaces.
	}
	cout << banner[2] << endl; selectColor(13);

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	selectColor(15);
}

void Banner::selectColor(int color)
//7: Dark White, 8: Dark Gray, 9: Dark Blue, 10: Neon Green, 11: Neon Teal, 12: Neon Red, 13: Neon Purple, 14: Neon Yellow, 15: Neon White
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}