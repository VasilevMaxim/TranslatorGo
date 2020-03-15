#include "RecursiveTraversal.h"
#include "Function.h"
#include "Errors/Error.h"

RecursiveTraversal::RecursiveTraversal(Node* headNode)
{
	Node* tempNode = headNode->Operand1;
	while (tempNode != nullptr)
	{
		if (tempNode->Operand1 != nullptr && tempNode->Operand1->GetType() == NodeType::FUNC)
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
		}
		
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
		bool isArray = currentNode->Operand1 && currentNode->Operand1->Operand1 != nullptr;
		string name = currentNode->GetValue();
		if (isArray == false)
		{
			if (_allVariable.IsVariable(name) == false)
			{
				Error("AST1");
			}
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
	else if (currentNode->GetType() == NodeType::NEW_CONST)
	{
		string name = currentNode->GetValue();
		VariableType type = VariableType::UNDEFINED;
		if (currentNode->Operand1 != nullptr)
		{
			type = GetTypeVariable(currentNode->Operand1->GetValue());
		}


		Variable* newVar = new Variable(name, type);
		newVar->IsConst = true;
		_allVariable.Add(newVar);
	}
	else if (currentNode->GetType() == NodeType::SET)
	{
		Node* varLeft = currentNode->Operand1;
		VariableType typeVarLeft = _allVariable.GetNameVariable(varLeft->GetValue())->GetType();

		if (_allVariable.GetNameVariable(varLeft->GetValue())->IsConst == true)
		{
			Error("AST4");
		}

		if (typeVarLeft == VariableType::INTEGER && IsTraversalExprDouble(currentNode) == true)
		{
			Error("AST3");
		}
	}


    Traversal(currentNode->Operand1);
    Traversal(currentNode->Operand2);
    Traversal(currentNode->Operand3);
    Traversal(currentNode->Operand4);
}

bool RecursiveTraversal::IsTraversalExprDouble(Node* currentNode)
{
	if (currentNode == nullptr)
		return false;

	if (currentNode->GetType() == NodeType::DIV)
	{
		return true;
	}
	if (currentNode->GetType() == NodeType::CONST_DOUBLE)
	{
		return true;
	}

	if (currentNode->GetType() == NodeType::VAR)
	{
		if (_allVariable.GetNameVariable(currentNode->GetValue())->GetType() != VariableType::INTEGER)
		{
			return true;
		}
	}

	return IsTraversalExprDouble(currentNode->Operand1) ||
		IsTraversalExprDouble(currentNode->Operand2) ||
		IsTraversalExprDouble(currentNode->Operand3) ||
		IsTraversalExprDouble(currentNode->Operand4);
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
