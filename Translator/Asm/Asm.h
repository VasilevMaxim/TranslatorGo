#pragma once
#include "../Node.h"

class Asm
{

public:
	Asm(Node* headNode);
	
private:
	string _writing;

	int _numFunction = 0;
	string GetTextFuncVariable();

	Node* RecursiveTraversal(Node* nodeHead);

	//////// Helper methods.

	Node* InitTextSegment(Node* node);
	void InitFunc(Node* func);


	//////////

	void Push(const string& value1, const string& value2);
	void Pop(const string& value1, const string& value2);

	void Mov(const string& value1, const string& value2);

	void Add(const string& value1, const string& value2);
	void Sub(const string& value1, const string& value2);
	void Mul(const string& value1, const string& value2);
	void Imul(const string& value1, const string& value2);

	void Jmp(const string& value);
	void Je(const string& value);
	void Jne(const string& value);
	void Jl(const string& value);
	void Jle(const string& value);
	void Jg(const string& value);
	void Jge(const string& value);
};

