#pragma once
#include "NodeType.h"
#include <string>

class Node
{
private:
	std::string _value;
	NodeType _type;


public:
	Node* Operand1;
	Node* Operand2;
	Node* Operand3;
	Node* Operand4;

	Node(NodeType type, std::string value = "", Node* operand1_ = nullptr, Node* operand2_ = nullptr,
		Node* operand3_ = nullptr, Node* operand4_ = nullptr);

	std::string GetValue();
	NodeType GetType();
};

