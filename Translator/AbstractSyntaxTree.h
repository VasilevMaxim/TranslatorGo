#pragma once
#include "Parser.h"

class AbstractSyntaxTree
{
private:
	
	Node* _tree;
	void ShowPartTree(Node* sub, size_t level);

public:

	AbstractSyntaxTree(Node* head);

	void ShowTree();
	void SetTree(Node* head);
};

