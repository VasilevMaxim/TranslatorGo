#pragma once

enum class TokenType
{
	CONST,
	VAR,
	INT,
	FLOAT,
	DOUBLE,
	STRING,
	BOOL,
	TRUE,
	FALSE,
	FOR,
	BREAK,
	IF,
	ELSE,
	IF_ELSE,
	LBRA, // sym = {
	RBRA, // sym = }
	LPAR, // sym = (
	RPAR, // sym = )
	
	L_SBRA, // sym = [
	R_SBRA, // sym = ]
	ASSIGN,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	EQUAL,
	NOT_EQUAL,
	MORE,
	LESS,
	LESS_EQUAL,
	MORE_EQUAL,
	
	AND,
	OR,

	AND_ONE,
	OR_ONE,
	
	SEMICOLON,
	NEW_LINE,
	COLON,
	COMMA,
	NUMBER,
	RETURN,
	LITERAL,
	
	INCREMENT,
	DECREMENT,

	FUNC,

	NON
};