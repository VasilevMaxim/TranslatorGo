#include "TableVariable.h"

TableVariable::~TableVariable()
{
	_vars.clear();
}

void TableVariable::Add(Variable* var)
{
	_vars.push_back(var);
	_volumeVariables += (int) var->GetType();
}

Variable* TableVariable::GetNameVariable(const string name)
{
    for (int i = _vars.size() - 1; i >= 0; i--)
    {
        if (_vars[i]->GetName() == name)
        {
            return _vars[i];
        }
    }

    // error
}

bool TableVariable::IsVariable(const string& name)
{
	for (int i = 0; i < _vars.size(); i++)
	{
		if (_vars[i]->GetName() == name)
		{
			return true;
		}
	}
	return false;
}

int TableVariable::GetVolumeVariables()
{
    return _volumeVariables;
}
