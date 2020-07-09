#include "Function.h"

Function::Function(const string& name, vector<VariableType>* types)
{
	_name = name;
	_typesReturn = types;

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

int Function::GetVolumeReturn()
{
	return _volumeReturned;
}

int Function::GetVolumeTotal()
{
	return LocalVariables.GetVolumeVariables() - ArgVariables.GetVolumeVariables();
}
