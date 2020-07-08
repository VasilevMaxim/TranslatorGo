#include "TableImport.h"

void TableImport::Add(Import* import)
{
	_imports.push_back(import);
}

Import* TableImport::GetImport(const string& name)
{
	for (auto& import : _imports)
	{
		if (import->GetValue() == name)
			return import;
	}

	return nullptr;
}

bool TableImport::ContainsImport(const string value)
{
	for (auto& import : _imports)
	{
		if (import->GetValue() == value)
		{
			return true;
		}
	}

	return false;
}

bool TableImport::ContainsFunction(const string value)
{
	for (auto& import : _imports)
	{
		if (import->IsKey(value) == true)
		{
			return true;
		}
	}

	return false;
}
