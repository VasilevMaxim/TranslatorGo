#include "Parser.h"
#include "BaseTokenTypes.h"

Token* Parser::GetCurrentToken()
{
	return _tokens[_indexCurrentToken];
}

void Parser::SetNextToken()
{
	_indexCurrentToken++;
}

Node* Parser::Parse()
{
	head = new Node(NodeType::PROG, "", Statement());
	if (GetCurrentToken()->GetValue()[0] != EOF)
	{
		// error("Invalid statement syntax")
	}
	return head;
}

Node* Parser::Statement()
{
	Node* node = nullptr;
	if (GetCurrentToken()->GetType() == TokenType::IF)
	{
		node = new Node(NodeType::IF); 
		SetNextToken();

		node->Operand1 = ParentExpr();
		node->Operand2 = Statement();

		Node* nodeActiveIfElse = node;
		while(GetCurrentToken()->GetType() == TokenType::ELSE)
		{
			SetNextToken();
			if (GetCurrentToken()->GetType() == TokenType::IF)
			{
				SetNextToken();
				Node* newNodeIfElse = new Node(NodeType::IF_ELSE);
				newNodeIfElse->Operand1 = ParentExpr();
				newNodeIfElse->Operand2 = Statement();
				nodeActiveIfElse->Operand3 = newNodeIfElse;
				nodeActiveIfElse = newNodeIfElse;
				SetNextToken();
			}
			else 
			{
				SetNextToken();
				break;
			}
		}
	
		if (GetCurrentToken()->GetType() == TokenType::ELSE)
		{
			Node* newNodeElse = new Node(NodeType::IF_ELSE);
			SetNextToken();
			newNodeElse->Operand1 = Statement();

			nodeActiveIfElse->Operand3 = newNodeElse;
		}
 	}
	else if (GetCurrentToken()->GetType() == TokenType::FOR)
	{
		node = new Node(NodeType::FOR);
		SetNextToken();
		if (GetCurrentToken()->GetType() != TokenType::LBRA)
		{
			node->Operand1 = ParentExpr();
			if (GetCurrentToken()->GetType() != TokenType::LBRA)
			{
				SetNextToken();
				_tokens[_indexCurrentToken];
				node->Operand2 = ParentExpr();
				SetNextToken();
				_tokens[_indexCurrentToken];
				node->Operand3 = ParentExpr();
			}
		}
		_tokens[_indexCurrentToken];
		node->Operand4 = Statement();
	}
	else if (GetCurrentToken()->GetType() == TokenType::SEMICOLON || GetCurrentToken()->GetType() == TokenType::NEW_LINE)
	{
		node = new Node(NodeType::EMPTY);
		SetNextToken();
	}
	else if (GetCurrentToken()->GetType() == TokenType::VAR)
	{
		SetNextToken();
		if (GetCurrentToken()->GetType() == TokenType::LPAR)
		{
			SetNextToken();
			SetNextToken();

			node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
			SetNextToken();
			SetNextToken();
			node = new Node(NodeType::SET, "", node, Expr());
			_isBlockVars = true;
		}
		else if (GetCurrentToken()->GetType() == TokenType::LITERAL)
		{
			node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
			SetNextToken();
			node->Operand1 = new Node(NodeType::VAR_TYPE, GetCurrentToken()->GetValue());
			SetNextToken();
			SetNextToken();
			node = new Node(NodeType::SET, "", node, Expr());
		}
	}
	else if (_isBlockVars == true && GetCurrentToken()->GetType() == TokenType::RPAR)
	{
		_isBlockVars == false;
		SetNextToken();
		SetNextToken();
	}
	else if (GetCurrentToken()->GetType() == TokenType::LBRA)
	{
		node = new Node(NodeType::EMPTY);
		SetNextToken();
		while (GetCurrentToken()->GetType() != TokenType::RBRA)
		{
			node = new Node(NodeType::SEQ, "", node, Statement());
		}
		SetNextToken();
	}
	else
	{
		node = new Node(NodeType::EXPR, "", Expr());
		if (GetCurrentToken()->GetType() != TokenType::SEMICOLON && GetCurrentToken()->GetType() != TokenType::NEW_LINE)
		{
			// error
		}

		SetNextToken();
	}
	
	return node;
}

Node* Parser::ParentExpr()
{
	if (GetCurrentToken()->GetType() == TokenType::LPAR)
	{
		SetNextToken();
	}
	Node* node = Expr();
	if (GetCurrentToken()->GetType() == TokenType::RPAR)
	{
		SetNextToken();
	}
	return node;
}

Node* Parser::Expr()
{
	 Node* node = nullptr;
	 if (GetCurrentToken()->GetType() == TokenType::NUMBER)
		 return Compare();

	 if (BaseTokenTypes::IsTypeVar(GetCurrentToken()->GetType()) == true)
	 {
		 SetNextToken();
		 SetNextToken();
		 node = new Node(NodeType::SET, "", node, Expr());
	 }

	 node = Compare();
	 if (node->GetType() == NodeType::VAR && GetCurrentToken()->GetType() == TokenType::ASSIGN)
	 {
		 SetNextToken(); 
		 node = new Node(NodeType::SET, "", node, Expr());
	 }


	 return node;
}

