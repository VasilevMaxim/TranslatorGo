#include "Function.h"

Function::Function(const string& name, vector<VariableType>* types)
{
	_name = name;
	_typesReturn = types;
}

string Function::GetName()
{
	return _name;
}

vector<VariableType>* Function::GetTypes()
{
	return _typesReturn;
}
