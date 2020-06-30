#include "Function.h"

Function::Function(const string& name, vector<VariableType>* types, TableVariable* globalVariables)
{
	_name = name;
	_typesReturn = types;
	_globalVariables = globalVariables;

	for (auto& type : *_typesReturn)
		_volumeReturned += (int) type;
		
}

string Function::GetName()
{
	return _name;
}

vector<VariableType>* Function::GetTypes()
{
	return _typesReturn;
}

int Function::GetVolumeTotal()
{
	return _globalVariables->GetVolumeVariables() + _volumeReturned + LocalVariables.GetVolumeVariables();
}
