#pragma once
#include "Node.h"
#include "TokenBreaking.h"

using std::vector;
using std::cout;
using std::endl;

class Parser
{
private:

	int _indexCurrentToken = 0;
	vector<Token*>* _tokens;
	bool _isBlockVars;

	Token* GetCurrentToken();
	void UseNextToken();
	vector<Node*> _nodesVar;

	Node* Parse();
	Node* Statement();
	Node* ParentExpr();
	Node* Expr();
	Node* Unar();
	Node* Compare();
	Node* Ymnog();
	Node* Summa();
	Node* GetNodeValue();

	Node* _head;

public:
	Parser(vector<Token*>* allTokens);
	
	Node* GetNodeHead();
};

