#pragma once
#include <iostream>
#include <vector>
#include "Token.h"

using std::vector;
using std::cout;
using std::endl;

class TokenBreaking
{
private:
	string _text;

	string _separators = " \t\r";
	string _znaks = ",()[]{}:=+-*%/!;<>&|\n";
	string _fixedZnaks = "\"\'";
	
	bool _delayMinus = false;

	vector<Token*> _tokens;

	Token* GetToken(string lexeme);
	void SplitIntoTokens();
	bool IsCompositesToken(char sym1, char sym2);
	bool IsCompositesSeparator(char sym1, char sym2);

public:
	TokenBreaking(string text);

	vector<Token*>* GetTokens();
	void ShowTokens();
	bool IsSymNumber(char sym);
	bool IsSymLit(char sym);
};

