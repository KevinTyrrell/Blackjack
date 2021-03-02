#include "include/TextboxStream.h"

TextboxStream::TextboxStream()
{
	clearStream();
}

void TextboxStream::clearStream()
{
	for (size_t i = 0; i < STREAM_SIZE; i++)
	{
		stream[i] = "";
	}
}

void TextboxStream::newEntry(string n)
{
	//Shift up everything one index. stream[3] is lost.
	for (size_t i = STREAM_SIZE - 1; i >= 1; i--)
	{
		stream[i] = stream[i - 1];
	}

	stream[0] = n; //Add the new line.
}

void TextboxStream::printTextbox()
{
	for (int i = STREAM_SIZE - 1; i >= 0; i--)
	{
		if (stream[i].find_first_of('!') == 0) //Check if the text has an important message, if so highlight it.
		{
			selectColor(14); cout << "                        " << stream[i] << endl; selectColor(15);
		}
		else if (stream[i].find_first_of('*') == 0) //Check if the text has a message saying you won.
		{
			selectColor(11); cout << "                        " << stream[i] << endl; selectColor(15);
		}
		else
		{
			cout << "                        " << stream[i] << endl;
		}
	}

	selectColor(8); cout << "                ---------------------------------------------------\a" << endl; 
	selectColor(15); //Add underline and make a sound signifying that a new message has appeared.
}

void TextboxStream::selectColor(int color)
//7: Dark White, 8: Dark Gray, 9: Dark Blue, 10: Neon Green, 11: Neon Teal, 12: Neon Red, 13: Neon Purple, 14: Neon Yellow, 15: Neon White
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}