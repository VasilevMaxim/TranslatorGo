#include "Asm.h"
#include "AsmConstants.h"
#include <iostream>
#include <any>
#include "../Random.h"

using namespace stc;
using std::cout;
using std::to_string;

Asm::Asm(Node* headNode, TableFunction* functions, TableImport* imports)
{
	_functions = functions;
	_imports = imports;

	_writing += AsmHeader;
	_writing += "\n";

	_dataWriting += dataBegin;
	_dataWriting += PrintFormat_d;
	_dataWriting += PrintFormat_s;
	_dataWriting += InputFormat;
	_dataWriting += SqrtResult;
	_dataWriting += divOperands;

	InitStringConstants(headNode);
	
	_dataWriting += dataEnd;
	_dataWriting += "\n";

	_writing += _dataWriting;

	_writing += textBegin;
	_writing += "\n";

	InitLocalVariables();
	InitArgumentVariables();
	_writing += "\n";

	_writing += ProcPrint_d;
	_writing += "\n";

	_writing += ProcPrint_s;
	_writing += "\n";

	_writing += ProcSqrt;
	_writing += "\n";

	_writing += ProcInput;
	_writing += "\n";

	// functions
	RecursiveTraversal(headNode);

	// main function
	_isMainFuncTraversal = true;
	RecursiveTraversal(headNode);

	_writing.append(functionEpilogue);
	_writing.append(functionReturn);
	_writing.append(textEnd);

	_writing.append(mainEnd);

	cout << "\n" + _writing;
}

string Asm::GetWritingAsm()
{
	return _writing;
}

string Asm::GetTextFuncVariable()
{
	string s;
	return s;
}

void Asm::InitLocalVariables()
{
	for (int i = 0; i < _functions->GetSize(); i++)
	{
		auto func = _functions->GetFunction(i);
		auto volumeTotal = func->GetVolumeTotal();

		string vars;
		int currentSize = 0;
		for (auto variable : func->LocalVariables._vars)
		{
			if (variable->IsArgument == false)
			{
				vars += tab;
				vars += variable->GetName() + std::to_string(variable->Postfix);
				vars += " = ";
				currentSize -= (int)variable->GetType();
				vars += to_string(currentSize);
				vars += "\n";
			}
		}

		_writing += vars;
	}
	
}

void Asm::InitArgumentVariables()
{
	for (int i = 0; i < _functions->GetSize(); i++)
	{
		_byteArguments = 8;
		auto vars = _functions->GetFunction(i)->ArgVariables._vars;

		for (int j = vars.size() - 1; j >= 0; j--)
		{
			_writing +=	GetArgument(vars[j]);
			_writing += "\n";
			_byteArguments += 4;
		}
	}
}

void Asm::InitArgumentsOnStack(Node* node) // 1 operand in signature
{
	if (node == nullptr)
		return;


	RecursiveTraversal(node);

	InitArgumentsOnStack(node->Operand2);
	return;
	


	InitArgumentsOnStack(node->Operand1);
	InitArgumentsOnStack(node->Operand2);
	InitArgumentsOnStack(node->Operand3);
	InitArgumentsOnStack(node->Operand4);
}

