#pragma once
#include "Node.h"
#include "TableFunction.h"
#include "ListSequence.h"

class RecursiveTraversal
{
private:
    
	TableVariable _globalVariable;

	ListSequence _listSequence;

	Function* _functionCurrent;
	int _indexCurrentFunction = 0;
	int _levelCurrentSequence = 0;


public:
	TableFunction _allFunction;

	RecursiveTraversal(Node* currentNode);
    void Traversal(Node* currentNode);
	bool IsTraversalExprDouble(Node* currentNode);
    VariableType GetTypeVariable(string type);
	
	int GetVolumeGlobalVariables();

	void Show();
};

