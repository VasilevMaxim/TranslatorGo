#include "VariableInit.h"
#include "BaseTokenTypes.h"

QueueVariableNode::QueueVariableNode()
{
	_tokens = ListTokens::GetInstance();
}

void QueueVariableNode::PlacedUnderControl(Parser* parser)
{
	_parser = parser;

	if (_tokens->GetCurrentToken()->GetType() == TokenType::LPAR)
	{
		_isLPAR = true;
		_tokens->UseNextToken();
		_tokens->UseNextToken();

		return;
	}
	else if (_tokens->GetCurrentToken()->GetType() != TokenType::LITERAL)
	{
		Error("name || var");
	}
	PushingVariables();
	
	if (_tokens->GetCurrentToken()->GetType() == TokenType::ASSIGN)
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
			frontVar->Operand1 = _type;
			_vars.push(frontVar);
		} 
		//_tokens->UseNextToken();
	}
}


void QueueVariableNode::PushingVariables()
{
	while (true)
	{
		_vars.push(new Node(NodeType::NEW_VAR, _tokens->GetCurrentToken()->GetValue()));
		_tokens->UseNextToken();

		if (_tokens->GetCurrentToken()->GetType() != TokenType::COMMA)
		{
			if (BaseTokenTypes::IsTypeVar(_tokens->GetCurrentToken()->GetType()) == true)
			{
				_type = GetType();
				_tokens->UseNextToken();
			}
			else if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
			{
				_type = GetType();
				_tokens->UseNextToken();
			}
			else if (_tokens->GetCurrentToken()->GetType() != TokenType::ASSIGN)
			{
				Error("Not Assign");
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

		frontVar->Operand1 = _type;
		
		Node* valueVar;
		if (_tokens->GetCurrentToken()->GetType() == TokenType::L_SBRA)
		{
			valueVar = InitializationArray();
		}
		else
		{
			valueVar = _parser->Expr();
		}

		frontVar = new Node(NodeType::SET, "", frontVar, valueVar);

		_vars.push(frontVar);

		if (_tokens->GetCurrentToken()->IsSeporator() == true)
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
	GetType();
	_tokens->UseNextToken();
	_tokens->UseNextToken();
	tempArray = _parser->Expr();
	headArray = tempArray;
	while (_tokens->GetCurrentToken()->GetType() != TokenType::RBRA)
	{
		_tokens->UseNextToken();

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
		Error("Not type");
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

void QueueVariableNode::SetLPAR(bool value)
{
	_isLPAR = value;
}

bool QueueVariableNode::IsEmpty()
{
	return _vars.empty();
}
