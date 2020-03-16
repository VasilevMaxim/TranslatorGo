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