Node* Parser::Compare()
{
	Node* node = Summa();
	if (GetCurrentToken()->GetType() == TokenType::LESS)
	{
		SetNextToken();
		node = new Node(NodeType::LESS, "", node, Summa());
	}
	else if (GetCurrentToken()->GetType() == TokenType::MORE)
	{
		SetNextToken();
		node = new Node(NodeType::MORE, "", node, Summa());
	}
	return node;
}



 

Node* Parser::Summa()
{
	Node* node = Ymnog();
	NodeType nodeType;
	while (GetCurrentToken()->GetType() == TokenType::PLUS || GetCurrentToken()->GetType() == TokenType::MINUS)
	{
		if (GetCurrentToken()->GetType() == TokenType::PLUS)
		{
			nodeType = NodeType::ADD;
		}
		else if (GetCurrentToken()->GetType() == TokenType::MINUS)
		{
			nodeType = NodeType::SUB;
		}

		SetNextToken();
		node = new Node(nodeType, "", node, Ymnog());
	}
	return node;
}

Node* Parser::Ymnog()
{
	Node* node = Unar();
	NodeType nodeType;
	while (GetCurrentToken()->GetType() == TokenType::SLASH || GetCurrentToken()->GetType() == TokenType::STAR)
	{
		if (GetCurrentToken()->GetType() == TokenType::SLASH)
		{
			nodeType = NodeType::DVS;
		}
		else if (GetCurrentToken()->GetType() == TokenType::STAR)
		{
			nodeType = NodeType::MUL;
		}

		SetNextToken();
		node = new Node(nodeType, "", node, Unar());
	}
	return node;
}

Node* Parser::Unar()
{
	Node* node = GetNodeValue();
	while (GetCurrentToken()->GetType() == TokenType::INCREMENT || GetCurrentToken()->GetType() == TokenType::DECREMENT)
	{
		node = new Node(NodeType::SUB, "", node, new Node(NodeType::CONST, "1"));
		SetNextToken();
	}
	return node;
}



Node* Parser::GetNodeValue()
{
	Node* node = nullptr;
	if (GetCurrentToken()->GetType() == TokenType::LITERAL)
	{
		node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
		SetNextToken();
		return node;
	}
	else if (GetCurrentToken()->GetType() == TokenType::NUMBER)
	{
		node = new Node(NodeType::CONST, GetCurrentToken()->GetValue());
		SetNextToken();
		return node;
	}
	else
	{
		return ParentExpr();
	}
}

Parser::Parser(std::vector<Token*> allTokens)
{
	_tokens = allTokens;
	Parse();
}

void Parser::ShowTree(Node* sub, size_t level)
{
	if (sub == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < level; i++)
	{
		std::cout << "|  ";
	}

	switch (sub->GetType())
	{
	case NodeType::NEW_VAR:
		std::cout << "NewVar ";
		break;
	case NodeType::VAR:
		std::cout << "+-Var ";
		break;
	case NodeType::VAR_TYPE:
		std::cout << "+-VarType ";
		break;
	case NodeType::NEW_CONST:
		break;
	case NodeType::CONST:
		std::cout << "+-Const ";
		break;
	case NodeType::ADD:
		std::cout << "+-Add ";
		break;
	case NodeType::SUB:
		std::cout << "+-Sub ";
		break;
	case NodeType::MUL:
		std::cout << "+-Mul ";
		break;
	case NodeType::DVS:
		std::cout << "+-Dvs ";
		break;
	case NodeType::FOR:
		std::cout << "For ";
		break;
	case NodeType::IF:
		std::cout << "If ";
		break;
	case NodeType::IF_ELSE:
		std::cout << "IfElse ";
		break;
	case NodeType::LESS:
		std::cout << "+-Less ";
		break;
	case NodeType::MORE:
		std::cout << "+-More ";
		break;
	case NodeType::EQUAL:
		std::cout << "Equal ";
		break;
	case NodeType::NOT_EQUAL:
		std::cout << "NotEqual ";
		break;
	case NodeType::LESS_EQUAL:
		break;
	case NodeType::GREATER_EQUAL:
		break;
	case NodeType::LT:
		break;
	case NodeType::SET:
		std::cout << "+-Set ";
		break;
	case NodeType::EMPTY:
		std::cout << "Empty ";
		break;
	case NodeType::EXPR:
		std::cout << "Expr ";
		break;
	case NodeType::PROG:
		std::cout << "Prog ";
		break;
	case NodeType::SEQ:
		std::cout << "Seq ";
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

	std::cout << sub->GetValue() << std::endl;

	ShowTree(sub->Operand1, level + 1);
	ShowTree(sub->Operand2, level + 1);
	ShowTree(sub->Operand3, level + 1);
	ShowTree(sub->Operand4, level + 1);
}
