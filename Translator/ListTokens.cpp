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
}
