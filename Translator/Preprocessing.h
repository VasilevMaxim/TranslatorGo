#pragma once
#include <string>
#include <vector>
#include "Token.h"

using std::string;
using std::vector;

class Preprocessing
{
private:
	string _text;
public:
	Preprocessing(string* text);
	string GetText();
};

