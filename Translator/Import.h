#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

class Import
{
public:
	Import(const string& value);
	string GetValue();

	void AddKey(const string& value);
	bool IsKey(const string& value);

private:
	string _value;
	vector<string> _keys;
};

