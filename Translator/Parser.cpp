#include "Parser.h"
#include "BaseTokenTypes.h"
#include "Errors/Error.h"
#include <queue>

using std::queue;

Parser::Parser(vector<Token*>* allTokens)
{
	_tokens = ListTokens::GetInstance();
	_tokens->Initialization(allTokens);
	_variableNodes = new QueueVariableNode();

	Parse();
}

Node* Parser::GetNodeHead()
{
	return _head;
}


Node* Parser::Parse()
{
	_head = new Node(NodeType::PROG, "", new Node(NodeType::STATEMENT, "", Statements()));
	if (_tokens->GetCurrentToken()->GetValue()[0] != EOF)
	{
		// error("Invalid statement syntax")
	}
	return _head;
}

Node* Parser::Statements()
{
	Node* head;
	Node* temp  = new Node(NodeType::STATEMENT, "", Statement());
	if (temp->Operand1 == nullptr)
	{
		temp->Operand2 = new Node(NodeType::STMT, "", Statement());
		temp = temp->Operand2;
	}
	head = temp;

	if (_tokens->GetCurrentToken()->IsSeporator() == true)
	{
		_tokens->UseNextToken();
	}
	else
	{
		Error("P112");
	}

	while (_tokens->IsBackTokens() == false)
	{
		if (_tokens->GetCurrentToken()->GetType() == TokenType::CONST || _tokens->GetCurrentToken()->GetType() == TokenType::VAR)
		{
			temp->Operand2 = new Node(NodeType::STMT, "", Statement());

			if (_tokens->GetCurrentToken()->IsSeporator() == true)
			{
				_tokens->UseNextToken();
			}
			else
			{
				Error("P112");
			}
		}
		else if(_tokens->GetCurrentToken()->GetType() == TokenType::FUNC)
		{
			temp->Operand2 = new Node(NodeType::STMT, "", new Node(NodeType::STATEMENT, "", Statement()));

			if (_tokens->GetCurrentToken()->IsSeporator() == true)
			{
 				_tokens->UseNextToken();
			}
			else
			{
				if (_tokens->IsBackTokens() == false)
				{
					Error("P112");
				}
			}
		}
		else
		{
			Error("P1223");
		}


		
		temp = temp->Operand2;
	}
	return head;
}

