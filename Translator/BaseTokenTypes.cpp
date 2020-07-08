#include "BaseTokenTypes.h"
#include <stdexcept>

map<string, TokenType> BaseTokenTypes::_baseTokenTypes =
{
	{ "string", TokenType::STRING },
	{ "const", TokenType::CONST },
	{ "for", TokenType::FOR },
	{ "break", TokenType::BREAK },
	{ "int", TokenType::INT },
	{ "float64", TokenType::FLOAT64 },
	{ "float32", TokenType::FLOAT32 },
	{ "bool", TokenType::BOOL },
	{ "if", TokenType::IF },
	{ "else", TokenType::ELSE },
	{ "true", TokenType::TRUE },
	{ "false", TokenType::FALSE },
	{ "!", TokenType::INVERSION },

	{ "func", TokenType::FUNC },

	{ "{", TokenType::LBRA },
	{ "}", TokenType::RBRA },
	{ "(", TokenType::LPAR },
	{ ")", TokenType::RPAR },
	{ "[", TokenType::L_SBRA },
	{ "]", TokenType::R_SBRA },

	{ "=", TokenType::ASSIGN },
	{ ":=", TokenType::ASSIGN_DECLARATION },

	{ "+", TokenType::PLUS },
	{ "-", TokenType::MINUS },
	{ "*", TokenType::STAR },
	{ "/", TokenType::SLASH },
	{ "%", TokenType::PROCENT },

	{ "+=", TokenType::PLUS_EQUAL },
	{ "-=", TokenType::MINUS_EQUAL },
	{ "*=", TokenType::STAR_EQUAL },
	{ "/=", TokenType::SLASH_EQUAL },
	{ "%=", TokenType::PROCENT_EQUAL },

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

	{ "import", TokenType::IMPORT },
	{ "package", TokenType::PACKAGE }
};


TokenType BaseTokenTypes::GetNumberToken(string token)
{
	TokenType type = TokenType::NON;
	bool isPoint = false;
	if (token[0] == '-')
	{
		token.erase(0, 1);
	}
	for (const char& sym : token)
	{
		if (sym == '.' && isPoint == false)
		{
			type = TokenType::NUMBER_DOUBLE;
			isPoint = true;
			continue;
		}

		if (sym == '.')
		{
			return TokenType::NON;
		}

		if ((sym < '0' || sym > '9'))
		{
			return TokenType::NON;
		}
	}


	if (type == TokenType::NON)
	{
		type = TokenType::NUMBER;
	}
	
	return type;
}


TokenType BaseTokenTypes::GetTypeToken(string token)
{
	try 
	{
		return _baseTokenTypes.at(token);
	}
	catch (std::out_of_range e)
	{
		TokenType type = GetNumberToken(token);
		
		if (type != TokenType::NON)
			return type;

		if (token[0] == '\"' && token.back() == '\"')
		{
			return TokenType::STRING_CONST;
		}

		return TokenType::LITERAL;
	}
}
