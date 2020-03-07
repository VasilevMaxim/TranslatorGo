#include "Error.h"
#include "ListTokens.h"

Error::Error(const string& message)
{
	PrintMessage(message);
	PrintLineError();
	throw std::logic_error(message);
}

Error::Error(const string& message, bool lexicAnalyzer)
{
	if (lexicAnalyzer == false)
	{
		Error::Error(message);
	}
	else
	{
		PrintMessage(message);
		throw std::logic_error(message);
	}
}


void Error::PrintLineError()
{
	cout << "str(" + std::to_string(ListTokens::GetInstance()->GetNumLine()) + "):  ";
	cout << ListTokens::GetInstance()->GetLineCurrentToken() << endl;
}

void Error::PrintMessage(const string& message)
{
	cout << message << endl;
}
