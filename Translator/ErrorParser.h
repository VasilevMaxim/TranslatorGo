#pragma once
#include "Error.h"
#include <string>
class ErrorParser : public Error
{
public:
	ErrorParser(int num) : Error(std::to_string(num), true) {}
};

