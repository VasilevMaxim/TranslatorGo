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

bool Token::IsSeporator()
{
	return _type == TokenType::SEMICOLON || _type == TokenType::NEW_LINE;
}


bool Token::IsVar()
{
	return _type == TokenType::INT || _type == TokenType::FLOAT || _type == TokenType::DOUBLE;
}