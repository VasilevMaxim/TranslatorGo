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
	static bool IsNumberToken(string token);
public:
	static bool IsTypeVar(TokenType type);
	static TokenType GetTypeToken(string token);
};

