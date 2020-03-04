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

public:
	void Initialization(vector<Token*>* tokens);

	Token* GetCurrentToken();
	void UseNextToken();
};