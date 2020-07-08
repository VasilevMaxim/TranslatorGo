#pragma once
#include "Import.h"
#include <vector>

using std::vector;

class TableImport
{
private:
	vector<Import*> _imports;
public:
	TableImport() = default;

	void Add(Import* import);
	Import* GetImport(const string& name);
	bool ContainsImport(const string value);
	bool ContainsFunction(const string value);
};

