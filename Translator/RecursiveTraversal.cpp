#include "RecursiveTraversal.h"

void RecursiveTraversal::Traversal(Node* currentNode)
{
    if (currentNode == nullptr)
        return;

    if (currentNode->GetType() == NodeType::VAR)
    {
        string name = currentNode->GetValue();
        VariableType type = GetTypeVariable(currentNode->Operand1->GetValue());

        Variable* newVar = new Variable(name, type);
        _allVariable.Add(newVar);
    }

    Traversal(currentNode->Operand1);
    Traversal(currentNode->Operand2);
    Traversal(currentNode->Operand3);
    Traversal(currentNode->Operand4);
}

VariableType RecursiveTraversal::GetTypeVariable(string type)
{
    if (type == "int")
    {
        return VariableType::INTEGER;
    }
    else if (type == "bool")
    {
        return VariableType::BOOLEAN;
    }
    else  if (type == "float64")
    {
        return VariableType::FLOAT64;
    }
    else  if (type == "double")
    {
        return VariableType::FLOAT;
    }

    return VariableType::UNDEFINED;
}
