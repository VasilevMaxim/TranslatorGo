#include <iostream>
#include <fstream>

#include "TokenBreaking.h"
#include "Parser.h"
#include "AbstractSyntaxTree.h"
#include "Preprocessing.h"
#include "RecursiveTraversal.h"

using std::ifstream;
using std::getline;

void OnCompilation(string pathFile);
string GetAllTextInFile(string pathFile);

int main()
{
	setlocale(LC_ALL, "Rus");

	OnCompilation("progGo.go");

	return 0;
}

void OnCompilation(string pathFile)
{
	string textInFile = GetAllTextInFile(pathFile);
	Preprocessing preprocessing(&textInFile);

	TokenBreaking tokenBreaking(preprocessing.GetText());
	tokenBreaking.ShowTokens();

	Parser parser(tokenBreaking.GetTokens());
	AbstractSyntaxTree tree(parser.GetNodeHead());
	tree.ShowTree();

	RecursiveTraversal recursiveTraversal;
	recursiveTraversal.Traversal(parser.GetNodeHead());
}

string GetAllTextInFile(string pathFile)
{
	string textInFile;
	string tempLineText;
	ifstream in(pathFile);
	while (getline(in, tempLineText))
	{
		textInFile += tempLineText + '\n';
	}
	in.close();

	return textInFile;
}