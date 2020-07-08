#include "RecursiveTraversal.h"
#include "Function.h"
#include "Errors/Error.h"

RecursiveTraversal::RecursiveTraversal(Node* headNode)
{
	_listSequence.Add(new Sequence(0));
	Node* tempNode = headNode->Operand1->Operand1;
	while (tempNode != nullptr)
	{
		if (tempNode->Operand1 != nullptr && tempNode->Operand1->GetType() == NodeType::FUNC)
		{
			Node* func = tempNode->Operand1;
			string name = func->GetValue();
			vector<VariableType>* types = new vector<VariableType>();

			Node* tempTypes = func->Operand1->Operand2;
			while (tempTypes != nullptr)
			{
				types->push_back(GetTypeVariable(tempTypes->GetValue()));
				tempTypes = tempTypes->Operand1;
			}

			Function* newfunc = new Function(name, types, &_globalVariable);
			_allFunction.Add(newfunc);
		}

		if (tempNode->Operand1->GetType() == NodeType::IMPORT)
		{
			_allImport.Add(new Import(tempNode->Operand1->GetValue()));
		}

		
		tempNode = tempNode->Operand2;
	}

	_allImport.GetImport("fmt")->AddKey("Println");
	_allImport.GetImport("math")->AddKey("Sqrt");

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
			Error("AST1", name);
		}
		else
		{
			auto var = _listSequence.GetVariable(name);
			currentNode->Variable = var;
		}
	}
	else if(currentNode->GetType() == NodeType::ARRAY_ACCESS)
	{
		string name = currentNode->GetValue();

		if (_listSequence.IsVariable(name) == false)
		{
			Error("AST1", name);
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
			Error("AST1", name);
		}

		if (IsTraversalExprDouble(currentNode->Operand1) == true)
		{
			Error("AST1", name);
		}
	}
	else if (currentNode->GetType() == NodeType::FUNC_ACCESS)
	{
		string name = currentNode->GetValue();

		if (_allFunction.IsVariable(name) == false)
		{
			auto dotPosition = name.find('.');

			if (dotPosition != string::npos)
			{
				auto first = name.substr(0, dotPosition);
				auto second = name.substr(dotPosition + 1, name.size() - dotPosition);

				if (_allImport.ContainsImport(first) == false)
				{
					Error("AST2", name);
				}
				else
				{
					if (_allImport.ContainsFunction(second) == false)
					{
						Error("AST2", name);
					}
				}
			}
			else
			{
				Error("AST2", name);
			}
		}
	}
	else if (currentNode->GetType() == NodeType::FUNC)
	{
		_functionCurrent = _allFunction.GetFunction(_indexCurrentFunction++);
		currentNode->Function = _functionCurrent;
	}
	else if (currentNode->GetType() == NodeType::SET)
	{
		Node* varLeft = currentNode->Operand1;

		if (currentNode->Operand1->GetType() != NodeType::NEW_VAR
			&& currentNode->Operand1->GetType() != NodeType::NEW_CONST)
		{
			string name = varLeft->GetValue();
			if (_listSequence.IsVariable(name) == false)
			{
				Error("AST1", name);
			}
		}

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
			if (varLeft->Operand1->IsValueNull() == true)
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
    else if (currentNode->GetType() == NodeType::NEW_VAR || currentNode->GetType() == NodeType::NEW_CONST || currentNode->GetType() == NodeType::ARRAY)
    {
        string name = currentNode->GetValue();
		VariableType type = GetTypeVariable(currentNode->Operand1->GetValue());
		Variable* newVar = new Variable(name, type);

		auto lastVar = _listSequence.GetVariable(name);
		Variable* nVar = nullptr;

		for (int i = _allFunction.GetSize() - 1; i >= 0 ; i--)
		{
			if (_allFunction.GetFunction(i)->LocalVariables.ContainsVariable(name) == true)
			{
				nVar = _allFunction.GetFunction(i)->LocalVariables.GetNameVariable(name);
			}
		}

		if (_listSequence.IsVariableInOnlyLast(name) == true)
		{
			Error("AST9", name);
		}

		if (lastVar != nullptr)
		{
			newVar->Postfix = lastVar->Postfix + 1;
			lastVar = newVar;
		}
		else if (nVar != nullptr)
		{
			newVar->Postfix = nVar->Postfix + 1;
			lastVar = newVar;
		}

		if (currentNode->GetType() == NodeType::NEW_CONST)
		{
			newVar->IsConst = true;
		}
		if (currentNode->GetType() == NodeType::ARRAY)
		{
			newVar->IsArray = true;
		}

		_listSequence.GetCurrentSequence()->LocalVariables.Add(newVar);

		if (_functionCurrent == nullptr)
			_globalVariable.Add(newVar);
		else
			_functionCurrent->LocalVariables.Add(newVar);

		if(lastVar == nullptr)
			currentNode->Variable = newVar;
		else
			currentNode->Variable = lastVar;
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

int RecursiveTraversal::GetVolumeGlobalVariables()
{
	return _globalVariable.GetVolumeVariables();
}



void RecursiveTraversal::Show()
{
	
}
