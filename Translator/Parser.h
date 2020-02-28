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
	Node* ParentExprSBra();
	Node* ParentExpr();
	Node* Expr();
	Node* Unar();
	Node* Compare();
	Node* Ymnog();
	Node* Summa();
	Node* LogOr();
	Node* LogAnd();
	Node* LogUnarOr();
	Node* LogUnarAnd();
	Node* GetNodeValue();

	Node* _head;

	void InitializationArray(Node* x, string type);
public:
	Parser(vector<Token*>* allTokens);
	
	Node* GetNodeHead();
};

