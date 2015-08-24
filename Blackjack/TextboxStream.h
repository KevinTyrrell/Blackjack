//=================================
// include guard
#ifndef __TEXTBOXSTREAM_H_INCLUDED__
#define __TEXTBOXSTREAM_H_INCLUDED__

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <string>		//For string
#include <iostream>		//For Input/Output
#include <windows.h>	//For Clear Console 

//=================================

/*
DESCRIPTION:
TextboxStream class manages a STREAM_SIZE line textbox in the console window
Each time a message to the player needs to be printed, it goes here
and just like a scrolling textfield, the message at the top is lost
and all the lines of text shift up one.
Ex:
ZZZZZZZ
XXXXXXX
XXXXXXX

New text of "YYYYYYY" needs to be printed, forget about the line ZZZZ..
and change to:

XXXXXXX
XXXXXXX
YYYYYYY
*/

using namespace std;

class TextboxStream
{
public:
	TextboxStream();			//Default Constructor
	void clearStream();			//Erases all six slots of the stream.
	void newEntry(string n);	//Moves stream indexes up one and puts a new stream[0].
	void printTextbox();		//Prints out the four lines of the array.
	void selectColor(int color);//Changes the color of text.

private:
	static const int STREAM_SIZE = 6;
	HANDLE hConsole;			//Allows colors to be implemented.
	string stream[STREAM_SIZE];	//Our main textbox array.

};

#endif //__TEXTBOXSTREAM_H_