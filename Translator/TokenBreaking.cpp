#include "TokenBreaking.h"
#include "TokenType.h"
#include <string>

Token* TokenBreaking::GetToken(string lexeme)
{
	return new Token(lexeme);
}

void TokenBreaking::SplitIntoTokens()
{
	bool isFixed = false;
	string tempLexems;
	for(int index = 0; index < _text.length(); index++)
	{
		if (isFixed == false)
		{
			if (_separators.find(_text[index]) != string::npos)
			{
				if (tempLexems.length() > 0)
				{
					_tokens.push_back(GetToken(tempLexems));
				} 
				tempLexems.clear();
				continue;
			}

			if (_znaks.find(_text[index]) != string::npos)
			{
				if (_tokens.size() > 0 && (IsCompositesSeparator(_text[index], _tokens[_tokens.size() - 1]->GetValue()[0]) == true))
				{
					continue;
				}
				string forSym;
				forSym += _text[index];

				bool isComposites = IsCompositesToken(_text[index], _text[index + 1]);
				if (isComposites == true)
				{
					forSym += _text[index + 1];
					index++;
				}

				if (tempLexems.empty() == false)
				{
					_tokens.push_back(GetToken(tempLexems));
				}

				_tokens.push_back(GetToken(forSym));
				tempLexems.clear();
				continue;
			}
		}

		if (_fixedZnaks.find(_text[index]) != string::npos)
		{
			isFixed = !isFixed;
		}


		tempLexems += _text[index];
	}
	
}

bool TokenBreaking::IsCompositesToken(char sym1, char sym2)
{
	switch (sym1)
	{
		case '=':
			if (sym2 == '=')
			{
				return true;
			}
			break;

		case '!':
			if (sym2 == '=')
			{
				return true;
			}
			break;

		case '>':
			if (sym2 == '=' || sym2 == '>')
			{
				return true;
			}
			break;

		case '<':
			if (sym2 == '=' || sym2 == '<')
			{
				return true;
			}
			break;

		case '&':
			if (sym2 == '=' || sym2 == '&')
			{
				return true;
			}
			break;

		case '|':
			if (sym2 == '=' || sym2 == '|')
			{
				return true;
			}
			break;

		case '/':
			if (sym2 == '=')
			{
				return true;
			}
			break;
		case '%':
			if (sym2 == '=')
			{
				return true;
			}
			break;
		case '-':
			if (sym2 == '=' || sym2 == '-')
			{
				return true;
			}
			break;

		case '+':
			if (sym2 == '=' || sym2 == '+')
			{
				return true;
			}
			break;

		case ':':
			if (sym2 == '=')
			{
				return true;
			}
			break;
	}

	return false;
}

bool TokenBreaking::IsCompositesSeparator(char sym1, char sym2)
{
	if ((sym1 == '\n' || sym1 == ';') && (sym2 == '\n' || sym2 == ';'))
	{
		return true;
	}
	return false;
}

TokenBreaking::TokenBreaking(string text)
{
	_text = text;
	SplitIntoTokens();
}

vector<Token*>* TokenBreaking::GetTokens()
{
	return &_tokens;
}

void TokenBreaking::ShowTokens()
{
	for (auto& token : _tokens)
	{
		if (token->GetValue() == "\n" || token->GetValue() == "\r")
		{
			cout << "\\n" << endl;
		}
		else
		{
			cout << token->GetValue() << endl;
		}
	}
}
