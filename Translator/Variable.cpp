#include "Variable.h"

Variable::Variable(const string& name, VariableType type)
{
	_name = name;
	_type = type;
}

string Variable::GetName()
{
	return _name;
}

string Variable::GetNameWithPostfix()
{
	return _name + std::to_string(Postfix);
}

VariableType Variable::GetType()
{
	return _type;
}

void Variable::SetType(VariableType type)
{
	_type = type;
}