Node* Parser::Statement()
{
	Node* node = nullptr;

	if (_variableNodes->IsLPAR() == true)
	{
		if (_tokens->GetCurrentToken()->GetType() == TokenType::LITERAL)
		{
			_variableNodes->PlacedUnderControl(this, _variableNodes->IsConst());
		}
		node = _variableNodes->Pop();
		if (_tokens->GetCurrentToken()->IsSeporator() == true)
		{
			_tokens->UseNextToken();
		}

		if (_tokens->GetCurrentToken()->GetType() == TokenType::RPAR)
		{
			_variableNodes->SetLPAR(false);
			_tokens->UseNextToken();
			_tokens->UseNextToken();
		}
	}
	else if (_variableNodes->IsEmpty() == false)
	{
		node = _variableNodes->Pop();
		if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
		{
			node = new Node(NodeType::FUNC_ACCESS, node->GetValue(), GetListParametersAccess());
		}

	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::VAR)
	{
		_tokens->UseNextToken();
		_variableNodes->PlacedUnderControl(this, false);
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::CONST)
	{
		_tokens->UseNextToken();
		_variableNodes->PlacedUnderControl(this, true);

		node = _variableNodes->Pop();
		if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
		{
			node = new Node(NodeType::FUNC_ACCESS, node->GetValue(), GetListParametersAccess());
		}

	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::LITERAL)
	{
		_variableNodes->PlacedUnderControl(this, _variableNodes->IsConst());
		if (_tokens->GetCurrentToken()->IsSeporator() == true)
		{
			_tokens->UseNextToken();
		}

		node = _variableNodes->Pop();
		if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
		{
			node = new Node(NodeType::FUNC_ACCESS, node->GetValue(), GetListParametersAccess());
		}

	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::RBRA)
	{
		return node;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::IF)
	{
		node = new Node(NodeType::IF); 
		_tokens->UseNextToken();

		node->Operand1 = Expr();
		
		if (_tokens->GetCurrentToken()->GetType() != TokenType::LBRA)
			Error("P8");

		node->Operand2 = new Node(NodeType::STATEMENT, "", Statement());
	
		if (_tokens->GetCurrentToken()->GetType() == TokenType::ELSE)
		{
			Node* nodeActiveIfElse = node;
			while (_tokens->GetCurrentToken()->GetType() == TokenType::ELSE)
			{
				_tokens->UseNextToken();
				if (_tokens->GetCurrentToken()->GetType() == TokenType::IF)
				{
					_tokens->UseNextToken();
					Node* newNodeIfElse = new Node(NodeType::IF_ELSE);
					newNodeIfElse->Operand1 = ParentExprSBra();
					newNodeIfElse->Operand2 = new Node(NodeType::STATEMENT, "", Statement());

					nodeActiveIfElse->Operand3 = newNodeIfElse;
					nodeActiveIfElse = newNodeIfElse;
				}
				else
				{
					Node* newNodeElse = new Node(NodeType::IF_ELSE);

					newNodeElse->Operand1 = new Node(NodeType::STATEMENT, "", Statement());
					// _tokens->UseNextToken();
					nodeActiveIfElse->Operand3 = newNodeElse;
					break;
				}
			}
		}
		else
		{
			//_tokens->UseNextToken();
		}
 	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::FOR)
	{
		node = new Node(NodeType::FOR);
		_tokens->UseNextToken();
		if (_tokens->GetCurrentToken()->GetType() != TokenType::LBRA)
		{
			node->Operand1 = ParentExprSBra();
			if (_tokens->GetCurrentToken()->GetType() != TokenType::LBRA)
			{
				_tokens->UseNextToken();
				node->Operand2 = ParentExprSBra();
				_tokens->UseNextToken();
				node->Operand3 = ParentExprSBra();
			}
		}

		node->Operand4 = new Node(NodeType::STATEMENT, "", Statement());
		_tokens->UseNextToken();
		node = new Node(NodeType::STATEMENT, "", node);
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::BREAK)
	{
		node = new Node(NodeType::BREAK);
		_tokens->UseNextToken();
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::SEMICOLON || _tokens->GetCurrentToken()->GetType() == TokenType::NEW_LINE)
	{
		_tokens->UseNextToken();
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::FUNC)
	{
		_tokens->UseNextToken();
		_isStartFunc = true;
		if (_tokens->GetCurrentToken()->GetType() != TokenType::LITERAL)
			Error("P1");

		node = new Node(NodeType::FUNC, _tokens->GetCurrentToken()->GetValue());
		node->Operand1 = GetSignatureFunc();
		node->Operand2 = new Node(NodeType::STATEMENT, "", Statement());
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::RETURN)
	{
		_tokens->UseNextToken();

		node = GetListParametersAccess();
	}
	else if (_isBlockVars == true && _tokens->GetCurrentToken()->GetType() == TokenType::RPAR)
	{
		_isBlockVars == false;
		_tokens->UseNextToken();
		_tokens->UseNextToken();
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::LBRA)
	{
		_tokens->UseNextToken();

		if (_isStartFunc == true)
		{
			_isStartFunc = false;
			node = Statement();
		}
		else
		{
			node = Statement();
			//node = new Node(NodeType::STATEMENT, "", Statement());
		}
		
		while (_tokens->GetCurrentToken()->GetType() != TokenType::RBRA)
		{
			node = new Node(NodeType::SEQ, "", node, Statement());
		}

		if (_tokens->IsBackTokens() == false)
		{
			_tokens->UseNextToken();
		}
	}
	else
	{
		node = new Node(NodeType::EXPR, "", Expr());
		if (_tokens->GetCurrentToken()->GetType() != TokenType::SEMICOLON && _tokens->GetCurrentToken()->GetType() != TokenType::NEW_LINE)
		{
			// error
		}

		if (_tokens->GetCurrentToken()->GetType() != TokenType::RBRA)
		{
			_tokens->UseNextToken();
		}
		
	}
	
	return node;
}

