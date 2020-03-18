#pragma once
#include "Sequence.h"

class ListSequence
{
public:
	vector<Sequence*> _listSequence;

	Sequence* GetCurrentSequence();
	void Add(Sequence* sequence);
	void RemoveBack();
	bool IsVariable(const string& name);
	Variable* GetVariable(const string& name);
};

