#include "AbstractSyntaxTree.h"

AbstractSyntaxTree::AbstractSyntaxTree(Node* head)
{
	_tree = head;
}

void AbstractSyntaxTree::ShowPartTree(Node* sub, size_t level)
{
	if (sub == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < level; i++)
	{
		cout << "|  ";
	}

	switch (sub->GetType())
	{
	case NodeType::NEW_VAR:
		cout << "NewVar ";
		break;
	case NodeType::VAR:
		cout << "+-Var ";
		break;
	case NodeType::VAR_TYPE:
		cout << "+-VarType ";
		break;
	case NodeType::NEW_CONST:
		break;
	case NodeType::CONST:
		cout << "+-Const ";
		break;
	case NodeType::ADD:
		cout << "+-Add ";
		break;
	case NodeType::SUB:
		cout << "+-Sub ";
		break;
	case NodeType::MUL:
		cout << "+-Mul ";
		break;
	case NodeType::DVS:
		cout << "+-Dvs ";
		break;
	case NodeType::FOR:
		cout << "For ";
		break;
	case NodeType::IF:
		cout << "If ";
		break;
	case NodeType::IF_ELSE:
		cout << "IfElse ";
		break;
	case NodeType::LESS:
		cout << "+-Less ";
		break;
	case NodeType::MORE:
		cout << "+-More ";
		break;
	case NodeType::EQUAL:
		cout << "Equal ";
		break;
	case NodeType::NOT_EQUAL:
		cout << "NotEqual ";
		break;
	case NodeType::LESS_EQUAL:
		break;
	case NodeType::MORE_EQUAL:
		break;
	case NodeType::LT:
		break;
	case NodeType::SET:
		cout << "+-Set ";
		break;
	case NodeType::EMPTY:
		cout << "Empty ";
		break;
	case NodeType::EXPR:
		cout << "Expr ";
		break;
	case NodeType::PROG:
		cout << "Prog ";
		break;
	case NodeType::SEQ:
		cout << "Seq ";
		break;
	case NodeType::STMT:
		break;
	case NodeType::FUNC:
		break;
	case NodeType::FUNC_ARGS:
		break;
	case NodeType::FUNC_ARG:
		break;
	case NodeType::FUNCTION_IMPL:
		break;
	case NodeType::FUNCTION_IMPL_ARGS:
		break;
	case NodeType::FUNCTION_IMPL_ARG:
		break;
	case NodeType::FUNCTION_IMPL_TYPE:
		break;
	case NodeType::RETURN:
		break;
	}

	cout << sub->GetValue() << endl;

	ShowPartTree(sub->Operand1, level + 1);
	ShowPartTree(sub->Operand2, level + 1);
	ShowPartTree(sub->Operand3, level + 1);
	ShowPartTree(sub->Operand4, level + 1);
}

void AbstractSyntaxTree::ShowTree()
{
	ShowPartTree(_tree, 0);
}

void AbstractSyntaxTree::SetTree(Node* head)
{
	_tree = head;
}
