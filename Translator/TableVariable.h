#pragma once
#include "Variable.h"
#include <vector>

using std::vector;

class TableVariable
{
private:
	vector<Variable*> _vars;
	int _volumeVariables = 0;
public:
	TableVariable() = default;
	~TableVariable();

	void Add(Variable* var);
	Variable* GetNameVariable(const string name);
	bool ContainsVariable(const string name);
	bool IsVariable(const string& name);

	int GetVolumeVariables();
};

