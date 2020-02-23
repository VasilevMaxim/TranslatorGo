#include "Parser.h"
#include "BaseTokenTypes.h"

Token* Parser::GetCurrentToken()
{
	return (*_tokens)[_indexCurrentToken];
}

void Parser::UseNextToken()
{
	_indexCurrentToken++;
}

Node* Parser::Parse()
{
	_head = new Node(NodeType::PROG, "", Statement());
	if (GetCurrentToken()->GetValue()[0] != EOF)
	{
		// error("Invalid statement syntax")
	}
	return _head;
}

Node* Parser::Statement()
{
	Node* node = nullptr;
	if (GetCurrentToken()->GetType() == TokenType::IF)
	{
		node = new Node(NodeType::IF); 
		UseNextToken();

		node->Operand1 = ParentExpr();
		node->Operand2 = Statement(); 
	
		if (GetCurrentToken()->GetType() == TokenType::ELSE)
		{
			Node* nodeActiveIfElse = node;
			while (GetCurrentToken()->GetType() == TokenType::ELSE)
			{
				UseNextToken();
				if (GetCurrentToken()->GetType() == TokenType::IF)
				{
					UseNextToken();
					Node* newNodeIfElse = new Node(NodeType::IF_ELSE);
					newNodeIfElse->Operand1 = ParentExpr();
					newNodeIfElse->Operand2 = Statement();

					nodeActiveIfElse->Operand3 = newNodeIfElse;
					nodeActiveIfElse = newNodeIfElse;
				}
				else
				{
					Node* newNodeElse = new Node(NodeType::IF_ELSE);

					newNodeElse->Operand1 = Statement();
					UseNextToken();
					nodeActiveIfElse->Operand3 = newNodeElse;
					break;
				}
			}
		}
		else
		{
			UseNextToken();
		}
 	}
	else if (GetCurrentToken()->GetType() == TokenType::FOR)
	{
		node = new Node(NodeType::FOR);
		UseNextToken();
		if (GetCurrentToken()->GetType() != TokenType::LBRA)
		{
			node->Operand1 = ParentExpr();
			if (GetCurrentToken()->GetType() != TokenType::LBRA)
			{
				UseNextToken();
				node->Operand2 = ParentExpr();
				UseNextToken();
				node->Operand3 = ParentExpr();
			}
		}

		node->Operand4 = Statement();
		UseNextToken();
	}
	else if (GetCurrentToken()->GetType() == TokenType::BREAK)
	{
		node = new Node(NodeType::BREAK);
		UseNextToken();
	}
	else if (GetCurrentToken()->GetType() == TokenType::SEMICOLON || GetCurrentToken()->GetType() == TokenType::NEW_LINE)
	{
		UseNextToken();
	}
	else if (_nodesVar.empty() == false)
	{
		node = _nodesVar.back();
		_nodesVar.pop_back();
	}
	else if (GetCurrentToken()->GetType() == TokenType::VAR)
	{
		UseNextToken();
		if (GetCurrentToken()->GetType() == TokenType::LPAR)
		{
			UseNextToken();
			UseNextToken();
			node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
			UseNextToken();
			UseNextToken();
			node = new Node(NodeType::SET, "", node, Expr());
			_isBlockVars = true;
		}
		else if (GetCurrentToken()->GetType() == TokenType::LITERAL)
		{
			node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
			UseNextToken();

			if (GetCurrentToken()->GetType() == TokenType::COMMA)
			{
				while (GetCurrentToken()->GetType() == TokenType::COMMA)
				{
					UseNextToken();
					Node* nodeVar = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
					_nodesVar.push_back(nodeVar);

					UseNextToken();
				}

				UseNextToken();

				node = new Node(NodeType::SET, "", node, Expr());

				for (int indexNodeVar = 0; GetCurrentToken()->GetType() == TokenType::COMMA; indexNodeVar++)
				{
					UseNextToken();
					_nodesVar[indexNodeVar] = new Node(NodeType::SET, "", _nodesVar[indexNodeVar], Expr());
				}
			}
			else
			{
				node->Operand1 = new Node(NodeType::VAR_TYPE, GetCurrentToken()->GetValue());
				UseNextToken();
				UseNextToken();
				node = new Node(NodeType::SET, "", node, Expr());
			}
		}
	}
	else if (_isBlockVars == true && GetCurrentToken()->GetType() == TokenType::RPAR)
	{
		_isBlockVars == false;
		UseNextToken();
		UseNextToken();
	}
	else if (GetCurrentToken()->GetType() == TokenType::LBRA)
	{
		UseNextToken();
		node = Statement();
		while (GetCurrentToken()->GetType() != TokenType::RBRA)
		{
			node = new Node(NodeType::SEQ, "", node, Statement());
		}
		UseNextToken();
	}
	else
	{
		node = new Node(NodeType::EXPR, "", Expr());
		if (GetCurrentToken()->GetType() != TokenType::SEMICOLON && GetCurrentToken()->GetType() != TokenType::NEW_LINE)
		{
			// error
		}

		UseNextToken();
	}
	
	return node;
}

