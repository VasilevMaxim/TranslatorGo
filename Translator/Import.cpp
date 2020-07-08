#include "Import.h"

Import::Import(const string& value)
{
	_value = value;
}

string Import::GetValue()
{
	return _value;
}

void Import::AddKey(const string& value)
{
	_keys.push_back(value);
}

bool Import::IsKey(const string& value)
{
	for (auto& key : _keys)
	{
		if (key == value)
			return true;
	}

	return false;
}
