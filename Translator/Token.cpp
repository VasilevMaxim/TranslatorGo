#include "Token.h"
#include "BaseTokenTypes.h"

Token::Token(string value)
{
	_value = value;
	_type = BaseTokenTypes::GetTypeToken(value);
}

std::string Token::GetValue()
{
	return _value;
}

TokenType Token::GetType()
{
	return _type;
}
