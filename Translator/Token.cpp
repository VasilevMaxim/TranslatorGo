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
	return _type == TokenType::INT || _type == TokenType::FLOAT64 || _type == TokenType::FLOAT32 || _type == TokenType::BOOL;
}

bool Token::IsNumber()
{
	switch (_type)
	{
	case TokenType::NUMBER:
		return true;
		break;
	case TokenType::NUMBER_DOUBLE:
	return true;
		break;
	}

	return false;
}

bool Token::IsWithAssing()
{
	switch (_type)
	{

	case TokenType::PLUS_EQUAL:
	case TokenType::MINUS_EQUAL:
	case TokenType::STAR_EQUAL:
	case TokenType::SLASH_EQUAL:
	case TokenType::PROCENT_EQUAL:
	case TokenType::ASSIGN:
	case TokenType::ASSIGN_DECLARATION:

	return true;
	
	default:
		return false;
	}
}

NodeType Token::GetNeighborNodeType()
{
	switch (_type)
	{
	case TokenType::CONST:
		break;
	case TokenType::VAR:
		break;
	case TokenType::INT:
		break;
	case TokenType::FLOAT64:
		break;
	case TokenType::FLOAT32:
		break;
	case TokenType::STRING:
		break;
	case TokenType::BOOL:
		break;
	case TokenType::TRUE:
		break;
	case TokenType::FALSE:
		break;
	case TokenType::FOR:
		break;
	case TokenType::BREAK:
		break;
	case TokenType::IF:
		break;
	case TokenType::ELSE:
		break;
	case TokenType::IF_ELSE:
		break;
	case TokenType::LBRA:
		break;
	case TokenType::RBRA:
		break;
	case TokenType::LPAR:
		break;
	case TokenType::RPAR:
		break;
	case TokenType::L_SBRA:
		break;
	case TokenType::R_SBRA:
		break;
	case TokenType::ASSIGN:
		break;
	case TokenType::ASSIGN_DECLARATION:
		break;
	case TokenType::PLUS:
		break;
	case TokenType::MINUS:
		break;
	case TokenType::STAR:
		break;
	case TokenType::SLASH:
		break;
	case TokenType::PROCENT:
		break;
	case TokenType::PLUS_EQUAL:
		break;
	case TokenType::MINUS_EQUAL:
		break;
	case TokenType::STAR_EQUAL:
		break;
	case TokenType::SLASH_EQUAL:
		break;
	case TokenType::PROCENT_EQUAL:
		break;
	case TokenType::EQUAL:
		break;
	case TokenType::NOT_EQUAL:
		break;
	case TokenType::MORE:
		break;
	case TokenType::LESS:
		break;
	case TokenType::LESS_EQUAL:
		break;
	case TokenType::MORE_EQUAL:
		break;
	case TokenType::AND:
		break;
	case TokenType::OR:
		break;
	case TokenType::AND_ONE:
		break;
	case TokenType::OR_ONE:
		break;
	case TokenType::SEMICOLON:
		break;
	case TokenType::NEW_LINE:
		break;
	case TokenType::COLON:
		break;
	case TokenType::COMMA:
		break;
	case TokenType::NUMBER:
		break;
	case TokenType::RETURN:
		break;
	case TokenType::LITERAL:
		break;
	case TokenType::INCREMENT:
		break;
	case TokenType::DECREMENT:
		break;
	case TokenType::FUNC:
		break;
	case TokenType::NON:
		break;
	default:
		break;
	}

	return NodeType::EMPTY;
}
