#include "TableFunction.h"

TableFunction::~TableFunction()
{
	_functions.clear();
}

void TableFunction::Add(Function* function)
{
	_functions.push_back(function);
}

Function* TableFunction::GetNameVariable(const string name)
{
	for (auto& variable : _functions)
	{
		if (variable->GetName() == name)
		{
			return variable;
		}
	}

	// error
}

bool TableFunction::ContainsVariable(const string name)
{
	for (auto& variable : _functions)
	{
		if (variable->GetName() == name)
		{
			return true;
		}
	}

	return false;
}
bool TableFunction::IsVariable(const string& name)
{
	for (int i = 0; i < _functions.size(); i++)
	{
		if (_functions[i]->GetName() == name)
		{
			return true;
		}
	}
	return false;
}

Function* TableFunction::GetFunction(int index)
{
	return _functions[index];
}
