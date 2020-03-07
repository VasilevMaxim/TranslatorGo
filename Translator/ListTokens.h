#pragma once
#include <queue>
#include <vector>
#include "Token.h"
#include "Node.h"
#include "Singleton.h"

using std::vector;

class ListTokens : public Singleton<ListTokens>
{
private:
	int _indexCurrentToken;
	vector<Token*>* _tokens;

	int _numCurrentLine = 1;
	int _indexFirstSymLine = 0;
public:
	void Initialization(vector<Token*>* tokens);

	Token* GetCurrentToken();
	void UseNextToken();

	string GetLineCurrentToken();
	int GetNumLine();
};