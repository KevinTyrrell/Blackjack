//=================================
// include guard
#ifndef __BANNER_H_INCLUDED__
#define __BANNER_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <iostream>		//For Input/Output
#include <sstream>		//For combining strings
#include <string>		//For string
#include <windows.h>	//For Clear Console 

//=================================

/*
DESCRIPTION:
Banner class manages the banner at the top of every single print.
Each line of the banner has 80 characters. Have function made so
whatever text the user wants, the banner will be correctly spaced out.
The banner will always look like the following:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HEADER TEXT HERE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
               FOOTER TEXT, LONGER THAN HEADER TEXT, WILL GO HERE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

banner[0] will be purple while banner[1] and banner[2] will be white (these are the header/footer)
*/

using namespace std;

class Banner
{
public:
	Banner();										//Default Constructor
	void changeBanner(string header, string footer);//Changes the banners appearance. Both header and footer must be EVEN # of chars.
	void printBanner();								//Prints the banner, with color.
	void selectColor(int color);					//Changes the color of text.

private:
	string banner[3];								//Each index will hold a part of the banner.
	HANDLE hConsole;								//Allows colors to be implemented.
};

#endif //__BANNER_H_