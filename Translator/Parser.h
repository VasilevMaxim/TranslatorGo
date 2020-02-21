#pragma once
#include "Node.h"
#include "TokenBreaking.h"

class Parser
{
private:

	int _indexCurrentToken = 0;
	std::vector<Token*> _tokens;
	bool _isBlockVars;

	Token* GetCurrentToken();
	void SetNextToken();
	

	Node* Parse();
	Node* Statement();
	Node* ParentExpr();
	Node* Expr();
	Node* Unar();
	Node* Compare();
	Node* Ymnog();
	Node* Summa();
	Node* GetNodeValue();

	
	void ShowLevelNode(std::string nodeType);

public:
	Parser(std::vector<Token*> allTokens);
	Node* head;
	void ShowTree(Node* sub, size_t level);
};

