#pragma once
#include "Node.h"
#include "TableVariable.h"
#include "TableFunction.h"

class RecursiveTraversal
{
private:
    TableVariable _allVariable;
	TableFunction _allFunction;
public:
	RecursiveTraversal(Node* currentNode);
    void Traversal(Node* currentNode);
    VariableType GetTypeVariable(string type);
	void Show();
};

