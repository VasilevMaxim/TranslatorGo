#include "QueueVariableNode.h"
#include "BaseTokenTypes.h"

QueueVariableNode::QueueVariableNode()
{
	_tokens = ListTokens::GetInstance();
}

void QueueVariableNode::PlacedUnderControl(Parser* parser, bool isConst)
{
	_isConst = isConst;
	if (_isConst == true)
	{
		_typeNewVar = NodeType::NEW_CONST;
	}
	else
	{
		_typeNewVar = NodeType::NEW_VAR;
	}

	_parser = parser;

	if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
	{
		_isLPAR = true;
		_tokens->UseNextToken();
		if (_tokens->GetCurrentToken()->IsSeporator() == true)
		{
			_tokens->UseNextToken();
		}
		

		return;
	}
	else if (_tokens->GetCurrentToken()->GetType() != TokenType::LITERAL)
	{
		Error("P12");
	}
	PushingVariables();

	if (_tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN || _tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN_DECLARATION)
	{
		_tokens->UseNextToken();
		InitializationVariables();
	}
	else
	{
		int sizeVars = _vars.size();
		while (sizeVars-- > 0)
		{
			auto frontVar = _vars.front();
			_vars.pop();

			if (frontVar->Operand1 == nullptr)
			{
				frontVar->Operand1 = _type;
			}
			_vars.push(frontVar);
		}
		//_tokens->UseNextToken();
	}

	_isKeyVar = false;
}

void QueueVariableNode::PlacedUnderControl(Parser* parser, bool isConst, bool isKeyVar)
{
	_isKeyVar = isKeyVar;
	PlacedUnderControl(parser, isConst);
}


void QueueVariableNode::PushingVariables()
{
	string nameVar = _tokens->GetCurrentToken()->GetValue();
	Node* node;
	while (true)
	{
		nameVar = _tokens->GetCurrentToken()->GetValue();
		_tokens->UseNextToken();

		if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
		{
			node = new Node(NodeType::ARRAY, nameVar, _parser->ParentExprSBra());
		}
		else
		{
			node = new Node(_typeNewVar, nameVar);
		}
		_vars.push(node);

		if (_tokens->GetCurrentToken()->GetType() != TokenType::COMMA)
		{	
			if (node->GetType() != NodeType::ARRAY_ACCESS)
			{
				_type = new Node(NodeType::VAR_TYPE, "null"); 
			}
			
			if (_tokens->GetCurrentToken()->IsVar() == true)
			{
				delete _type;
				_type = GetType();
				_tokens->UseNextToken();
			}
			else if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA) 
			{
				delete _type;
				_type = GetType();
				_tokens->UseNextToken();
			}
			else if ((_tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN_DECLARATION) || (_tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN && _isLPAR  == true))
			{
				_vars.pop();
				_vars.push(new Node(NodeType::NEW_VAR, node->GetValue(), node->Operand1));
			}
			else if (_tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN && _isKeyVar == false)
			{
				_vars.pop();
				_vars.push(new Node(NodeType::VAR, node->GetValue(), node->Operand1));
			}
			else if (_tokens->GetCurrentToken()->GetType() != TokenType::ASSIGN && 
				_tokens->GetCurrentToken()->GetType() != TokenType::ASSIGN_DECLARATION && 
				_tokens->GetCurrentToken()->GetType() != TokenType::LPAR)
			{
				Error("P13");
			}

			break;
		}

		_tokens->UseNextToken();
	}
}

void QueueVariableNode::InitializationVariables()
{
	while (true)
	{
		auto frontVar = _vars.front();
		_vars.pop();

		if (frontVar->Operand1 == nullptr)
		{
			frontVar->Operand1 = _type;
		}
		
		Node* valueVar;
		if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
		{
			valueVar = InitializationArray();
			frontVar->Operand1 = valueVar->Operand2;
		}
		else
		{
			valueVar = _parser->Expr();
		}

		frontVar = new Node(NodeType::SET, "", frontVar, valueVar);

		_vars.push(frontVar);

		if (_tokens->GetCurrentToken()->IsSeporator() == true || _tokens->GetCurrentToken()->GetType() == TokenType::RPAR)
		{
			break;
		}

		_tokens->UseNextToken();
	}
}

Node* QueueVariableNode::InitializationArray()
{
	Node* tempArray; 
	Node* headArray;
	Node* typeArray = GetType();
	_tokens->UseNextToken();
	_tokens->UseNextToken();
	if (_tokens->GetCurrentToken()->GetType() == TokenType::NEW_LINE)
	{
		_tokens->UseNextToken();
	}
	tempArray = _parser->Expr();
	headArray = tempArray;
	headArray->Operand2 = typeArray;
	while (_tokens->GetCurrentToken()->GetType() != TokenType::RBRA)
	{
		_tokens->UseNextToken();

		if (_tokens->GetCurrentToken()->GetType() == TokenType::NEW_LINE)
		{
			_tokens->UseNextToken();

			if (_tokens->GetCurrentToken()->GetType() == TokenType::RBRA)
			{
				break;
			}
		}

		tempArray->Operand1 = _parser->Expr();
		tempArray = tempArray->Operand1;
	}

	_tokens->UseNextToken();

	return headArray;
}

Node* QueueVariableNode::GetType()
{
	Node* type = nullptr;
	Node* expr = nullptr;

	if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
	{
		_tokens->UseNextToken();
		expr = _parser->Expr();
		_tokens->UseNextToken();
	}
	if (_tokens->GetCurrentToken()->IsVar() == false)
	{
		Error("P14");
	}
	type = new Node(NodeType::VAR_TYPE, _tokens->GetCurrentToken()->GetValue(), expr);

	return type;
}

Node* QueueVariableNode::Pop()
{
	if (_vars.empty() == true)
	{
		// error
	}
	
	auto var = _vars.front();
	_vars.pop();

	if (_vars.empty() == true)
	{
		_type = nullptr;
	}

	return var;
}

bool QueueVariableNode::IsLPAR()
{
	return _isLPAR;
}

bool QueueVariableNode::IsConst()
{
	return _isConst;
}

void QueueVariableNode::SetLPAR(bool value)
{
	_isLPAR = value;
}

bool QueueVariableNode::IsEmpty()
{
	return _vars.empty();
}
