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
		cout << "+-NewConst ";
		break;
	case NodeType::ARRAY:
		cout << "+-Array ";
		break;
	case NodeType::ARRAY_ACCESS:
		cout << "+-ArrayAccess ";
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
	case NodeType::DIV:
		cout << "+-Div ";
		break;
	case NodeType::REM_OF_DIV :
		cout << "+-RemOfDiv ";
		break;
	case NodeType::FOR:
		cout << "For ";
		break;
	case NodeType::BREAK:
		cout << "+-Break ";
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
	case NodeType::MORE_EQUAL:
		cout << "+-MoreEqual ";
		break;
	case NodeType::LESS_EQUAL:
		cout << "+-LessEqual ";
		break;
	case NodeType::EQUAL:
		cout << "+-Equal ";
		break;
	case NodeType::NOT_EQUAL:
		cout << "+-NotEqual ";
		break;
	case NodeType::AND:
		cout << "+-And ";
		break;
	case NodeType::OR:
		cout << "+-Or ";
		break;
	case NodeType::AND_ONE:
		cout << "+-AndOne ";
		break;
	case NodeType::OR_ONE:
		cout << "+-OrOne ";
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
	case NodeType::INCREMENT:
		cout << "+-Inc ";
		break;
	case NodeType::DECREMENT:
		cout << "+-Dec ";
		break;
	case NodeType::INCREMENT_AFTER:
		cout << "+-IncAfter ";
		break;
	case NodeType::DECREMENT_AFTER:
		cout << "+-DecAfter ";
		break;
	case NodeType::STMT:
		cout << "+-Stmt ";
		break;
	case NodeType::FUNC:
		cout << "+-Func ";
		break;
	case NodeType::FUNC_ARGS:
		cout << "+-FuncArgs ";
		break;
	case NodeType::FUNC_ARG:
		cout << "+-FuncArg ";
		break;
	case NodeType::FUNCTION_IMPL:
		cout << "+-FuncImpl ";
		break;
	case NodeType::FUNCTION_IMPL_ARGS:
		cout << "+-FuncImplArgs ";
		break;
	case NodeType::FUNCTION_IMPL_ARG:
		cout << "+-FuncImplArg ";
		break;
	case NodeType::FUNCTION_IMPL_TYPE:
		break;
	case NodeType::CAST:
		cout << "Cast ";
		break;
	case NodeType::STATEMENT:
		cout << "Statement ";
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
