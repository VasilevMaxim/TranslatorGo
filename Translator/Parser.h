#pragma once
#include "Node.h"
#include "TokenBreaking.h"
#include "VariableInit.h"

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
	ListTokens* _tokens;
	QueueVariableNode* _variableNodes;

	Node* Cast();
	Node* Inversion();
	Node* GetListParametersAccess();
	Node* Statements();
	Node* GetSignatureFunc();
	Node* GetResultFunc();
	Node* GetNodeArray();
	Node* GetListParameters();
	Node* RezultParameters();
	Node* ApplyTypeParameters();
	Node* Parameters();

	Node* GetTypeParams();

	Node* Parse();
	Node* Statement();
	Node* ParentExpr();

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

	Node* ParentExprSBra();
	Node* Expr();

	Parser(vector<Token*>* allTokens);
	
	Node* GetNodeHead();
};

