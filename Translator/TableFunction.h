#pragma once
#include "Function.h"
#include <vector>

using std::vector;

class TableFunction
{
private:
	vector<Function*> _functions;
public:
	TableFunction() = default;
	~TableFunction();

	void Add(Function* var);
	Function* GetNameVariable(const string name);
	bool ContainsVariable(const string name);
	bool IsVariable(const string& name);
	Function* GetFunction(int index);
};

