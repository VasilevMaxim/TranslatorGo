#pragma once
#include "Node.h"
#include "TableFunction.h"
#include "ListSequence.h"

class RecursiveTraversal
{
private:
    TableVariable _globalVariable;
	TableFunction _allFunction;

	ListSequence _listSequence;

	int _levelCurrentSequence = 0;
public:
	RecursiveTraversal(Node* currentNode);
    void Traversal(Node* currentNode);
	bool IsTraversalExprDouble(Node* currentNode);
    VariableType GetTypeVariable(string type);
	
	void Show();
};

