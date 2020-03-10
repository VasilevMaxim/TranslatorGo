#pragma once

enum class TokenType
{
	CONST,
	VAR,
	INT,
	FLOAT64,
	FLOAT32,

	INVERSION,
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
	ASSIGN_DECLARATION,
	
	PLUS,
	MINUS,
	STAR,
	SLASH,
	PROCENT,

	PLUS_EQUAL,
	MINUS_EQUAL,
	STAR_EQUAL,
	SLASH_EQUAL,
	PROCENT_EQUAL,

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