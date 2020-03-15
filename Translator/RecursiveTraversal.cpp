#include "RecursiveTraversal.h"
#include "Function.h"
#include "Errors/Error.h"

RecursiveTraversal::RecursiveTraversal(Node* headNode)
{
	Node* tempNode = headNode->Operand1;
	while (tempNode != nullptr)
	{
		string name = tempNode->Operand1->GetValue();
		vector<VariableType>* types = new vector<VariableType>();

		Node* tempTypes = tempNode->Operand1->Operand1->Operand2;
		while (tempTypes != nullptr)
		{
			types->push_back(GetTypeVariable(tempTypes->GetValue()));
			tempTypes = tempTypes->Operand1;
		}

		Function* newfunc = new Function(name, types);
		_allFunction.Add(newfunc);

		tempNode = tempNode->Operand2;
	}
	Traversal(headNode);
}

void RecursiveTraversal::Traversal(Node* currentNode)
{
    if (currentNode == nullptr)
        return;

	if (currentNode->GetType() == NodeType::VAR)
	{
		string name = currentNode->GetValue();
		if (_allVariable.IsVariable(name) == false)
		{
			//Error("AST1");
		}
	}
	else if (currentNode->GetType() == NodeType::FUNC_ACCESS)
	{
		string name = currentNode->GetValue();
		if (_allFunction.IsVariable(name) == false)
		{
			Error("AST2");
		}
	}
    else if (currentNode->GetType() == NodeType::NEW_VAR)
    {
        string name = currentNode->GetValue();
		VariableType type = VariableType::UNDEFINED;
		if(currentNode->Operand1 != nullptr)
		{
			type = GetTypeVariable(currentNode->Operand1->GetValue());
		}
         

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



void RecursiveTraversal::Show()
{
	_allVariable;
}
