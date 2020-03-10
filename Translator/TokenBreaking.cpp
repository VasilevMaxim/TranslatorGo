#include "TokenBreaking.h"
#include "TokenType.h"
#include <string>
#include "Error.h"

Token* TokenBreaking::GetToken(string lexeme)
{
	Token* newToken = new Token(lexeme);

	if (_delayMinus == true)
	{
		if (newToken->GetType() == TokenType::LITERAL || newToken->GetType() == TokenType::NUMBER)
		{
			newToken = new Token("-" + lexeme);
		}
		else
		{
			Error("WL002",true);
		}
		_delayMinus = false;
	}
	
	return newToken;
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
				if (_tokens.size() > 0 && (IsCompositesSeparator(_text[index], _tokens.back()->GetValue()[0]) == true))
				{
					continue;
				}

				if (_text[index] == '-' && (_tokens.back()->GetType() != TokenType::LITERAL && _tokens.back()->GetType() != TokenType::NUMBER))
				{
					tempLexems += _text[index];
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

		if (index > 0 && IsSymNumber(_text[index - 1]) == true && IsSymLit(_text[index - 2]) == false)
		{
			if (IsSymLit(_text[index]) == true)
			{
				Error("WL001", true);
			}
		}
	}

	if (_tokens[0]->GetType() == TokenType::NEW_LINE || _tokens[0]->GetType() == TokenType::SEMICOLON)
	{
		_tokens.erase(_tokens.begin());
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

string TokenBreaking::GetLineCurrentToken(int numCurrentLine)
{
	int currentNewLine = 0;
	int column = 0;
	while (column != numCurrentLine)
	{
		currentNewLine = _text.find("\n", currentNewLine);
		column++;
	}

	return "";
}

bool TokenBreaking::IsSymNumber(char sym)
{
	if (sym >= 48 && sym <= 57)
	{
		return true;
	}

	return false;
}

bool TokenBreaking::IsSymLit(char sym)
{
	// UNICODE

	// Eng (a-z, A-Z)
	if ((sym >= 65 && sym <= 90) || (sym >= 97 && sym <= 122))
	{
		return true;
	}

	// Rus (a-ß)
	if (sym >= 192 && sym <= 255)
	{
		return true;
	}

	return false;
}
