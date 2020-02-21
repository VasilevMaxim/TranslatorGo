#pragma once
#include <iostream>
#include <vector>
#include "Token.h"

class TokenBreaking
{
private:
	std::string _text;

	std::string _separators = " \t\r";
	std::string _znaks = ",()[]{}:=+-*/!;.<>&|\n";
	std::string _fixedZnaks = "\"\'";

	std::vector<Token*> _tokens;

	bool isFixed = false;

	Token* GetToken(std::string lexeme);
	void SplitIntoTokens();
	bool IsCompositesToken(char sym1, char sym2);
	bool IsCompositesSeparator(char sym1, char sym2);

public:
	TokenBreaking(std::string text);

	std::vector<Token*>* GetTokens();
	void ShowTokens();
};

