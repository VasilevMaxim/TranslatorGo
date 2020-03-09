#include "ListTokens.h"

void ListTokens::Initialization(vector<Token*>* tokens)
{
	_tokens = tokens;
}

Token* ListTokens::GetCurrentToken()
{
	return (*_tokens)[_indexCurrentToken];
}

void ListTokens::UseNextToken()
{
	_indexCurrentToken++;

	if (GetCurrentToken()->GetType() == TokenType::NEW_LINE)
	{
		_numCurrentLine++;
		_indexFirstSymLine = _indexCurrentToken + 1;
	}
}

string ListTokens::GetLineCurrentToken()
{
	string line = "";
	int indexLine = _indexFirstSymLine;
	while ((*_tokens)[indexLine]->GetType() != TokenType::NEW_LINE)
	{
		line += (*_tokens)[indexLine++]->GetValue();
	}

	return line;
}

int ListTokens::GetNumLine()
{
	return _numCurrentLine;
}

bool ListTokens::IsBackTokens()
{
	if (_indexCurrentToken == _tokens->size() - 1)
	{
		return true;
	}

	return false;
}
