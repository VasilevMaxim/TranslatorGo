#include "Preprocessing.h"



Preprocessing::Preprocessing(string* text)
{
	_text = *text;
	int indexFirstComments;
	int indexFirst = 0;
	int indexSecond = 0;
	while (indexFirst < _text.length())
	{
		while (indexFirst < _text.length() && _text[indexFirst++] != '/');
		if (_text[indexFirst] == '/')
		{
			indexFirst--;
			indexSecond = indexFirst;
			while (indexSecond  < _text.length() && _text[++indexSecond] != '\n');
			_text.erase(indexFirst, indexSecond - indexFirst);
		}
		else if (_text[indexFirst] == '*')
		{
			indexFirst--;
			indexSecond = indexFirst;
			while (indexSecond + 1 < _text.length())
			{
				if (_text[++indexSecond] == '*' && _text[indexSecond + 1] == '/')
				{
					indexSecond += 2;
					break;
				}
			}

			if (indexSecond + 1 >= _text.length())
			{
				// error
			}
			
			_text.erase(indexFirst, indexSecond - indexFirst);
		}
	}
	
}

string Preprocessing::GetText()
{
	return _text;
}