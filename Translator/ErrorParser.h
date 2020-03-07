#pragma once
#include "Error.h"
class ErrorParser : public Error
{
public:
	ErrorParser(string text) : Error(text, true) {}
};

