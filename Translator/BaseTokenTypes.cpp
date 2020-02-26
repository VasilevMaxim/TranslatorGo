#include "BaseTokenTypes.h"
#include <stdexcept>

map<string, TokenType> BaseTokenTypes::_baseTokenTypes =
{
	{ "string", TokenType::STRING },
	{ "const", TokenType::CONST },
	{ "for", TokenType::FOR },
	{ "break", TokenType::BREAK },
	{ "int", TokenType::INT },
	{ "float", TokenType::FLOAT },
	{ "double", TokenType::DOUBLE },
	{ "if", TokenType::IF },
	{ "else", TokenType::ELSE },

	{ "func", TokenType::FUNC },

	{ "{", TokenType::LBRA },
	{ "}", TokenType::RBRA },
	{ "(", TokenType::LPAR },
	{ ")", TokenType::RPAR },
	{ "[", TokenType::L_SBRA },
	{ "]", TokenType::R_SBRA },

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
	{ ">=", TokenType::MORE_EQUAL },

	{ "&&", TokenType::AND },
	{ "||", TokenType::OR },
	{ "&", TokenType::AND_ONE },
	{ "|", TokenType::OR_ONE },


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

bool BaseTokenTypes::IsNumberToken(string token)
{
	bool isPoint = false;

	for (const char& sym : token)
	{
		if (sym == '.' && !isPoint)
		{
			isPoint = true;
			continue;
		}

		if (sym == '.')
		{
			return false;
		}

		if ((sym < '0' || sym > '9'))
		{
			return false;
		}
	}

	return true;
}

bool BaseTokenTypes::IsTokenSeparator(TokenType token)
{
	return token == TokenType::SEMICOLON || token == TokenType::NEW_LINE;
}

TokenType BaseTokenTypes::GetTypeToken(string token)
{
	try 
	{
		return _baseTokenTypes.at(token);
	}
	catch (std::out_of_range e)
	{
		if (IsNumberToken(token))
		{
			return TokenType::NUMBER;
		}

		return TokenType::LITERAL;
	}
}
