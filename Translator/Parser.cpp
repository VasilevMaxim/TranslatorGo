#include "Parser.h"
#include "BaseTokenTypes.h"
#include "ErrorParser.h"
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
	_head = new Node(NodeType::PROG, "", Statements());
	if (_tokens->GetCurrentToken()->GetValue()[0] != EOF)
	{
		// error("Invalid statement syntax")
	}
	return _head;
}

Node* Parser::Statements()
{
	Node* temp  = new Node(NodeType::STMT, "", Statement());
	while (_tokens->IsBackTokens() == false)
	{
		_tokens->UseNextToken();
		temp = temp->Operand1;
		temp = new Node(NodeType::STMT, "", temp, Statement());
	}
	return temp;
}

Node* Parser::Statement()
{
	Node* node = nullptr;
	if (_tokens->GetCurrentToken()->GetType() == TokenType::IF)
	{
		node = new Node(NodeType::IF); 
		_tokens->UseNextToken();

		node->Operand1 = ParentExprSBra();
		
		if (_tokens->GetCurrentToken()->GetType() != TokenType::LBRA)
			ErrorParser(8);

		node->Operand2 = Statement(); 
	
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
					newNodeIfElse->Operand2 = Statement();

					nodeActiveIfElse->Operand3 = newNodeIfElse;
					nodeActiveIfElse = newNodeIfElse;
				}
				else
				{
					Node* newNodeElse = new Node(NodeType::IF_ELSE);

					newNodeElse->Operand1 = Statement();
					_tokens->UseNextToken();
					nodeActiveIfElse->Operand3 = newNodeElse;
					break;
				}
			}
		}
		else
		{
			_tokens->UseNextToken();
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

		node->Operand4 = Statement();
		_tokens->UseNextToken();
	}
	else if (_variableNodes->IsLPAR() == true)
	{
		if (_tokens->GetCurrentToken()->GetType() == TokenType::LITERAL)
		{
			_variableNodes->PlacedUnderControl(this, _variableNodes->IsConst());
		}
		node = _variableNodes->Pop(); 
		_tokens->UseNextToken();

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

		if (_tokens->GetCurrentToken()->GetType() != TokenType::LITERAL)
			ErrorParser(1);

		node = new Node(NodeType::FUNC, _tokens->GetCurrentToken()->GetValue());
		node->Operand1 = GetSignatureFunc();
		node->Operand2 = Statement();
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
		node = Statement();
		while (_tokens->GetCurrentToken()->GetType() != TokenType::RBRA)
		{
			node = new Node(NodeType::SEQ, "", node, Statement());
		}
		_tokens->UseNextToken();
	}
	else
	{
		node = new Node(NodeType::EXPR, "", Expr());
		if (_tokens->GetCurrentToken()->GetType() != TokenType::SEMICOLON && _tokens->GetCurrentToken()->GetType() != TokenType::NEW_LINE)
		{
			// error
		}

		_tokens->UseNextToken();
	}
	
	return node;
}

Node* Parser::GetSignatureFunc()
{
	_tokens->UseNextToken();

	if (_tokens->GetCurrentToken()->GetType() != TokenType::LPAR)
		ErrorParser(2);

	_tokens->UseNextToken();
	Node* node = GetListParameters();
	_tokens->UseNextToken();

	if (_tokens->GetCurrentToken()->GetType() == TokenType::LBRA)
	{
		return node;
	}

	node->Operand4 = GetResultFunc();

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
			ErrorParser(7);
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
			ErrorParser(6);

		_tokens->UseNextToken();
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

	_tokens->UseNextToken();

	while (true)
	{
		temp = Parameters();

		// Create List.
		pastTemp->Operand2 = temp;
		pastTemp = temp;

		if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA || BaseTokenTypes::IsTypeVar(_tokens->GetCurrentToken()->GetType()) == true)
		{
			break;
		}

		if (_tokens->GetCurrentToken()->GetType() != TokenType::COMMA)
			ErrorParser(4);

		_tokens->UseNextToken();

	}

	return begin;
}


Node* Parser::Parameters()
{
	if (_tokens->GetCurrentToken()->GetType() != TokenType::LITERAL)
		ErrorParser(3);

	Node* node = new Node(NodeType::VAR, _tokens->GetCurrentToken()->GetValue());
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
		ErrorParser(5);
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
	 if (_tokens->GetCurrentToken()->GetType() == TokenType::NUMBER)
		 return LogOr();

	 if (BaseTokenTypes::IsTypeVar(_tokens->GetCurrentToken()->GetType()) == true)
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
		node = GetNodeValue();
		node = new Node(NodeType::INCREMENT, "", node);
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::DECREMENT)
	{
		_tokens->UseNextToken();
		node = GetNodeValue();
		node = new Node(NodeType::DECREMENT, "", node);
	}
	else
	{
		node = GetNodeValue();
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
			node = new Node(NodeType::ARRAY_ACCESS, nameVar, ParentExpr());
		}

		return node;
	}
	else if (_tokens->GetCurrentToken()->GetType() == TokenType::NUMBER)
	{
		node = new Node(NodeType::CONST, _tokens->GetCurrentToken()->GetValue());
		_tokens->UseNextToken();
		return node;
	}
	else
	{
		return ParentExprSBra();
	}
}

