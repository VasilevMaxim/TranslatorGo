#include "Node.h"

Node::Node(NodeType type, string value, Node* operand1, Node* operand2, Node* operand3, Node* operand4)
{
	_type = type;
	_value = value;
	Operand1 = operand1;
	Operand2 = operand2;
	Operand3 = operand3;
	Operand4 = operand4;
}

string Node::GetValue()
{
	return _value;
}

NodeType Node::GetType()
{
	return _type;
}

bool Node::IsValueNull()
{
	return _value == "null";
}

bool Node::IsComparisonOperator() const
{
	return Node::IsComparisonOperator(this->_type);
}


bool Node::IsComparisonOperator(NodeType type)
{
	return type == NodeType::LESS ||
		type == NodeType::MORE ||
		type == NodeType::LESS_EQUAL ||
		type == NodeType::MORE_EQUAL ||
		type == NodeType::EQUAL ||
		type == NodeType::NOT_EQUAL ||
		type == NodeType::AND ||
		type == NodeType::OR;
}
