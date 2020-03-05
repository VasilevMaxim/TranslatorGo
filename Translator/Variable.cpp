#include "Variable.h"

Variable::Variable(const string name, VariableType type)
{
	_name = name;
	_type = type;
}

string Variable::GetName()
{
	return _name;
}

VariableType Variable::GetType()
{
	return _type;
}