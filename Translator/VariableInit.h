#pragma once
#include <queue>
#include <vector>
#include "Token.h"
#include "Node.h"
#include "ListTokens.h"
#include "Singleton.h"
#include "Parser.h"
#include "Errors/Error.h"

using std::vector;
using std::queue;

class Parser;

class QueueVariableNode
{

private:
	queue<Node*> _vars;
	Node* _type;
	ListTokens* _tokens;

	bool _isConst = false;
	NodeType _typeNewVar = NodeType::NEW_VAR;

	bool _isLPAR = false;
	Parser* _parser;

	void PushingVariables();
	void InitializationVariables();
	Node* GetType();
	Node* InitializationArray();
public:

	QueueVariableNode();
	void PlacedUnderControl(Parser* parser, bool isConst);

	Node* Pop();

	bool IsLPAR();
	bool IsConst();
	void SetLPAR(bool value);
	bool IsEmpty();
};