Node* Parser::GetSignatureFunc()
{
	_tokens->UseNextToken();

	if (_tokens->GetCurrentToken()->GetType() != TokenType::LPAR)
		Error("P2");

	Node* node = new Node(NodeType::SIGNATURE);
	
	_tokens->UseNextToken();
	if (_tokens->GetCurrentToken()->GetType() != TokenType::RPAR)
	{
		node->Operand1 = GetListParameters();
	}
	
	_tokens->UseNextToken();

	if (_tokens->GetCurrentToken()->GetType() == TokenType::LBRA)
	{
		return node;
	}

	node->Operand2 = GetResultFunc();

	return node;
}

Node* Parser::GetResultFunc()
{
	Node* tempRezult = GetTypeParams();
	Node* headRezult = tempRezult;

	while (true)
	{
		_tokens->UseNextToken();

		if (_tokens->GetCurrentToken()->GetType() == TokenType::LBRA)
		{
			break;
		}
		else if (_tokens->GetCurrentToken()->GetType() == TokenType::COMMA)
		{
			_tokens->UseNextToken();
		}
		else
		{
			Error("P7");
		}

		tempRezult->Operand2 = GetTypeParams();
		tempRezult = tempRezult->Operand2;
	}

	return headRezult;
}

Node* Parser::GetNodeArray()
{
	return nullptr;
}

Node* Parser::GetListParameters()
{
	Node* headListOtherTypesParams = ApplyTypeParameters();
	Node* temp = headListOtherTypesParams;

	if (_tokens->GetCurrentToken()->GetType() != TokenType::RPAR)
	{
		_tokens->UseNextToken();
		while (true)
		{
			temp->Operand3 = ApplyTypeParameters();
			temp = temp->Operand3;

			if (_tokens->GetCurrentToken()->GetType() == TokenType::RPAR)
			{
				break;
			}

			if (_tokens->GetCurrentToken()->GetType() != TokenType::COMMA)
				Error("P6");

			_tokens->UseNextToken();
		}
	}
	
	return headListOtherTypesParams;
}

Node* Parser::ApplyTypeParameters()
{
	Node* headListParams = RezultParameters();
	Node* temp = headListParams;

	Node* type = GetTypeParams();

	while (temp != nullptr)
	{
		temp->Operand1 = type;
		temp = temp->Operand2;
	}

	_tokens->UseNextToken();
	return headListParams;
}


Node* Parser::RezultParameters()
{
	Node* temp = Parameters();
	Node* begin = temp;
	Node* pastTemp = temp;

	if (_tokens->GetCurrentToken()->GetType() == TokenType::COMMA)
	{
		_tokens->UseNextToken();
		while (true)
		{
			temp = Parameters();

			// Create List.
			pastTemp->Operand2 = temp;
			pastTemp = temp;

			if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA || _tokens->GetCurrentToken()->IsVar() == true)
			{
				break;
			}

			if (_tokens->GetCurrentToken()->GetType() != TokenType::COMMA)
				Error("P4");

			_tokens->UseNextToken();

		}
	}

	return begin;
}


Node* Parser::Parameters()
{	
	if (_tokens->GetCurrentToken()->GetType() != TokenType::LITERAL &&  _tokens->GetCurrentToken()->IsNumber() == false)
		Error("P3");

	Node* node = new Node(NodeType::NEW_VAR, _tokens->GetCurrentToken()->GetValue());
	_tokens->UseNextToken();

	return node;
}

Node* Parser::GetTypeParams()
{
	Node* type = nullptr;
	Node* expr = nullptr;

	if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
	{
		_tokens->UseNextToken();
		expr = Expr();
		_tokens->UseNextToken();
	}

	if (_tokens->GetCurrentToken()->IsVar() == false)
	{
		Error("P4");
	}
	
	type = new Node(NodeType::VAR_TYPE, _tokens->GetCurrentToken()->GetValue(), expr);
	
	return type;
}