Node* Asm::RecursiveTraversal(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->GetType() == NodeType::FUNC)
	{
		if ((node->Function->GetName() != "main" && _isMainFuncTraversal == false) || 
			(node->Function->GetName() == "main" && _isMainFuncTraversal == true))
		{
			if (_isFirstFunc == false)
			{
				_writing += functionEpilogue;
				Ret(std::to_string(_functionLast->ArgVariables.GetVolumeVariables()));
				_writing += _lastFunctionName + " ENDP\n\n";
			}

			_functionLast = node->Function;
			InitTextSegment(node);
			_lastFunctionName = node->GetValue();
			_isFirstFunc = false;
		}
		else
		{
			return nullptr;
		}
	}
	else if (node->GetType() == NodeType::FOR)
	{
		ForBlockAsm(node);
		return nullptr;
	}
	else if (node->GetType() == NodeType::IF || node->GetType() == NodeType::IF_ELSE)
	{
		IfBlockAsm(node);
		return nullptr;
	}
	else if (node->GetType() == NodeType::SET)
	{
		SetBlockAsm(node->Operand2);
		Pop(GetLocalVar(node->Operand1->Variable->GetNameWithPostfix()));
		return nullptr;
	}
	else if (node->GetType() == NodeType::RETURN)
	{
		InitReturn(node);
		return nullptr;
	}
	else if (node->GetType() == NodeType::STATEMENT || node->GetType() == NodeType::SEQ)
	{
		RecursiveTraversal(node->Operand1);
		
		if(node->Operand2 != nullptr)
			RecursiveTraversal(node->Operand2);

		return nullptr;
	}
	else if (node->GetType() == NodeType::FUNC_ACCESS)
	{
		auto dotPosition2 = node->GetValue().find('.');		
		if (dotPosition2 != string::npos)
		{
			auto nameFunc = node->GetValue().substr(dotPosition2 + 1, node->GetValue().size() - dotPosition2);
			
			if (nameFunc == "Println")
			{
				string var;
				Node* tempArgument = node->Operand1;
				bool newLine = false;
				while (tempArgument != nullptr)
				{
					if (tempArgument->GetType() == NodeType::CONST_STRING)
					{
						var = tempArgument->GetValue();
						Println_s(_stringsConst[var]);
						newLine = false;
					}
					else
					{
						if (tempArgument->Variable != nullptr)
							var = GetLocalVar(tempArgument->Variable->GetNameWithPostfix());
						else if (tempArgument->GetType() == NodeType::CONST)
							var = tempArgument->GetValue();

						Println_d(var);
					}

					tempArgument = tempArgument->Operand4;
				}


			}

			if (nameFunc == "Sqrt")
			{
				Sqrt(GetLocalVar(node->Operand1->Variable->GetNameWithPostfix()));
				Mov(GetLocalVar(node->Operand1->Variable->GetNameWithPostfix()), eax);
			}

			if (nameFunc == "Scan")
			{
				Scan(GetLocalVar(node->Operand1->Variable->GetNameWithPostfix()));
				Mov(GetLocalVar(node->Operand1->Variable->GetNameWithPostfix()), eax);
			}
		}
		else
		{
			FunctionCallToAsm(node, false);
		}
		
		return nullptr;
	}
	else if (node->IsComparisonOperator() == true)
	{
		RecursiveRelationExpressionToAsm(node);
		return nullptr;
	}
	else
	{
		//ExprAsm(node);
	}
	
	


	RecursiveTraversal(node->Operand1);
	RecursiveTraversal(node->Operand2);
	RecursiveTraversal(node->Operand3);
	RecursiveTraversal(node->Operand4);
}

