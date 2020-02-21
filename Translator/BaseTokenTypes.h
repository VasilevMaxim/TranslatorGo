#pragma once
#include <map>
#include <string>
#include "TokenType.h"

class BaseTokenTypes
{
private:
	static std::map<std::string, TokenType> _baseTokenTypes;
	static bool IsNumberToken(std::string token);
public:
	static bool IsTypeVar(TokenType type);
	static TokenType GetTypeToken(std::string token);
};