void Parser::InitializationArray(Node* node, string type)
{
	Node* tempActiveElementArray = new Node(NodeType::VAR, _tokens->GetCurrentToken()->GetValue());
	tempActiveElementArray->Operand1 = new Node(NodeType::VAR_TYPE, type);
	node->Operand4 = tempActiveElementArray;

	while (true)
	{
		_tokens->UseNextToken();
		if (_tokens->GetCurrentToken()->GetType() == TokenType::COMMA)
		{
			_tokens->UseNextToken();
			if (_tokens->GetCurrentToken()->GetType() == TokenType::RBRA)
			{
				_tokens->UseNextToken();
				break;
			}
			else if (_tokens->GetCurrentToken()->GetType() == TokenType::NEW_LINE)
			{
				_tokens->UseNextToken();
				if (_tokens->GetCurrentToken()->GetType() == TokenType::RBRA)
				{
					_tokens->UseNextToken();
					break;
				}
			}
		}
		else if (_tokens->GetCurrentToken()->GetType() == TokenType::RBRA)
		{
			_tokens->UseNextToken();
			break;
		}


		Node* newElementArray = new Node(NodeType::VAR, _tokens->GetCurrentToken()->GetValue());
		newElementArray->Operand1 = new Node(NodeType::VAR_TYPE, type);

		tempActiveElementArray->Operand2 = newElementArray;
		tempActiveElementArray = newElementArray;
	}
}

Node* Parser::ParentExprSBra()
{
	if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
	{
		_tokens->UseNextToken();
	}

	Node* node = ParentExpr();

	if (_tokens->GetCurrentToken()->GetType() == TokenType::R_SBRA)
	{
		_tokens->UseNextToken();

	}

	return node;
}

Node* Parser::ParentExpr()
{
	if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
	{
		_tokens->UseNextToken();
	}

	Node* node = Expr();

	if (_tokens->GetCurrentToken()->GetType() == TokenType::RPAR)
	{
		_tokens->UseNextToken();
	}

	return node;
}


Node* Parser::Expr()
{
	 Node* node = nullptr;
	 if (_tokens->GetCurrentToken()->IsNumber() == true)
		 return LogOr();

	 if (_tokens->GetCurrentToken()->IsVar() == true)
	 {
		 _tokens->UseNextToken();
		 _tokens->UseNextToken();
		 node = new Node(NodeType::SET, "", node, Expr());
	 }

	 node = LogOr();


	 if (node->GetType() == NodeType::VAR && _tokens->GetCurrentToken()->IsWithAssing())
	 {
		 if (_tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN_DECLARATION)
		 {
			 node = new Node(NodeType::NEW_VAR, node->GetValue());
			 node = new Node(NodeType::NEW_VAR, node->GetValue());
			 node->Operand1 = new Node(NodeType::VAR_TYPE, "null");
		 }

		 switch (_tokens->GetCurrentToken()->GetType())
		 {
			 case TokenType::PLUS_EQUAL:
				 _tokens->UseNextToken();
				 node = new Node(NodeType::SET, "", node, new Node(NodeType::ADD, "", node, ParentExprSBra()));
				break;
			 case TokenType::MINUS_EQUAL:
				 _tokens->UseNextToken();
				 node = new Node(NodeType::SET, "", node, new Node(NodeType::SUB, "", node, ParentExprSBra()));
				 break;
			 case TokenType::STAR_EQUAL:
				 _tokens->UseNextToken();
				 node = new Node(NodeType::SET, "", node, new Node(NodeType::MUL, "", node, ParentExprSBra()));
				 break;
			 case TokenType::SLASH_EQUAL:
				 _tokens->UseNextToken();
				 node = new Node(NodeType::SET, "", node, new Node(NodeType::DIV, "", node, ParentExprSBra()));
				 break;
			 case TokenType::PROCENT_EQUAL:
				 _tokens->UseNextToken();
				 node = new Node(NodeType::SET, "", node, new Node(NodeType::REM_OF_DIV, "", node, ParentExprSBra()));
				 break;
			 default:
			 {
				 _tokens->UseNextToken();
				 if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
				 {
					 node->Operand2 = ParentExprSBra();
					 node->Operand1 = new Node(NodeType::VAR_TYPE, _tokens->GetCurrentToken()->GetValue());
					 string tempType = _tokens->GetCurrentToken()->GetValue();
					 _tokens->UseNextToken();
					 _tokens->UseNextToken();
					 InitializationArray(node, tempType);
				 }
				 else
				 {
					 node = new Node(NodeType::SET, "", node, ParentExprSBra());
				 }
			 }

		 }
	 }

	 return node;
}




