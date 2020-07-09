#pragma once
#include "VariableType.h"
#include "TableVariable.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Function
{
private:
	string _name;
	vector<VariableType>* _typesReturn;
	
	int _volumeReturned = 0;
	TableVariable* _globalVariables;

public:
	Function(const string& name, vector<VariableType>* types);

	TableVariable LocalVariables;
	TableVariable ArgVariables;

	string GetName();
	vector<VariableType>* GetTypes();

	int GetVolumeReturn();
	int GetVolumeTotal();
};

