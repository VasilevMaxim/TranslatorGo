#pragma once
#include "VariableType.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Function
{
private:
	string _name;
	vector<VariableType>* _typesReturn;
public:
	Function(const string& name, vector<VariableType>* types);
	string GetName();
	vector<VariableType>* GetTypes();
};

