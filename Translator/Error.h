#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Error
{
private:
	void PrintMessage(const string& message);
	
	void PrintLineError();

public:
	Error(const string& message);
	Error(const string& message, bool lexicAnalyzer);
};