Node* Parser::LogOr()
{
	Node* node = LogAnd();

	while (_tokens->GetCurrentToken()->GetType() == TokenType::OR)
	{
		_tokens->UseNextToken();
		node = new Node(NodeType::OR, "", node, LogAnd());
	}
	return node;
}

Node* Parser::LogAnd()
{
	Node* node = LogUnarOr();

	while (_tokens->GetCurrentToken()->GetType() == TokenType::AND)
	{
		_tokens->UseNextToken();
		node = new Node(NodeType::AND, "", node, LogUnarOr());
	}
	return node;
}


Node* Parser::LogUnarOr()
{
	Node* node = LogUnarAnd();

	while (_tokens->GetCurrentToken()->GetType() == TokenType::OR_ONE)
	{
		_tokens->UseNextToken();
		node = new Node(NodeType::OR_ONE, "", node, LogUnarAnd());
	}
	return node;
}

Node* Parser::LogUnarAnd()
{
	Node* node = Compare();

	while (_tokens->GetCurrentToken()->GetType() == TokenType::AND_ONE)
	{
		_tokens->UseNextToken();
		node = new Node(NodeType::AND_ONE, "", node, Compare());
	}
	return node;
}


Node* Parser::Compare()
{
	Node* node = Summa();
	NodeType typeCompare;

	
	if (_tokens->GetCurrentToken()->GetType() == TokenType::LESS)
	{
		typeCompare = NodeType::LESS;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::MORE)
	{
		typeCompare = NodeType::MORE;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::LESS_EQUAL)
	{
		typeCompare = NodeType::LESS_EQUAL;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::MORE_EQUAL)
	{
		typeCompare = NodeType::MORE_EQUAL;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::EQUAL)
	{
		typeCompare = NodeType::EQUAL;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::NOT_EQUAL)
	{
		typeCompare = NodeType::NOT_EQUAL;
	}

	if (_tokens->GetCurrentToken()->GetType() == TokenType::LESS || _tokens->GetCurrentToken()->GetType() == TokenType::MORE
		|| _tokens->GetCurrentToken()->GetType() == TokenType::LESS_EQUAL || _tokens->GetCurrentToken()->GetType() == TokenType::MORE_EQUAL 
		|| _tokens->GetCurrentToken()->GetType() == TokenType::EQUAL || _tokens->GetCurrentToken()->GetType() == TokenType::NOT_EQUAL)
	{
		_tokens->UseNextToken();
		node = new Node(typeCompare, "", node, Summa());
	}
	
	return node;
}


Node* Parser::Summa()
{
	Node* node = Ymnog();
	NodeType nodeType;
	while (_tokens->GetCurrentToken()->GetType() == TokenType::PLUS || _tokens->GetCurrentToken()->GetType() == TokenType::MINUS)
	{
		if (_tokens->GetCurrentToken()->GetType() == TokenType::PLUS)
		{
			nodeType = NodeType::ADD;
		}
		else if (_tokens->GetCurrentToken()->GetType() == TokenType::MINUS)
		{
			nodeType = NodeType::SUB;
		}

		_tokens->UseNextToken();
		node = new Node(nodeType, "", node, Ymnog());
	}
	return node;
}

Node* Parser::Ymnog()
{
	Node* node = Unar();
	NodeType nodeType;
	while (_tokens->GetCurrentToken()->GetType() == TokenType::SLASH || _tokens->GetCurrentToken()->GetType() == TokenType::STAR || _tokens->GetCurrentToken()->GetType() == TokenType::PROCENT)
	{
		if (_tokens->GetCurrentToken()->GetType() == TokenType::SLASH)
		{
			nodeType = NodeType::DIV;
		}
		else if (_tokens->GetCurrentToken()->GetType() == TokenType::STAR)
		{
			nodeType = NodeType::MUL;
		}
		else if (_tokens->GetCurrentToken()->GetType() == TokenType::PROCENT)
		{
			nodeType = NodeType::REM_OF_DIV;
		}

		_tokens->UseNextToken();
		node = new Node(nodeType, "", node, Unar());
	}
	return node;
}


