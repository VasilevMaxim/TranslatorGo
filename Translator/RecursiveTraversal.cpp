#include "RecursiveTraversal.h"
#include "Function.h"
#include "Errors/Error.h"

RecursiveTraversal::RecursiveTraversal(Node* headNode)
{
	_listSequence.Add(new Sequence(0));
	Node* tempNode = headNode->Operand1;
	while (tempNode != nullptr)
	{
		if (tempNode->Operand1 != nullptr && tempNode->Operand1->GetType() == NodeType::STATEMENT)
		{
			Node* func = tempNode->Operand1->Operand1;
			string name = func->GetValue();
			vector<VariableType>* types = new vector<VariableType>();

			Node* tempTypes = func->Operand1->Operand2;
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
		string name = currentNode->GetValue();

		if (_listSequence.IsVariable(name) == false)
		{
			Error("AST1");
		}
	}
	else if (currentNode->GetType() == NodeType::STATEMENT)
	{
		_levelCurrentSequence++;
		_listSequence.Add(new Sequence(_levelCurrentSequence));
	}
	else if (currentNode->GetType() == NodeType::ARRAY_ACCESS)
	{
		string name = currentNode->GetValue();

		if (_listSequence.IsVariable(name) == false)
		{
			Error("AST1");
		}

		if (IsTraversalExprDouble(currentNode->Operand1) == true)
		{
			Error("AST1");
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
	else if (currentNode->GetType() == NodeType::SET)
	{
		Node* varLeft = currentNode->Operand1;
		VariableType typeVarLeft = VariableType::UNDEFINED;
		Variable* var = _listSequence.GetVariable(varLeft->GetValue());
		if (var != nullptr)
		{
			typeVarLeft = var->GetType();

			if (_listSequence.GetVariable(varLeft->GetValue())->IsConst == true)
			{
				Error("AST4");
			}

			if (typeVarLeft == VariableType::INTEGER && IsTraversalExprDouble(currentNode) == true)
			{
				Error("AST3");
			}
		}
		else
		{
			if (varLeft->Operand1->GetValue() == "null")
			{
				if (IsTraversalExprDouble(currentNode->Operand2) == true)
				{
					varLeft->Operand1 = new Node(NodeType::VAR_TYPE, "float64");
				}
				else
				{
					varLeft->Operand1 = new Node(NodeType::VAR_TYPE, "int");
				}
			}
		}

	}
    else if (currentNode->GetType() == NodeType::NEW_VAR || currentNode->GetType() == NodeType::NEW_CONST)
    {
        string name = currentNode->GetValue();
		VariableType type = GetTypeVariable(currentNode->Operand1->GetValue());

        Variable* newVar = new Variable(name, type);

		if (currentNode->GetType() == NodeType::NEW_CONST)
		{
			newVar->IsConst = true;
		}

		_listSequence.GetCurrentSequence()->LocalVariables.Add(newVar);
    }
	


    Traversal(currentNode->Operand1);
    Traversal(currentNode->Operand2);
    Traversal(currentNode->Operand3);
    Traversal(currentNode->Operand4);


	if (currentNode->GetType() == NodeType::STATEMENT)
	{
		_levelCurrentSequence--;
		_listSequence.RemoveBack();
	}
}

bool RecursiveTraversal::IsTraversalExprDouble(Node* currentNode)
{
	if (currentNode == nullptr)
		return false;


	if (currentNode->GetType() == NodeType::CONST_DOUBLE)
	{
		return true;
	}

	if (currentNode->GetType() == NodeType::VAR)
	{
		if (_listSequence.GetVariable(currentNode->GetValue())->GetType() != VariableType::INTEGER)
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
	else  if (type == "null")
	{
		return VariableType::UNDEFINED;
	}
    return VariableType::UNDEFINED;
}



void RecursiveTraversal::Show()
{
	
}
