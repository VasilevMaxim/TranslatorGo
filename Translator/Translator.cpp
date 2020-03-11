#include <iostream>
#include <fstream>
#include <vector>
#include "TokenBreaking.h"
#include "Parser.h"
#include "AbstractSyntaxTree.h"
#include "Preprocessing.h"
#include "RecursiveTraversal.h"
#include "Errors/ErrorSettings.h"
#include <Windows.h>

using std::ifstream;
using std::getline;
using std::vector;

void OnCompilation(string pathFile);
string GetAllTextInFile(string pathFile);

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	ErrorSettings::SetLanguage(Language::Russian);
	vector<Table*> tables;
	tables.push_back(new Table("ErrorsParser.csv"));
	ErrorSettings::InitTables(tables);

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

	// RecursiveTraversal recursiveTraversal;
	// recursiveTraversal.Traversal(parser.GetNodeHead());
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