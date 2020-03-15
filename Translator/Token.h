#pragma once
#include <iostream>
#include "TokenType.h"
#include "NodeType.h"

using std::string;

class Token
{
private:
	string _value;
	TokenType _type;
	
public:
	Token(string value);

	string GetValue();
	TokenType GetType();

	bool IsSeporator();
	bool IsVar();
	bool IsNumber();
	bool IsWithAssing();

	NodeType GetNeighborNodeType();
};