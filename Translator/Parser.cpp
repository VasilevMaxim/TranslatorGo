#include "Parser.h"
#include "BaseTokenTypes.h"
#include <queue>

using std::queue;

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

		node->Operand1 = ParentExprSBra();
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
					newNodeIfElse->Operand1 = ParentExprSBra();
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
			node->Operand1 = ParentExprSBra();
			if (GetCurrentToken()->GetType() != TokenType::LBRA)
			{
				UseNextToken();
				node->Operand2 = ParentExprSBra();
				UseNextToken();
				node->Operand3 = ParentExprSBra();
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
	else if (GetCurrentToken()->GetType() == TokenType::FUNC)
	{
		UseNextToken();
		string nameFunc = GetCurrentToken()->GetValue();
		UseNextToken();
		if (GetCurrentToken()->GetType() != TokenType::LPAR)
		{
			// error
		}

		UseNextToken();
		if (GetCurrentToken()->GetType() == TokenType::RPAR)
		{
			node = new Node(NodeType::FUNC, nameFunc);
			UseNextToken();
		}
		else
		{
			node = new Node(NodeType::FUNC_ARG, nameFunc);

			Node* _tempActiveParam = nullptr;
			queue<string> paramsPull;
			string nameParam;
			bool isLPAR = false;

			while (true)
			{
				if (GetCurrentToken()->GetType() == TokenType::LITERAL)
				{
					paramsPull.push(GetCurrentToken()->GetValue());
					UseNextToken();
					if (GetCurrentToken()->GetType() == TokenType::COMMA)
					{
						UseNextToken();
					}
				}
				else if (GetCurrentToken()->GetType() == TokenType::L_SBRA)
				{
					UseNextToken();
					Node* exprNumNodeArray = new Node(NodeType::EXPR, "", Expr());
					UseNextToken();
					string typeArrays = GetCurrentToken()->GetValue();

					while (paramsPull.empty() == false) 
					{
						Node* newParam = new Node(NodeType::ARRAY, paramsPull.front());
						paramsPull.pop();
						newParam->Operand1 = new Node(NodeType::VAR_TYPE, typeArrays);
						newParam->Operand2 = exprNumNodeArray;

						if (_tempActiveParam == nullptr)
						{
							node->Operand1 = newParam;
						}
						else
						{
							_tempActiveParam->Operand3 = newParam;
						}

						_tempActiveParam = newParam;
					}
					
					UseNextToken(); // 
					if (GetCurrentToken()->GetType() == TokenType::LPAR)
					{
						isLPAR = true;
					}
					UseNextToken(); // param
				}
				else if(BaseTokenTypes::IsTypeVar(GetCurrentToken()->GetType()) == true && isLPAR == false)
				{
					string typeArrays = GetCurrentToken()->GetValue();

					while (paramsPull.empty() == false)
					{
						Node* newParam = new Node(NodeType::VAR, paramsPull.front());
						paramsPull.pop();
						newParam->Operand1 = new Node(NodeType::VAR_TYPE, typeArrays);

						if (_tempActiveParam == nullptr)
						{
							node->Operand1 = newParam;
						}
						else
						{
							_tempActiveParam->Operand3 = newParam;
						}

						_tempActiveParam = newParam;
					}

					UseNextToken(); // ,

					if (GetCurrentToken()->GetType() == TokenType::LPAR)
					{
						isLPAR = true;
					}
					UseNextToken(); // param
				}
				else if (BaseTokenTypes::IsTypeVar(GetCurrentToken()->GetType()) == true || GetCurrentToken()->GetType() == TokenType::L_SBRA)
				{
					Node* _tempActiveParam2 = nullptr;
					string typeReturn = nullptr;
					Node* nodeTypeReturn = nullptr;
					Node* exprNumNodeArray = nullptr;

					while (BaseTokenTypes::IsTypeVar(GetCurrentToken()->GetType()) == true || GetCurrentToken()->GetType() == TokenType::L_SBRA)
					{
						if (GetCurrentToken()->GetType() == TokenType::L_SBRA)
						{
							UseNextToken();
							exprNumNodeArray = new Node(NodeType::EXPR, "", Expr());
							UseNextToken();
							typeReturn = GetCurrentToken()->GetValue();
						}
						else
						{
							exprNumNodeArray = nullptr;
							typeReturn = GetCurrentToken()->GetValue();
						}

						nodeTypeReturn = new Node(NodeType::VAR_TYPE, typeReturn, exprNumNodeArray);
						if (_tempActiveParam2 == nullptr)
						{
							node->Operand2 = nodeTypeReturn;
						}
						else
						{
							_tempActiveParam2->Operand3 = nodeTypeReturn;
						}

						_tempActiveParam2 = nodeTypeReturn;

						UseNextToken();
						if (GetCurrentToken()->GetType() == TokenType::LBRA)
						{
							break;
						}
						UseNextToken();
					}

				}
				else if (GetCurrentToken()->GetType() == TokenType::LBRA)
				{
					break;
				}
				else 
				{
					// error
				}
			}
		}

		node->Operand3 = Statement();
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
			string nameArray = GetCurrentToken()->GetValue();

			UseNextToken();
			if (GetCurrentToken()->GetType() == TokenType::L_SBRA)
			{
				
				UseNextToken();
				Node* exprNumNodeArray = new Node(NodeType::EXPR, "", Expr());
				node = new Node(NodeType::ARRAY, nameArray);

				UseNextToken(); // type

				string tempType = GetCurrentToken()->GetValue();
				node->Operand1 = new Node(NodeType::VAR_TYPE, GetCurrentToken()->GetValue());
				node->Operand2 = exprNumNodeArray;
				
				UseNextToken();
				if (GetCurrentToken()->GetType() == TokenType::ASSIGN)
				{
					UseNextToken(); // [
					UseNextToken(); // num
					Node* tempNodeAmount = new Node(NodeType::EXPR, "", Expr());
					node->Operand3 = tempNodeAmount;
					UseNextToken(); // type
					if (GetCurrentToken()->GetValue() != tempType)
					{
						// error
					}

					UseNextToken(); // {
					UseNextToken(); // value
					InitializationArray(node, tempType);
					
				}
			}
			else if (GetCurrentToken()->GetType() == TokenType::COMMA)
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
				if (GetCurrentToken()->GetType() == TokenType::ASSIGN)
				{
					UseNextToken();
					node = new Node(NodeType::SET, "", node, Expr());
				}
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

void Parser::InitializationArray(Node* node, string type)
{
	Node* tempActiveElementArray = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
	tempActiveElementArray->Operand1 = new Node(NodeType::VAR_TYPE, type);
	node->Operand4 = tempActiveElementArray;

	while (true)
	{
		UseNextToken();
		if (GetCurrentToken()->GetType() == TokenType::COMMA)
		{
			UseNextToken();
			if (GetCurrentToken()->GetType() == TokenType::RBRA)
			{
				UseNextToken();
				break;
			}
			else if (GetCurrentToken()->GetType() == TokenType::NEW_LINE)
			{
				UseNextToken();
				if (GetCurrentToken()->GetType() == TokenType::RBRA)
				{
					UseNextToken();
					break;
				}
			}
		}
		else if (GetCurrentToken()->GetType() == TokenType::RBRA)
		{
			UseNextToken();
			break;
		}


		Node* newElementArray = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
		newElementArray->Operand1 = new Node(NodeType::VAR_TYPE, type);

		tempActiveElementArray->Operand2 = newElementArray;
		tempActiveElementArray = newElementArray;
	}
}

Node* Parser::ParentExprSBra()
{
	if (GetCurrentToken()->GetType() == TokenType::L_SBRA)
	{
		UseNextToken();
	}

	Node* node = ParentExpr();

	if (GetCurrentToken()->GetType() == TokenType::R_SBRA)
	{
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
		 return LogOr();

	 if (BaseTokenTypes::IsTypeVar(GetCurrentToken()->GetType()) == true)
	 {
		 UseNextToken();
		 UseNextToken();
		 node = new Node(NodeType::SET, "", node, Expr());
	 }

	 node = LogOr();
	 if (node->GetType() == NodeType::VAR && GetCurrentToken()->GetType() == TokenType::ASSIGN)
	 {
		 UseNextToken(); 
		 if (GetCurrentToken()->GetType() == TokenType::L_SBRA)
		 {
			 node->Operand2 = ParentExprSBra();
			 node->Operand1 = new Node(NodeType::VAR_TYPE, GetCurrentToken()->GetValue());
			 string tempType = GetCurrentToken()->GetValue();
			 UseNextToken();
			 UseNextToken();
			 InitializationArray(node, tempType);
		 }
		 else
		 {
			 node = new Node(NodeType::SET, "", node, ParentExprSBra());
		 }
	 }

	 return node;
}

Node* Parser::LogOr()
{
	Node* node = LogAnd();

	while (GetCurrentToken()->GetType() == TokenType::OR)
	{
		UseNextToken();
		node = new Node(NodeType::OR, "", node, LogAnd());
	}
	return node;
}

Node* Parser::LogAnd()
{
	Node* node = LogUnarOr();

	while (GetCurrentToken()->GetType() == TokenType::AND)
	{
		UseNextToken();
		node = new Node(NodeType::AND, "", node, LogUnarOr());
	}
	return node;
}


Node* Parser::LogUnarOr()
{
	Node* node = LogUnarAnd();

	while (GetCurrentToken()->GetType() == TokenType::OR_ONE)
	{
		UseNextToken();
		node = new Node(NodeType::OR_ONE, "", node, LogUnarAnd());
	}
	return node;
}

Node* Parser::LogUnarAnd()
{
	Node* node = Compare();

	while (GetCurrentToken()->GetType() == TokenType::AND_ONE)
	{
		UseNextToken();
		node = new Node(NodeType::AND_ONE, "", node, Compare());
	}
	return node;
}


Node* Parser::Compare()
{
	Node* node = Summa();
	NodeType typeCompare;

	
	if (GetCurrentToken()->GetType() == TokenType::LESS)
	{
		typeCompare = NodeType::LESS;
	}
	else if (GetCurrentToken()->GetType() == TokenType::MORE)
	{
		typeCompare = NodeType::MORE;
	}
	else if (GetCurrentToken()->GetType() == TokenType::LESS_EQUAL)
	{
		typeCompare = NodeType::LESS_EQUAL;
	}
	else if (GetCurrentToken()->GetType() == TokenType::MORE_EQUAL)
	{
		typeCompare = NodeType::MORE_EQUAL;
	}
	else if (GetCurrentToken()->GetType() == TokenType::EQUAL)
	{
		typeCompare = NodeType::EQUAL;
	}
	else if (GetCurrentToken()->GetType() == TokenType::NOT_EQUAL)
	{
		typeCompare = NodeType::NOT_EQUAL;
	}

	if (GetCurrentToken()->GetType() == TokenType::LESS || GetCurrentToken()->GetType() == TokenType::MORE
		|| GetCurrentToken()->GetType() == TokenType::LESS_EQUAL || GetCurrentToken()->GetType() == TokenType::MORE_EQUAL 
		|| GetCurrentToken()->GetType() == TokenType::EQUAL || GetCurrentToken()->GetType() == TokenType::NOT_EQUAL)
	{
		UseNextToken();
		node = new Node(typeCompare, "", node, Summa());
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
		string nameVar = GetCurrentToken()->GetValue();
		node = new Node(NodeType::VAR, GetCurrentToken()->GetValue());
		UseNextToken();


		if (GetCurrentToken()->GetType() == TokenType::L_SBRA)
		{
			node = new Node(NodeType::ARRAY_ACCESS, nameVar, ParentExpr());
			UseNextToken();
			node = new Node(NodeType::SET, "", node, ParentExpr());
		}

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
		return ParentExprSBra();
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
