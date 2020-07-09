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
	bool IsArray = false;
	bool IsArgument = false;

	int Postfix = 0;
	
	Variable(const string& name, VariableType type);

	string GetName();
	string GetNameWithPostfix();
	VariableType GetType();
	void SetType(VariableType type);
};

