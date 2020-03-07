#include "TableVariable.h"

TableVariable::~TableVariable()
{
	_vars.clear();
}

void TableVariable::Add(Variable* var)
{
	_vars.push_back(var);
}

Variable* TableVariable::GetNameVariable(const string name)
{
    for (auto& variable : _vars)
    {
        if (variable->GetName() == name)
        {
            return variable;
        }
    }

    // error
}

bool TableVariable::ContainsVariable(const string name)
{
    for (auto& variable : _vars)
    {
        if (variable->GetName() == name)
        {
            return true;
        }
    }

    return false;
}
