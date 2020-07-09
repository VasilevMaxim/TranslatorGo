#pragma once
#include "Node.h"
#include "TokenBreaking.h"
#include "QueueVariableNode.h"

using std::vector;
using std::cout;
using std::endl;

class VariableInit;
class QueueVariableNode;

class Parser
{

private:

	bool _isBlockVars;
	bool _isStartFunc = false;

	bool _isIncrementAfter = false;
	bool _isDecrementAfter = false;
	Node* nodeAfter;

	ListTokens* _tokens;
	QueueVariableNode* _variableNodes;

	// Parser
	Node* Parse();
	Node* Statements();
	Node* Statement();
	Node* GetSignatureFunc();	
	Node* GetListParameters();
	Node* GetResultFunc();
	Node* ApplyTypeParameters();
	Node* RezultParameters();
	Node* Parameter();

	Node* GetTypeParams();

	void InitializationArray(Node* x, string type);
	
	
	// ParentExprSBra
	Node* ParentExpr();
	// Expr
	Node* LogOr();
	Node* LogAnd();
	Node* LogUnarOr();
	Node* LogUnarAnd();
	Node* Compare();
	Node* Add();
	Node* Mul();
	Node* Unar();
	Node* Inversion();

	Node* GetNodeValue();

	Node* GetListParametersAccess();

	Node* _head;
public:

	Node* ParentExprSBra();
	Node* Expr();

	Parser(vector<Token*>* allTokens);
	
	Node* GetNodeHead();
};

