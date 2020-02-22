#pragma once
#include <iostream>
#include "TokenType.h"

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
};