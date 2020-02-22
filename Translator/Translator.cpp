#include <iostream>
#include <fstream>

#include "TokenBreaking.h"
#include "Parser.h"
#include "AbstractSyntaxTree.h"

using std::ifstream;
using std::getline;

void OnCompilation(string pathFile);
string GetAllTextInFile(string pathFile);

int main()
{
	OnCompilation("progGo.go");

	return 0;
}

void OnCompilation(string pathFile)
{
	string textInFile = GetAllTextInFile(pathFile);

	TokenBreaking tb(textInFile);
	tb.ShowTokens();

	Parser parser(tb.GetTokens());
	AbstractSyntaxTree tree(parser.GetNodeHead());
	tree.ShowTree();
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