Node* Parser::Unar()
{
	Node* node = nullptr;
	if (_tokens->GetCurrentToken()->GetType() == TokenType::INCREMENT)
	{
		_tokens->UseNextToken();
		node = Inversion();
		node = new Node(NodeType::INCREMENT, "", node);
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::DECREMENT)
	{
		_tokens->UseNextToken();
		node = Inversion();
		node = new Node(NodeType::DECREMENT, "", node);
	}
	else
	{
		node = Inversion();
		if (_tokens->GetCurrentToken()->GetType() == TokenType::INCREMENT || _tokens->GetCurrentToken()->GetType() == TokenType::DECREMENT)
		{
			if (_tokens->GetCurrentToken()->GetType() == TokenType::INCREMENT)
			{
				node = new Node(NodeType::INCREMENT_AFTER, "", node);
			}
			else if (_tokens->GetCurrentToken()->GetType() == TokenType::DECREMENT)
			{
				node = new Node(NodeType::DECREMENT_AFTER, "", node);
			}
			_tokens->UseNextToken();
		}
	}


	return node;
}

Node* Parser::Cast()
{
	return nullptr;
}

Node* Parser::Inversion()
{
	Node* node = nullptr;
	if (_tokens->GetCurrentToken()->GetType() == TokenType::INVERSION)
	{
		_tokens->UseNextToken();
		node = new Node(NodeType::INVERSION, "", node, GetNodeValue());
	}
	else
	{
		node = GetNodeValue();
	}


	return node;
}


Node* Parser::GetNodeValue()
{
	Node* node = nullptr;
	if (_tokens->GetCurrentToken()->GetType() == TokenType::LITERAL)
	{
		string nameVar = _tokens->GetCurrentToken()->GetValue();
		node = new Node(NodeType::VAR, _tokens->GetCurrentToken()->GetValue());

		_tokens->UseNextToken();

		if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
		{
			node = new Node(NodeType::ARRAY_ACCESS, nameVar, ParentExprSBra());
		}
		if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
		{
			_tokens->UseNextToken();
			node = new Node(NodeType::FUNC_ACCESS, nameVar, GetListParametersAccess());
		}

		return node;
	}
	else if (_tokens->GetCurrentToken()->IsNumber() == true)
	{
		if (_tokens->GetCurrentToken()->GetType() == TokenType::NUMBER)
		{
			node = new Node(NodeType::CONST, _tokens->GetCurrentToken()->GetValue());
		}
		if (_tokens->GetCurrentToken()->GetType() == TokenType::NUMBER_DOUBLE)
		{
			node = new Node(NodeType::CONST_DOUBLE, _tokens->GetCurrentToken()->GetValue());
		}
	
		_tokens->UseNextToken();
		return node;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::TRUE || _tokens->GetCurrentToken()->GetType() == TokenType::FALSE)
	{
		node = new Node(NodeType::BOOL, _tokens->GetCurrentToken()->GetValue());
		_tokens->UseNextToken();
		return node;
	}
	else if (_tokens->GetCurrentToken()->IsVar() == true)
	{
		string temp = _tokens->GetCurrentToken()->GetValue();
		_tokens->UseNextToken();
		_tokens->UseNextToken();
		node = new Node(NodeType::CAST, temp, Expr());
		_tokens->UseNextToken();
		return node;
	}
	else
	{
		return ParentExprSBra();
	}
}

Node* Parser::GetListParametersAccess()
{
	Node* headParam = ParentExprSBra();
	Node* temp = headParam;
	while (_tokens->GetCurrentToken()->GetType() == TokenType::COMMA)
	{
		_tokens->UseNextToken();
		temp->Operand4 = ParentExprSBra();
		temp = temp->Operand4;
	}
	
	return headParam;
	
}