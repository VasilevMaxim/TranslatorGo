#pragma once
#include "../Node.h"
#include "../TableFunction.h"
#include "../TableImport.h"
#include <map>

using std::map;

class Asm
{

public:
	Asm(Node* headNode, TableFunction* functions, TableImport* imports);
	string GetWritingAsm();
private:
	string _writing;
	string _dataWriting;


	int _byteArguments = 0;

	bool _isFirstFunc = true;
	bool _isMainFuncTraversal = false;
	
	map<string, string> _stringsConst;
	int _numStringConst = 0;

	Function* _functionLast;
	string _lastFunctionName;

	TableFunction* _functions;
	TableImport* _imports;
	string GetTextFuncVariable();


	void InitLocalVariables();
	void InitArgumentVariables();
	void InitArgumentsOnStack(Node* node);

	Node* RecursiveTraversal(Node* nodeHead);
	void RecursiveRelationExpressionToAsm(Node* node);

	// ------- Helper methods.---------
	void InitStringConstants(Node* node);
	Node* InitTextSegment(Node* node);
	void InitFunc(Node* func);
	void InitReturn(Node* node);
	void ExprAsm(Node* node);

	string GetArgument(Variable* variable);

	string GetLocalVar(const string& value);
	string GetLableColon(const string& value);
	string GetStringConst(const string& value, bool isNewLine);

	Node* SetBlockAsm(Node* node);
	void IfBlockAsm(Node* node);
	Node* ForBlockAsm(Node* node);

	void FunctionCallToAsm(Node* node, bool inExpr);
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

	string GetOffset(const string& value);

	void Call(const string& value);
	void Ret(const string& value);

	void Println_d(const string& value);
	void Println_s(const string& value);
	void Sqrt(const string& value);
	void Scan(const string& value);
};

