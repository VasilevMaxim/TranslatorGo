#pragma once
#include "NodeType.h"
#include <string>

using std::string;

class Node
{
private:
	string _value;
	NodeType _type;


public:
	Node* Operand1;
	Node* Operand2;
	Node* Operand3;
	Node* Operand4;

	Node(NodeType type, string value = "", Node* operand1_ = nullptr, Node* operand2_ = nullptr,
		Node* operand3_ = nullptr, Node* operand4_ = nullptr);

	string GetValue();
	NodeType GetType();
};

