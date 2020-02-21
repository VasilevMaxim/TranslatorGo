#include "BaseTokenTypes.h"

std::map<std::string, TokenType> BaseTokenTypes::_baseTokenTypes =
{
	{ "string", TokenType::STRING },
	{ "const", TokenType::CONST },
	{ "for", TokenType::FOR },
	{ "int", TokenType::INT },
	{ "float", TokenType::FLOAT },
	{ "if", TokenType::IF },
	{ "else", TokenType::ELSE },
	{ "{", TokenType::LBRA },
	{ "}", TokenType::RBRA },
	{ "(", TokenType::LPAR },
	{ ")", TokenType::RPAR },
	{ "=", TokenType::ASSIGN },
	{ ":=", TokenType::ASSIGN },
	{ "+", TokenType::PLUS },
	{ "-", TokenType::MINUS },
	{ "*", TokenType::STAR },
	{ "/", TokenType::SLASH },
	{ "==", TokenType::EQUAL },
	{ "!=", TokenType::NOT_EQUAL },
	{ ">", TokenType::MORE },
	{ "<", TokenType::LESS },
	{ "<=", TokenType::LESS_EQUAL },
	{ ">=", TokenType::GREATER_EQUAL },
	{ ";", TokenType::SEMICOLON },
	{ ":", TokenType::COLON },
	{ ",", TokenType::COMMA },
	{ "true", TokenType::TRUE },
	{ "false", TokenType::FALSE },
	{ "\n", TokenType::NEW_LINE },
	{ "var", TokenType::VAR },

	{ "++", TokenType::INCREMENT },
	{ "--", TokenType::DECREMENT },

	{ "return", TokenType::RETURN },

};

bool BaseTokenTypes::IsTypeVar(TokenType type)
{
	switch (type)
	{
	case TokenType::INT:
		return true;
		break;
	case TokenType::FLOAT:
		return true;
		break;
	case TokenType::DOUBLE:
		return true;
		break;
	}

	return false;
}

bool BaseTokenTypes::IsNumberToken(std::string token)
{
	bool point = false;
	for (const char& s : token)
	{
		if (s == '.' && !point)
		{
			point = true;
			continue;
		}

		if (s == '.')
		{
			return false;
		}

		if ((s < '0' || s > '9'))
		{
			return false;
		}
	}

	return true;
}

TokenType BaseTokenTypes::GetTypeToken(std::string token)
{
	std::map <std::string, TokenType> ::iterator it;
	it = _baseTokenTypes.find(token);
	
	if (it == _baseTokenTypes.end())
	{
		if (IsNumberToken(token))
		{
			return TokenType::NUMBER;
		}

		return TokenType::LITERAL;
	}

	return it->second;
}
