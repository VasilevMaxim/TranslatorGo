#include "ListSequence.h"

Sequence* ListSequence::GetCurrentSequence()
{
	return _listSequence.back();
}

void ListSequence::Add(Sequence* sequence)
{
	_listSequence.push_back(sequence);
}

void ListSequence::RemoveBack()
{
	_listSequence.pop_back();
}

bool ListSequence::IsVariable(const string& name)
{
	for (int i = _listSequence.size() - 1; i >= 0; i--)
	{
		if (_listSequence[i]->LocalVariables.IsVariable(name) == true)
		{
			return true;
		}
	}

	return false;
}

Variable* ListSequence::GetVariable(const string& name)
{
	for (int i = _listSequence.size() - 1; i >= 0; i--)
	{
		if (_listSequence[i]->LocalVariables.IsVariable(name) == true)
		{
			return _listSequence[i]->LocalVariables.GetNameVariable(name);
		}
	}

	return nullptr;
}

bool ListSequence::IsVariableInOnlyLast(const string& name)
{
	for (int i = _listSequence.size() - 1; i >= 0; i--)
	{
		if (_listSequence[i]->LocalVariables._vars.size() > 0)
		{
			if(_listSequence[i]->LocalVariables.IsVariable(name) == true)
				return true;
			else
				return false;
		}
	}

	return false;
}
