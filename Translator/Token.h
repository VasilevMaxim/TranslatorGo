#pragma once
#include <iostream>
#include "TokenType.h"

class Token
{
private:
	std::string _value;
	TokenType _type;
	
public:
	Token(std::string value);

	std::string GetValue();
	TokenType GetType();
};