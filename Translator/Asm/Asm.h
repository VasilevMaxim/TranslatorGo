#pragma once
#include "../Node.h"
#include "../TableFunction.h"
#include "../TableImport.h"

class Asm
{

public:
	Asm(Node* headNode, TableFunction* functions, TableImport* imports);
	string GetWritingAsm();
private:
	string _writing;

	bool _isFirstFunc = true;

	string _lastFunc;
	TableFunction* _functions;
	TableImport* _imports;
	string GetTextFuncVariable();


	void InitLocalVariables();
	Node* RecursiveTraversal(Node* nodeHead);
	void RecursiveRelationExpressionToAsm(Node* node);

	// ------- Helper methods.---------
	Node* InitTextSegment(Node* node);
	void InitFunc(Node* func);
	void ExprAsm(Node* node);

	string GetLocalVar(const string& value);
	string GetLableColon(const string& value);

	Node* SetBlockAsm(Node* node);
	Node* IfBlockAsm(Node* node);
	Node* ForBlockAsm(Node* node);


	//////////

	void Push(const string& value);
	void Pop(const string& value);

	void Mov(const string& value1, const string& value2);

	void Add(const string& value1, const string& value2);
	void Sub(const string& value1, const string& value2);
	void Imul(const string& value1, const string& value2);

	void Finit();
	void Fild(const string& value);
	void Fdiv(const string& value1, const string& value2);
	void Fist(const string& value);

	void Cmp(const string& value1, const string& value2);

	void Jmp(const string& value);
	void Je(const string& value);
	void Jne(const string& value);
	void Jl(const string& value);
	void Jle(const string& value);
	void Jg(const string& value);
	void Jge(const string& value);

	string GetOr(const string& value1, const string& value2);
	string GetAnd(const string& value1, const string& value2);

	/////////

	void Call(const string& value);

	/////////

	void Println_d(const string& value);
	void Sqrt(const string& value);
};