void Asm::RecursiveRelationExpressionToAsm(Node* node)
{
	if (node == nullptr)
		return;

	if (node->GetType() == NodeType::CONST)
	{
		const auto value = node->GetValue();

		if (value == "0")
		{
			Push(null);
		}
		else
		{
			Push(value);
		}
	}
	else if (node->GetType() == NodeType::VAR ||
		node->GetType() == NodeType::CONST)
	{
		const auto currentTime = Random::GetTimeNanoSecondsString();

		const auto labelIfEqual = "_compare_equal" + currentTime;
		const auto labelIfNotEqual = "_compare_not_equal" + currentTime;
		const auto labelCompareEnd = "_compare_end" + currentTime;

		//if (variable->isArgument())
		//	Cmp(GetLocalVar(variableName), null);
		//else
			Cmp(GetLocalVar(node->GetValue()), null);


		// jne (!=) label
		Jne(labelIfNotEqual);
		Push(null);
		Jmp(labelCompareEnd);

		_writing += GetLableColon(labelIfNotEqual);
		Push(one);

		_writing += GetLableColon(labelCompareEnd);

	}
	else if (node->GetType() == NodeType::AND)
	{
		const auto op1 = node->Operand1;
		const auto op2 = node->Operand2;

		RecursiveRelationExpressionToAsm(op1);
		Pop(eax);
		RecursiveRelationExpressionToAsm(op2);
		Pop(ebx);

		_writing += GetAnd(eax, ebx);
		Push(eax);
	}
	else if (node->GetType() == NodeType::OR)
	{
				const auto op1 = node->Operand1;
		const auto op2 = node->Operand2;

		RecursiveRelationExpressionToAsm(op1);
		Pop(eax);
		RecursiveRelationExpressionToAsm(op2);
		Pop(ebx);

		_writing += GetOr(eax, ebx);
		Push(eax);
	}
	else
	{
		const auto currentTime = Random::GetTimeNanoSecondsString();

		const auto op1 = node->Operand1;
		const auto op2 = node->Operand2;

		ExprAsm(op1);
		Pop(ecx);
		ExprAsm(op2);
		Pop(edx);

		// cmp ecx, edx
		Cmp(ecx, edx);

		const auto labelIfEqual = "_compare_equal" + currentTime;
		const auto labelIfNotEqual = "_compare_not_equal" + currentTime;
		const auto labelCompareEnd = "_compare_end" + currentTime;


		if (node->GetType() == NodeType::LESS)
		{
			// jge (>=) label
			Jge(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (node->GetType() == NodeType::LESS_EQUAL)
		{
			// jg (>) label
			Jg(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (node->GetType() == NodeType::MORE)
		{
			// jle (<=) label
			Jle(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (node->GetType() == NodeType::MORE_EQUAL)
		{
			// jl (<) label
			Jl(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (node->GetType() == NodeType::EQUAL)
		{
			// jne (!=) label
			Jne(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (node->GetType() == NodeType::NOT_EQUAL)
		{
			// je (==) label
			Je(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}

		return;
	}
}

void Asm::IfBlockAsm(Node* node)
{
	const auto conditionNode = node->Operand1;
	const auto statementNode = node->Operand2;
	const auto elseStatementNode = node->Operand3;

	auto randomName = Random::GetTimeNanoSecondsString();

	const auto startLabel = "__if_start_" + randomName;
	const auto endLabel = "__if_end_" + randomName;
	const auto elseLabel = "__if_else_" + randomName;

	// обрабатываем поддерево с условием
	ExprAsm(conditionNode);

	if (elseStatementNode != nullptr)
	{
		Pop(eax);
		Cmp(eax, null);
	}

	auto endOrElseLabel = elseLabel;

	if (elseStatementNode != nullptr)
		Je(endOrElseLabel);


	if (node->GetType() == NodeType::IF || node->GetType() == NodeType::IF_ELSE)
	{
		// label:
		_writing += GetLableColon(startLabel);
		RecursiveTraversal(statementNode);

		// jmp label
		Jmp(endLabel);

		// label:
		_writing += GetLableColon(elseLabel);
		RecursiveTraversal(elseStatementNode);

		// label:
		_writing += GetLableColon(endLabel);

	}
}

Node* Asm::ForBlockAsm(Node* node)
{
	string currentTime = Random::GetTimeNanoSecondsString();

	const auto preventionNode = node->Operand1;
	const auto conditionNode = node->Operand2;
	const auto afterEffectsNode = node->Operand3;
	const auto statementNode = node->Operand4;

	const auto startLabel = "__loop_start_" + currentTime;
	const auto endLabel = "__loop_end_" + currentTime;
	const auto afterEffectsLabel = "__loop_aftereffects_" + currentTime;
	
	
	if (node->Operand2 == nullptr)
	{
		// while

		_writing += GetLableColon(startLabel);
		RecursiveTraversal(conditionNode);

		Pop(eax);
		Cmp(eax, null);

		Je(endLabel);

		RecursiveTraversal(statementNode);
		Jmp(startLabel);

		// label:
		_writing += GetLableColon(endLabel);
	}
	else
	{
		// for

		RecursiveTraversal(preventionNode);
		_writing += GetLableColon(startLabel);

		RecursiveTraversal(conditionNode);

		Pop(eax);
		Cmp(eax, null);

		Je(endLabel);


		RecursiveTraversal(statementNode);
		_writing += GetLableColon(afterEffectsLabel);

		RecursiveTraversal(afterEffectsNode);
		Jmp(startLabel);

		// label:
		_writing += GetLableColon(endLabel);
	}

	return nullptr;
}

void Asm::FunctionCallToAsm(Node* node, bool inExpr)
{
	const auto function = node->Function;
	const auto& functionName = function->GetName();

	_writing += "\n";

	auto tempVar = node->Operand1;
	while (tempVar != nullptr)
	{
		ExprAsm(tempVar);
		tempVar = tempVar->Operand4;
	}
	


	Call(functionName);

	if (function->GetVolumeReturn() != 0 && inExpr == true)
	{
		Push(eax);
	}
}

Node* Asm::SetBlockAsm(Node* node)
{
	if (node == nullptr)
		return nullptr;

	ExprAsm(node);
}


void Asm::InitStringConstants(Node* node)
{
	if (node == nullptr)
		return;
	
	if (node->GetType() == NodeType::CONST_STRING)
	{
		bool isNewLine = false;

		int positionSl = node->GetValue().find('\\');
		if (positionSl != string::npos)
		{
			if (node->GetValue().size() > positionSl + 1)
			{
				if (node->GetValue()[positionSl + 1] == 'n')
				{
					isNewLine = true;
				}
			}
		}

		node->RemoveNewLineWrap();
		_dataWriting += GetStringConst(node->GetValue(), isNewLine);
		


		_stringsConst[node->GetValue()] = "string_const_" + std::to_string(_numStringConst);
		
		node->Id = _numStringConst;
		_numStringConst++;
	}

	InitStringConstants(node->Operand1);
	InitStringConstants(node->Operand2);
	InitStringConstants(node->Operand3);
	InitStringConstants(node->Operand4);
}

Node* Asm::InitTextSegment(Node* node)
{
	InitFunc(node);

	return nullptr;
}

void Asm::InitFunc(Node* func)
{
	auto volumeTotal = func->Function->GetVolumeTotal();

	string newFunc;
	if (func->GetValue() == "main")
		newFunc += mainBegin;
	else
		newFunc += func->GetValue() + " PROC\n";

	newFunc.append(functionProlog);
	newFunc.append(std::to_string(volumeTotal));
	newFunc.append(", 0\n");
	
	_writing += newFunc;

}

void Asm::InitReturn(Node* node)
{
	if (node->Operand1 != nullptr)
	{
		ExprAsm(node->Operand1);
		Pop(eax);
	}
}

void Asm::ExprAsm(Node* currentNode)
{
    if (currentNode == nullptr)
        return;


    if (currentNode->GetType() == NodeType::ADD)
    {
		ExprAsm(currentNode->Operand1);
		ExprAsm(currentNode->Operand2);
		
        // pop eax
        Pop(eax);
        // pop ebx
        Pop(ebx);
        // add eax, ebx
        Add(eax, ebx);
        // push eax
        Push(eax);
    }
    else if (currentNode->GetType() == NodeType::SUB)
    {
		ExprAsm(currentNode->Operand1);
		ExprAsm(currentNode->Operand2);
		
        // pop ebx
        Pop(ebx);
        // pop eax
        Pop(eax);
        // sub eax, ebx
        Sub(eax, ebx);
        // push eax
		Push(eax);
    }
    else if (currentNode->GetType() == NodeType::MUL)
    {
		ExprAsm(currentNode->Operand1);
		ExprAsm(currentNode->Operand2);
		
        // pop eax
        Pop(eax);
        // pop ebx
        Pop(ebx);
        // imul eax, ebx
        Imul(eax, ebx);
        // push eax
        Push(eax);
    }
    else if (currentNode->GetType() == NodeType::DIV)
    {
		ExprAsm(currentNode->Operand1);
		ExprAsm(currentNode->Operand2);
		
        // pop ebx
        Pop(ebx);
        // pop eax
        Pop(eax);

		Mov("div_operand_1", eax);
		Mov("div_operand_2", ebx);
		// Сопроцессор, SPU

		// Инитит сопроцессор
		Finit();

		// Типа пуша, помещает на стек
		Fild("div_operand_2");
		Fild("div_operand_1");

		// Указатели на вершину стека, и под
		Fdiv("st(0)", "st(1)");
		
		// Достает из стека
		Fist("div_operand_1");
		
		Push("div_operand_1");
    }
	else if (currentNode->GetType() == NodeType::CONST)
	{
		Push(currentNode->GetValue());
	}
	else if (currentNode->GetType() == NodeType::CONST_STRING)
	{
		const auto id = currentNode->Id;
		const auto stringAccess = "string_const_" + to_string(id);
		Push(GetOffset(stringAccess));
	}
	else if (currentNode->GetType() == NodeType::VAR)
	{	
		Push(GetLocalVar(currentNode->Variable->GetNameWithPostfix()));
	}
	else if (currentNode->GetType() == NodeType::FUNC_ACCESS)
	{
		FunctionCallToAsm(currentNode, true);
	}
	else
	{
		string currentTime = Random::GetTimeNanoSecondsString();

		const auto op1 = currentNode->Operand1;
		const auto op2 = currentNode->Operand2;

		ExprAsm(op1);
		Pop(ecx);
		ExprAsm(op2);
		Pop(edx);

		// cmp ecx, edx
		Cmp(ecx, edx);

		const auto labelIfEqual = "_compare_equal" + currentTime;
		const auto labelIfNotEqual = "_compare_not_equal" + currentTime;
		const auto labelCompareEnd = "_compare_end" + currentTime;

		if (currentNode->GetType() == NodeType::LESS)
		{
			// jge (>=) label
			Jge(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (currentNode->GetType() == NodeType::LESS_EQUAL)
		{
			// jg (>) label
			Jg(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (currentNode->GetType() == NodeType::MORE)
		{
			// jle (<=) label
			Jle(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (currentNode->GetType() == NodeType::MORE_EQUAL)
		{
			// jl (<) label
			Jl(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (currentNode->GetType() == NodeType::EQUAL)
		{
			// jne (!=) label
			Jne(labelIfNotEqual);
			Push(one);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(null);

			_writing += GetLableColon(labelCompareEnd);
		}
		else if (currentNode->GetType() == NodeType::NOT_EQUAL)
		{
			// je (==) label
			Je(labelIfNotEqual);
			Push(null);
			Jmp(labelCompareEnd);

			_writing += GetLableColon(labelIfNotEqual);
			Push(one);

			_writing += GetLableColon(labelCompareEnd);
		}
	}
}

string Asm::GetArgument(Variable* variable)
{
	const auto variableName = variable->GetNameWithPostfix();
	const auto variableSize = 4;

	return tab + variableName + " = " + std::to_string(_byteArguments);
}


void Asm::Push(const string& value)
{
	_writing += tab + "push " + value + "\n";
}

void Asm::Pop(const string& value)
{
	_writing += tab + "pop " + value + "\n";
}

void Asm::Mov(const string& value1, const string& value2)
{
	_writing += tab + "mov " + value1 + ", " + value2 + "\n";
}

void Asm::Add(const string& value1, const string& value2)
{
	_writing += tab + "add " + value1 + ", " + value2 + "\n";
}

void Asm::Sub(const string& value1, const string& value2)
{
	_writing += tab + "sub " + value1 + ", " + value2 + "\n";
}

void Asm::Imul(const string& value1, const string& value2)
{
	_writing += tab + "imul " + value1 + ", " + value2 + "\n";
	//return nullptr;
}

void Asm::Finit()
{
	_writing += tab + "finit\n";
}

void Asm::Fild(const string& value)
{
	_writing += tab + "fild " + value + "\n";
}

void Asm::Fdiv(const string& value1, const string& value2)
{
	_writing += tab + "fdiv " + value1 + ", " + value2 + "\n";
}

void Asm::Fist(const string& value)
{
	_writing += tab + "fist " + value + "\n";
}

void Asm::Cmp(const string& value1, const string& value2)
{
	_writing += tab + "cmp " + value1 + ", " + value2 + "\n";
}

void Asm::Jmp(const string& value)
{
	_writing += tab + "jmp " + value + "\n";
}

void Asm::Je(const string& value)
{
	_writing += tab + "je " + value + "\n";
}

void Asm::Jne(const string& value)
{
	_writing += tab + "jne " + value + "\n";
}

void Asm::Jl(const string& value)
{
	_writing += tab + "jl " + value + "\n";
}

void Asm::Jle(const string& value)
{
	_writing += tab + "jle " + value + "\n";
}

void Asm::Jg(const string& value)
{
	_writing += tab + "jg " + value + "\n";
}

void Asm::Jge(const string& value)
{
	_writing += tab + "jge " + value + "\n";
}

string Asm::GetOr(const string& value1, const string& value2)
{
	return tab + "or " + value1 + ", " + value2 + "\n";
}

string Asm::GetAnd(const string& value1, const string& value2)
{
	return tab + "and " + value1 + ", " + value2 + "\n";
}

string Asm::GetOffset(const string& value)
{
	return "offset " + value;
}

void Asm::Call(const string& value)
{
	_writing += tab + "call " + value + "\n";
}

void Asm::Ret(const string& value)
{
	_writing += tab + "ret " + value + "\n";
}

void Asm::Println_d(const string& value)
{
	Mov(eax, value);
	Push(eax);
	Call(print_d);
}

void Asm::Println_s(const string& value)
{
	Push(GetOffset(value));
	Call(print_s);
}

void Asm::Sqrt(const string& value)
{
	Mov(eax, value);
	Push(eax);
	Call(stc::sqrt);
}

void Asm::Scan(const string& value)
{
	Call(scan);
}



string Asm::GetLocalVar(const string& value)
{
	return value + "[ebp]";
}

string Asm::GetLableColon(const string& value)
{
	return value + ":\n";
}

string Asm::GetStringConst(const string& value, bool isNewLine)
{
	if(isNewLine == true)
		return tab + "string_const_" + std::to_string(_numStringConst) + " db " + value + ", 13,10,0\n";
	else
		return tab + "string_const_" + std::to_string(_numStringConst) + " db " + value + ", 0\n";
}