Node* Parser::ParentExpr()
{
	if (GetCurrentToken()->GetType() == TokenType::LPAR)
	{
		UseNextToken();
	}

	Node* node = Expr();

	if (GetCurrentToken()->GetType() == TokenType::RPAR)
	{
		UseNextToken();
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
		 UseNextToken();
		 UseNextToken();
		 node = new Node(NodeType::SET, "", node, Expr());
	 }

	 node = Compare();
	 if (node->GetType() == NodeType::VAR && GetCurrentToken()->GetType() == TokenType::ASSIGN)
	 {
		 UseNextToken(); 
		 node = new Node(NodeType::SET, "", node, Expr());
	 }


	 return node;
}

Node* Parser::Compare()
{
	Node* node = Summa();
	if (GetCurrentToken()->GetType() == TokenType::LESS)
	{
		UseNextToken();
		node = new Node(NodeType::LESS, "", node, Summa());
	}
	else if (GetCurrentToken()->GetType() == TokenType::MORE)
	{
		UseNextToken();
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

		UseNextToken();
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

		UseNextToken();
		node = new Node(nodeType, "", node, Unar());
	}
	return node;
}


Node* Parser::Unar()
{
	Node* node = nullptr;
	if (GetCurrentToken()->GetType() == TokenType::INCREMENT)
	{
		UseNextToken();
		node = GetNodeValue();
		node = new Node(NodeType::INCREMENT, "", node);
	}
	else if (GetCurrentToken()->GetType() == TokenType::DECREMENT)
	{
		UseNextToken();
		node = GetNodeValue();
		node = new Node(NodeType::DECREMENT, "", node);
	}
	else
	{
		node = GetNodeValue();
		if (GetCurrentToken()->GetType() == TokenType::INCREMENT || GetCurrentToken()->GetType() == TokenType::DECREMENT)
		{
			if (GetCurrentToken()->GetType() == TokenType::INCREMENT)
			{
				node = new Node(NodeType::INCREMENT_AFTER, "", node);
			}
			else if (GetCurrentToken()->GetType() == TokenType::DECREMENT)
			{
				node = new Node(NodeType::DECREMENT_AFTER, "", node);
			}
			UseNextToken();
		}
	}


	return node;
}

Node* Parser::GetNodeValue()
{
	Node* node = nullptr;
	if (GetCurrentToken()->GetType() == TokenType::LITERAL)
	{
		node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
		UseNextToken();
		return node;
	}
	else if (GetCurrentToken()->GetType() == TokenType::NUMBER)
	{
		node = new Node(NodeType::CONST, GetCurrentToken()->GetValue());
		UseNextToken();
		return node;
	}
	else
	{
		return ParentExpr();
	}
}

Parser::Parser(vector<Token*>* allTokens)
{
	_tokens = allTokens;
	Parse();
}

Node* Parser::GetNodeHead()
{
	return _head;
}
