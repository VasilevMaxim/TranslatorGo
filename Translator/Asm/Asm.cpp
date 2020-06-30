#include "Asm.h"
#include "AsmConstants.h"

Asm::Asm(Node* headNode)
{
	RecursiveTraversal(headNode);
}

string Asm::GetTextFuncVariable()
{
	string s;
	return s;
}

Node* Asm::RecursiveTraversal(Node* node)
{
	if (node == nullptr)
		return nullptr;

	InitTextSegment(node);


	RecursiveTraversal(node->Operand1);
	RecursiveTraversal(node->Operand2);
	RecursiveTraversal(node->Operand3);
	RecursiveTraversal(node->Operand4);
}

Node* Asm::InitTextSegment(Node* node)
{
	_writing.append(stc::textBegin);
	if (node->GetType() == NodeType::FUNC)
		InitFunc(node);

	_writing.append(stc::textEnd);
	_writing.append(stc::mainEnd);

	return nullptr;
}

void Asm::InitFunc(Node* func)
{
	auto volumeTotal = func->Function->GetVolumeTotal();
	string x;
	x.append(stc::mainBegin);

	x.append(stc::functionProlog);
	x.append(std::to_string(volumeTotal));
	x.append(", 0\n");

	//Push("eax");

	x.append(stc::functionEpilogue);
	x.append(stc::functionReturn);
}

void Asm::Push(const string& value1, const string& value2)
{

}

void Asm::Pop(const string& value1, const string& value2)
{

}

void Asm::Mov(const string& value1, const string& value2)
{

}

void Asm::Add(const string& value1, const string& value2)
{

}

void Asm::Sub(const string& value1, const string& value2)
{

}

void Asm::Mul(const string& value1, const string& value2)
{
}

void Asm::Imul(const string& value1, const string& value2)
{

}

void Asm::Jmp(const string& value)
{
}

void Asm::Je(const string& value)
{
}

void Asm::Jne(const string& value)
{
}

void Asm::Jl(const string& value)
{
}

void Asm::Jle(const string& value)
{
}

void Asm::Jg(const string& value)
{
}

void Asm::Jge(const string& value)
{
}
