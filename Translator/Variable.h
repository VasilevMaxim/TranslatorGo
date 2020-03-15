#pragma once
#include "VariableType.h"
#include <string>

using std::string;

class Variable
{
private:
	string _name;
	VariableType _type;
public:
	bool IsConst = false;

	Variable(const string& name, VariableType type);

	string GetName();
	VariableType GetType();
};

