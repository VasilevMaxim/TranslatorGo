#pragma once
#include <map>
#include <string>
#include "TokenType.h"

using std::string;
using std::map;

class BaseTokenTypes
{
private:
	static map<string, TokenType> _baseTokenTypes;
	static TokenType GetNumberToken(string token);
	
public:
	static TokenType GetTypeToken(string token);
};

