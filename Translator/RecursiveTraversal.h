#pragma once
#include "Node.h"
#include "TableVariable.h"

class RecursiveTraversal
{
private:
    TableVariable _allVariable;
public:
    void Traversal(Node* currentNode);
    VariableType GetTypeVariable(string type);
};

